// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StoneAndSword : ModuleRules
{
	public StoneAndSword(ReadOnlyTargetRules Target) : base(Target)
	{
		// Use explicit or shared PCHs for better compilation performance
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Public dependencies - exposed in header files
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"ProceduralMeshComponent",
			"Landscape"
		});

		// Private dependencies - used only in implementation files
		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate",
			"SlateCore"
		});

		// Uncomment if using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your .uproject file
	}
}
