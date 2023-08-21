// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "CoreMinimal.h"
#include "Core/Game.h"
#include "Engine/DataTable.h"
#include "InputActionValue.h"
#include "SGGameMode.generated.h"

class ASGSnake;
class ASGGrid;
class ASGFood;
class UInputAction;
class UInputMappingContext;

UCLASS()
class SNAKEGAME_API ASGGameMode : public AGameModeBase
{
    GENERATED_BODY()
public:
    ASGGameMode();

    // Called after BeginPlay of all actors in scene
    virtual void StartPlay() override;

    /**
     * Updates grid and scene background colors according to ColorsDataTable
     * @param TableRowIndex row index in ColorsDataTable
     */
    void UpdateColors(uint32 TableRowIndex);

    UDataTable* GetColorsDataTable() const { return ColorsDataTable; }

    virtual void Tick(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 10, ClampMax = 50), Category = "GameSettings")
    FUintPoint GridSize{20, 10};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 3, ClampMax = 10), Category = "GameSettings")
    uint32 SnakeDefaultLength{4};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 0.01f, ClampMax = 10f), Category = "GameSettings")
    float GameTickInterval{1.0f};

    UPROPERTY(EditDefaultsOnly, meta = (ClampMin = 10, ClampMax = 50), Category = "GameSettings")
    uint32 CellSizeWorld{10};

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TSubclassOf<ASGGrid> GridViewClass;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TSubclassOf<ASGSnake> SnakeViewClass;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TSubclassOf<ASGFood> FoodViewClass;

    UPROPERTY(EditDefaultsOnly, Category = "Design")
    TObjectPtr<UDataTable> ColorsDataTable;

    UPROPERTY(EditDefaultsOnly, Category = "GameInput")
    TObjectPtr<UInputAction> InputActionRight;

    UPROPERTY(EditDefaultsOnly, Category = "GameInput")
    TObjectPtr<UInputAction> InputActionUp;

    UPROPERTY(EditDefaultsOnly, Category = "GameInput")
    TObjectPtr<UInputAction> InputActionReset;

    UPROPERTY(EditDefaultsOnly, Category = "GameInput")
    TObjectPtr<UInputMappingContext> InputMappingContext;

private:
    TUniquePtr<CoreGame::Game> Game;

    uint32 ColorsDataTableRowIndex{0};

    CoreGame::Input Input = CoreGame::Input::Default;

    // UPROPERTY(), because it may be accidentally deleted by GC
    UPROPERTY()
    TObjectPtr<ASGGrid> GridView;

    UPROPERTY()
    TObjectPtr<ASGSnake> SnakeView;

    UPROPERTY()
    TObjectPtr<ASGFood> FoodView;

    UFUNCTION(Exec, Category = "Debug")
    void NextColor();

    CoreGame::Settings GetGameSettings() const;
    void ResetGame();
    void SetupInput();

    void OnInputRight(const FInputActionValue& InputValue);
    void OnInputUp(const FInputActionValue& InputValue);
    void OnInputReset(const FInputActionValue& InputValue);
};
