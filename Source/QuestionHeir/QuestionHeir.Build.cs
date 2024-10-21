// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class QuestionHeir : ModuleRules
{
	public QuestionHeir(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "AIModule", "Json", "JsonUtilities", "DesktopPlatform", "Slate", "SlateCore" });
	}
}
