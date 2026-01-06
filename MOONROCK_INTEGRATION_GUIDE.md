# Moonrock Procedural Biomes Integration Guide

This guide explains how to integrate the **Moonrock Procedural Biomes** asset from Fab marketplace into the Stone and Sword planetary world generation system.

## Overview

The WorldGenerator has been designed with a planetary continental biome system that can be enhanced with the Moonrock Procedural Biomes asset for more detailed and realistic biome generation.

## Prerequisites

1. **Purchase/Download Moonrock Procedural Biomes** from Fab marketplace:
   - Listing ID: `4f985bab-2930-4cd9-b0a0-29c5fc2ec1f2`
   - Available at: https://www.fab.com/

2. **Unreal Engine 5.6** or later

3. **Stone and Sword project** with the latest WorldGenerator implementation

## Installation Steps

### Step 1: Acquire the Asset

1. Open Unreal Engine 5.6
2. Go to **Window > Fab** (or click **Get Content** in Content Browser)
3. Search for "Moonrock Procedural Biomes" or use listing ID: `4f985bab-2930-4cd9-b0a0-29c5fc2ec1f2`
4. Purchase/Download the asset
5. Add to your project

### Step 2: Import into Project

1. The asset will be downloaded to your project's `Content` folder
2. Verify the Moonrock plugin/content appears in your Content Browser
3. Check for any required dependencies or setup instructions from the asset documentation

### Step 3: Update Build Configuration

If Moonrock is a plugin, add it to your `StoneAndSword.Build.cs`:

```csharp
PublicDependencyModuleNames.AddRange(new string[] { 
    "Core", 
    "CoreUObject", 
    "Engine", 
    "InputCore",
    "ProceduralMeshComponent",
    "Landscape",
    "MoonrockBiomes"  // Add this if it's a code plugin
});
```

## Integration Options

### Option 1: Use Moonrock for Biome Detail (Recommended)

Keep the WorldGenerator for large-scale planetary biome distribution, and use Moonrock for detailed biome characteristics:

```cpp
// In WorldGenerator.h, add:
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes")
TObjectPtr<UObject> MoonrockBiomeGenerator;  // Reference to Moonrock system

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planetary Biomes")
bool bUseMoonrockForDetails;
```

```cpp
// In WorldGenerator.cpp, modify ApplyBiomeModifiers:
float AWorldGenerator::ApplyBiomeModifiers(float BaseHeight, float X, float Y, EBiomeType BiomeType) const
{
    // Get base biome characteristics
    FBiomeData BiomeData = GetBiomeData(BiomeType);
    float ModifiedHeight = (BaseHeight * BiomeData.HeightMultiplier) + BiomeData.BaseHeightOffset;
    
    // If Moonrock is enabled, use it for fine detail
    if (bUseMoonrockForDetails && MoonrockBiomeGenerator)
    {
        // Call Moonrock's biome detail generation here
        // This will depend on Moonrock's API
        // ModifiedHeight = MoonrockBiomeGenerator->GenerateDetail(X, Y, BiomeType, ModifiedHeight);
    }
    
    // Apply terrain roughness
    if (BiomeData.TerrainRoughness > 1.0f)
    {
        FVector RoughnessSample = FVector(X * 0.05f, Y * 0.05f, RandomSeed * 0.5f);
        float RoughnessNoise = FMath::PerlinNoise3D(RoughnessSample);
        ModifiedHeight += RoughnessNoise * 20.0f * (BiomeData.TerrainRoughness - 1.0f);
    }
    
    return ModifiedHeight;
}
```

### Option 2: Use Moonrock for Complete Biome Generation

Replace the current biome system with Moonrock's generation:

1. Disable `bEnablePlanetaryBiomes` in WorldGenerator
2. Use Moonrock's biome generator as the primary system
3. Keep WorldGenerator's base terrain structure

### Option 3: Hybrid Approach

Use WorldGenerator for terrain shape and Moonrock for biome-specific features (vegetation, materials, props):

- WorldGenerator generates the base terrain mesh with height and basic colors
- Moonrock adds biome-specific vegetation, rocks, materials, and environmental details
- Spawn Moonrock biome actors/components based on the biome type at each location

## Biome Type Mapping

Map Stone and Sword biome types to Moonrock biome types:

