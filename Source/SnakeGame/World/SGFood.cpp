// SnakeGame. Copyright slrdv. All right Reserved.

#include "World/SGFood.h"

#include "Utils/SGUtils.h"

ASGFood::ASGFood()
{
    PrimaryActorTick.bCanEverTick = true;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);
    FoodMesh = CreateDefaultSubobject<UStaticMeshComponent>("FoodMesh");
    check(FoodMesh);
    FoodMesh->SetupAttachment(Origin);
}

void ASGFood::SetModel(const TSharedPtr<CoreGame::Food>& SnakeModel, uint32 InCellSizeWorld, const CoreGame::Size& InGridSize)
{
    FoodPtr = SnakeModel;
    CellSizeWorld = InCellSizeWorld;
    GridSize = InGridSize;

    FoodMesh->SetRelativeScale3D(SGUtils::GetWorldScale(FoodMesh, FVector(InCellSizeWorld)));
}

void ASGFood::SetColor(const FLinearColor& Color)
{
    auto* Material = FoodMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (!Material) return;
    Material->SetVectorParameterValue("Color", Color);
}

void ASGFood::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!FoodPtr.IsValid()) return;

    SetActorLocation(SGUtils::GridToWorld(FoodPtr.Pin()->getPosition(), CellSizeWorld, GridSize, 0.5));
}