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

	// Planetary biome settings for continuous world with continental biomes
	bEnablePlanetaryBiomes = true;
	TemperatureNoiseScale = 0.002f;  // Large-scale temperature gradients
	MoistureNoiseScale = 0.003f;     // Large-scale moisture patterns
	ContinentalScale = 0.001f;       // Very large continental formations
	BiomeBlendFactor = 0.3f;         // Smooth transitions between biomes

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

	// Generate vertices with planetary biome blending
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

			// Determine biome and color for this position
			FLinearColor VertexColor = FLinearColor::White;
			if (bEnablePlanetaryBiomes)
			{
				BlendBiomeEffects(WorldX, WorldY, Height, VertexColor);
			}
			else
			{
				// Default coloring based on height
				float HeightFactor = FMath::Clamp((Height + 100.0f) / 200.0f, 0.0f, 1.0f);
				VertexColor = FLinearColor(0.4f, 0.8f, 0.3f) * (0.5f + HeightFactor * 0.5f);
			}
			
			VertexColors.Add(VertexColor.ToFColor(false));
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

	// Apply planetary biome-specific modifiers if enabled
	if (bEnablePlanetaryBiomes)
	{
		EBiomeType BiomeAtPos = DetermineBiomeAtPosition(X, Y);
		Height = ApplyBiomeModifiers(Height, X, Y, BiomeAtPos);
	}

	return Height;
}

FBiomeData AWorldGenerator::GetBiomeData(EBiomeType BiomeType) const
{
	// Define characteristics for each of the 12 biome types
	// Each biome represents a continental region on the planet
	switch (BiomeType)
	{
		case EBiomeType::TropicalJungle:
			return FBiomeData(TEXT("Tropical Jungle"), 1.5f, FLinearColor(0.1f, 0.6f, 0.2f), 0.0f, 2.0f);
		
		case EBiomeType::TemperateForest:
			return FBiomeData(TEXT("Temperate Forest"), 1.2f, FLinearColor(0.3f, 0.7f, 0.3f), 0.0f, 1.5f);
		
		case EBiomeType::BorealTaiga:
			return FBiomeData(TEXT("Boreal Taiga"), 1.0f, FLinearColor(0.2f, 0.5f, 0.3f), 0.0f, 1.3f);
		
		case EBiomeType::Grasslands:
			return FBiomeData(TEXT("Grasslands"), 0.5f, FLinearColor(0.4f, 0.8f, 0.3f), 0.0f, 0.5f);
		
		case EBiomeType::Savanna:
			return FBiomeData(TEXT("Savanna"), 0.8f, FLinearColor(0.7f, 0.7f, 0.3f), 0.0f, 1.0f);
		
		case EBiomeType::Desert:
			return FBiomeData(TEXT("Desert"), 1.2f, FLinearColor(0.9f, 0.8f, 0.5f), 0.0f, 1.8f);
		
		case EBiomeType::Tundra:
			return FBiomeData(TEXT("Tundra"), 0.6f, FLinearColor(0.6f, 0.7f, 0.7f), 0.0f, 0.8f);
		
		case EBiomeType::ArcticSnow:
			return FBiomeData(TEXT("Arctic Snow"), 1.5f, FLinearColor(0.9f, 0.95f, 1.0f), 50.0f, 2.0f);
		
		case EBiomeType::Mountains:
			return FBiomeData(TEXT("Mountains"), 3.0f, FLinearColor(0.5f, 0.5f, 0.5f), 100.0f, 3.0f);
		
		case EBiomeType::VolcanicWasteland:
			return FBiomeData(TEXT("Volcanic Wasteland"), 2.5f, FLinearColor(0.4f, 0.2f, 0.1f), 20.0f, 2.5f);
		
		case EBiomeType::Swampland:
			return FBiomeData(TEXT("Swampland"), 0.4f, FLinearColor(0.3f, 0.4f, 0.3f), -20.0f, 1.2f);
		
		case EBiomeType::RockyBadlands:
			return FBiomeData(TEXT("Rocky Badlands"), 2.0f, FLinearColor(0.6f, 0.4f, 0.3f), 30.0f, 2.2f);
		
		default:
			return FBiomeData(TEXT("Default"), 1.0f, FLinearColor::White, 0.0f, 1.0f);
	}
}

