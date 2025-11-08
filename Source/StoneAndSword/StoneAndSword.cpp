// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoneAndSword.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogStoneAndSword, Log, All);

void FStoneAndSwordModule::StartupModule()
{
	// This code will execute after your module is loaded into memory
	UE_LOG(LogStoneAndSword, Log, TEXT("StoneAndSword module started"));
}

void FStoneAndSwordModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module
	UE_LOG(LogStoneAndSword, Log, TEXT("StoneAndSword module shutdown"));
}

IMPLEMENT_PRIMARY_GAME_MODULE(FStoneAndSwordModule, StoneAndSword, "StoneAndSword");
