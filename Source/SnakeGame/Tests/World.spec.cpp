// SnakeGame. Copyright <CompanyName>. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/AutomationCommon.h"
#include "Utils/TestUtils.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Game/SGGameMode.h"
#include "Game/SGPawn.h"
#include "Kismet/GameplayStatics.h"

BEGIN_DEFINE_SPEC(FSnakeGameWorld, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

UWorld* World = nullptr;

END_DEFINE_SPEC(FSnakeGameWorld)

void FSnakeGameWorld::Define()
{
    using namespace TestUtils;

    Describe("Global",
        [this]()
        {
            It("GameLevelShouldExist",
                [this]()
                {
                    //
                    TestTrueExpr(IsMapExist("GameLevel"));
                });
        });

    Describe("Framework",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("/Game/Levels/GameLevel");
                    World = GetTestGameWorld();
                });

            It("FrameworkClassesShouldBeSetupCorrectly",
                [this]()
                {
                    TestNotNull("GameMode exists", Cast<ASGGameMode>(World->GetAuthGameMode()));
                    TestNotNull("Pawn exists", Cast<ASGPawn>(World->GetFirstPlayerController()->GetPawn()));
                });

            xIt("PawnLocationShouldBeAdjustCorrectly", [this]() { unimplemented(); });
        });

    Describe("World",
        [this]()
        {
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("/Game/Levels/GameLevel");
                    World = GetTestGameWorld();
                });

            It("GridIsExistAndUnique",
                [this]()
                {
                    TArray<AActor*> Actors;
                    UGameplayStatics::GetAllActorsOfClass(World, ASGGrid::StaticClass(), Actors);
                    TestTrue("Grid is unique", Actors.Num() == 1);
                    TestNotNull("Grid is exist", Actors[0]);
                });
        });
}

#endif
