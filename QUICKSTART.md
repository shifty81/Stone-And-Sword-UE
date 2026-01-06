# Quick Start Guide

This guide will help you quickly get started building and running the Stone and Sword standalone Windows game application.

## Prerequisites

Before you begin, ensure you have:

1. **Unreal Engine 5.6.1** installed from Epic Games Launcher
2. **Visual Studio 2022** (Windows) with C++ development tools
3. **Git** for version control
4. **Windows operating system**

## Step-by-Step Setup

### 1. Clone the Repository

```bash
git clone https://github.com/shifty81/Stone-And-Sword-UE.git
cd Stone-And-Sword-UE
```

### 2. Generate Project Files

**Windows:**
- Right-click on `StoneAndSword.uproject`
- Select "Generate Visual Studio project files"
- Wait for the process to complete

### 3. Build the Project

**Option A: Using Visual Studio (Windows)**
1. Open `StoneAndSword.sln`
2. Select "Development" or "Shipping" configuration
3. Set "StoneAndSword" as the startup project
4. Press F5 or click "Local Windows Debugger" to build and run

**Option B: Using Command Line**
```bash
# Windows
"C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles\Build.bat" StoneAndSword Win64 Development -Project="StoneAndSword.uproject"
```

### 4. Run the Game

**Standalone Application:**
After building successfully:
- Run from Visual Studio by pressing F5
- Or find the executable in `Binaries/Win64/StoneAndSword.exe` and double-click to run

**Testing in Unreal Editor (Optional):**
- Double-click `StoneAndSword.uproject` to open the Unreal Editor
- Press Play (Alt+P) to test the game
- Use "Package Project > Windows" to create a distributable build

## Running Your First Game

**Automatic World Generation:**

When you run the standalone game application:

1. The game launches automatically
2. The world generator creates the procedural terrain
3. The player character spawns in the world
4. You can immediately start playing!

**Controls:**
- **WASD**: Move around
- **Mouse**: Look around
- **Spacebar**: Jump
- **ESC**: Quit game

**Testing Different Worlds (Using Editor):**

If you want to customize the world before building:

1. Open the project in the Unreal Editor
2. Create a new level or open an existing one
3. Add actors and configure settings
4. Save the level
5. Rebuild the game to include your changes

**Advanced Customization (Manual Setup):**

For developers who want full control over the world:

### 1. Create a New Level

1. In the editor, go to **File > New Level**
2. Select "Empty Level"
3. Save it as `MainWorld` in `Content/Maps/`

### 2. Add Basic Lighting

1. In the Place Actors panel, search for "Directional Light"
2. Drag it into the level
3. Position it above the origin (0, 0, 1000)
4. Set rotation to (-50, 0, 0) for nice lighting angle

### 3. Add Sky

1. Search for "Sky Atmosphere" in Place Actors
2. Drag it into the level
3. Search for "Sky Light" and add it
4. In Sky Light details, click "Recapture Scene"

### 4. Add the World Generator

1. In Place Actors panel, search for "WorldGenerator"
2. Drag the WorldGenerator actor into the level
3. In the Details panel, configure:
   - **World Size X**: 10000 (10km)
   - **World Size Y**: 10000 (10km)
   - **Grid Resolution**: 100 (distance between vertices)
   - **Height Variation**: 50 (slight undulation)
   - **Auto Generate On Begin Play**: ✓ (checked)

### 5. Add Player Start

1. Search for "Player Start" in Place Actors
2. Drag it into the level
3. Position it at (0, 0, 200) - above where the terrain will be

### 6. Test Your World

1. Click the **Play** button in the toolbar
2. You should see a flat terrain generated
3. Use **WASD** to move around
4. Use **Mouse** to look around
5. Press **Spacebar** to jump

## Building for Distribution

### Creating a Standalone Executable

1. Open the project in Unreal Engine 5.6.1
2. Go to **File > Package Project > Windows > Windows (64-bit)**
3. Choose an output directory
4. Wait for packaging to complete (this may take several minutes)
5. Find the executable in the output directory
6. Distribute the entire packaged folder to end users

### Build Configurations

- **Development**: For testing with debugging capabilities
- **DebugGame**: For deep debugging with full symbols
- **Shipping**: For final release (optimized, smallest size, no debug features)

## Customizing the Game

### Modifying Game Code

1. Open the project in Visual Studio
2. Edit C++ files in `Source/StoneAndSword/`
3. Rebuild the project
4. Run the game to test your changes
5. Package for distribution when ready

