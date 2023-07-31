// SnakeGame. Copyright egorpk. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"

DEFINE_SPEC(FCoreGame, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FCoreGame::Define()
{
    Describe("CoreGame",
        [this]()
        {
            It("GridShouldExists",
                [this]()
                {
                    constexpr CoreGame::Settings GameSettings{5, 5};
                    CoreGame::Game Game{GameSettings};
                    TestTrueExpr(Game.getGrid().IsValid());
                });
        });

    Describe("CoreGrid",
        [this]()
        {
            It("GridSizeShouldIncludeWalls",
                [this]()
                {
                    constexpr CoreGame::Size Size{5, 5};
                    CoreGame::Grid Grid{Size};
                    TestTrueExpr(Grid.getSize().width == Size.width + 2 && Grid.getSize().height == Size.height + 2);
                });
        });
}

#endif