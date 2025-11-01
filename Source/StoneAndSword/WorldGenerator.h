// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "WorldGenerator.generated.h"

/**
 * Procedural world generator that creates a flat terrain for the open world
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

protected:
	/** Procedural mesh component for the terrain */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World Generation")
	UProceduralMeshComponent* ProceduralMesh;

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

	/** Random seed for world generation */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation")
	int32 RandomSeed;

	/** Auto-generate world on begin play */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation")
	bool bAutoGenerateOnBeginPlay;

	/** Material to apply to the terrain */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Generation")
	UMaterialInterface* TerrainMaterial;

private:
	/** Generate mesh data for a flat terrain chunk */
	void GenerateTerrainMesh(TArray<FVector>& Vertices, TArray<int32>& Triangles, 
							 TArray<FVector>& Normals, TArray<FVector2D>& UVs, 
							 TArray<FColor>& VertexColors);

	/** Calculate terrain height at a given position */
	float CalculateTerrainHeight(float X, float Y);
};
