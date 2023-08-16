// SnakeGame. Copyright slrdv. All right Reserved.

#include "World/SGSnakeLink.h"

// Sets default values
ASGSnakeLink::ASGSnakeLink()
{
    PrimaryActorTick.bCanEverTick = false;

    Origin = CreateDefaultSubobject<USceneComponent>("Origin");
    check(Origin);
    SetRootComponent(Origin);
    LinkMesh = CreateDefaultSubobject<UStaticMeshComponent>("LinkMesh");
    check(LinkMesh);
    LinkMesh->SetupAttachment(Origin);
}

void ASGSnakeLink::SetColor(const FLinearColor& Color)
{
    auto* Material = LinkMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (!Material) return;
    Material->SetVectorParameterValue("Color", Color);
}

void ASGSnakeLink::SetScale(uint32 CellSize)
{
    const FBox BoundingBox = LinkMesh->GetStaticMesh()->GetBoundingBox();
    const FVector BoxSize = BoundingBox.GetSize();
    check(BoxSize.X != 0 && BoxSize.Y != 0);
    LinkMesh->SetRelativeScale3D(FVector(CellSize / BoxSize.X, CellSize / BoxSize.Y, CellSize / BoxSize.Z));
}
