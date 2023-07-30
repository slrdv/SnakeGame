// SnakeGame. Copyright slrdv. All right Reserved.

#include "SGGameMode.h"
#include "SGPawn.h"
#include "Core/Game.h"

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
}