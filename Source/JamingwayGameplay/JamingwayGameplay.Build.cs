using UnrealBuildTool;

public class JamingwayGameplay : ModuleRules
{
    public JamingwayGameplay(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}