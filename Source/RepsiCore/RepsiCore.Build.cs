using UnrealBuildTool;

public class RepsiCore : ModuleRules
{
	public RepsiCore(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		bEnforceIWYU = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" ,"UMG"});
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
