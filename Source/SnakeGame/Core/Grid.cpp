// SnakeGame. Copyright slrdv. All right Reserved.

#include "Grid.h"

// Define own log category
DEFINE_LOG_CATEGORY_STATIC(SGLogCoreGrid, All, All);

using namespace CoreGame;

Grid::Grid(const Size& size, const IPositionRandomizerPtr& randomizer)
    : s_size(Size{size.width + 2, size.height + 2}), m_positionRandomizer(randomizer)
{
    initGrid();
}

void Grid::updateSnake(const PositionListNode* head)
{
    clear(CellType::Snake);

    auto* current = head;
    while (current)
    {
        m_cells[posToIndex(current->GetValue())] = CellType::Snake;
        current = current->GetNextNode();
    }
}

void Grid::updateFood(const Position& foodPosition)
{
    clear(CellType::Food);
    m_cells[posToIndex(foodPosition)] = CellType::Food;
}

void Grid::initGrid()
{
    m_cells.Init(CellType::Empty, s_size.width * s_size.height);
    for (uint32 y = 0; y < s_size.height; ++y)
    {
        for (uint32 x = 0; x < s_size.width; ++x)
        {
            if (x == 0 || x == s_size.width - 1 || y == 0 || y == s_size.height - 1)
            {
                m_cells[posToIndex(x, y)] = CellType::Wall;
            }
        }
    }
}

void Grid::clear(CellType cellType)
{
    for (auto& cell : m_cells)
    {
        if (cell == cellType)
        {
            cell = CellType::Empty;
        }
    }
}

bool Grid::getRandomEmptyPosition(Position& outPosition) const
{
    return m_positionRandomizer->getPosition(outPosition, m_cells, s_size);
}

bool Grid::isEmpty(const Position& position) const
{
    const uint32 index = posToIndex(position);
    return index < static_cast<uint32>(m_cells.Num()) && m_cells[index] == CellType::Empty;
}

void Grid::printDebug() const
{
// Remove from shipping build
#if !UE_BUILD_SHIPPING
    FString line = FString::Printf(TEXT("Grid (x: %d, y: %d)\n"), s_size.width, s_size.height);
    for (uint32 y = 0; y < s_size.height; ++y)
    {
        TCHAR sym;
        for (uint32 x = 0; x < s_size.width; ++x)
        {
            switch (m_cells[posToIndex(x, y)])
            {
                case CellType::Empty: sym = '-'; break;
                case CellType::Wall: sym = '#'; break;
                case CellType::Snake: sym = '*'; break;
                case CellType::Food: sym = '@'; break;
                default: sym = '?';
            }
            line.AppendChar(sym).AppendChar(' ');
        }
        line.AppendChar('\n');
    }
    UE_LOG(SGLogCoreGrid, Display, TEXT("%s"), *line)
#endif
}
