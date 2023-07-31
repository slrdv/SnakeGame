// SnakeGame. Copyright slrdv. All right Reserved.

#include "SGGameMode.h"
#include "SGPawn.h"
#include "Core/Game.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "World/SGWorldTypes.h"

DEFINE_LOG_CATEGORY_STATIC(SGLogGameMode, All, All);

void ASGGameMode::StartPlay()
{
    Super::StartPlay();

    check(GetWorld());

    const CoreGame::Settings Settings{GridSize.X, GridSize.Y};
    Game = MakeUnique<CoreGame::Game>(Settings);
    if (!Game.IsValid())
    {
        UE_LOG(SGLogGameMode, Fatal, TEXT("Game model is null! Abort."))
    }

    const FTransform GridOrigin = FTransform::Identity;

    // Unlike UWorld::SpawnActor() SpawnActorDeferred allows to do something with object before initialization complete
    GridView = GetWorld()->SpawnActorDeferred<ASGGrid>(GridViewClass, GridOrigin);
    check(GridView);

    check(Game->getGrid().IsValid());
    GridView->SetModel(Game->getGrid(), CellSizeWorld);

    // Finishing spawn, after that actors BeginPlay will be called
    GridView->FinishSpawning(GridOrigin);

    const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    check(PlayerController);
    ASGPawn* Pawn = Cast<ASGPawn>(PlayerController->GetPawn());
    check(Pawn);
    Pawn->FitToGrid(Game->getGrid()->getSize(), CellSizeWorld, GridOrigin);

    UpdateColors(0);
}

void ASGGameMode::UpdateColors(uint32 TableRowIndex)
{
    if (!ColorsDataTable || ColorsDataTable->GetRowNames().Num() < 1) return;

    ColorsDataTableRowIndex = TableRowIndex;

    const FName RowName = ColorsDataTable->GetRowNames()[TableRowIndex];

    const FSGColors* Colors = ColorsDataTable->FindRow<FSGColors>(RowName, {});
    if (!Colors) return;
    GridView->UpdateColors(*Colors);

    auto* Fog = Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(GetWorld(), AExponentialHeightFog::StaticClass()));
    if (!Fog || !Fog->GetComponent()) return;

    Fog->GetComponent()->SetFogInscatteringColor(Colors->SceneBackgroundColor);
}

void ASGGameMode::NextColor()
{
    if (!ColorsDataTable || ColorsDataTable->GetRowNames().Num() < 1) return;

    const uint32 NextIndex = (ColorsDataTableRowIndex + 1) % ColorsDataTable->GetRowNames().Num();
    UpdateColors(NextIndex);
}