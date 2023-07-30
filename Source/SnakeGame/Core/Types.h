#pragma once

namespace CoreGame
{
    struct Size
    {
        uint32 width;
        uint32 height;
    };

    struct Settings
    {
        Size gridSize;
    };

    enum class CellType
    {
        Empty = 0,
        Wall,
    };

}  // namespace CoreGame
