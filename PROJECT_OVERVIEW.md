# Stone and Sword - Project Overview

## Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│              STONE AND SWORD - WINDOWS APPLICATION              │
│             Standalone Game with Unreal Engine 5.4              │
└─────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────┐
│                        RUNTIME MODULE                             │
├──────────────────────────────────────────────────────────────────┤
│                                                                   │
│  ┌─────────────────────────────────────────────────────────┐    │
│  │         StoneAndSword Game Module                        │    │
│  │  (Standalone Windows Application Runtime)               │    │
│  ├─────────────────────────────────────────────────────────┤    │
│  │                                                           │    │
│  │  AStoneAndSwordGameModeBase                             │    │
│  │  ├── Manages game rules and flow                        │    │
│  │  └── Sets default pawn to WorldPlayerCharacter          │    │
│  │                                                           │    │
│  │  AWorldPlayerCharacter                                   │    │
│  │  ├── First-person character controller                  │    │
│  │  ├── Camera system (First-Person Camera)                │    │
│  │  ├── Input handling (WASD, Mouse, Gamepad)              │    │
│  │  ├── Movement and jump mechanics                         │    │
│  │  └── Optional first-person arms/hands support           │    │
│  │                                                           │    │
│  │  AWorldGenerator                                         │    │
│  │  ├── Procedural mesh generation                          │    │
│  │  ├── Flat terrain with height variation                 │    │
│  │  ├── Configurable size and resolution                   │    │
│  │  ├── Noise-based height calculation                     │    │
│  │  └── UV mapping and vertex colors                        │    │
│  │                                                           │    │
│  └─────────────────────────────────────────────────────────┘    │
│                                                                   │
└──────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────┐
│                          CONTENT ASSETS                           │
├──────────────────────────────────────────────────────────────────┤
│                                                                   │
│  Content/                                                         │
│  ├── Maps/                                                       │
│  │   └── MainWorld.umap (To be created by user)                 │
│  │                                                               │
│  ├── Textures/                                                   │
│  │   ├── T_Grass.tga   (512x512 green texture)                  │
│  │   ├── T_Stone.tga   (512x512 gray texture)                   │
│  │   ├── T_Dirt.tga    (512x512 brown texture)                  │
│  │   └── T_Normal.tga  (512x512 normal map)                     │
│  │                                                               │
│  ├── Materials/                                                  │
│  │   └── (User creates M_Terrain material)                      │
│  │                                                               │
│  └── Blueprints/                                                 │
│      └── (User can create BP derivatives)                        │
│                                                                   │
└──────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────┐
│                      CONFIGURATION FILES                          │
├──────────────────────────────────────────────────────────────────┤
│  Config/                                                          │
│  ├── DefaultEngine.ini  - Engine settings, rendering, physics    │
│  ├── DefaultGame.ini    - Game-specific settings                 │
│  └── DefaultInput.ini   - Input mappings and controls            │
└──────────────────────────────────────────────────────────────────┘
```

## Data Flow

```
┌──────────────┐
│  Game Start  │
└──────┬───────┘
       │
       ▼
┌─────────────────────────┐
│  Game Mode Initialized  │
│  (AStoneAndSwordGameModeBase) │
└──────┬──────────────────┘
       │
       ▼
┌───────────────────────────────┐
│  Player Character Spawned      │
│  (AWorldPlayerCharacter)       │
│  - Camera setup                │
│  - Input binding               │
└──────┬────────────────────────┘
       │
       ▼
┌────────────────────────────────┐
│  World Generator Begins Play   │
│  (AWorldGenerator)             │
│  - If Auto-generate enabled    │
└──────┬─────────────────────────┘
       │
       ▼
┌────────────────────────────────────┐
│  Generate Terrain                   │
│  1. Calculate grid dimensions       │
│  2. Generate vertices with heights  │
│  3. Create triangles                │
│  4. Calculate normals               │
│  5. Apply UVs and vertex colors    │
│  6. Create procedural mesh section  │
│  7. Apply material                  │
│  8. Enable collision                │
└──────┬─────────────────────────────┘
       │
       ▼
