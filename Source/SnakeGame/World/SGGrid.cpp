// SnakeGame. Copyright slrdv. All right Reserved.

#include "World/SGGrid.h"
#include "Core/Grid.h"
#include "DrawDebugHelpers.h"
#include "Components/LineBatchComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SGLogGrid, All, All);

ASGGrid::ASGGrid()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASGGrid::BeginPlay()
{
    Super::BeginPlay();
}

void ASGGrid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    DrawGrid();
}

void ASGGrid::SetModel(const TSharedPtr<CoreGame::Grid>& Grid, uint32 CellSize)
{
    CellSizeWorld = CellSize;
    if (!Grid.IsValid())
    {
        // Crash if Grid isn't valid (verbosity Fatal)
        UE_LOG(SGLogGrid, Fatal, TEXT("Grid model is null! Abort."))
    }

    CoreGridSize = Grid.Get()->getSize();
}

void ASGGrid::DrawGrid() const
{
    if (CellSizeWorld == 0)
    {
        return;
    }

    check(GetWorld());
    check(GetWorld()->LineBatcher);
    ULineBatchComponent* LineBatcher = GetWorld()->LineBatcher;
    for (uint32 x = 0; x < CoreGridSize.height + 1; ++x)
    {
        FVector StartOffset = GetActorLocation() + GetActorForwardVector() * x * CellSizeWorld;
        FVector EndOffset = StartOffset + GetActorRightVector() * GetWidthWorld();
        LineBatcher->DrawLine(StartOffset, EndOffset, FColor::Black, 0, 1.0f, -1.0f);
    }

    for (uint32 y = 0; y < CoreGridSize.width + 1; ++y)
    {
        FVector StartOffset = GetActorLocation() + GetActorRightVector() * y * CellSizeWorld;
        FVector EndOffset = StartOffset + GetActorForwardVector() * GetHeightWorld();
        LineBatcher->DrawLine(StartOffset, EndOffset, FColor::Black, 0, 1.0f, -1.0f);
    }
}
