# Custom Game Engine Architecture

## Overview

This document describes the architecture for transitioning from Unreal Engine 5.4 to a custom C++ game engine with Lua scripting support and modern rendering backends (DirectX 11/12, OpenGL, or Vulkan).

## Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    STONE AND SWORD ENGINE                        │
│            Custom C++ Game Engine with Lua Scripting             │
└─────────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────────┐
│                         ENGINE LAYERS                             │
├──────────────────────────────────────────────────────────────────┤
│                                                                   │
│  ┌────────────────────────────────────────────────────────┐     │
│  │                  APPLICATION LAYER                      │     │
│  │  - Game Loop                                            │     │
│  │  - Window Management                                    │     │
│  │  - Event System                                         │     │
│  │  - Resource Management                                  │     │
│  └────────────────────────────────────────────────────────┘     │
│                              ▼                                    │
│  ┌────────────────────────────────────────────────────────┐     │
│  │               SCRIPTING LAYER (Lua)                     │     │
│  │  - Lua 5.4+ Integration                                 │     │
│  │  - C++ ↔ Lua Bridge (LuaBridge3 or Sol2)              │     │
│  │  - Game Logic Scripts                                   │     │
│  │  - Entity Behavior Scripts                              │     │
│  └────────────────────────────────────────────────────────┘     │
│                              ▼                                    │
│  ┌────────────────────────────────────────────────────────┐     │
│  │                 GAME SYSTEMS LAYER                      │     │
│  │  - Entity Component System (ECS)                        │     │
│  │  - World Generation System                              │     │
│  │  - Character Controller                                 │     │
│  │  - Physics System                                       │     │
│  │  - Audio System                                         │     │
│  │  - Input Management                                     │     │
│  └────────────────────────────────────────────────────────┘     │
│                              ▼                                    │
│  ┌────────────────────────────────────────────────────────┐     │
│  │            RENDERING ABSTRACTION LAYER                  │     │
│  │  - Renderer Interface                                   │     │
│  │  - Mesh Management                                      │     │
│  │  - Material System                                      │     │
│  │  - Camera System                                        │     │
│  │  - Shader Management                                    │     │
│  └────────────────────────────────────────────────────────┘     │
│                              ▼                                    │
│  ┌────────────────────────────────────────────────────────┐     │
│  │              GRAPHICS API BACKENDS                      │     │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐             │     │
│  │  │DirectX 11│  │DirectX 12│  │  Vulkan  │             │     │
│  │  └──────────┘  └──────────┘  └──────────┘             │     │
│  │  ┌──────────┐                                           │     │
│  │  │ OpenGL   │                                           │     │
│  │  └──────────┘                                           │     │
│  └────────────────────────────────────────────────────────┘     │
│                              ▼                                    │
│  ┌────────────────────────────────────────────────────────┐     │
│  │                  PLATFORM LAYER                         │     │
│  │  - Windows API                                          │     │
│  │  - File I/O                                             │     │
│  │  - Threading                                            │     │
│  │  - Timing                                               │     │
│  └────────────────────────────────────────────────────────┘     │
│                                                                   │
└──────────────────────────────────────────────────────────────────┘
```

## Core Components

### 1. Application Layer

**Purpose**: Main engine entry point and lifetime management

**Components**:
- `Engine`: Main engine class managing all subsystems
- `Window`: Platform-specific window creation and management
- `GameLoop`: Frame timing and update/render loop
- `EventSystem`: Event dispatch and handling

**Key Files**:
```
Engine/
├── Core/
│   ├── Engine.h/cpp          # Main engine class
│   ├── Window.h/cpp          # Window management
│   ├── GameLoop.h/cpp        # Game loop implementation
│   └── Event.h/cpp           # Event system
```

### 2. Scripting Layer (Lua)

**Purpose**: High-level game logic and rapid iteration

**Features**:
- Lua 5.4+ for scripting
- C++ to Lua binding (LuaBridge3 or Sol2)
- Hot-reloading of scripts
- Sandboxed execution environment

**Script Types**:
- Game initialization scripts
- Entity behavior scripts
- World generation logic
- UI and menu scripts

**Key Files**:
```
Engine/
├── Scripting/
│   ├── LuaEngine.h/cpp       # Lua VM management
│   ├── LuaBridge.h/cpp       # C++ ↔ Lua bindings
│   └── ScriptManager.h/cpp   # Script loading/execution
```

### 3. Game Systems Layer

**Purpose**: Core gameplay functionality

**Entity Component System (ECS)**:
- Entities: Unique IDs for game objects
- Components: Data containers (Transform, Mesh, RigidBody, etc.)
- Systems: Logic processors (RenderSystem, PhysicsSystem, etc.)

**World Generation System**:
- Procedural mesh generation
- Height map generation
- Texture splatting
- Biome system

**Character Controller**:
- Input handling
- Movement physics
- Camera control
- Animation (future)

**Key Files**:
```
Engine/
├── ECS/
│   ├── Entity.h/cpp
│   ├── Component.h/cpp
│   ├── System.h/cpp
│   └── World.h/cpp
├── WorldGen/
│   ├── WorldGenerator.h/cpp
│   ├── NoiseGenerator.h/cpp
│   └── TerrainMesh.h/cpp
└── Gameplay/
    ├── CharacterController.h/cpp
    ├── Camera.h/cpp
    └── Input.h/cpp
