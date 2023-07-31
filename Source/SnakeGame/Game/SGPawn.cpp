// SnakeGame. Copyright slrdv. All right Reserved.

#include "Game/SGPawn.h"
#include "Core/CoreUtils.h"
#include "Camera/CameraComponent.h"

ASGPawn::ASGPawn()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);

    // USceneComponent - base component with transform matrix
    // Set USceneComponent as ASGPawn root component, actor transform matrix will match the transform matrix of root component
    SetRootComponent(Origin);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
    check(CameraComponent);

    // Attach CameraComponent to root component (camera transform matrix will be multiplied by the root transform matrix)
    CameraComponent->SetupAttachment(GetRootComponent());
}

void ASGPawn::FitToGrid(const CoreGame::Size& InGridSize, uint32 InCellSizeWorld, const FTransform& InGridTransform)
{
    GridSize = InGridSize;
    CellSizeWorld = InCellSizeWorld;
    GridTransform = InGridTransform;

    check(GEngine);
    check(GEngine->GameViewport);
    check(GEngine->GameViewport->Viewport);

    auto* Viewport = GEngine->GameViewport->Viewport;
    Viewport->ViewportResizedEvent.Remove(ViewportResizedHandle);
    ViewportResizedHandle = Viewport->ViewportResizedEvent.AddUObject(this, &ASGPawn::UpdatePosition);

#if WITH_EDITOR
    UpdatePosition(Viewport, 0);
#endif
}

void ASGPawn::UpdatePosition(FViewport* Viewport, uint32 v)
{
    if (!Viewport || GridSize.height == 0 || Viewport->GetSizeXY().Y == 0) return;

    const uint32 GridWorldWidth = GridSize.width * CellSizeWorld;
    const uint32 GridWorldHeight = GridSize.height * CellSizeWorld;

    FVector Offset = FVector(GridWorldHeight, GridWorldWidth, 0.0) * 0.5;
    const FIntPoint ViewportSize = Viewport->GetSizeXY();
    const double HFOVRad = FMath::DegreesToRadians(CameraComponent->FieldOfView);
    const double ViewportAspect = static_cast<float>(ViewportSize.X) / ViewportSize.Y;
    const double GridAspect = static_cast<float>(GridWorldWidth) / GridWorldHeight;

    // Calculate camera z offset
    if (ViewportAspect <= GridAspect)
    {
        Offset.Z = CoreUtils::calcIsoscelesH(GridWorldWidth + Margins * 2, HFOVRad);
    }
    else
    {
        const double VFOVRad = CoreUtils::calcVFov(HFOVRad, ViewportSize.X, ViewportSize.Y);
        Offset.Z = CoreUtils::calcIsoscelesH(GridWorldHeight + Margins * 2, VFOVRad);
    }

    FTransform PawnOrigin = FTransform::Identity;
    PawnOrigin.SetLocation(Offset);

    FRotator Rotator = PawnOrigin.GetRotation().Rotator();
    Rotator.Pitch += -90.0;
    PawnOrigin.SetRotation((Rotator + CameraRotationOffset).Quaternion());

    // Set scale, position, rotation relative to grid transform matrix
    SetActorTransform(PawnOrigin * GridTransform);
}
