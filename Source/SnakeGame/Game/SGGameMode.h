// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "CoreMinimal.h"
#include "Core/Game.h"
#include "World/SGGrid.h"
#include "SGGameMode.generated.h"

UCLASS()
class SNAKEGAME_API ASGGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    // Called after BeginPlay of all actors in scene
    virtual void StartPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 10, ClampMax = 50))
    FUintPoint GridSize{10, 10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 10, ClampMax = 50))
    uint32 CellSizeWorld{10};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASGGrid> GridViewClass;

private:
    TUniquePtr<CoreGame::Game> Game;

    // UPROPERTY(), because it may be accidentally deleted by GC
    UPROPERTY()
    ASGGrid* GridView;
};
