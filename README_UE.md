# Stone and Sword - Windows Game Application

A standalone Windows game application built with Unreal Engine 5.4, featuring a procedural world generation system.

## Project Overview

This is a standalone Windows game application that hosts the Unreal Engine 5.4 runtime with the following features:
- Procedural flat world generation system
- Third-person character controller with camera
- Generic terrain textures (grass, stone, dirt)
- Walking and exploration mechanics
- Scalable world generation engine

## Project Structure

```
StoneAndSword/
├── Config/                 # Configuration files for engine, input, and game
│   ├── DefaultEngine.ini   # Engine settings
│   ├── DefaultGame.ini     # Game settings
│   └── DefaultInput.ini    # Input mappings
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
│   └── StoneAndSword.Target.cs           # Game build target
└── StoneAndSword.uproject  # Unreal Engine project file

```

## Key Systems

### World Generation System
The `AWorldGenerator` class provides procedural terrain generation with 12 distinct biome types:
- **Large-scale biome worlds**: Each biome is a huge, distinct world area (3-10x base world size)
- **12 biome types**: Tropical Jungle, Temperate Forest, Boreal Taiga, Grasslands, Savanna, Desert, Tundra, Arctic Snow, Mountains, Volcanic Wasteland, Swampland, Rocky Badlands
- **Realistic terrain with Perlin noise**: Uses industry-standard Perlin noise (Fractional Brownian Motion) for natural-looking landscapes
- **Biome-specific characteristics**: Each biome has unique height multipliers, colors, roughness, and base elevations
- **Configurable parameters**:
  - World size (X and Y dimensions)
  - Grid resolution (vertex spacing)
  - Height variation (terrain undulation)
  - Noise scale (terrain frequency/detail)
  - Noise octaves (1-8, controls level of detail)
  - Noise persistence (0.1-1.0, controls octave contribution)
  - Noise lacunarity (1.0-4.0, controls frequency multiplier)
  - Random seed (for reproducible worlds)
  - Current biome type (selects which biome to generate)
  - Biome world size multiplier (1.0-10.0x for huge biomes)
- **Auto-generation**: Can automatically generate terrain on level start
- **Material support**: Apply custom materials to the terrain
- **Multi-scene architecture**: Each biome can be a separate level/map for boat/ferry traversal

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
- Visual Studio 2022 (Windows)
- Git
- Windows operating system

### Building the Windows Application

1. Clone this repository
2. Navigate to the project directory
3. Right-click `StoneAndSword.uproject` and select "Generate Visual Studio project files"
4. Open `StoneAndSword.sln` in Visual Studio
5. Build the project in "Development" or "Shipping" configuration
6. Run the standalone game application

### Running the Game

**Option 1: From Visual Studio**
- Set configuration to "Development" or "Shipping"
- Press F5 to build and launch the game

**Option 2: From Unreal Engine**
- Double-click `StoneAndSword.uproject`
- Click "Play" (Alt+P) to test in the engine
- Use "Package Project > Windows" to create a standalone executable

**Option 3: Standalone Executable**
- After packaging, find the executable in the `Binaries/Win64` directory
- Double-click to run the game directly

## Game Features

The standalone Windows application automatically initializes with:
- **Auto-generated world**: Procedurally generated terrain on game start
- **Player character**: Ready-to-play third-person character
- **Full controls**: WASD movement, mouse look, spacebar jump
- **Gamepad support**: Xbox/PlayStation controller compatible

## Textures

The game includes procedurally generated textures in `Content/Textures/`:
- **T_Grass.tga**: Green grass texture with natural variation
- **T_Stone.tga**: Gray stone texture for rocky areas
- **T_Dirt.tga**: Brown dirt texture for terrain
- **T_Normal.tga**: Default normal map for flat surfaces

These textures can be used as a starting point and can be replaced with higher-quality assets as needed.

## Customization

### Extending Game Features
The application can be extended with:
- More complex terrain algorithms (Perlin noise, biomes, etc.)
- Additional game mechanics and systems
- New player abilities and interactions
- Enhanced graphics and visual effects

### Modifying the Source Code
1. Edit C++ classes in `Source/StoneAndSword/`
2. Rebuild the project in Visual Studio
3. Test changes by running the game

### Building for Distribution
1. Open the project in Unreal Engine
2. Go to File > Package Project > Windows
3. Choose a target directory
4. Wait for packaging to complete
5. Distribute the packaged application

## Build Configurations

- **Development**: For development and testing with debugging symbols
- **DebugGame**: For deep debugging with full debug information
- **Shipping**: For final release builds (optimized, no debug info)

## License

See LICENSE file for details.

## Contributing

This is a standalone Windows game application designed to be extended and customized for your specific requirements.
