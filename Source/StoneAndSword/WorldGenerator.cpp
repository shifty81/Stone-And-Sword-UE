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
	NoiseOctaves = 4;
	NoisePersistence = 0.5f;
	NoiseLacunarity = 2.0f;
	RandomSeed = 12345;
	bAutoGenerateOnBeginPlay = true;
	TerrainMaterial = nullptr;

	// Biome settings for huge world maps
	CurrentBiome = EBiomeType::Grasslands;
	BiomeWorldSizeMultiplier = 3.0f;  // Makes biomes 3x larger by default
	bUseBiomeSpecificGeneration = true;

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

	// Get current biome data
	FBiomeData BiomeData = GetBiomeData(CurrentBiome);

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

			// Add vertex color based on biome color and height
			FLinearColor BaseColor = BiomeData.BiomeColor;
			float HeightFactor = FMath::Clamp((Height + 100.0f) / 200.0f, 0.0f, 1.0f);
			FLinearColor FinalColor = BaseColor * (0.5f + HeightFactor * 0.5f);
			VertexColors.Add(FinalColor.ToFColor(false));
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
	TArray<FProcMeshTangent> Tangents;
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVs, Normals, Tangents);
}

float AWorldGenerator::CalculateTerrainHeight(float X, float Y) const
{
	// Use Perlin noise with multiple octaves for realistic terrain generation
	// This implements Fractional Brownian Motion (fBM) for natural-looking landscapes
	
	// Constants for seed offset calculation (using prime numbers for better distribution)
	static constexpr float PRIME_MULTIPLIER_X = 0.1031f;
	static constexpr float PRIME_MULTIPLIER_Y = 0.1030f;
	static constexpr float PRIME_MULTIPLIER_Z = 0.0973f;
	static constexpr float OCTAVE_OFFSET_SPACING = 100.0f;
	
	float Height = 0.0f;
	float Amplitude = HeightVariation;
	float Frequency = NoiseScale;
	float MaxValue = 0.0f; // Used for normalization

	// Apply random seed offset to make different seeds produce different terrain
	const float SeedOffsetX = RandomSeed * PRIME_MULTIPLIER_X;
	const float SeedOffsetY = RandomSeed * PRIME_MULTIPLIER_Y;
	const float SeedOffsetZ = RandomSeed * PRIME_MULTIPLIER_Z;

	// Add multiple octaves of Perlin noise
	for (int32 Octave = 0; Octave < NoiseOctaves; Octave++)
	{
		// Sample 3D Perlin noise (using Z=0 for 2D-like terrain)
		// Add octave-specific offset for variation between octaves
		FVector SamplePos = FVector(
			X * Frequency + SeedOffsetX + Octave * OCTAVE_OFFSET_SPACING,
			Y * Frequency + SeedOffsetY + Octave * OCTAVE_OFFSET_SPACING,
			SeedOffsetZ + Octave * OCTAVE_OFFSET_SPACING
		);
		float NoiseValue = FMath::PerlinNoise3D(SamplePos);
		
		// PerlinNoise3D returns values roughly in [-1, 1], so we don't need additional scaling
		Height += NoiseValue * Amplitude;
		MaxValue += Amplitude;

		// Prepare for next octave
		Amplitude *= NoisePersistence;  // Each octave has less impact
		Frequency *= NoiseLacunarity;   // Each octave has higher frequency (more detail)
	}

	// Normalize to keep the height variation within expected range
	if (MaxValue > 0.0f)
	{
		Height = (Height / MaxValue) * HeightVariation;
	}

	// Apply biome-specific modifiers if enabled
	if (bUseBiomeSpecificGeneration)
	{
		Height = ApplyBiomeModifiers(Height, X, Y);
	}

	return Height;
}

