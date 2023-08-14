// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGSnakeLink.generated.h"

UCLASS()
class SNAKEGAME_API ASGSnakeLink : public AActor
{
    GENERATED_BODY()

public:
    ASGSnakeLink();

    void SetColor(const FLinearColor& Color);

    void SetScale(uint32 CellSize);

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* LinkMesh;
};
