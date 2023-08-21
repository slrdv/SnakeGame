// SnakeGame. Copyright egorpk. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"

DEFINE_SPEC(FCoreGrid, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FCoreGrid::Define()
{
    Describe("Core.Grid",
        [this]()
        {
            It("GridSizeShouldIncludeWalls",
                [this]()
                {
                    constexpr CoreGame::Size Size{5, 5};
                    const CoreGame::Grid Grid{Size};
                    TestTrueExpr(Grid.getSize().width == Size.width + 2 && Grid.getSize().height == Size.height + 2);
                });
            It("GridCenterShouldBeCalculatedCorrectly",
                [this]()
                {
                    TestTrueExpr(CoreGame::Grid::getCenter({9, 7}) == CoreGame::Position(5, 4));
                    TestTrueExpr(CoreGame::Grid::getCenter({10, 8}) == CoreGame::Position(6, 5));
                });
            It("FoodPositionShouldBeUpdatedCorrectly",
                [this]()
                {
                    CoreGame::Grid Grid{CoreGame::Size{10, 10}};
                    TestTrueExpr(Grid.getCell({5, 5}) == CoreGame::CellType::Empty);
                    Grid.updateFood({5, 5});
                    TestTrueExpr(Grid.getCell({5, 5}) == CoreGame::CellType::Food);
                    Grid.updateFood({5, 6});
                    TestTrueExpr(Grid.getCell({5, 5}) == CoreGame::CellType::Empty);
                    TestTrueExpr(Grid.getCell({5, 6}) == CoreGame::CellType::Food);
                });
            It("SnakePositionShouldBeSetupCorrectly",
                [this]()
                {
                    CoreGame::Grid Grid{{20, 20}};

                    constexpr uint32 SnakeLength{4};
                    const CoreGame::Position SnakePosition = CoreGame::Grid::getCenter(Grid.getSize());
                    const CoreGame::Snake Snake{SnakeLength, SnakePosition};

                    for (uint32 i = 0; i < SnakeLength; ++i)
                    {
                        TestTrueExpr(Grid.getCell(SnakePosition - CoreGame::Position{i, 0}) == CoreGame::CellType::Empty);
                    }

                    Grid.updateSnake(Snake.head());

                    for (uint32 i = 0; i < SnakeLength; ++i)
                    {
                        TestTrueExpr(Grid.getCell(SnakePosition - CoreGame::Position{i, 0}) == CoreGame::CellType::Snake);
                    }
                });
            It("RandomEmptyPositionShouldExists",
                [this]()
                {
                    CoreGame::Grid Grid{{4, 1}};

                    CoreGame::PositionList Positions;
                    Positions.AddTail({1, 1});
                    Positions.AddTail({2, 1});
                    Positions.AddTail({3, 1});

                    Grid.updateSnake(Positions.GetHead());
                    CoreGame::Position Position;
                    Grid.getRandomEmptyPosition(Position);
                    TestTrueExpr(Position == CoreGame::Position(4, 1));
                });
            It("RandomCellCannotBeFoundIfNoEmptyCells",
                [this]()
                {
                    CoreGame::Grid Grid{{4, 1}};

                    CoreGame::PositionList Positions;
                    Positions.AddTail({1, 1});
                    Positions.AddTail({2, 1});
                    Positions.AddTail({3, 1});
                    Positions.AddTail({4, 1});

                    Grid.updateSnake(Positions.GetHead());
                    CoreGame::Position Position;
                    TestTrueExpr(!Grid.getRandomEmptyPosition(Position));
                });
        });
}

#endif