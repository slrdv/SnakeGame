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
    FLinearColor GridBackgroundColor{ForceInit};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor GridLineColor{ForceInit};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor GridWallColor{ForceInit};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor SceneBackgroundColor{ForceInit};
};