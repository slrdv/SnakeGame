// SnakeGame. Copyright egorpk. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Core/Game.h"

DEFINE_SPEC(FCoreFood, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

void FCoreFood::Define()
{
    Describe("Core.Food",
        [this]()
        {
            It("FoodPositionShouldBeUpdatedCorrectly",
                [this]()
                {
                    CoreGame::Food Food;
                    Food.setPosition({2, 2});
                    TestTrueExpr(Food.getPosition() == CoreGame::Position(2, 2));
                });
        });
}

#endif