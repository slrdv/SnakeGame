// SnakeGame. Copyright slrdv. All right Reserved.

#include "Types.h"

using namespace CoreGame;

const Input Input::Default = Input{1, 0};

bool PositionRandomizer::getPosition(Position& position, const TArray<CellType>& cells, const Size& size) const
{
    const uint32 randomIndex = FMath::RandRange(0, cells.Num() - 1);

    uint32 i = randomIndex;
    do
    {
        i = (i + 1) % cells.Num();
        if (cells[i] == CellType::Empty)
        {
            position = {i % size.width, i / size.width};
            return true;
        }
    } while (i != randomIndex);

    return false;
}
