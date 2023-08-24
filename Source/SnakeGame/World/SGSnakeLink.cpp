// SnakeGame. Copyright slrdv. All right Reserved.

#include "World/SGSnakeLink.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Utils/SGUtils.h"

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
    MeshColor = Color;

    auto* Material = LinkMesh->CreateAndSetMaterialInstanceDynamic(0);
    if (!Material) return;
    Material->SetVectorParameterValue("Color", Color);
}

void ASGSnakeLink::SetScale(uint32 CellSize)
{
    const FBox BoundingBox = LinkMesh->GetStaticMesh()->GetBoundingBox();
    const FVector BoxSize = BoundingBox.GetSize();
    check(BoxSize.X != 0 && BoxSize.Y != 0);
    LinkMesh->SetRelativeScale3D(SGUtils::GetWorldScale(LinkMesh, FVector(CellSize)));
}

void ASGSnakeLink::Explode()
{
    if (!GetWorld()) return;

    if (auto* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation()))
    {
        NiagaraComponent->SetVariableLinearColor("ParticleColor", MeshColor);
    }
    SetActorHiddenInGame(true);
}
