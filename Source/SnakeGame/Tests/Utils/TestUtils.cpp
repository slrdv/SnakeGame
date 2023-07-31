#include "TestUtils.h"
#include "CoreMinimal.h"

namespace TestUtils
{
    UWorld* GetTestGameWorld()
    {
        for (const FWorldContext& Context : GEngine->GetWorldContexts())
        {
            if ((Context.WorldType == EWorldType::PIE || Context.WorldType == EWorldType::Game) && Context.World())
            {
                return Context.World();
            }
        }
        return nullptr;
    }

    bool IsMapExist(const FString& Name)
    {
        TArray<FString> OutFiles;
        IFileManager::Get().FindFilesRecursive(OutFiles, *FPaths::ProjectContentDir(), TEXT("*.umap"), true, false);
        TArray<FString> Names;
        for (const auto& File : OutFiles)
        {
            FString OutPath, OutName, OutExtension;
            FPaths::Split(File, OutPath, OutName, OutExtension);
            if (OutName.Equals(Name))
            {
                return true;
            }
        }

        return false;
    }

}  // namespace TestUtils
