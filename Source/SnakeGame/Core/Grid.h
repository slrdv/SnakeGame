// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace CoreGame
{
    class Grid
    {
    public:
        Grid(const Size& size);

        /**
         * Return grid size include walls (width + 2, height + 2)
         * @return CoreGame::Size grid size
         */
        Size getSize() const { return s_size; }

    private:
        const Size s_size;
        TArray<CellType> m_cells;

        void initGrid();
        void printDebug() const;

        FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const { return y * s_size.width + x; }
    };

}  // namespace CoreGame
