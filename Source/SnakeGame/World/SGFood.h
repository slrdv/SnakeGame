// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGWorldTypes.h"
#include "GameFramework/Actor.h"
#include "Core/Food.h"
#include "SGFood.generated.h"

UCLASS()
class SNAKEGAME_API ASGFood : public AActor
{
    GENERATED_BODY()

public:
    ASGFood();

    void SetModel(const TSharedPtr<CoreGame::Food>& FoodModel, uint32 InCellSizeWorld, const CoreGame::Size& InGridSize);

    void SetColor(const FLinearColor& Color);

    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* FoodMesh;

    TWeakPtr<CoreGame::Food> FoodPtr;
    uint32 CellSizeWorld;
    CoreGame::Size GridSize;
};
