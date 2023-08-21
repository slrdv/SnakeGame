// SnakeGame. Copyright slrdv. All right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Types.h"

namespace CoreGame
{
    class Grid
    {
    public:
        /**
         * Returns center position in grid (walls included)
         * @param size grid size without walls
         * @return Position center of grid
         */
        static Position getCenter(const Size& size) { return Position{size.width / 2 + 1, size.height / 2 + 1}; }

        Grid(const Size& size);

        /**
         * Returns grid size include walls (width + 2, height + 2)
         * @return CoreGame::Size grid size
         */
        Size getSize() const { return s_size; }

        /**
         * Returns cell type by position
         * @param position cell position
         * @return CoreGame::CellType cell type
         */
        CellType getCell(const Position& position) const { return m_cells[posToIndex(position)]; }

        /**
         * Updates snake cells
         * @param head pointer to the snake head node
         */
        void updateSnake(const PositionListNode* head);

        /**
         * Updates food cell
         * @param foodPosition new food position
         */
        void updateFood(const Position& foodPosition);

        /**
         * Prints grid debug information to console
         */
        void printDebug() const;

        /**
         * Returns empty position by ref
         * @param[out] outPosition on the grid
         * @return bool true if empty position exists
         */
        bool getRandomEmptyPosition(Position& outPosition) const;

        /**
         * Returns true if cell is empty
         * @param position cell position
         * @return bool true if cell is empty
         */
        bool isEmpty(const Position& position) const;

    private:
        const Size s_size;
        TArray<CellType> m_cells;

        void initGrid();

        void clear(CellType cellType);

        FORCEINLINE uint32 posToIndex(uint32 x, uint32 y) const { return y * s_size.width + x; }

        FORCEINLINE uint32 posToIndex(const Position& position) const { return posToIndex(position.x, position.y); }

        FORCEINLINE Position indexToPos(uint32 index) const { return {index % s_size.width, index / s_size.width}; }
    };

}  // namespace CoreGame
