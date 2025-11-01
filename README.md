# Stone and Sword - Open World Game

An open world game project built with Unreal Engine 5.4, featuring a procedural world generation system.

## Project Overview

This project provides a structured foundation for an open world game with the following features:
- Procedural flat world generation system
- Third-person character controller with camera
- Generic terrain textures (grass, stone, dirt)
- Walking and exploration mechanics
- Scalable world generation engine

## Project Structure

```
StoneAndSword/
├── Config/                 # Configuration files for engine, input, and editor
│   ├── DefaultEngine.ini   # Engine settings
│   ├── DefaultGame.ini     # Game settings
│   ├── DefaultInput.ini    # Input mappings
│   └── DefaultEditor.ini   # Editor settings
├── Content/                # Game content and assets
│   ├── Maps/              # Game maps (MainWorld)
│   ├── Textures/          # Texture assets (grass, stone, dirt, normal maps)
│   ├── Materials/         # Material assets
│   └── Blueprints/        # Blueprint assets
├── Source/                 # C++ source code
│   ├── StoneAndSword/     # Main game module
│   │   ├── StoneAndSword.h/.cpp              # Module implementation
│   │   ├── StoneAndSword.Build.cs            # Build configuration
│   │   ├── StoneAndSwordGameModeBase.h/.cpp  # Game mode
│   │   ├── WorldPlayerCharacter.h/.cpp       # Player character
│   │   └── WorldGenerator.h/.cpp             # World generation system
│   ├── StoneAndSwordEditor/  # Editor module
│   │   ├── StoneAndSwordEditor.h/.cpp     # Editor module implementation
│   │   └── StoneAndSwordEditor.Build.cs   # Editor build configuration
│   ├── StoneAndSword.Target.cs           # Game build target
│   └── StoneAndSwordEditor.Target.cs     # Editor build target
└── StoneAndSword.uproject  # Unreal Engine project file

```

## Key Systems

### World Generation System
The `AWorldGenerator` class provides procedural terrain generation:
- **Flat terrain with height variation**: Creates a walkable surface with subtle undulation
- **Configurable parameters**:
  - World size (X and Y dimensions)
  - Grid resolution (vertex spacing)
  - Height variation (terrain undulation)
  - Noise scale (terrain detail)
  - Random seed (for reproducible worlds)
- **Auto-generation**: Can automatically generate terrain on level start
- **Material support**: Apply custom materials to the terrain

### Character Controller
The `AWorldPlayerCharacter` class provides player control:
- **Third-person camera** with spring arm for smooth following
- **WASD movement** with mouse look
- **Jump capability**
- **Gamepad support**
- **Configurable movement speed**

### Input Mappings
- **W/S**: Move forward/backward
- **A/D**: Move left/right
- **Mouse**: Look around
- **Spacebar**: Jump
- **Gamepad**: Full controller support

## Getting Started

### Prerequisites
- Unreal Engine 5.4 or later
- Visual Studio 2022 (for Windows) or appropriate C++ development tools
- Git

### Quick Start for Testing

**The fastest way to test the world generation system:**

1. Clone this repository
2. Open `StoneAndSword.uproject` in Unreal Engine 5.4
3. Create a new Empty Level (File > New Level > Empty Level)
4. Press Play (Alt+P)
5. The world will automatically generate with all necessary components!

See **TESTING.md** for detailed testing instructions and customization options.

### Full Setup for Development

### Opening the Project
1. Clone this repository
2. Navigate to the project directory
3. Right-click `StoneAndSword.uproject` and select "Generate Visual Studio project files"
4. Open `StoneAndSword.sln` in Visual Studio
5. Build the project (Development Editor configuration)
6. Launch the editor from Visual Studio or by double-clicking the .uproject file

### Creating Your First World
1. Open the Unreal Editor
2. Create a new level or open an existing one
3. Add a `WorldGenerator` actor to the level (Place Actors panel > All Classes > WorldGenerator)
4. Configure the world generation parameters in the Details panel:
   - Adjust `World Size X` and `World Size Y` for terrain dimensions
   - Modify `Grid Resolution` for detail level
   - Set `Height Variation` for terrain undulation
   - Configure `Auto Generate On Begin Play` to generate at runtime
5. Add a `WorldPlayerCharacter` or use the default game mode
6. Press Play to explore your generated world

## Textures

The project includes procedurally generated textures in `Content/Textures/`:
- **T_Grass.tga**: Green grass texture with natural variation
- **T_Stone.tga**: Gray stone texture for rocky areas
- **T_Dirt.tga**: Brown dirt texture for terrain
- **T_Normal.tga**: Default normal map for flat surfaces

These textures can be used as a starting point and can be replaced with higher-quality assets as needed.

## Customization

### Extending the World Generator
To add more complex terrain features:
1. Modify `WorldGenerator.cpp` and `WorldGenerator.h`
2. Add new generation algorithms (Perlin noise, biomes, etc.)
3. Implement LOD system for large worlds
4. Add vegetation spawning
5. Implement chunk-based streaming for infinite worlds

### Adding Game Features
The project structure supports easy extension:
- Add new C++ classes in `Source/StoneAndSword/`
- Create Blueprints in `Content/Blueprints/`
- Implement game-specific mechanics in the game mode
- Add UI using UMG widgets

## Build Targets

- **Development**: For development and testing
- **DebugGame**: For debugging
- **Shipping**: For final release builds

## License

See LICENSE file for details.

## Contributing

This is a foundation project designed to be extended and customized for your specific game requirements.
