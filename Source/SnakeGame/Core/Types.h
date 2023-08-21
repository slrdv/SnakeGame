// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"

namespace CoreGame
{
    struct Size
    {
        uint32 width;
        uint32 height;
    };

    struct Position
    {
        Position(uint32 x = 0, uint32 y = 0) : x(x), y(y) {}

        uint32 x;
        uint32 y;

        FORCEINLINE bool operator==(const Position& rhs) const { return x == rhs.x && y == rhs.y; }
        FORCEINLINE Position operator+(const Position& rhs) const { return Position(x + rhs.x, y + rhs.y); }
        FORCEINLINE Position operator-(const Position& rhs) const { return Position(x - rhs.x, y - rhs.y); }
    };

    struct Settings
    {
        Size gridSize{20, 10};
        uint32 snakeLength{4};
        Position snakePosition{0, 0};
        float tickInterval = 1.0f;
    };

    enum class CellType
    {
        Empty = 0,
        Wall,
        Snake,
        Food
    };

    struct Input
    {
        int8 x;
        int8 y;

        FORCEINLINE bool isOpposite(const Input& rhs) const { return (x == -rhs.x && x != 0) || (y == -rhs.y && y != 0); }

        static const Input Default;
    };

    using PositionList = TDoubleLinkedList<Position>;
    using PositionListNode = PositionList::TDoubleLinkedListNode;

}  // namespace CoreGame
