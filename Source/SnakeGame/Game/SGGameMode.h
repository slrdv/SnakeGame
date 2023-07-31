// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "CoreMinimal.h"
#include "Core/Game.h"
#include "World/SGGrid.h"
#include "Engine/DataTable.h"
#include "SGGameMode.generated.h"

UCLASS()
class SNAKEGAME_API ASGGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    // Called after BeginPlay of all actors in scene
    virtual void StartPlay() override;

    /**
     * Updates grid and scene background colors according to ColorsDataTable
     * @param TableRowIndex row index in ColorsDataTable
     */
    void UpdateColors(uint32 TableRowIndex);

    UDataTable* GetColorsDataTable() const { return ColorsDataTable; }

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 10, ClampMax = 50))
    FUintPoint GridSize{10, 10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 10, ClampMax = 50))
    uint32 CellSizeWorld{10};

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ASGGrid> GridViewClass;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TObjectPtr<UDataTable> ColorsDataTable;

private:
    TUniquePtr<CoreGame::Game> Game;

    uint32 ColorsDataTableRowIndex{0};

    // UPROPERTY(), because it may be accidentally deleted by GC
    UPROPERTY()
    ASGGrid* GridView;

    UFUNCTION(Exec, Category = "Debug")
    void NextColor();
};