```

### 4. Rendering Abstraction Layer

**Purpose**: Graphics API independent rendering interface

**Design Pattern**: Abstract factory pattern for API-specific implementations

**Core Classes**:
- `IRenderer`: Abstract renderer interface
- `IMesh`: Mesh representation
- `IMaterial`: Material/shader representation
- `ITexture`: Texture management
- `IShader`: Shader compilation and binding

**Key Files**:
```
Engine/
├── Renderer/
│   ├── IRenderer.h           # Renderer interface
│   ├── Mesh.h/cpp
│   ├── Material.h/cpp
│   ├── Texture.h/cpp
│   ├── Shader.h/cpp
│   ├── Camera.h/cpp
│   └── RenderCommand.h/cpp
```

### 5. Graphics API Backends

**Purpose**: Platform-specific rendering implementations

#### DirectX 11 Backend
```
Engine/
├── Renderer/
│   └── DX11/
│       ├── DX11Renderer.h/cpp
│       ├── DX11Mesh.h/cpp
│       ├── DX11Shader.h/cpp
│       └── DX11Texture.h/cpp
```

#### DirectX 12 Backend
```
Engine/
├── Renderer/
│   └── DX12/
│       ├── DX12Renderer.h/cpp
│       ├── DX12CommandList.h/cpp
│       ├── DX12DescriptorHeap.h/cpp
│       └── DX12Resources.h/cpp
```

#### Vulkan Backend
```
Engine/
├── Renderer/
│   └── Vulkan/
│       ├── VulkanRenderer.h/cpp
│       ├── VulkanDevice.h/cpp
│       ├── VulkanSwapchain.h/cpp
│       └── VulkanPipeline.h/cpp
```

#### OpenGL Backend
```
Engine/
├── Renderer/
│   └── OpenGL/
│       ├── OpenGLRenderer.h/cpp
│       ├── OpenGLMesh.h/cpp
│       ├── OpenGLShader.h/cpp
│       └── OpenGLTexture.h/cpp
```

### 6. Platform Layer

**Purpose**: OS-specific functionality abstraction

**Features**:
- File I/O
- Threading and synchronization
- Memory management
- High-resolution timing
- Window creation (Win32 API)

**Key Files**:
```
Engine/
├── Platform/
│   ├── Windows/
│   │   ├── WindowsWindow.h/cpp
│   │   ├── WindowsFileSystem.h/cpp
│   │   └── WindowsThread.h/cpp
│   └── FileSystem.h/cpp
```

## Data Flow

### Initialization Sequence

```
1. main()
   └─> Engine::Initialize()
       ├─> Window::Create()
       ├─> Renderer::Initialize(API)  # Select DX11/DX12/Vulkan/OpenGL
       ├─> LuaEngine::Initialize()
       ├─> ECS::Initialize()
       ├─> Input::Initialize()
       ├─> Audio::Initialize()
       └─> LoadGame("game.lua")
