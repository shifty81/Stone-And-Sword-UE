// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldSetupManager.generated.h"

/**
 * Manages automatic world setup for testing and development.
 * Automatically spawns and configures necessary actors for the game world.
 * Includes world generator, lighting, and sky atmosphere setup.
 */
UCLASS()
class STONEANDSWORD_API AWorldSetupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldSetupManager();

protected:
	virtual void BeginPlay() override;

public:	
	/** Whether to auto-setup the world on begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup")
	bool bAutoSetupWorld;

	/** Whether to spawn a WorldGenerator if one doesn't exist */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup")
	bool bSpawnWorldGenerator;

	/** Whether to setup lighting automatically */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup")
	bool bSetupLighting;

	/** Whether to setup sky automatically */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup")
	bool bSetupSky;

	/** Default world size for generated terrain (X direction) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup", meta = (ClampMin = "100", ClampMax = "100000"))
	int32 DefaultWorldSizeX;

	/** Default world size for generated terrain (Y direction) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup", meta = (ClampMin = "100", ClampMax = "100000"))
	int32 DefaultWorldSizeY;

	/** Default grid resolution for terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup", meta = (ClampMin = "10", ClampMax = "1000"))
	float DefaultGridResolution;

	/** Default height variation for terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Setup", meta = (ClampMin = "0", ClampMax = "500"))
	float DefaultHeightVariation;

private:
	/** Setup the world with default actors and configuration */
	void SetupWorld();

	/** Spawn and configure the WorldGenerator actor */
	void SpawnWorldGenerator();

	/** Setup directional light for the world */
	void SetupDirectionalLight();

	/** Setup sky atmosphere and skylight */
	void SetupSkyAtmosphere();
};
