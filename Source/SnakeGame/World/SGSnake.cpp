// SnakeGame. Copyright slrdv. All right Reserved.

#include "SGSnake.h"

#include "SGSnakeLink.h"
#include "SGWorldTypes.h"
#include "Utils/SGUtils.h"

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
    BodyColor = Colors.SnakeBodyColor;

    for (int i = 0; i < SnakeLinks.Num(); ++i)
    {
        SnakeLinks[i]->SetColor(i == 0 ? Colors.SnakeHeadColor : Colors.SnakeBodyColor);
    }
}

void ASGSnake::Explode()
{
    LinkIndex = 0;
    GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ThisClass::OnLinkExplosion, ExplosionRate, true, 0);
}

void ASGSnake::OnLinkExplosion()
{
    if (LinkIndex == SnakeLinks.Num())
    {
        GetWorldTimerManager().ClearTimer(ExplosionTimerHandle);
        OnExplosionFinishedDelegate.Execute();
    }
    else
    {
        SnakeLinks[LinkIndex++]->Explode();
    }
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
        SpawnLink(LinkGridPosition, i == 0 ? SnakeHeadClass : SnakeBodyClass);
        ++i;
    }
}

ASGSnakeLink* ASGSnake::SpawnLink(const CoreGame::Position& Position, TSubclassOf<ASGSnakeLink> LinkClass)
{
    check(GetWorld());
    auto* LinkActor = GetWorld()->SpawnActorDeferred<ASGSnakeLink>(LinkClass, FTransform::Identity);
    check(LinkActor);

    LinkActor->SetScale(CellSizeWorld);
    LinkActor->SetActorLocation(SGUtils::GridToWorld(Position, CellSizeWorld, GridSize, 0.5));
    LinkActor->FinishSpawning(FTransform::Identity);

    SnakeLinks.Add(LinkActor);

    return LinkActor;
}

// Called every frame
void ASGSnake::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    int32 i = 0;
    for (const auto& LinkGridPosition : SnakePtr.Pin()->links())
    {
        ASGSnakeLink* LinkActor;
        if (i >= SnakeLinks.Num())
        {
            LinkActor = SpawnLink(LinkGridPosition, SnakeBodyClass);
            LinkActor->SetColor(BodyColor);
        }
        else
        {
            LinkActor = SnakeLinks[i];
        }

        LinkActor->SetActorLocation(SGUtils::GridToWorld(LinkGridPosition, CellSizeWorld, GridSize, 0.5));
        ++i;
    }
}