```

### Game Loop

```
while (Engine::IsRunning())
{
    // 1. Process Events
    Window::PollEvents();
    Input::Update();
    
    // 2. Fixed Update (Physics)
    while (accumulator >= fixedDeltaTime)
    {
        Physics::Update(fixedDeltaTime);
        accumulator -= fixedDeltaTime;
    }
    
    // 3. Update Game Logic
    LuaEngine::Update(deltaTime);
    ECS::UpdateSystems(deltaTime);
    
    // 4. Render
    Renderer::BeginFrame();
    Renderer::Clear();
    ECS::RenderSystems(Renderer);
    Renderer::EndFrame();
    Renderer::Present();
}
```

### Scripting Flow

```
C++ Engine
    ↓ (Register functions)
Lua VM
    ↓ (Call C++ from Lua)
Game Logic Script
    ↓ (Spawn entities, set components)
ECS World
    ↓ (Process systems)
Renderer
```

## Directory Structure

```
StoneAndSword/
├── Engine/                   # Custom game engine source
│   ├── Core/                # Core engine functionality
│   ├── ECS/                 # Entity Component System
│   ├── Renderer/            # Rendering abstraction + backends
│   │   ├── DX11/           # DirectX 11 implementation
│   │   ├── DX12/           # DirectX 12 implementation
│   │   ├── Vulkan/         # Vulkan implementation
│   │   └── OpenGL/         # OpenGL implementation
│   ├── Scripting/          # Lua integration
│   ├── WorldGen/           # World generation system
│   ├── Gameplay/           # Gameplay systems
│   ├── Platform/           # Platform abstraction
│   ├── Physics/            # Physics system
│   └── Audio/              # Audio system
├── Game/                    # Game-specific code
│   ├── Scripts/            # Lua game scripts
│   ├── Assets/             # Game assets
│   │   ├── Textures/
│   │   ├── Shaders/
│   │   ├── Models/
│   │   └── Audio/
│   └── Config/             # Configuration files
├── ThirdParty/             # External dependencies
│   ├── Lua/                # Lua 5.4+
│   ├── LuaBridge3/         # C++ to Lua binding
│   ├── glm/                # Math library
│   ├── stb/                # Image loading
│   ├── OpenAL/             # Audio
│   └── PhysX/              # Physics (optional)
├── Docs/                   # Documentation
├── Build/                  # Build output
└── Tools/                  # Build tools and scripts
```

## Technology Stack

### Core Engine
- **Language**: C++17 or C++20
- **Build System**: CMake 3.20+
- **Compiler**: MSVC 2019+ (Windows)

### Scripting
- **Language**: Lua 5.4+
- **Binding**: LuaBridge3 or Sol2 (modern C++ Lua binding)

### Graphics APIs
- **DirectX 11**: For Windows compatibility
- **DirectX 12**: For modern Windows performance
- **Vulkan**: For cross-platform and modern API
- **OpenGL 4.5+**: For maximum compatibility

### Mathematics
- **GLM** (OpenGL Mathematics): Vector, matrix, and quaternion operations

### Asset Loading
- **stb_image**: Image loading (PNG, JPG, TGA, etc.)
- **stb_truetype**: Font rendering
- **Assimp**: 3D model loading (optional)

### Audio
- **OpenAL Soft**: 3D audio rendering

### Physics
- **PhysX** or **Bullet**: 3D physics simulation (optional)

### Windowing
- **Win32 API**: Native Windows windowing
- **SDL2** or **GLFW**: Optional cross-platform windowing

## Design Patterns

### 1. Abstract Factory Pattern
Used for renderer backend selection:
```cpp
class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual void Initialize() = 0;
    virtual void Clear() = 0;
    virtual void Present() = 0;
    // ...
};