EBiomeType AWorldGenerator::DetermineBiomeAtPosition(float X, float Y) const
{
	// Temperature and moisture thresholds for biome classification
	static constexpr float TEMP_VERY_COLD = 0.2f;
	static constexpr float TEMP_COOL = 0.4f;
	static constexpr float TEMP_MODERATE = 0.6f;
	static constexpr float TEMP_WARM = 0.8f;
	
	static constexpr float MOISTURE_DRY = 0.3f;
	static constexpr float MOISTURE_MODERATE = 0.4f;
	static constexpr float MOISTURE_HUMID = 0.6f;
	static constexpr float MOISTURE_WET = 0.7f;

	// Calculate temperature and moisture at this position
	float Temperature = CalculateTemperature(X, Y);
	float Moisture = CalculateMoisture(X, Y);

	// Use temperature-moisture matrix to determine biome
	// Temperature: 0 (cold) to 1 (hot)
	// Moisture: 0 (dry) to 1 (wet)
	
	// Special case: Check for extreme terrain (Mountains and Rocky Badlands)
	// Sample additional noise to determine if this area should be mountainous
	FVector MountainSample = FVector(X * ContinentalScale * 2.0f, Y * ContinentalScale * 2.0f, RandomSeed * 2.0f);
	float MountainNoise = FMath::PerlinNoise3D(MountainSample);
	
	// Mountains can appear anywhere but more likely at continental boundaries (high noise values)
	if (MountainNoise > 0.6f)
	{
		return EBiomeType::Mountains;
	}
	
	// Rocky Badlands appear in hot, dry regions with moderate mountain noise
	if (Temperature > TEMP_WARM && Moisture < MOISTURE_DRY && MountainNoise > 0.3f)
	{
		return EBiomeType::RockyBadlands;
	}

	if (Temperature < TEMP_VERY_COLD)
	{
		// Cold regions
		if (Moisture < MOISTURE_DRY) return EBiomeType::Tundra;
		else return EBiomeType::ArcticSnow;
	}
	else if (Temperature < TEMP_COOL)
	{
		// Cool temperate
		if (Moisture < MOISTURE_DRY) return EBiomeType::Grasslands;
		else if (Moisture < MOISTURE_WET) return EBiomeType::BorealTaiga;
		else return EBiomeType::Swampland;
	}
	else if (Temperature < TEMP_MODERATE)
	{
		// Moderate temperate
		if (Moisture < MOISTURE_MODERATE) return EBiomeType::Grasslands;
		else if (Moisture < MOISTURE_WET) return EBiomeType::TemperateForest;
		else return EBiomeType::Swampland;
	}
	else if (Temperature < TEMP_WARM)
	{
		// Warm
		if (Moisture < MOISTURE_DRY) return EBiomeType::Desert;
		else if (Moisture < MOISTURE_HUMID) return EBiomeType::Savanna;
		else return EBiomeType::TropicalJungle;
	}
	else
	{
		// Hot
		if (Moisture < MOISTURE_MODERATE) return EBiomeType::VolcanicWasteland;
		else if (Moisture < MOISTURE_WET) return EBiomeType::Savanna;
		else return EBiomeType::TropicalJungle;
	}
	
	// Safety fallback (should never reach here due to exhaustive if-else chain above)
	return EBiomeType::Grasslands;
}

float AWorldGenerator::CalculateTemperature(float X, float Y) const
{
	// Use large-scale noise for continental temperature patterns
	FVector TempSample = FVector(X * TemperatureNoiseScale, Y * TemperatureNoiseScale, RandomSeed * 0.7f);
	float TempNoise = FMath::PerlinNoise3D(TempSample);
	
	// Convert from [-1, 1] to [0, 1]
	float Temperature = (TempNoise + 1.0f) * 0.5f;
	
	// Add latitude-based gradient (colder towards edges, warmer in middle)
	float NormalizedY = FMath::Abs(Y / WorldSizeY);
	float LatitudeEffect = 1.0f - FMath::Pow(NormalizedY, 2.0f);
	Temperature = Temperature * 0.6f + LatitudeEffect * 0.4f;
	
	return FMath::Clamp(Temperature, 0.0f, 1.0f);
}