| Stone & Sword Biome | Suggested Moonrock Equivalent |
|---------------------|-------------------------------|
| TropicalJungle      | Tropical/Rainforest biome     |
| TemperateForest     | Temperate Forest biome        |
| BorealTaiga         | Taiga/Boreal Forest biome     |
| Grasslands          | Plains/Grassland biome        |
| Savanna             | Savanna biome                 |
| Desert              | Desert/Dunes biome            |
| Tundra              | Tundra biome                  |
| ArcticSnow          | Arctic/Snow biome             |
| Mountains           | Mountain/Alpine biome         |
| VolcanicWasteland   | Volcanic/Lava biome           |
| Swampland           | Swamp/Wetland biome           |
| RockyBadlands       | Badlands/Canyon biome         |

## Usage in Editor

### Configure Planetary Biomes

1. Place a **WorldGenerator** actor in your level
2. In the Details panel, expand **Planetary Biomes** section
3. Enable **bEnablePlanetaryBiomes**
4. Adjust noise scales:
   - **Temperature Noise Scale**: 0.002 (controls temperature variation)
   - **Moisture Noise Scale**: 0.003 (controls rainfall patterns)
   - **Continental Scale**: 0.001 (controls continent size)
   - **Biome Blend Factor**: 0.3 (controls transition smoothness)

### Add Moonrock Integration

1. If using Option 1, assign Moonrock generator to **MoonrockBiomeGenerator** property
2. Enable **bUseMoonrockForDetails**
3. Configure Moonrock-specific settings per their documentation

### Test Generation

1. Press **Play** in editor
2. The world will generate with planetary biomes
3. Walk around to see different biome continents
4. Observe biome transitions and Moonrock details

## Blueprint Integration

You can also integrate Moonrock using Blueprints:

1. Create a Blueprint that derives from `AWorldGenerator`
2. Override `ApplyBiomeModifiers` or `BlendBiomeEffects` in Blueprint
3. Call Moonrock Blueprint functions to add biome details
4. Use the Blueprint in your level instead of the C++ WorldGenerator

## Performance Considerations

- **Chunk-based generation**: For large planets, consider generating terrain in chunks
- **Level streaming**: Use Unreal's level streaming for distant biomes
- **LOD**: Implement level-of-detail for distant terrain
- **Moonrock settings**: Adjust Moonrock's detail levels based on performance needs

## Troubleshooting

### Asset Not Found
- Verify Moonrock is downloaded and appears in Content Browser
- Check project dependencies in `.uproject` file
- Restart Unreal Editor

### Build Errors
- Ensure Moonrock module is added to `StoneAndSword.Build.cs` if it's a code plugin
- Regenerate Visual Studio project files
- Clean and rebuild the project

### Biomes Not Generating
- Check `bEnablePlanetaryBiomes` is enabled
- Verify noise scales are set correctly (very small values like 0.001-0.003)
- Check WorldSizeX and WorldSizeY are large enough (10,000+ recommended)

### Performance Issues
- Increase `GridResolution` for fewer vertices
- Reduce `NoiseOctaves` for simpler terrain
- Disable Moonrock details for testing
- Use World Partition or Level Streaming for very large worlds

## Further Customization

### Custom Biome Logic

You can create custom biome assignment logic:

```cpp
// Override in your derived class
EBiomeType AMyWorldGenerator::DetermineBiomeAtPosition(float X, float Y) const
{
    // Your custom logic here
    // Could use Moonrock's biome selection if available
    return EBiomeType::Grasslands;
}
```

### Material Integration

Moonrock likely includes materials. Apply them based on biome:

```cpp
void AWorldGenerator::GenerateWorld()
{
    // After generating mesh...
    if (bUseMoonrockForDetails)
    {
        // Apply Moonrock materials based on biome at each section
        // This depends on Moonrock's API
    }
}
```

## Support

- **Moonrock Asset Support**: Check Moonrock's documentation or contact the asset creator on Fab
- **Stone and Sword Integration**: Open an issue on the GitHub repository
- **Unreal Engine**: https://docs.unrealengine.com/

## Notes

- The exact integration method will depend on Moonrock's specific API and features
- This guide provides a framework; adjust based on Moonrock's actual implementation
- Test performance with Moonrock enabled, as procedural biomes can be intensive
- Consider using Moonrock primarily for close-range detail and WorldGenerator for distant terrain

## Example Configuration

**For a balanced planetary world with Moonrock:**

```
WorldSizeX: 50000
WorldSizeY: 50000
GridResolution: 200
HeightVariation: 100
NoiseOctaves: 4
TemperatureNoiseScale: 0.002
MoistureNoiseScale: 0.003
ContinentalScale: 0.001
BiomeBlendFactor: 0.3
bEnablePlanetaryBiomes: true
bUseMoonrockForDetails: true
```

This creates a large planet (50km x 50km) with smooth continental biomes and Moonrock detail enhancement.
