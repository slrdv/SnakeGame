// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"
#include "GameFramework/Actor.h"
#include "World/SGWorldTypes.h"
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

    /**
     * Set Grid actor model
     * @param Grid grid model object
     * @param CellSize world size of the cell in UE units
     */
    void SetModel(const TSharedPtr<CoreGame::Grid>& Grid, uint32 CellSize);

    /**
     * Returns Grid actor width
     * @return uint32 Grid actor width
     */
    FORCEINLINE uint32 GetWidthWorld() const { return CoreGridSize.width * CellSizeWorld; }

    /**
     * Returns Grid actor height
     * @return uint32 Grid actor height
     */
    FORCEINLINE uint32 GetHeightWorld() const { return CoreGridSize.height * CellSizeWorld; }

    /**
     * Updates line, wall and background colors
     * @param Colors colors data
     */
    void UpdateColors(const FSGColors& Colors);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* GridMesh;

    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UMaterialInstanceDynamic* GridMaterial;

    // Cell size in UE units (сm)
    uint32 CellSizeWorld{0};
    CoreGame::Size CoreGridSize;

    void DrawGrid() const;
};