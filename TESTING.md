# Testing the World Generation System

This document explains how to quickly test the procedurally generated world in Stone and Sword.

## Quick Start (Automatic Setup)

The project now includes an **automatic world setup system** that makes testing incredibly easy:

### Option 1: Using the Default Empty Level

1. Open the Unreal Editor by double-clicking `StoneAndSword.uproject`
2. When prompted to create a new level or if no level is open:
   - Go to **File > New Level**
   - Select **Empty Level**
   - Click **Create**
3. Press the **Play** button (or press Alt+P)
4. The world will automatically:
   - Spawn a WorldGenerator with default settings
   - Create directional lighting
   - Setup sky atmosphere and skylight
   - Generate a 10km x 10km terrain
   - Spawn your character at the origin

That's it! You can now explore the world with:
- **WASD**: Move around
- **Mouse**: Look around
- **Spacebar**: Jump

### Option 2: Create Your Own Level

If you want to customize the setup:

1. Open the Unreal Editor
2. Create a new Empty Level (File > New Level > Empty Level)
3. Add a **WorldSetupManager** actor:
   - Open the Place Actors panel (Window > Place Actors)
   - Search for "WorldSetupManager"
   - Drag it into the level
4. Configure the WorldSetupManager in the Details panel:
   - **Auto Setup World**: ✓ (checked)
   - **Spawn World Generator**: ✓ (checked)
   - **Setup Lighting**: ✓ (checked)
   - **Setup Sky**: ✓ (checked)
   - **Default World Size X/Y**: 10000 (or customize)
   - **Default Grid Resolution**: 100 (or customize)
   - **Default Height Variation**: 50 (or customize)
5. Save your level in `Content/Maps/`
6. Press Play to test

### Option 3: Manual Setup (Full Control)

For complete control over your world, follow the manual setup instructions in the main README.md file.

## How It Works

The automatic setup system uses two key components:

### WorldSetupManager
- Automatically spawned by the GameMode when the level starts
- Checks if a WorldGenerator exists; spawns one if not
- Sets up lighting and sky atmosphere
- Configurable to enable/disable specific features

### StoneAndSwordGameModeBase
- Automatically spawns WorldSetupManager at game start
- Sets WorldPlayerCharacter as the default pawn
- Can be configured to disable auto-setup if desired

## Customizing the Default Setup

### Disable Automatic Setup

If you want to disable the automatic world setup:

1. In the World Settings panel (Window > World Settings)
2. Under "Game Mode", find "Auto Spawn World Setup Manager"
3. Uncheck it

Or in C++:
```cpp
// In your custom GameMode class
bAutoSpawnWorldSetupManager = false;
```

### Customize World Parameters

To change the default world generation parameters:

1. Place a WorldSetupManager in your level
2. Adjust the parameters in the Details panel:
   - **Default World Size X/Y**: Terrain dimensions
   - **Default Grid Resolution**: Vertex spacing (lower = more detail)
   - **Default Height Variation**: Terrain undulation height

### Add Your Own WorldGenerator

If you want to use your own WorldGenerator instead of the automatic one:

1. Disable "Spawn World Generator" in WorldSetupManager
2. Manually place a WorldGenerator in your level
3. Configure it as desired

## Troubleshooting

### No Terrain Appears

**Possible causes**:
- WorldSetupManager is not in the level and GameMode auto-spawn is disabled
- WorldGenerator "Auto Generate On Begin Play" is unchecked
- Check the Output Log (Window > Developer Tools > Output Log) for errors

**Solutions**:
- Ensure GameMode has "Auto Spawn World Setup Manager" enabled
- Or manually add WorldSetupManager to your level
- Check WorldGenerator settings in Details panel

### Character Falls Through Terrain

**Possible causes**:
- Player Start is placed too low
- Collision not enabled on ProceduralMesh

**Solutions**:
- Verify Player Start Z position is above 100
- Check WorldGenerator collision settings
- Look for collision-related errors in Output Log

### No Lighting

**Possible causes**:
- WorldSetupManager has "Setup Lighting" disabled
- Existing lights in the level are conflicting

**Solutions**:
- Enable "Setup Lighting" in WorldSetupManager
- Or manually add a Directional Light
- Check if auto-setup is finding existing lights (check Output Log)

### Performance Issues

**Possible causes**:
- Grid Resolution is too low (too many vertices)
- World Size is too large

**Solutions**:
- Increase Grid Resolution (e.g., 200 instead of 100)
- Decrease World Size
- Consider implementing LOD system for larger worlds

## Next Steps

Once you've tested the basic world generation:

1. **Customize the Terrain**: Modify WorldGenerator.cpp to add more complex algorithms
2. **Add Biomes**: Create different terrain types (forests, mountains, deserts)
3. **Add Vegetation**: Implement a procedural vegetation spawning system
4. **Create Materials**: Design custom terrain materials in Content/Materials/
5. **Add Game Mechanics**: Implement gameplay features like combat, inventory, quests

## Performance Tips

- **Grid Resolution**: Default is 100 units. Increase for better performance, decrease for more detail.
- **World Size**: Start with 10km x 10km. Increase gradually while monitoring FPS.
- **LOD System**: For worlds larger than 20km, consider implementing level-of-detail.
- **Chunk-based Loading**: For infinite or very large worlds, implement chunk streaming.

## Additional Resources

- Main README.md: Complete project documentation
- QUICKSTART.md: Detailed setup guide
- PROJECT_OVERVIEW.md: Architecture and design overview
- MATERIALS.md: Material creation guide

Happy world building!