std::unique_ptr<IRenderer> CreateRenderer(RenderAPI api) {
    switch(api) {
        case RenderAPI::DirectX11: return std::make_unique<DX11Renderer>();
        case RenderAPI::DirectX12: return std::make_unique<DX12Renderer>();
        case RenderAPI::Vulkan: return std::make_unique<VulkanRenderer>();
        case RenderAPI::OpenGL: return std::make_unique<OpenGLRenderer>();
    }
}
```

### 2. Entity Component System
Separates data from logic:
```cpp
struct Transform : Component {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;
};

struct MeshRenderer : Component {
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;
};

class RenderSystem : public System {
    void Update(ECSWorld& world, float deltaTime) override {
        for (auto entity : world.GetEntitiesWith<Transform, MeshRenderer>()) {
            // Render logic
        }
    }
};
```

### 3. Resource Management
RAII and smart pointers:
```cpp
class ResourceManager {
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures_;
    std::unordered_map<std::string, std::shared_ptr<Mesh>> meshes_;
    
public:
    std::shared_ptr<Texture> LoadTexture(const std::string& path);
    std::shared_ptr<Mesh> LoadMesh(const std::string& path);
};
```

### 4. Observer Pattern
Event system:
```cpp
class EventDispatcher {
public:
    template<typename EventType>
    void Subscribe(std::function<void(const EventType&)> callback);
    
    template<typename EventType>
    void Dispatch(const EventType& event);
};
```

## Memory Management

### Strategies
1. **Smart Pointers**: Use `std::unique_ptr` and `std::shared_ptr`
2. **Object Pools**: For frequently created/destroyed objects
3. **Custom Allocators**: For performance-critical systems
4. **RAII**: Resource acquisition is initialization

### Example
```cpp
class MeshPool {
    std::vector<std::unique_ptr<Mesh>> pool_;
    std::queue<Mesh*> available_;
    
public:
    Mesh* Acquire();
    void Release(Mesh* mesh);
};
```

## Threading Model

### Main Thread
- Game loop
- Rendering
- Input processing

### Worker Threads
- Asset loading
- World generation
- Physics simulation (optional)
- Audio processing

### Synchronization
```cpp
class TaskScheduler {
public:
    void ScheduleTask(std::function<void()> task);
    void WaitForCompletion();
    
private:
    std::vector<std::thread> workers_;
    ThreadSafeQueue<std::function<void()>> tasks_;
};
```

## Performance Considerations

### Rendering
1. **Batch Rendering**: Group draw calls by material
2. **Instancing**: Render multiple objects with one draw call
3. **Frustum Culling**: Skip objects outside camera view
4. **Occlusion Culling**: Skip objects behind other objects
5. **LOD System**: Use simpler meshes for distant objects

### World Generation
1. **Chunk-Based**: Generate world in chunks
2. **Async Generation**: Generate in background thread
3. **Caching**: Cache generated chunks
4. **Streaming**: Load/unload chunks dynamically

### Scripting
1. **Hot-Reloading**: Reload scripts without restart
2. **Bytecode Compilation**: Compile Lua to bytecode
3. **Function Caching**: Cache frequently called functions

## Extensibility

### Adding New Game Features
1. Create new component types
2. Create new systems
3. Write Lua scripts
4. No engine recompilation needed

### Adding New Renderers
1. Implement `IRenderer` interface
2. Add to renderer factory
3. Engine automatically supports it

### Adding New Platforms
1. Implement platform layer interfaces
2. Add platform-specific code
3. Update build system

## Next Steps

See the following documentation files:
- **DEPENDENCIES.md**: Complete list of required libraries
- **IMPLEMENTATION_GUIDE.md**: Step-by-step implementation guide
- **API_REFERENCE.md**: Engine API documentation
- **SCRIPTING_API.md**: Lua scripting API reference
- **BUILD_GUIDE.md**: How to build the engine
