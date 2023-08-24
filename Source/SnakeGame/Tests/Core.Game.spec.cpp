// SnakeGame. Copyright egorpk. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"

using namespace CoreGame;

BEGIN_DEFINE_SPEC(FCoreGame, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

Settings GameSettings;
TUniquePtr<Game> GamePtr;

END_DEFINE_SPEC(FCoreGame)

class TestPositionRandomizer : public IPositionRandomizer
{
public:
    virtual bool getPosition(Position& outPosition, const TArray<CellType>& cells, const Size& size) const override
    {
        outPosition = Positions[Index++];
        return true;
    }
    void SetPositions(const TArray<Position>& InPositions) { Positions = InPositions; }

private:
    mutable int32 Index{0};
    TArray<Position> Positions;
};

void FCoreGame::Define()
{
    Describe("Core.Game",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    GameSettings.gridSize = Size{10, 10};
                    GameSettings.snakePosition = Grid::getCenter(GameSettings.gridSize);
                    GameSettings.tickInterval = 1.0f;
                    GamePtr = MakeUnique<Game>(GameSettings);
                });
            It("GridShouldExists", [this]() { TestTrueExpr(GamePtr->getGrid().IsValid()); });
            It("SnakeShouldExists", [this]() { TestTrueExpr(GamePtr->getSnake().IsValid()); });
            It("FoodShouldExists", [this]() { TestTrueExpr(GamePtr->getFood().IsValid()); });
            It("GameCanBeOver",
                [this]()
                {
                    bool bGameOver{false};
                    GamePtr->subscribeGameEvent(
                        [&bGameOver](GameEvent Event)
                        {
                            if (Event == GameEvent::GameOver) bGameOver = true;
                        });
                    int32 Moves = GamePtr->getGrid()->getSize().width - (GamePtr->getSnake()->head()->GetValue().x + 1) - 1;

                    for (int i = 0; i < Moves; ++i)
                    {
                        GamePtr->update(1.0f, Input::Default);
                        TestTrueExpr(!bGameOver);
                    }
                    GamePtr->update(1.0f, Input::Default);
                    TestTrueExpr(bGameOver);
                });
            It("FoodCanBeTaken",
                [this]()
                {
                    TSharedPtr<TestPositionRandomizer> Randomizer = MakeShared<TestPositionRandomizer>();

                    const Position Head = Grid::getCenter(GameSettings.gridSize);
                    Randomizer->SetPositions({{Head.x + 1, Head.y}, {Head.x + 3, Head.y}, {1, 1}});

                    GamePtr = MakeUnique<Game>(GameSettings, Randomizer);

                    uint32 Score{0};
                    GamePtr->subscribeGameEvent(
                        [&Score](GameEvent Event)
                        {
                            if (Event == GameEvent::FoodTaken) ++Score;
                        });

                    TestTrueExpr(Score == 0 && GamePtr->getScore() == 0);

                    GamePtr->update(1.0f, {1, 0});
                    TestTrueExpr(Score == 1 && GamePtr->getScore() == 1);

                    GamePtr->update(1.0f, {1, 0});
                    TestTrueExpr(Score == 1 && GamePtr->getScore() == 1);

                    GamePtr->update(1.0f, {1, 0});
                    TestTrueExpr(Score == 2 && GamePtr->getScore() == 2);
                });
        });
}

#endif