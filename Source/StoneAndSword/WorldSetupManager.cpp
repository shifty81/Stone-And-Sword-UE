// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldSetupManager.h"
#include "WorldGenerator.h"
#include "Engine/DirectionalLight.h"
#include "Engine/SkyLight.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "EngineUtils.h"

AWorldSetupManager::AWorldSetupManager()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set default values
	bAutoSetupWorld = true;
	bSpawnWorldGenerator = true;
	bSetupLighting = true;
	bSetupSky = true;
	
	DefaultWorldSizeX = 10000;
	DefaultWorldSizeY = 10000;
	DefaultGridResolution = 100.0f;
	DefaultHeightVariation = 50.0f;
}

void AWorldSetupManager::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoSetupWorld)
	{
		SetupWorld();
	}
}

void AWorldSetupManager::SetupWorld()
{
	UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Setting up world..."));

	// Spawn WorldGenerator if needed
	if (bSpawnWorldGenerator)
	{
		// Check if a WorldGenerator already exists in the level
		bool bFoundWorldGenerator = false;
		for (TActorIterator<AWorldGenerator> It(GetWorld()); It; ++It)
		{
			bFoundWorldGenerator = true;
			UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Found existing WorldGenerator"));
			break;
		}

		if (!bFoundWorldGenerator)
		{
			SpawnWorldGenerator();
		}
	}

	// Setup lighting
	if (bSetupLighting)
	{
		SetupDirectionalLight();
	}

	// Setup sky
	if (bSetupSky)
	{
		SetupSkyAtmosphere();
	}

	UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: World setup complete"));
}

void AWorldSetupManager::SpawnWorldGenerator()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("WorldSetupManager: Failed to get world"));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn at origin
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = FRotator::ZeroRotator;

	AWorldGenerator* WorldGenerator = World->SpawnActor<AWorldGenerator>(
		AWorldGenerator::StaticClass(),
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (WorldGenerator)
	{
		// Configure the world generator with default values
		WorldGenerator->SetActorLabel(TEXT("WorldGenerator_Auto"));
		
		UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Spawned and configured WorldGenerator"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WorldSetupManager: Failed to spawn WorldGenerator"));
	}
}

void AWorldSetupManager::SetupDirectionalLight()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// Check if directional light already exists
	bool bFoundDirectionalLight = false;
	for (TActorIterator<ADirectionalLight> It(World); It; ++It)
	{
		bFoundDirectionalLight = true;
		UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Found existing Directional Light"));
		break;
	}

	if (!bFoundDirectionalLight)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// Spawn directional light above the origin
		FVector LightLocation = FVector(0.0f, 0.0f, 1000.0f);
		FRotator LightRotation = FRotator(-50.0f, 0.0f, 0.0f);

		ADirectionalLight* DirectionalLight = World->SpawnActor<ADirectionalLight>(
			ADirectionalLight::StaticClass(),
			LightLocation,
			LightRotation,
			SpawnParams
		);

		if (DirectionalLight)
		{
			DirectionalLight->SetActorLabel(TEXT("DirectionalLight_Auto"));
			
			// Configure light properties
			if (UDirectionalLightComponent* LightComponent = DirectionalLight->GetComponent())
			{
				LightComponent->SetIntensity(10.0f);
				LightComponent->SetLightColor(FLinearColor(1.0f, 0.95f, 0.9f));
			}
			
			UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Spawned Directional Light"));
		}
	}
}

void AWorldSetupManager::SetupSkyAtmosphere()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	// Check if sky light already exists
	bool bFoundSkyLight = false;
	for (TActorIterator<ASkyLight> It(World); It; ++It)
	{
		bFoundSkyLight = true;
		UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Found existing Sky Light"));
		break;
	}

	if (!bFoundSkyLight)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		FVector SkyLocation = FVector::ZeroVector;
		FRotator SkyRotation = FRotator::ZeroRotator;

		ASkyLight* SkyLight = World->SpawnActor<ASkyLight>(
			ASkyLight::StaticClass(),
			SkyLocation,
			SkyRotation,
			SpawnParams
		);

		if (SkyLight)
		{
			SkyLight->SetActorLabel(TEXT("SkyLight_Auto"));
			
			// Configure sky light
			if (USkyLightComponent* SkyLightComponent = SkyLight->GetLightComponent())
			{
				SkyLightComponent->SetIntensity(1.0f);
				SkyLightComponent->SetCastShadows(true);
				SkyLightComponent->RecaptureSky();
			}
			
			UE_LOG(LogTemp, Log, TEXT("WorldSetupManager: Spawned Sky Light"));
		}
	}
}
