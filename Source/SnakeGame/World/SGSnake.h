// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SGWorldTypes.h"
#include "Core/Game.h"
#include "GameFramework/Actor.h"
#include "SGSnake.generated.h"

class ASGSnakeLink;

UCLASS()
class SNAKEGAME_API ASGSnake : public AActor
{
    GENERATED_BODY()

public:
    ASGSnake();

    /**
     * Set Snake actor model
     * @param SnakeModel snake model object
     * @param InCellSizeWorld  world size of the cell in UE units
     * @param InGridSize grid size
     */
    void SetModel(const TSharedPtr<CoreGame::Snake>& SnakeModel, uint32 InCellSizeWorld, const CoreGame::Size& InGridSize);

    /**
     * Updates Snake actor colors
     * @param Colors colors data
     */
    void SetColor(const FSGColors& Colors);

    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ASGSnakeLink> SnakeHeadClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TSubclassOf<ASGSnakeLink> SnakeBodyClass;

private:
    UPROPERTY()
    TArray<ASGSnakeLink*> SnakeLinks;

    TWeakPtr<CoreGame::Snake> SnakePtr;
    uint32 CellSizeWorld;
    CoreGame::Size GridSize;

    FLinearColor BodyColor;

    void CreateLinks();

    ASGSnakeLink* SpawnLink(const CoreGame::Position& Position, TSubclassOf<ASGSnakeLink> LinkClass);
};
