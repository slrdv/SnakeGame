// SnakeGame. Copyright egorpk. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"

BEGIN_DEFINE_SPEC(FCoreSnake, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

uint32 SnakeSize;
CoreGame::Position StartPosition;
TUniquePtr<CoreGame::Snake> Snake;

END_DEFINE_SPEC(FCoreSnake)

void FCoreSnake::Define()
{
    Describe("Core.Snake",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    SnakeSize = 10;
                    StartPosition = CoreGame::Position{20, 20};
                    Snake = MakeUnique<CoreGame::Snake>(SnakeSize, StartPosition);
                });
            It("SnakeShouldBeInitedCorrectly",
                [this]()
                {
                    TestTrueExpr(Snake->links().Num() == SnakeSize);

                    auto* Node = Snake->head();
                    uint32 i = 0;
                    while (Node)
                    {
                        TestTrueExpr(Node->GetValue() == CoreGame::Position(StartPosition.x - i, StartPosition.y));
                        Node = Node->GetNextNode();
                        ++i;
                    }
                });
            It("SnakeShouldBeMovedRightCorrectly",
                [this]()
                {
                    constexpr CoreGame::Input Input{1, 0};
                    Snake->move(Input);

                    auto* Node = Snake->head();
                    uint32 i = 0;
                    while (Node)
                    {
                        TestTrueExpr(Node->GetValue() == CoreGame::Position(StartPosition.x - i + 1, StartPosition.y));
                        Node = Node->GetNextNode();
                        ++i;
                    }
                });
            It("SnakeCannotMoveOpposite",
                [this]()
                {
                    constexpr CoreGame::Input Input{-1, 0};
                    Snake->move(Input);

                    auto* Node = Snake->head();
                    uint32 i = 0;
                    while (Node)
                    {
                        TestTrueExpr(Node->GetValue() == CoreGame::Position(StartPosition.x - i + 1, StartPosition.y));
                        Node = Node->GetNextNode();
                        ++i;
                    }
                });
            It("SnakeShouldBeMovedUpCorrectly",
                [this]()
                {
                    constexpr CoreGame::Input Input{0, 1};
                    Snake->move(Input);

                    TestTrueExpr(Snake->head()->GetValue() == CoreGame::Position(StartPosition.x, StartPosition.y + 1));

                    auto* Node = Snake->head()->GetNextNode();
                    uint32 i = 1;
                    while (Node)
                    {
                        TestTrueExpr(Node->GetValue() == CoreGame::Position(StartPosition.x - i + 1, StartPosition.y));
                        Node = Node->GetNextNode();
                        ++i;
                    }
                });
            It("SnakeShouldBeMovedDownCorrectly",
                [this]()
                {
                    constexpr CoreGame::Input Input{0, -1};
                    Snake->move(Input);

                    TestTrueExpr(Snake->head()->GetValue() == CoreGame::Position(StartPosition.x, StartPosition.y - 1));

                    auto* Node = Snake->head()->GetNextNode();
                    uint32 i = 1;
                    while (Node)
                    {
                        TestTrueExpr(Node->GetValue() == CoreGame::Position(StartPosition.x - i + 1, StartPosition.y));
                        Node = Node->GetNextNode();
                        ++i;
                    }
                });
            It("SnakeCanBeIncreased",
                [this]()
                {
                    TestTrueExpr(Snake->links().Num() == SnakeSize);
                    Snake->feed();
                    TestTrueExpr(Snake->links().Num() == SnakeSize + 1);
                });
        });
}

#endif