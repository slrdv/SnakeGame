// SnakeGame. Copyright slrdv. All right Reserved.

#include "SGSnake.h"

#include "SGSnakeLink.h"
#include "SGWorldTypes.h"

// Sets default values
ASGSnake::ASGSnake()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ASGSnake::SetModel(const TSharedPtr<CoreGame::Snake>& SnakeModel, uint32 InCellSizeWorld, const CoreGame::Size& InGridSize)
{
    SnakePtr = SnakeModel;
    CellSizeWorld = InCellSizeWorld;
    GridSize = InGridSize;

    CreateLinks();
}

void ASGSnake::SetColor(const FSGColors& Colors)
{
    for (int i = 0; i < SnakeLinks.Num(); ++i)
    {
        SnakeLinks[i]->SetColor(i == 0 ? Colors.SnakeHeadColor : Colors.SnakeBodyColor);
    }
}

// Called when the game starts or when spawned
void ASGSnake::BeginPlay()
{
    Super::BeginPlay();
}

void ASGSnake::CreateLinks()
{
    check(SnakePtr.IsValid() && GetWorld());

    for (auto* Link : SnakeLinks)
    {
        Link->Destroy();
    }

    SnakeLinks.Empty();

    uint32 i = 0;
    for (const auto& LinkGridPosition : SnakePtr.Pin()->links())
    {
        auto LinkClass = i == 0 ? SnakeHeadClass : SnakeBodyClass;
        auto* LinkActor = GetWorld()->SpawnActorDeferred<ASGSnakeLink>(LinkClass, FTransform::Identity);
        LinkActor->SetScale(CellSizeWorld);
        UpdateLinkPosition(LinkActor, LinkGridPosition);
        LinkActor->FinishSpawning(FTransform::Identity);

        SnakeLinks.Add(LinkActor);
        ++i;
    }
}

void ASGSnake::UpdateLinkPosition(ASGSnakeLink* Link, const CoreGame::Position& GridPosition)
{
    if (!Link) return;
    FVector Position;
    Position.X = (GridSize.height - 1 - GridPosition.y) * CellSizeWorld;
    Position.Y = GridPosition.x * CellSizeWorld;

    Link->SetActorLocation(Position + FVector(CellSizeWorld * 0.5));
}

// Called every frame
void ASGSnake::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    uint32 i = 0;
    for (const auto& LinkGridPosition : SnakePtr.Pin()->links())
    {
        auto* LinkActor = SnakeLinks[i];
        UpdateLinkPosition(LinkActor, LinkGridPosition);
        ++i;
    }
}
