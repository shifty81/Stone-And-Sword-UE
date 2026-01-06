// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldGenerator.generated.h"

// Forward declarations
class UProceduralMeshComponent;
class UMaterialInterface;

/**
 * Procedural world generator that creates terrain for the open world.
 * Uses ProceduralMeshComponent to generate runtime terrain with configurable parameters.
 * Supports auto-generation, custom materials, and physics collision.
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

	/** Calculate terrain height at a given position */
	float CalculateTerrainHeight(float X, float Y) const;
};
