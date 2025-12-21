// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldGenerator.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogWorldGenerator, Log, All);

AWorldGenerator::AWorldGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the procedural mesh component
	ProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ProceduralMesh"));
	RootComponent = ProceduralMesh;

	// Set default values
	WorldSizeX = 10000;
	WorldSizeY = 10000;
	GridResolution = 100.0f;
	HeightVariation = 50.0f;
	NoiseScale = 0.01f;
	RandomSeed = 12345;
	bAutoGenerateOnBeginPlay = true;
	TerrainMaterial = nullptr;

	// Enable collision for the procedural mesh
	ProceduralMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ProceduralMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
}

void AWorldGenerator::BeginPlay()
{
	Super::BeginPlay();

	if (bAutoGenerateOnBeginPlay)
	{
		GenerateWorld();
	}
}

void AWorldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorldGenerator::GenerateWorld()
{
	UE_LOG(LogWorldGenerator, Log, TEXT("Generating world with size (%d, %d), resolution %.1f"), 
		WorldSizeX, WorldSizeY, GridResolution);

	ClearWorld();

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FColor> VertexColors;

	GenerateTerrainMesh(Vertices, Triangles, Normals, UVs, VertexColors);

	// Create the mesh section
	ProceduralMesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVs, VertexColors, TArray<FProcMeshTangent>(), true);

	// Apply material if set
	if (TerrainMaterial)
	{
		ProceduralMesh->SetMaterial(0, TerrainMaterial);
		UE_LOG(LogWorldGenerator, Log, TEXT("Applied terrain material"));
	}

	// Enable collision
	ProceduralMesh->ContainsPhysicsTriMeshData(true);
	
	UE_LOG(LogWorldGenerator, Log, TEXT("World generation complete: %d vertices, %d triangles"), 
		Vertices.Num(), Triangles.Num() / 3);
}

void AWorldGenerator::ClearWorld()
{
	ProceduralMesh->ClearAllMeshSections();
}

void AWorldGenerator::SetWorldParameters(int32 InWorldSizeX, int32 InWorldSizeY, float InGridResolution, float InHeightVariation)
{
	WorldSizeX = FMath::Clamp(InWorldSizeX, 100, 100000);
	WorldSizeY = FMath::Clamp(InWorldSizeY, 100, 100000);
	GridResolution = FMath::Clamp(InGridResolution, 10.0f, 1000.0f);
	HeightVariation = FMath::Clamp(InHeightVariation, 0.0f, 500.0f);
}

void AWorldGenerator::GenerateTerrainMesh(TArray<FVector>& Vertices, TArray<int32>& Triangles, 
										  TArray<FVector>& Normals, TArray<FVector2D>& UVs, 
										  TArray<FColor>& VertexColors)
{
	// Calculate grid dimensions
	int32 NumVerticesX = FMath::CeilToInt(WorldSizeX / GridResolution) + 1;
	int32 NumVerticesY = FMath::CeilToInt(WorldSizeY / GridResolution) + 1;

	// Reserve space for arrays
	Vertices.Reserve(NumVerticesX * NumVerticesY);
	UVs.Reserve(NumVerticesX * NumVerticesY);
	Normals.Reserve(NumVerticesX * NumVerticesY);
	VertexColors.Reserve(NumVerticesX * NumVerticesY);
	Triangles.Reserve((NumVerticesX - 1) * (NumVerticesY - 1) * 6);

	// Initialize random stream
	FRandomStream RandomStream(RandomSeed);

	// Generate vertices
	for (int32 Y = 0; Y < NumVerticesY; Y++)
	{
		for (int32 X = 0; X < NumVerticesX; X++)
		{
			float WorldX = X * GridResolution - (WorldSizeX * 0.5f);
			float WorldY = Y * GridResolution - (WorldSizeY * 0.5f);
			float Height = CalculateTerrainHeight(WorldX, WorldY);

			// Add vertex
			Vertices.Add(FVector(WorldX, WorldY, Height));

			// Add UV
			float U = static_cast<float>(X) / static_cast<float>(NumVerticesX - 1);
			float V = static_cast<float>(Y) / static_cast<float>(NumVerticesY - 1);
			UVs.Add(FVector2D(U * 10.0f, V * 10.0f)); // Scale UVs for tiling

			// Add normal (pointing up for flat terrain)
			Normals.Add(FVector(0.0f, 0.0f, 1.0f));

			// Add vertex color based on height
			uint8 ColorValue = FMath::Clamp(static_cast<int32>(128 + Height), 0, 255);
			VertexColors.Add(FColor(ColorValue, ColorValue, ColorValue, 255));
		}
	}

	// Generate triangles
	for (int32 Y = 0; Y < NumVerticesY - 1; Y++)
	{
		for (int32 X = 0; X < NumVerticesX - 1; X++)
		{
			int32 BottomLeft = Y * NumVerticesX + X;
			int32 BottomRight = BottomLeft + 1;
			int32 TopLeft = (Y + 1) * NumVerticesX + X;
			int32 TopRight = TopLeft + 1;

			// First triangle
			Triangles.Add(BottomLeft);
			Triangles.Add(TopLeft);
			Triangles.Add(BottomRight);

			// Second triangle
			Triangles.Add(BottomRight);
			Triangles.Add(TopLeft);
			Triangles.Add(TopRight);
		}
	}

	// Calculate smooth normals
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVs, Normals, TArray<FProcMeshTangent>());
}

float AWorldGenerator::CalculateTerrainHeight(float X, float Y) const
{
	// Simple Perlin-like noise using sine waves for height variation
	float Height = 0.0f;

	// Add multiple octaves of noise for more natural terrain
	float Frequency = NoiseScale;
	float Amplitude = HeightVariation;

	for (int32 Octave = 0; Octave < 3; Octave++)
	{
		Height += FMath::Sin(X * Frequency) * FMath::Cos(Y * Frequency) * Amplitude;
		Frequency *= 2.0f;
		Amplitude *= 0.5f;
	}

	return Height;
}
