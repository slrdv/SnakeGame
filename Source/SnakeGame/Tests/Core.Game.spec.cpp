// SnakeGame. Copyright egorpk. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"

BEGIN_DEFINE_SPEC(FCoreGame, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

TUniquePtr<CoreGame::Game> Game;

END_DEFINE_SPEC(FCoreGame)

void FCoreGame::Define()
{
    Describe("Core.Game",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    CoreGame::Settings GameSettings;
                    GameSettings.gridSize = CoreGame::Size{10, 10};
                    GameSettings.snakePosition = CoreGame::Grid::getCenter(GameSettings.gridSize);
                    Game = MakeUnique<CoreGame::Game>(GameSettings);
                });
            It("GridShouldExists", [this]() { TestTrueExpr(Game->getGrid().IsValid()); });
            It("SnakeShouldExists", [this]() { TestTrueExpr(Game->getSnake().IsValid()); });
            It("FoodShouldExists", [this]() { TestTrueExpr(Game->getFood().IsValid()); });
        });
}

#endif