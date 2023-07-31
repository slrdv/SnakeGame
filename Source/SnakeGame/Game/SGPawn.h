// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Core/Types.h"
#include "SGPawn.generated.h"

class UCameraComponent;

UCLASS()
class SNAKEGAME_API ASGPawn : public APawn
{
    GENERATED_BODY()

public:
    ASGPawn();

    /**
     * Set parameters for fitting camera position to grid, subscribe to viewport resize event
     * @param GridSize core grid dimensions
     * @param CellSizeWorld cell size in Unreal Engine units
     * @param GridTransform world grid transform
     */
    void FitToGrid(const CoreGame::Size& GridSize, uint32 CellSizeWorld, const FTransform& GridTransform);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly)
    uint32 Margins{10};

    UPROPERTY(EditDefaultsOnly)
    FRotator CameraRotationOffset;

private:
    CoreGame::Size GridSize;
    uint32 CellSizeWorld;
    FTransform GridTransform;

    FDelegateHandle ViewportResizedHandle;

    void UpdatePosition(FViewport* Viewport, uint32 v);
};