float AWorldGenerator::CalculateMoisture(float X, float Y) const
{
	// Use large-scale noise for continental moisture patterns
	FVector MoistureSample = FVector(X * MoistureNoiseScale, Y * MoistureNoiseScale, RandomSeed * 1.3f);
	float MoistureNoise = FMath::PerlinNoise3D(MoistureSample);
	
	// Convert from [-1, 1] to [0, 1]
	float Moisture = (MoistureNoise + 1.0f) * 0.5f;
	
	return FMath::Clamp(Moisture, 0.0f, 1.0f);
}

float AWorldGenerator::ApplyBiomeModifiers(float BaseHeight, float X, float Y, EBiomeType BiomeType) const
{
	// Constants for terrain roughness calculation
	static constexpr float ROUGHNESS_NOISE_SCALE_X = 0.05f;
	static constexpr float ROUGHNESS_NOISE_SCALE_Y = 0.05f;
	static constexpr float ROUGHNESS_SEED_MULTIPLIER = 0.5f;
	static constexpr float ROUGHNESS_HEIGHT_MULTIPLIER = 20.0f;

	FBiomeData BiomeData = GetBiomeData(BiomeType);
	
	// Apply biome-specific height multiplier and base offset
	float ModifiedHeight = (BaseHeight * BiomeData.HeightMultiplier) + BiomeData.BaseHeightOffset;
	
	// Apply terrain roughness (affects the character of the terrain)
	if (BiomeData.TerrainRoughness > 1.0f)
	{
		// Add additional high-frequency noise for rough biomes (mountains, volcanic, etc.)
		FVector RoughnessSample = FVector(
			X * ROUGHNESS_NOISE_SCALE_X, 
			Y * ROUGHNESS_NOISE_SCALE_Y, 
			RandomSeed * ROUGHNESS_SEED_MULTIPLIER
		);
		float RoughnessNoise = FMath::PerlinNoise3D(RoughnessSample);
		ModifiedHeight += RoughnessNoise * ROUGHNESS_HEIGHT_MULTIPLIER * (BiomeData.TerrainRoughness - 1.0f);
	}
	
	return ModifiedHeight;
}

void AWorldGenerator::BlendBiomeEffects(float X, float Y, float& Height, FLinearColor& Color) const
{
	// Determine primary biome at this position
	EBiomeType PrimaryBiome = DetermineBiomeAtPosition(X, Y);
	FBiomeData PrimaryData = GetBiomeData(PrimaryBiome);
	
	// Apply biome color based on height
	float HeightFactor = FMath::Clamp((Height + 100.0f) / 200.0f, 0.0f, 1.0f);
	Color = PrimaryData.BiomeColor * (0.5f + HeightFactor * 0.5f);
	
	// Apply biome blending for smooth transitions
	if (BiomeBlendFactor > 0.0f)
	{
		// Sample distance for blending calculation
		static constexpr float BLEND_SAMPLE_DISTANCE = 500.0f;
		
		// Sample neighboring positions to detect biome transitions
		TArray<FVector2D> SampleOffsets = {
			FVector2D(BLEND_SAMPLE_DISTANCE, 0.0f),
			FVector2D(-BLEND_SAMPLE_DISTANCE, 0.0f),
			FVector2D(0.0f, BLEND_SAMPLE_DISTANCE),
			FVector2D(0.0f, -BLEND_SAMPLE_DISTANCE)
		};
		
		FLinearColor BlendedColor = PrimaryData.BiomeColor;
		int32 DifferentBiomeCount = 0;
		
		// Check neighboring biomes
		for (const FVector2D& Offset : SampleOffsets)
		{
			EBiomeType NeighborBiome = DetermineBiomeAtPosition(X + Offset.X, Y + Offset.Y);
			if (NeighborBiome != PrimaryBiome)
			{
				FBiomeData NeighborData = GetBiomeData(NeighborBiome);
				BlendedColor += NeighborData.BiomeColor;
				DifferentBiomeCount++;
			}
		}
		
		// If we're near a biome boundary, blend the colors
		if (DifferentBiomeCount > 0)
		{
			float BlendWeight = BiomeBlendFactor * (static_cast<float>(DifferentBiomeCount) / SampleOffsets.Num());
			BlendedColor = BlendedColor / (DifferentBiomeCount + 1);  // Average colors
			Color = FMath::Lerp(PrimaryData.BiomeColor, BlendedColor, BlendWeight);
			Color = Color * (0.5f + HeightFactor * 0.5f);  // Reapply height-based shading
		}
	}
}
