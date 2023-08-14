// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace CoreGame
{
    class Grid
    {
    public:
        static Position getCenter(const Size& size) { return Position{size.width / 2 + 1, size.height / 2 + 1}; }

        Grid(const Size& size);

        /**
         * Return grid size include walls (width + 2, height + 2)
         * @return CoreGame::Size grid size
         */
        Size getSize() const { return s_size; }

        CellType getCell(const Position& position) const { return m_cells[posToIndex(position)]; }

        void updateSnake(const PositionListNode* head);

        void printDebug() const;

    private:
        const Size s_size;
        TArray<CellType> m_cells;

        void initGrid();

        void clear(CellType cellType);

        FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const { return y * s_size.width + x; }
        FORCEINLINE uint32 posToIndex(const Position& position) const { return posToIndex(position.x, position.y); }
    };

}  // namespace CoreGame
