// Copyright Epic Games, Inc. All Rights Reserved.

#include "StoneAndSwordGameModeBase.h"
#include "WorldPlayerCharacter.h"
#include "WorldSetupManager.h"
#include "UObject/ConstructorHelpers.h"

AStoneAndSwordGameModeBase::AStoneAndSwordGameModeBase()
{
	// Set default pawn class to our character
	DefaultPawnClass = AWorldPlayerCharacter::StaticClass();
	
	// Enable auto-spawn of WorldSetupManager by default
	bAutoSpawnWorldSetupManager = true;
	WorldSetupManager = nullptr;
}

void AStoneAndSwordGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Automatically spawn WorldSetupManager if enabled
	if (bAutoSpawnWorldSetupManager && GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SpawnLocation = FVector::ZeroVector;
		FRotator SpawnRotation = FRotator::ZeroRotator;

		WorldSetupManager = GetWorld()->SpawnActor<AWorldSetupManager>(
			AWorldSetupManager::StaticClass(),
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);

		if (WorldSetupManager)
		{
			UE_LOG(LogTemp, Log, TEXT("GameMode: WorldSetupManager spawned successfully"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("GameMode: Failed to spawn WorldSetupManager"));
		}
	}
}
