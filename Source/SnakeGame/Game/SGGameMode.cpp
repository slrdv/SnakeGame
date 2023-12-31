// SnakeGame. Copyright slrdv. All right Reserved.

#include "SGGameMode.h"

#include "EnhancedInputComponent.h"
#include "SGPawn.h"
#include "Core/Game.h"
#include "World/SGGrid.h"
#include "World/SGSnake.h"
#include "World/SGFood.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "World/SGWorldTypes.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY_STATIC(SGLogGameMode, All, All);

ASGGameMode::ASGGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASGGameMode::StartPlay()
{
    Super::StartPlay();

    check(GetWorld());

    Game = MakeUnique<CoreGame::Game>(GetGameSettings());
    if (!Game)
    {
        UE_LOG(SGLogGameMode, Fatal, TEXT("Game model is null! Abort."))
    }
    SubscribeGameEvents();

    const FTransform GridOrigin = FTransform::Identity;

    // Unlike UWorld::SpawnActor() SpawnActorDeferred allows to do something with object before initialization complete
    GridView = GetWorld()->SpawnActorDeferred<ASGGrid>(GridViewClass, GridOrigin);
    check(GridView);

    check(Game->getGrid());
    GridView->SetModel(Game->getGrid(), CellSizeWorld);

    // Finishing spawn, after that actors BeginPlay will be called
    GridView->FinishSpawning(GridOrigin);

    SnakeView = GetWorld()->SpawnActorDeferred<ASGSnake>(SnakeViewClass, GridOrigin);
    check(SnakeView);
    SnakeView->SetModel(Game->getSnake(), CellSizeWorld, Game->getGrid()->getSize());
    SnakeView->FinishSpawning(GridOrigin);

    SnakeView->OnExplosionFinishedDelegate.BindUObject(this, &ThisClass::OnExplosionFinished);

    FoodView = GetWorld()->SpawnActorDeferred<ASGFood>(FoodViewClass, GridOrigin);
    check(FoodView);
    FoodView->SetModel(Game->getFood(), CellSizeWorld, Game->getGrid()->getSize());
    FoodView->FinishSpawning(GridOrigin);

    const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    check(PlayerController);
    ASGPawn* Pawn = Cast<ASGPawn>(PlayerController->GetPawn());
    check(Pawn);
    Pawn->FitToGrid(Game->getGrid()->getSize(), CellSizeWorld, GridOrigin);

    UpdateColors(0);
    SetupInput();
}

void ASGGameMode::UpdateColors(uint32 TableRowIndex)
{
    if (!ColorsDataTable || ColorsDataTable->GetRowNames().Num() < 1) return;

    ColorsDataTableRowIndex = TableRowIndex;
    const FName RowName = ColorsDataTable->GetRowNames()[TableRowIndex];
    const FSGColors* Colors = ColorsDataTable->FindRow<FSGColors>(RowName, {});
    if (!Colors) return;

    GridView->UpdateColors(*Colors);
    SnakeView->SetColor(*Colors);
    FoodView->SetColor(Colors->FoodColor);

    auto* Fog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
    if (!Fog || !Fog->GetComponent()) return;
    Fog->GetComponent()->SetFogInscatteringColor(Colors->SceneBackgroundColor);
}

void ASGGameMode::Tick(float DeltaSeconds)
{
    Game->update(DeltaSeconds, Input);
}

void ASGGameMode::NextColor()
{
    if (!ColorsDataTable || ColorsDataTable->GetRowNames().Num() < 1) return;

    const uint32 NextIndex = (ColorsDataTableRowIndex + 1) % ColorsDataTable->GetRowNames().Num();
    UpdateColors(NextIndex);
}

CoreGame::Settings ASGGameMode::GetGameSettings() const
{
    CoreGame::Settings Settings;
    Settings.gridSize = CoreGame::Size{GridSize.X, GridSize.Y};
    Settings.snakeLength = SnakeDefaultLength;
    Settings.snakePosition = CoreGame::Grid::getCenter(Settings.gridSize);
    Settings.tickInterval = GameTickInterval;

    return Settings;
}

void ASGGameMode::ResetGame()
{
    if (!bCanReset) return;

    Game.Reset(new CoreGame::Game(GetGameSettings()));
    check(Game);

    SubscribeGameEvents();

    Input = CoreGame::Input::Default;
    GridView->SetModel(Game->getGrid(), CellSizeWorld);
    SnakeView->SetModel(Game->getSnake(), CellSizeWorld, Game->getGrid()->getSize());
    FoodView->SetModel(Game->getFood(), CellSizeWorld, Game->getGrid()->getSize());

    UpdateColors(ColorsDataTableRowIndex);

    bCanReset = false;
}

void ASGGameMode::SetupInput()
{
    check(GetWorld());

    const auto* PlayerController = GetWorld()->GetFirstPlayerController();
    check(PlayerController);

    const auto* Player = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
    check(Player);

    if (auto* InputSubsystem = Player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
    {
        if (!InputMappingContext) return;
        InputSubsystem->AddMappingContext(InputMappingContext, 0);

        auto* PlayerInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
        check(PlayerInputComponent);

        PlayerInputComponent->BindAction(InputActionRight, ETriggerEvent::Started, this, &ThisClass::OnInputRight);
        PlayerInputComponent->BindAction(InputActionUp, ETriggerEvent::Started, this, &ThisClass::OnInputUp);
        PlayerInputComponent->BindAction(InputActionReset, ETriggerEvent::Started, this, &ThisClass::OnInputReset);
    }
}

void ASGGameMode::OnInputRight(const FInputActionValue& InputValue)
{
    const float Value = InputValue.Get<float>();
    Input = {static_cast<int8>(Value), 0};
}

void ASGGameMode::OnInputUp(const FInputActionValue& InputValue)
{
    const float Value = InputValue.Get<float>();
    Input = {0, static_cast<int8>(Value)};
}

void ASGGameMode::OnInputReset(const FInputActionValue& InputValue)
{
    if (InputValue.Get<bool>())
    {
        ResetGame();
    }
}

void ASGGameMode::OnExplosionFinished()
{
    bCanReset = true;
}

void ASGGameMode::SubscribeGameEvents()
{
    Game->subscribeGameEvent(
        [&](CoreGame::GameEvent EventType)
        {
            switch (EventType)
            {
                case CoreGame::GameEvent::GameOver:
                    UE_LOG(SGLogGameMode, Display, TEXT("Game Over! Score: %d"), Game->getScore());
                    SnakeView->Explode();
                    break;
                case CoreGame::GameEvent::GameCompleted:
                    UE_LOG(SGLogGameMode, Display, TEXT("Game Completed! Score: %d"), Game->getScore());
                    bCanReset = true;
                    break;
                case CoreGame::GameEvent::FoodTaken:
                    UE_LOG(SGLogGameMode, Display, TEXT("Food Taken! Score: %d"), Game->getScore());
                    FoodView->Explode();
                    break;
                default: break;
            }
        });
}
