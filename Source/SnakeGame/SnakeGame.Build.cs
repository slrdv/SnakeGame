// SnakeGame. Copyright slrdv. All right Reserved.

using UnrealBuildTool;

public class SnakeGame : ModuleRules
{
    public SnakeGame(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PublicIncludePaths.AddRange(new string[] { "SnakeGame" });
    }
}
