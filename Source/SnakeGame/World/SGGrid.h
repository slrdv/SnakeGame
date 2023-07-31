// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "GameFramework/Actor.h"
#include "SGGrid.generated.h"

// Forward declaration
namespace CoreGame
{
    class Grid;
}

UCLASS()
class SNAKEGAME_API ASGGrid : public AActor
{
    GENERATED_BODY()

public:
    ASGGrid();

    virtual void Tick(float DeltaTime) override;

    void SetModel(const TSharedPtr<CoreGame::Grid>& Grid, uint32 CellSize);

    FORCEINLINE uint32 GetWidthWorld() const { return CoreGridSize.width * CellSizeWorld; }

    FORCEINLINE uint32 GetHeightWorld() const { return CoreGridSize.height * CellSizeWorld; }

protected:
    virtual void BeginPlay() override;

private:
    // Cell size in UE units (сm)
    uint32 CellSizeWorld{0};
    CoreGame::Size CoreGridSize;

    void DrawGrid() const;
};