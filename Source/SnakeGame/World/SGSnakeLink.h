// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGSnakeLink.generated.h"

class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASGSnakeLink : public AActor
{
    GENERATED_BODY()

public:
    ASGSnakeLink();

    void SetColor(const FLinearColor& Color);

    void SetScale(uint32 CellSize);

    void Explode();

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LinkMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> ExplosionEffect;

private:
    FLinearColor MeshColor;
};
