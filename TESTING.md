# Testing the Standalone Windows Game

This document explains how to test and verify the Stone and Sword standalone Windows game application.

## Running the Standalone Game

### Option 1: Run from Visual Studio

1. Open `StoneAndSword.sln` in Visual Studio
2. Set configuration to "Development" or "Shipping"
3. Press F5 to build and run
4. The game will launch with automatic world generation
5. Test the controls:
   - **WASD**: Move around
   - **Mouse**: Look around
   - **Spacebar**: Jump
   - **ESC**: Quit game

### Option 2: Run the Executable

After building:
1. Navigate to `Binaries/Win64/`
2. Double-click `StoneAndSword.exe`
3. The game launches automatically with generated world

### Option 3: Test in Unreal Editor (Development Only)

For development and testing purposes:

1. Open `StoneAndSword.uproject` in Unreal Editor
2. When prompted or if no level is open:
   - Go to **File > New Level**
   - Select **Empty Level**
   - Click **Create**
3. Press the **Play** button (or press Alt+P)
4. The world will automatically generate and you can test gameplay

## What Gets Tested Automatically

When you run the standalone game, the following systems are automatically initialized:

1. **World Generation**: Procedural terrain is generated (10km x 10km by default)
2. **Lighting**: Directional light and sky atmosphere are set up
3. **Player Character**: Third-person character spawns and is ready to control
4. **Camera System**: Spring arm camera follows the player
5. **Input System**: All controls are bound and functional

## Testing Checklist

### Basic Functionality
- [ ] Game launches without errors
- [ ] Terrain generates correctly
- [ ] Character spawns at origin
- [ ] Camera follows player smoothly
- [ ] Movement (WASD) works correctly
- [ ] Mouse look works smoothly
- [ ] Jump mechanic works
- [ ] Collision detection works (can't walk through terrain)
- [ ] Game exits cleanly (ESC key)

### Visual Quality
- [ ] Lighting is appropriate
- [ ] Textures load correctly
- [ ] No visual artifacts or glitches
- [ ] Terrain looks smooth and natural

### Performance
- [ ] Maintains acceptable framerate (30+ FPS)
- [ ] No stuttering or freezing
- [ ] Memory usage is reasonable
- [ ] CPU/GPU usage is acceptable

## Advanced Testing (Using Editor)

For developers who want to test custom configurations:

1. Open the project in Unreal Editor
2. Create or open a level
3. Add a **WorldSetupManager** actor (Place Actors > All Classes)
4. Configure parameters in Details panel:
   - **Default World Size X/Y**: Terrain dimensions
   - **Default Grid Resolution**: Vertex spacing
   - **Default Height Variation**: Terrain undulation
5. Press Play to test
6. Rebuild the game to include changes

## Customizing for Distribution

To modify the game before packaging:

## Troubleshooting

### Game Won't Launch

**Possible causes**:
- Missing Visual C++ Redistributable
- DirectX not installed
- Missing DLL files

**Solutions**:
- Install Visual C++ Redistributable 2022
- Update DirectX
- Ensure all dependencies are in the game directory

### No Terrain Appears

**Possible causes**:
- WorldSetupManager is not spawning correctly
- WorldGenerator initialization failed
- Check console log for errors

**Solutions**:
- Verify WorldGenerator code is correct
- Check GameMode settings
- Look for errors in log files

### Character Falls Through Terrain

**Possible causes**:
- Collision not enabled on ProceduralMesh
- Character spawns before terrain generates

**Solutions**:
- Verify collision settings in WorldGenerator
- Adjust spawn location Z position
- Check timing of world generation

### Performance Issues

**Possible causes**:
- Grid Resolution is too low (too many vertices)
- World Size is too large
- Graphics settings too high

**Solutions**:
- Increase Grid Resolution (e.g., 200 instead of 100)
- Decrease World Size
- Adjust graphics quality settings
- Consider implementing LOD system

## Development Testing

For developers making changes to the game:

1. **Code Changes**: Edit C++ files in Visual Studio
2. **Build**: Compile the project (Ctrl+Shift+B)
3. **Test**: Run from Visual Studio (F5) or run the executable
4. **Iterate**: Make adjustments and rebuild
5. **Package**: Create final build when ready

## Performance Benchmarking

Recommended performance targets:
- **Framerate**: 60+ FPS (Development), 30+ FPS minimum
- **Load Time**: < 10 seconds to main game
- **Memory Usage**: < 4GB for baseline game
- **World Generation**: < 5 seconds for 10km x 10km world

## Next Steps

Once you've tested the basic game:

1. **Customize the Terrain**: Modify WorldGenerator.cpp to add more complex algorithms
2. **Add Biomes**: Create different terrain types (forests, mountains, deserts)
3. **Add Vegetation**: Implement a procedural vegetation spawning system
4. **Create Materials**: Design custom terrain materials in Content/Materials/
5. **Add Game Mechanics**: Implement gameplay features like combat, inventory, quests

## Performance Tips

- **Grid Resolution**: Default is 100 units. Increase for better performance, decrease for more detail
- **World Size**: Start with 10km x 10km. Increase gradually while monitoring FPS
- **LOD System**: For worlds larger than 20km, consider implementing level-of-detail
- **Chunk-based Loading**: For infinite or very large worlds, implement chunk streaming
- **Graphics Settings**: Adjust rendering quality based on target hardware

## Distribution Testing

Before distributing the game to end users:

1. **Clean Build**: Package in "Shipping" configuration
2. **Test on Different Systems**: Verify on various Windows versions
3. **Check Dependencies**: Ensure all required DLLs are included
4. **Installer Testing**: If using an installer, test installation process
5. **Uninstall Testing**: Verify clean uninstallation
6. **Performance Testing**: Test on minimum spec hardware

## Additional Resources

- Main README.md: Complete project documentation
- QUICKSTART.md: Build and setup guide
- PROJECT_OVERVIEW.md: Architecture and design overview

Happy game development!
