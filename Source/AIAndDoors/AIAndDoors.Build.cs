// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class AIAndDoors : ModuleRules
{
	public AIAndDoors(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" });

		PrivateDependencyModuleNames.AddRange(new string[] { "SmartObjectsModule","GameplayBehaviorSmartObjectsModule" });
	}
}
