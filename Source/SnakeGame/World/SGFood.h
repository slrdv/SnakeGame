// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Core/Food.h"
#include "SGFood.generated.h"

class UNiagaraSystem;

UCLASS()
class SNAKEGAME_API ASGFood : public AActor
{
    GENERATED_BODY()

public:
    ASGFood();

    /**
     * Set Food actor model
     * @param FoodModel food model object
     * @param InCellSizeWorld  world size of the cell in UE units
     * @param InGridSize grid size
     */
    void SetModel(const TSharedPtr<CoreGame::Food>& FoodModel, uint32 InCellSizeWorld, const CoreGame::Size& InGridSize);

    /**
     * Updates Food actor color
     * @param Color food color
     */
    void SetColor(const FLinearColor& Color);

    virtual void Tick(float DeltaTime) override;

    void Explode() const;

protected:
    UPROPERTY(VisibleAnywhere)
    USceneComponent* Origin;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* FoodMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> ExplosionEffect;

private:
    TWeakPtr<CoreGame::Food> FoodPtr;

    uint32 CellSizeWorld;
    CoreGame::Size GridSize;

    FLinearColor MeshColor;
};
