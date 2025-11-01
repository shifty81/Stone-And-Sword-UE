// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class StoneAndSwordEditor : ModuleRules
{
	public StoneAndSwordEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine",
			"UnrealEd",
			"StoneAndSword"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate",
			"SlateCore",
			"EditorStyle",
			"PropertyEditor"
		});
	}
}
