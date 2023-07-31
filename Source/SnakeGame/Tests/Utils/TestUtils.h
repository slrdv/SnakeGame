#pragma once

#if WITH_AUTOMATION_TESTS

namespace TestUtils
{
    UWorld* GetTestGameWorld();

    bool IsMapExist(const FString& Name);

    template <class T>
    T* SpawnBlueprint(UWorld* World, const FString& Path, FTransform Transform = FTransform::Identity, bool bSpawnDeferred = false)
    {
        if (!World) return nullptr;

        const UBlueprint* Blueprint = LoadObject<UBlueprint>(nullptr, *Path);
        if (!Blueprint) return nullptr;

        if (bSpawnDeferred)
        {
            return World->SpawnActorDeferred<T>(Blueprint->GeneratedClass, Transform);
        }

        return World->SpawnActor<T>(Blueprint->GeneratedClass, Transform);
    }

}  // namespace TestUtils

#endif
