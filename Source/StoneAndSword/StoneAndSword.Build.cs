// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StoneAndSword : ModuleRules
{
	public StoneAndSword(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"ProceduralMeshComponent",
			"Landscape"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate",
			"SlateCore"
		});
	}
}
