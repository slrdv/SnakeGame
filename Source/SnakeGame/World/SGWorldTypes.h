// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SGWorldTypes.generated.h"

USTRUCT(BlueprintType)
struct FSGColors : public FTableRowBase
{
    GENERATED_BODY();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor GridBackgroundColor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor GridLineColor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor GridWallColor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor SceneBackgroundColor;
};