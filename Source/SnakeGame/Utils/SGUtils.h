// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Types.h"

class SGUtils
{
public:
    static FVector GetWorldScale(const UStaticMeshComponent* Mesh, const FVector& WorldSize)
    {
        check(Mesh);

        const FBox BoundingBox = Mesh->GetStaticMesh()->GetBoundingBox();
        const FVector BoxSize = BoundingBox.GetSize();
        check(BoxSize.X && BoxSize.Y && BoxSize.Z);

        return WorldSize / BoxSize;
    }

    static FVector GridToWorld(const CoreGame::Position& Position, uint32 WorldSize, const CoreGame::Size& GridSize, double Offset = 0.0)
    {
        return FVector((GridSize.height - 1 - Position.y) * WorldSize, Position.x * WorldSize, 0.0) + WorldSize * Offset;
    }
};
