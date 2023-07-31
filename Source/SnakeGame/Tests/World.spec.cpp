// SnakeGame. Copyright <CompanyName>. All right Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/AutomationCommon.h"
#include "Utils/TestUtils.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Game/SGGameMode.h"
#include "Game/SGPawn.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/ExponentialHeightFog.h"
#include "Components/ExponentialHeightFogComponent.h"

BEGIN_DEFINE_SPEC(FSnakeGameWorld, "SnakeGame",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

UWorld* World = nullptr;
CoreGame::Size GridSize;
uint32 CellSizeWorld;
TSharedPtr<CoreGame::Grid> CoreGridModel;
ASGGrid* Grid = nullptr;
UStaticMeshComponent* GridMesh = nullptr;

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

            It("SceneColorShouldBeSetupCorrectly",
                [this]()
                {
                    auto* GameMode = Cast<ASGGameMode>(World->GetAuthGameMode());
                    auto* ColorsDataTable = GameMode->GetColorsDataTable();

                    FSGColors Colors;
                    Colors.SceneBackgroundColor = FLinearColor::MakeRandomColor();

                    const FName RowName = FName(FGuid::NewGuid().ToString());
                    ColorsDataTable->AddRow(RowName, Colors);

                    const uint32 Index = ColorsDataTable->GetRowNames().IndexOfByKey(RowName);
                    GameMode->UpdateColors(Index);

                    const auto* Fog =
                        Cast<AExponentialHeightFog>(UGameplayStatics::GetActorOfClass(World, AExponentialHeightFog::StaticClass()));
                    const FLinearColor ActualColor = Fog->GetComponent()->FogInscatteringLuminance;

                    TestTrueExpr(ActualColor.Equals(Colors.SceneBackgroundColor));
                });
        });

    Describe("World.Grid",
        [this]()
        {
            // Call before each test
            BeforeEach(
                [this]()
                {
                    AutomationOpenMap("/Game/Test/TestLevel");
                    World = GetTestGameWorld();

                    const FString GridBlueprintPath = "/Script/Engine.Blueprint'/Game/Blueprints/World/BP_SGGrid.BP_SGGrid'";
                    Grid = TestUtils::SpawnBlueprint<ASGGrid>(World, GridBlueprintPath, FTransform::Identity, true);
                    check(Grid);

                    GridSize = CoreGame::Size{20, 10};
                    CoreGridModel = MakeShared<CoreGame::Grid>(GridSize);
                    CellSizeWorld = 10;

                    Grid->SetModel(CoreGridModel, CellSizeWorld);
                    Grid->FinishSpawning(FTransform::Identity);

                    GridMesh = Cast<UStaticMeshComponent>(Grid->GetComponentByClass(UStaticMeshComponent::StaticClass()));
                    check(GridMesh);
                });

            It("GridHaveCorrectTransform",
                [this]()
                {
                    const FVector Size = GridMesh->GetStaticMesh()->GetBoundingBox().GetSize();
                    const uint32 HeightWorld = CoreGridModel->getSize().height * CellSizeWorld;
                    const uint32 WidthWorld = CoreGridModel->getSize().width * CellSizeWorld;
                    TestTrueExpr(GridMesh->GetRelativeScale3D().Equals(FVector(HeightWorld / Size.X, WidthWorld / Size.Y, 1.0)));
                    TestTrueExpr(GridMesh->GetRelativeLocation().Equals(0.5 * FVector(HeightWorld, WidthWorld, -Size.Z)));
                });
            It("GridHaveCorrectColors",
                [this]()
                {
                    FSGColors Colors;
                    Colors.GridBackgroundColor = FLinearColor::MakeRandomColor();
                    Colors.GridLineColor = FLinearColor::MakeRandomColor();
                    Colors.GridWallColor = FLinearColor::MakeRandomColor();

                    Grid->UpdateColors(Colors);

                    const auto GridMaterial = GridMesh->GetMaterial(0);
                    FLinearColor ActualColor;

                    GridMaterial->GetVectorParameterValue(FName("BackgroundColor"), ActualColor);
                    TestTrueExpr(ActualColor.Equals(Colors.GridBackgroundColor));

                    GridMaterial->GetVectorParameterValue(FName("LineColor"), ActualColor);
                    TestTrueExpr(ActualColor.Equals(Colors.GridLineColor));

                    GridMaterial->GetVectorParameterValue(FName("WallColor"), ActualColor);
                    TestTrueExpr(ActualColor.Equals(Colors.GridWallColor));
                });
        });
}

#endif