### Creating Materials (Optional)

If you want to customize materials using the editor:

1. Open the project in Unreal Editor
2. In Content Browser, navigate to `Content/Materials`
3. Right-click and select **Material**
4. Name it `M_Terrain`
5. Open the material editor
6. Add nodes:
   - Texture Sample (T_Grass)
   - Connect to Base Color
7. Save and compile

### Apply Material to World Generator (Optional)

To apply custom materials:

1. Open the level in Unreal Editor
2. Select the WorldGenerator in the level
3. In Details panel, find "Terrain Material"
4. Select `M_Terrain`
5. Rebuild and run the game to see textured terrain

## Adjusting Game Settings

### Terrain Configuration

Edit settings in WorldGenerator class or via the editor:
- **World Size**: Increase for larger worlds
- **Grid Resolution**: Decrease for more detail (warning: affects performance)
- **Height Variation**: Increase for more dramatic terrain
- **Noise Scale**: Controls the overall scale/frequency of terrain features
- **Noise Octaves**: Number of noise layers (1-8, more = more detail, default: 4)
- **Noise Persistence**: How much each octave contributes (0.1-1.0, default: 0.5)
- **Noise Lacunarity**: Frequency multiplier between octaves (1.0-4.0, default: 2.0)
- **Random Seed**: Change to generate different terrain layouts

**Perlin Noise Parameters:**
The terrain uses proper Perlin noise (Fractional Brownian Motion) for realistic landscapes:
- Higher octaves add more fine detail but may impact performance
- Lower persistence creates smoother terrain
- Higher lacunarity creates more varied, rougher terrain

**Biome System (NEW):**
Choose from 12 distinct biome types for huge world maps:
- **Current Biome**: Select which biome to generate (Tropical Jungle, Temperate Forest, Boreal Taiga, Grasslands, Savanna, Desert, Tundra, Arctic Snow, Mountains, Volcanic Wasteland, Swampland, Rocky Badlands)
- **Biome World Size Multiplier**: Makes biomes larger (1.0-10.0x, default: 3.0x)
- **Use Biome Specific Generation**: Enables biome-specific terrain modifiers

Each biome is designed as a huge, separate world map/scene. Players traverse between biomes using boat/ferry systems (to be implemented in gameplay).

### Character Settings

Modify character behavior in WorldPlayerCharacter class:
- Movement speed: Edit `MaxWalkSpeed` in Character Movement component
- Camera distance: Edit `TargetArmLength` in Camera Boom
- Jump height: Edit `JumpZVelocity` in Character Movement component

## Common Issues

### Build Errors

**Issue**: Missing ProceduralMeshComponent module
**Solution**: Ensure the ProceduralMeshComponent plugin is enabled in the .uproject file

**Issue**: Cannot generate project files
**Solution**: Verify UE 5.6.1 is installed and associated with .uproject files

### Runtime Issues

**Issue**: No terrain appears
**Solution**: 
- Check WorldGenerator is in the level
- Verify "Auto Generate On Begin Play" is checked
- Check Output Log for errors

**Issue**: Character falls through terrain
**Solution**: 
- Ensure Player Start is above terrain (Z > 100)
- Verify ProceduralMesh has collision enabled
- Check collision settings in WorldGenerator

**Issue**: Cannot move character
**Solution**: 
- Verify input mappings in Project Settings > Input
- Check that WorldPlayerCharacter is set as default pawn

## Next Steps

1. **Add More Detail**: Modify WorldGenerator.cpp to add more complex terrain features
2. **Create Biomes**: Implement different terrain types (forests, deserts, mountains)
3. **Add Vegetation**: Create a vegetation spawning system
4. **Implement LOD**: Add level-of-detail for large worlds
5. **Add Game Mechanics**: Implement combat, inventory, quests, etc.
6. **Optimize Performance**: Add culling, streaming, and chunk loading

## Resources

- [Unreal Engine Documentation](https://docs.unrealengine.com/)
- [Procedural Mesh Component Guide](https://docs.unrealengine.com/5.6/en-US/API/Plugins/ProceduralMeshComponent/)
- [C++ Programming Guide](https://docs.unrealengine.com/5.6/en-US/unreal-engine-cpp-quick-start/)

## Getting Help

If you encounter issues:
1. Check the Output Log in the editor (Window > Developer Tools > Output Log)
2. Review the README.md for project structure
3. Check MATERIALS.md for material setup guidance
4. Open an issue on GitHub with detailed error information

Happy game development!