FBiomeData AWorldGenerator::GetBiomeData(EBiomeType BiomeType) const
{
	// Define characteristics for each of the 12 biome types
	// Each biome is designed to be a huge, distinct world area
	switch (BiomeType)
	{
		case EBiomeType::TropicalJungle:
			return FBiomeData(TEXT("Tropical Jungle"), 1.5f, FLinearColor(0.1f, 0.6f, 0.2f), 0.0f, 2.0f, TEXT("TropicalJungle"));
		
		case EBiomeType::TemperateForest:
			return FBiomeData(TEXT("Temperate Forest"), 1.2f, FLinearColor(0.3f, 0.7f, 0.3f), 0.0f, 1.5f, TEXT("TemperateForest"));
		
		case EBiomeType::BorealTaiga:
			return FBiomeData(TEXT("Boreal Taiga"), 1.0f, FLinearColor(0.2f, 0.5f, 0.3f), 0.0f, 1.3f, TEXT("BorealTaiga"));
		
		case EBiomeType::Grasslands:
			return FBiomeData(TEXT("Grasslands"), 0.5f, FLinearColor(0.4f, 0.8f, 0.3f), 0.0f, 0.5f, TEXT("Grasslands"));
		
		case EBiomeType::Savanna:
			return FBiomeData(TEXT("Savanna"), 0.8f, FLinearColor(0.7f, 0.7f, 0.3f), 0.0f, 1.0f, TEXT("Savanna"));
		
		case EBiomeType::Desert:
			return FBiomeData(TEXT("Desert"), 1.2f, FLinearColor(0.9f, 0.8f, 0.5f), 0.0f, 1.8f, TEXT("Desert"));
		
		case EBiomeType::Tundra:
			return FBiomeData(TEXT("Tundra"), 0.6f, FLinearColor(0.6f, 0.7f, 0.7f), 0.0f, 0.8f, TEXT("Tundra"));
		
		case EBiomeType::ArcticSnow:
			return FBiomeData(TEXT("Arctic Snow"), 1.5f, FLinearColor(0.9f, 0.95f, 1.0f), 50.0f, 2.0f, TEXT("ArcticSnow"));
		
		case EBiomeType::Mountains:
			return FBiomeData(TEXT("Mountains"), 3.0f, FLinearColor(0.5f, 0.5f, 0.5f), 100.0f, 3.0f, TEXT("Mountains"));
		
		case EBiomeType::VolcanicWasteland:
			return FBiomeData(TEXT("Volcanic Wasteland"), 2.5f, FLinearColor(0.4f, 0.2f, 0.1f), 20.0f, 2.5f, TEXT("VolcanicWasteland"));
		
		case EBiomeType::Swampland:
			return FBiomeData(TEXT("Swampland"), 0.4f, FLinearColor(0.3f, 0.4f, 0.3f), -20.0f, 1.2f, TEXT("Swampland"));
		
		case EBiomeType::RockyBadlands:
			return FBiomeData(TEXT("Rocky Badlands"), 2.0f, FLinearColor(0.6f, 0.4f, 0.3f), 30.0f, 2.2f, TEXT("RockyBadlands"));
		
		default:
			return FBiomeData(TEXT("Default"), 1.0f, FLinearColor::White, 0.0f, 1.0f, TEXT("Default"));
	}
}

float AWorldGenerator::ApplyBiomeModifiers(float BaseHeight, float X, float Y) const
{
	FBiomeData BiomeData = GetBiomeData(CurrentBiome);
	
	// Apply biome-specific height multiplier and base offset
	float ModifiedHeight = (BaseHeight * BiomeData.HeightMultiplier) + BiomeData.BaseHeightOffset;
	
	// Apply terrain roughness (affects the character of the terrain)
	if (BiomeData.TerrainRoughness > 1.0f)
	{
		// Add additional high-frequency noise for rough biomes (mountains, volcanic, etc.)
		FVector RoughnessSample = FVector(X * 0.05f, Y * 0.05f, RandomSeed * 0.5f);
		float RoughnessNoise = FMath::PerlinNoise3D(RoughnessSample);
		ModifiedHeight += RoughnessNoise * 20.0f * (BiomeData.TerrainRoughness - 1.0f);
	}
	
	return ModifiedHeight;
}