┌────────────────────────┐
│  Player Can Explore    │
│  - WASD: Movement      │
│  - Mouse: Look around  │
│  - Space: Jump         │
└────────────────────────┘
```

## Class Relationships

```
UObject (Unreal Engine Base)
  │
  ├── AActor
  │   │
  │   ├── AWorldGenerator
  │   │   ├── Uses: UProceduralMeshComponent
  │   │   └── Creates: Procedural terrain mesh
  │   │
  │   └── APawn
  │       │
  │       └── ACharacter
  │           │
  │           └── AWorldPlayerCharacter
  │               ├── Uses: UCameraComponent (First-Person)
  │               ├── Uses: UCharacterMovementComponent
  │               └── Optional: First-person arms mesh
  │
  └── AGameModeBase
      │
      └── AStoneAndSwordGameModeBase
          └── Sets: DefaultPawnClass = AWorldPlayerCharacter
```

## Key Features

### 🎮 Standalone Windows Application
- **Self-contained game**: Runs independently without editor dependencies
- **Optimized runtime**: Focused on game performance and execution
- **Easy distribution**: Package and distribute as a standalone executable
- **Windows native**: Built specifically for Windows platform

### 🌍 World Generation System
- **Procedural Mesh Generation**: Uses UProceduralMeshComponent for runtime terrain
- **Configurable Parameters**: Size, resolution, height, noise scale, random seed
- **Performance**: Grid-based generation with customizable detail levels
- **Extensible**: Easy to add biomes, vegetation, and advanced features

### 🎮 Player Controller
- **First-Person View**: Camera at eye level for immersive FPS experience
- **Standard Controls**: WASD movement, mouse look, spacebar jump
- **Gamepad Support**: Full controller compatibility
- **Customizable**: Movement speed, camera height, rotation rates
- **Optional Arms**: Can add visible first-person arms/hands

### 🎨 Material System
- **Generic Textures**: Grass, stone, dirt, and normal maps included
- **UV Mapping**: 10x tiling for better detail
- **Vertex Colors**: Height-based coloring for material blending
- **Material Support**: Apply custom materials to terrain

### 🔧 Development Features
- **Modular Architecture**: Clean game runtime module structure
- **C++ and Blueprint**: Full support for both workflows
- **Well-Documented**: Comprehensive guides and comments
- **Standard UE Conventions**: Follows Epic's coding standards
- **Standalone Builds**: Optimized for shipping and distribution

## Performance Considerations

### Current Implementation
- **Grid Resolution**: Default 100 units (configurable)
- **World Size**: Default 10km x 10km (configurable)
- **Collision**: Full physics collision enabled
- **Vertices**: Approximately (WorldSize/GridResolution)² vertices

### Optimization Opportunities
1. **LOD System**: Add level-of-detail for distant terrain
2. **Chunk-Based Loading**: Split world into manageable chunks
3. **Instanced Rendering**: For vegetation and props
4. **Occlusion Culling**: Cull non-visible geometry
5. **Streaming**: Load/unload terrain dynamically

## Extension Points

### Easy to Add
- ✅ More complex terrain algorithms (Perlin noise, Diamond-Square)
- ✅ Multiple biomes with smooth transitions
- ✅ Water bodies and rivers
- ✅ Vegetation spawning system
- ✅ Building placement system
- ✅ Dynamic weather
- ✅ Day/night cycle

### Requires More Work
- ⚙️ Infinite world generation (chunk streaming)
- ⚙️ Multiplayer support (replication)
- ⚙️ Save/load system for generated worlds
- ⚙️ Advanced AI navigation mesh
- ⚙️ Destructible terrain

## Technology Stack

- **Platform**: Windows (standalone application)
- **Engine**: Unreal Engine 5.4 Runtime
- **Language**: C++ (with Blueprint support)
- **Build System**: Unreal Build Tool
- **Target**: Windows 64-bit
- **Key Plugins**:
  - ProceduralMeshComponent
  - Landmass
  - Water

## Getting Started

See **QUICKSTART.md** for detailed setup instructions.

## Further Reading

- **README.md**: Comprehensive project documentation
- **MATERIALS.md**: Material creation guide
- **QUICKSTART.md**: Step-by-step setup guide
- **Source Code**: Well-commented C++ classes

## License

See LICENSE file for details.
