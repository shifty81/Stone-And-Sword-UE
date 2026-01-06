// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGenerator.generated.h"

// Forward declarations
class UProceduralMeshComponent;
class UMaterialInterface;

/**
 * Biome types for procedural world generation
 * Each biome represents a large continent on the planet
 */
UENUM(BlueprintType)
enum class EBiomeType : uint8
{
	TropicalJungle		UMETA(DisplayName = "Tropical Jungle"),
	TemperateForest		UMETA(DisplayName = "Temperate Forest"),
	BorealTaiga			UMETA(DisplayName = "Boreal Taiga"),
	Grasslands			UMETA(DisplayName = "Grasslands/Plains"),
	Savanna				UMETA(DisplayName = "Savanna"),
	Desert				UMETA(DisplayName = "Desert"),
	Tundra				UMETA(DisplayName = "Tundra"),
	ArcticSnow			UMETA(DisplayName = "Arctic Snow"),
	Mountains			UMETA(DisplayName = "Mountains"),
	VolcanicWasteland	UMETA(DisplayName = "Volcanic Wasteland"),
	Swampland			UMETA(DisplayName = "Swampland"),
	RockyBadlands		UMETA(DisplayName = "Rocky Badlands")
};

/**
 * Biome data structure containing terrain properties for continental biomes
 */
USTRUCT(BlueprintType)
struct FBiomeData
{
	GENERATED_BODY()

	/** Display name of the biome continent */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biome")
	FString BiomeName;

	/** Height multiplier for this biome's terrain variation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biome")
	float HeightMultiplier = 1.0f;

	/** Base height offset for this biome (e.g., mountains start higher) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biome")
	float BaseHeightOffset = 0.0f;

	/** Color tint for this biome's terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biome")
	FLinearColor BiomeColor = FLinearColor::White;

	/** Terrain roughness factor (affects noise frequency) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Biome")
	float TerrainRoughness = 1.0f;

	FBiomeData() = default;

	FBiomeData(const FString& InName, float InHeightMultiplier, const FLinearColor& InColor, 
		float InBaseOffset = 0.0f, float InRoughness = 1.0f)
		: BiomeName(InName)
		, HeightMultiplier(InHeightMultiplier)
		, BaseHeightOffset(InBaseOffset)
		, BiomeColor(InColor)
		, TerrainRoughness(InRoughness)
	{
	}
};

/**
 * Procedural world generator that creates a planetary terrain system with continental biomes.
 * Generates a continuous world where each continent represents a distinct biome type.
 * Uses temperature and moisture gradients to distribute biomes across the planet naturally.
 * Supports seamless transitions between continental biomes with ocean/water boundaries.
 */
UCLASS()
class STONEANDSWORD_API AWorldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldGenerator();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	/** Generate the world mesh */
	UFUNCTION(BlueprintCallable, Category = "World Generation")
	void GenerateWorld();

	/** Clear the world mesh */
	UFUNCTION(BlueprintCallable, Category = "World Generation")
	void ClearWorld();

	/** Set world generation parameters */
	UFUNCTION(BlueprintCallable, Category = "World Generation")
	void SetWorldParameters(int32 InWorldSizeX, int32 InWorldSizeY, float InGridResolution, float InHeightVariation);

	/** Get the current world size X */
	UFUNCTION(BlueprintPure, Category = "World Generation")
	int32 GetWorldSizeX() const { return WorldSizeX; }

	/** Get the current world size Y */
	UFUNCTION(BlueprintPure, Category = "World Generation")
	int32 GetWorldSizeY() const { return WorldSizeY; }

	/** Get the current grid resolution */
	UFUNCTION(BlueprintPure, Category = "World Generation")
	float GetGridResolution() const { return GridResolution; }

	/** Get the current height variation */
	UFUNCTION(BlueprintPure, Category = "World Generation")
	float GetHeightVariation() const { return HeightVariation; }

protected:
	/** Procedural mesh component for the terrain */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Generation")
	TObjectPtr<UProceduralMeshComponent> ProceduralMesh;

	/** World size in units (X direction) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "100", ClampMax = "100000"))
	int32 WorldSizeX;

	/** World size in units (Y direction) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "100", ClampMax = "100000"))
	int32 WorldSizeY;

	/** Grid resolution - distance between vertices */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "10", ClampMax = "1000"))
	float GridResolution;

	/** Height variation for slight terrain undulation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "0", ClampMax = "500"))
	float HeightVariation;

	/** Noise scale for terrain generation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "0.001", ClampMax = "1.0"))
	float NoiseScale;

	/** Number of octaves for Perlin noise (more octaves = more detail) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "1", ClampMax = "8"))
	int32 NoiseOctaves;

	/** Persistence - how much each octave contributes (amplitude multiplier) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "0.1", ClampMax = "1.0"))
	float NoisePersistence;

	/** Lacunarity - frequency multiplier for each octave */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation", meta = (ClampMin = "1.0", ClampMax = "4.0"))
	float NoiseLacunarity;

	/** Random seed for world generation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation")
	int32 RandomSeed;

	/** Enable continental biome system for planetary generation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes")
	bool bEnablePlanetaryBiomes;

	/** Temperature gradient noise scale - affects continental distribution */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes", meta = (ClampMin = "0.0001", ClampMax = "0.01", EditCondition = "bEnablePlanetaryBiomes"))
	float TemperatureNoiseScale;

	/** Moisture gradient noise scale - affects biome distribution */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes", meta = (ClampMin = "0.0001", ClampMax = "0.01", EditCondition = "bEnablePlanetaryBiomes"))
	float MoistureNoiseScale;

	/** Continental scale - controls size of biome continents */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes", meta = (ClampMin = "0.0001", ClampMax = "0.005", EditCondition = "bEnablePlanetaryBiomes"))
	float ContinentalScale;

	/** Biome transition blend distance (0-1, higher = smoother transitions) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "bEnablePlanetaryBiomes"))
	float BiomeBlendFactor;

	/** Auto-generate world on begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation")
	bool bAutoGenerateOnBeginPlay;

	/** Material to apply to the terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation")
	TObjectPtr<UMaterialInterface> TerrainMaterial;

private:
	/** Generate mesh data for a flat terrain chunk */
	void GenerateTerrainMesh(TArray<FVector>& Vertices, TArray<int32>& Triangles, 
							 TArray<FVector>& Normals, TArray<FVector2D>& UVs, 
							 TArray<FColor>& VertexColors);

	/** Calculate terrain height at a given position with biome-specific modifications */
	float CalculateTerrainHeight(float X, float Y) const;

	/** Get biome data for a specific biome type */
	FBiomeData GetBiomeData(EBiomeType BiomeType) const;

	/** Determine biome type at a given world position based on temperature and moisture */
	EBiomeType DetermineBiomeAtPosition(float X, float Y) const;

	/** Calculate temperature value at a given position (0-1 range, affects biome distribution) */
	float CalculateTemperature(float X, float Y) const;

	/** Calculate moisture value at a given position (0-1 range, affects biome distribution) */
	float CalculateMoisture(float X, float Y) const;

	/** Apply biome-specific effects to height calculation with smooth blending */
	float ApplyBiomeModifiers(float BaseHeight, float X, float Y, EBiomeType BiomeType) const;

	/** Blend between multiple biomes for smooth continental transitions */
	void BlendBiomeEffects(float X, float Y, float& Height, FLinearColor& Color) const;
};
