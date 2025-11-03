# Implementation Guide: From Unreal Engine to Custom C++ Engine

## Overview

This guide provides a step-by-step approach to migrating the Stone and Sword project from Unreal Engine 5.4 to a custom C++ game engine with Lua scripting and modern rendering backends.

## Table of Contents

1. [Phase 1: Foundation Setup](#phase-1-foundation-setup)
2. [Phase 2: Core Engine Framework](#phase-2-core-engine-framework)
3. [Phase 3: Rendering Abstraction](#phase-3-rendering-abstraction)
4. [Phase 4: Rendering Backends](#phase-4-rendering-backends)
5. [Phase 5: Lua Scripting Integration](#phase-5-lua-scripting-integration)
6. [Phase 6: Game Systems](#phase-6-game-systems)
7. [Phase 7: World Generation Port](#phase-7-world-generation-port)
8. [Phase 8: Character Controller Port](#phase-8-character-controller-port)
9. [Phase 9: Polish and Documentation](#phase-9-polish-and-documentation)

---

## Phase 1: Foundation Setup

### Step 1.1: Project Structure

Create the new directory structure:

```
StoneAndSword/
├── CMakeLists.txt           # Root CMake configuration
├── Engine/                  # Engine source code
│   ├── CMakeLists.txt
│   ├── Core/
│   ├── Renderer/
│   ├── Scripting/
│   ├── ECS/
│   ├── WorldGen/
│   ├── Gameplay/
│   ├── Platform/
│   ├── Physics/
│   └── Audio/
├── Game/                    # Game-specific code
│   ├── Scripts/            # Lua scripts
│   ├── Assets/             # Game assets
│   └── Config/             # Configuration
├── ThirdParty/             # External dependencies
├── Docs/                   # Documentation
└── Tools/                  # Build scripts
```

### Step 1.2: CMake Setup

Create root `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(StoneAndSword VERSION 1.0.0 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Options
option(BUILD_WITH_VULKAN "Build with Vulkan support" ON)
option(BUILD_WITH_DX11 "Build with DirectX 11 support" ON)
option(BUILD_WITH_DX12 "Build with DirectX 12 support" ON)
option(BUILD_WITH_OPENGL "Build with OpenGL support" ON)

# vcpkg integration (if using vcpkg)
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
endif()

# Add subdirectories
add_subdirectory(ThirdParty)
add_subdirectory(Engine)
add_subdirectory(Game)
```

### Step 1.3: Install Dependencies

Using vcpkg:

```powershell
# Install vcpkg (if not already installed)
git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install

# Install dependencies
.\vcpkg install glm:x64-windows
.\vcpkg install lua:x64-windows
.\vcpkg install glfw3:x64-windows
.\vcpkg install spdlog:x64-windows
.\vcpkg install nlohmann-json:x64-windows
```

---

## Phase 2: Core Engine Framework

### Step 2.1: Engine Class

Create `Engine/Core/Engine.h`:

```cpp
#pragma once
#include <memory>
#include <string>

namespace StoneAndSword {

class Window;
class Renderer;
class LuaEngine;
class ECSWorld;
class InputManager;

class Engine {
public:
    Engine();
    ~Engine();

    bool Initialize(const std::string& configPath);
    void Shutdown();
    
    void Run();
    
    // Subsystem accessors
    Window* GetWindow() { return window_.get(); }
    Renderer* GetRenderer() { return renderer_.get(); }
    LuaEngine* GetLuaEngine() { return luaEngine_.get(); }
    ECSWorld* GetWorld() { return world_.get(); }
    InputManager* GetInput() { return input_.get(); }
    
    bool IsRunning() const { return isRunning_; }
    void Stop() { isRunning_ = false; }

private:
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    
    std::unique_ptr<Window> window_;
    std::unique_ptr<Renderer> renderer_;
    std::unique_ptr<LuaEngine> luaEngine_;
    std::unique_ptr<ECSWorld> world_;
    std::unique_ptr<InputManager> input_;
    
    bool isRunning_;
    float lastFrameTime_;
};

} // namespace StoneAndSword
```

Create `Engine/Core/Engine.cpp`:

```cpp
#include "Engine.h"
#include "Window.h"
#include "../Renderer/Renderer.h"
#include "../Scripting/LuaEngine.h"
#include "../ECS/World.h"
#include "Input.h"
#include <chrono>
#include <spdlog/spdlog.h>

namespace StoneAndSword {

Engine::Engine()
    : isRunning_(false)
    , lastFrameTime_(0.0f)
{
}

Engine::~Engine() {
    Shutdown();
}

bool Engine::Initialize(const std::string& configPath) {
    spdlog::info("Initializing Stone and Sword Engine...");
    
    // Initialize window
    window_ = std::make_unique<Window>();
    if (!window_->Create("Stone and Sword", 1280, 720)) {
        spdlog::error("Failed to create window");
        return false;
    }
    
    // Initialize renderer
    renderer_ = std::make_unique<Renderer>();
    if (!renderer_->Initialize(window_.get(), RenderAPI::DirectX11)) {
        spdlog::error("Failed to initialize renderer");
        return false;
    }
    
    // Initialize Lua engine
    luaEngine_ = std::make_unique<LuaEngine>();
    if (!luaEngine_->Initialize()) {
        spdlog::error("Failed to initialize Lua engine");
        return false;
    }
    
    // Initialize ECS world
    world_ = std::make_unique<ECSWorld>();
    
    // Initialize input
    input_ = std::make_unique<InputManager>();
    input_->Initialize(window_.get());
    
    // Load game configuration
    if (!luaEngine_->ExecuteFile(configPath)) {
        spdlog::warn("Failed to load game config: {}", configPath);
    }
    
    isRunning_ = true;
    spdlog::info("Engine initialized successfully");
    return true;
}

void Engine::Shutdown() {
    spdlog::info("Shutting down engine...");
    
    input_.reset();
    world_.reset();
    luaEngine_.reset();
    renderer_.reset();
    window_.reset();
    
    spdlog::info("Engine shut down");
}

void Engine::Run() {
    using Clock = std::chrono::high_resolution_clock;
    auto lastTime = Clock::now();
    
    while (isRunning_) {
        // Calculate delta time
        auto currentTime = Clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;
        
        // Engine loop
        ProcessEvents();
        Update(deltaTime);
        Render();
    }
}

void Engine::ProcessEvents() {
    window_->PollEvents();
    
    if (window_->ShouldClose()) {
        isRunning_ = false;
    }
    
    input_->Update();
}

void Engine::Update(float deltaTime) {
    // Update Lua scripts
    luaEngine_->Update(deltaTime);
    
    // Update ECS systems
    world_->Update(deltaTime);
}

void Engine::Render() {
    renderer_->BeginFrame();
    renderer_->Clear(0.1f, 0.1f, 0.2f, 1.0f);
    
    // Render world
    world_->Render(renderer_.get());
    
    renderer_->EndFrame();
    renderer_->Present();
}

} // namespace StoneAndSword
```

### Step 2.2: Window Class (Win32)

Create `Engine/Platform/Windows/WindowsWindow.h`:

```cpp
#pragma once
#include <string>
#include <Windows.h>

namespace StoneAndSword {

class Window {
public:
    Window();
    ~Window();
    
    bool Create(const std::string& title, int width, int height);
    void Destroy();
    
    void PollEvents();
    bool ShouldClose() const { return shouldClose_; }
    
    int GetWidth() const { return width_; }
    int GetHeight() const { return height_; }
    HWND GetHandle() const { return hwnd_; }
    
private:
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    HWND hwnd_;
    int width_;
    int height_;
    bool shouldClose_;
};

} // namespace StoneAndSword
```

### Step 2.3: Main Entry Point

Create `Game/Main.cpp`:

```cpp
#include <Engine/Core/Engine.h>
#include <spdlog/spdlog.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Setup logging
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting Stone and Sword...");
    
    // Create and initialize engine
    StoneAndSword::Engine engine;
    if (!engine.Initialize("Game/Config/game.lua")) {
        spdlog::error("Failed to initialize engine");
        return -1;
    }
    
    // Run game loop
    engine.Run();
    
    // Cleanup
    engine.Shutdown();
    
    spdlog::info("Stone and Sword shut down successfully");
    return 0;
}
```

---

## Phase 3: Rendering Abstraction

### Step 3.1: Renderer Interface

Create `Engine/Renderer/IRenderer.h`:

```cpp
#pragma once
#include <glm/glm.hpp>
#include <memory>

namespace StoneAndSword {

enum class RenderAPI {
    None = 0,
    DirectX11,
    DirectX12,
    Vulkan,
    OpenGL
};

class IMesh;
class IShader;
class ITexture;
class Window;

class IRenderer {
public:
    virtual ~IRenderer() = default;
    
    virtual bool Initialize(Window* window) = 0;
    virtual void Shutdown() = 0;
    
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void Present() = 0;
    
    virtual void Clear(float r, float g, float b, float a) = 0;
    virtual void SetViewport(int x, int y, int width, int height) = 0;
    
    virtual void DrawMesh(IMesh* mesh, const glm::mat4& transform) = 0;
    
    virtual std::shared_ptr<IMesh> CreateMesh() = 0;
    virtual std::shared_ptr<IShader> CreateShader() = 0;
    virtual std::shared_ptr<ITexture> CreateTexture() = 0;
    
    virtual RenderAPI GetAPI() const = 0;
};

// Factory function
std::unique_ptr<IRenderer> CreateRenderer(RenderAPI api);

} // namespace StoneAndSword
```

### Step 3.2: Mesh Interface

Create `Engine/Renderer/IMesh.h`:

```cpp
#pragma once
#include <glm/glm.hpp>
#include <vector>

namespace StoneAndSword {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
    glm::vec4 color;
};

class IMesh {
public:
    virtual ~IMesh() = default;
    
    virtual void SetVertices(const std::vector<Vertex>& vertices) = 0;
    virtual void SetIndices(const std::vector<uint32_t>& indices) = 0;
    
    virtual void Upload() = 0;
    virtual void Bind() = 0;
    virtual void Draw() = 0;
    
    virtual size_t GetVertexCount() const = 0;
    virtual size_t GetIndexCount() const = 0;
};

} // namespace StoneAndSword
```

---

## Phase 4: Rendering Backends

### Step 4.1: DirectX 11 Renderer

Create `Engine/Renderer/DX11/DX11Renderer.h`:

```cpp
#pragma once
#include "../IRenderer.h"
#include <d3d11.h>
#include <wrl/client.h>

namespace StoneAndSword {

using Microsoft::WRL::ComPtr;

class DX11Renderer : public IRenderer {
public:
    DX11Renderer();
    ~DX11Renderer() override;
    
    bool Initialize(Window* window) override;
    void Shutdown() override;
    
    void BeginFrame() override;
    void EndFrame() override;
    void Present() override;
    
    void Clear(float r, float g, float b, float a) override;
    void SetViewport(int x, int y, int width, int height) override;
    
    void DrawMesh(IMesh* mesh, const glm::mat4& transform) override;
    
    std::shared_ptr<IMesh> CreateMesh() override;
    std::shared_ptr<IShader> CreateShader() override;
    std::shared_ptr<ITexture> CreateTexture() override;
    
    RenderAPI GetAPI() const override { return RenderAPI::DirectX11; }
    
    ID3D11Device* GetDevice() { return device_.Get(); }
    ID3D11DeviceContext* GetContext() { return context_.Get(); }

private:
    bool CreateDeviceAndSwapChain(Window* window);
    bool CreateRenderTargetView();
    bool CreateDepthStencilView(int width, int height);
    
    ComPtr<ID3D11Device> device_;
    ComPtr<ID3D11DeviceContext> context_;
    ComPtr<IDXGISwapChain> swapChain_;
    ComPtr<ID3D11RenderTargetView> renderTargetView_;
    ComPtr<ID3D11DepthStencilView> depthStencilView_;
    ComPtr<ID3D11Texture2D> depthStencilBuffer_;
};

} // namespace StoneAndSword
```

Create `Engine/Renderer/DX11/DX11Renderer.cpp`:

```cpp
#include "DX11Renderer.h"
#include "DX11Mesh.h"
#include "../../Platform/Windows/WindowsWindow.h"
#include <spdlog/spdlog.h>

namespace StoneAndSword {

DX11Renderer::DX11Renderer() {
}

DX11Renderer::~DX11Renderer() {
    Shutdown();
}

bool DX11Renderer::Initialize(Window* window) {
    spdlog::info("Initializing DirectX 11 renderer...");
    
    if (!CreateDeviceAndSwapChain(window)) {
        return false;
    }
    
    if (!CreateRenderTargetView()) {
        return false;
    }
    
    if (!CreateDepthStencilView(window->GetWidth(), window->GetHeight())) {
        return false;
    }
    
    // Set viewport
    SetViewport(0, 0, window->GetWidth(), window->GetHeight());
    
    spdlog::info("DirectX 11 renderer initialized successfully");
    return true;
}

void DX11Renderer::Shutdown() {
    depthStencilView_.Reset();
    depthStencilBuffer_.Reset();
    renderTargetView_.Reset();
    swapChain_.Reset();
    context_.Reset();
    device_.Reset();
}

void DX11Renderer::BeginFrame() {
    // Set render targets
    context_->OMSetRenderTargets(1, renderTargetView_.GetAddressOf(), depthStencilView_.Get());
}

void DX11Renderer::EndFrame() {
    // Nothing to do here for DX11
}

void DX11Renderer::Present() {
    swapChain_->Present(1, 0); // VSync on
}

void DX11Renderer::Clear(float r, float g, float b, float a) {
    float clearColor[4] = { r, g, b, a };
    context_->ClearRenderTargetView(renderTargetView_.Get(), clearColor);
    context_->ClearDepthStencilView(depthStencilView_.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void DX11Renderer::SetViewport(int x, int y, int width, int height) {
    D3D11_VIEWPORT viewport = {};
    viewport.TopLeftX = static_cast<float>(x);
    viewport.TopLeftY = static_cast<float>(y);
    viewport.Width = static_cast<float>(width);
    viewport.Height = static_cast<float>(height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    
    context_->RSSetViewports(1, &viewport);
}

void DX11Renderer::DrawMesh(IMesh* mesh, const glm::mat4& transform) {
    if (mesh) {
        mesh->Bind();
        mesh->Draw();
    }
}

std::shared_ptr<IMesh> DX11Renderer::CreateMesh() {
    return std::make_shared<DX11Mesh>(this);
}

std::shared_ptr<IShader> DX11Renderer::CreateShader() {
    // TODO: Implement DX11Shader
    return nullptr;
}

std::shared_ptr<ITexture> DX11Renderer::CreateTexture() {
    // TODO: Implement DX11Texture
    return nullptr;
}

bool DX11Renderer::CreateDeviceAndSwapChain(Window* window) {
    // Swap chain description
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 2;
    swapChainDesc.BufferDesc.Width = window->GetWidth();
    swapChainDesc.BufferDesc.Height = window->GetHeight();
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = window->GetHandle();
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    
    // Feature levels
    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0
    };
    
    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    
    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        createDeviceFlags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain_,
        &device_,
        &featureLevel,
        &context_
    );
    
    if (FAILED(hr)) {
        spdlog::error("Failed to create D3D11 device and swap chain");
        return false;
    }
    
    spdlog::info("D3D11 device created with feature level: {:#x}", static_cast<int>(featureLevel));
    return true;
}

bool DX11Renderer::CreateRenderTargetView() {
    ComPtr<ID3D11Texture2D> backBuffer;
    HRESULT hr = swapChain_->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        spdlog::error("Failed to get swap chain back buffer");
        return false;
    }
    
    hr = device_->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTargetView_);
    if (FAILED(hr)) {
        spdlog::error("Failed to create render target view");
        return false;
    }
    
    return true;
}

bool DX11Renderer::CreateDepthStencilView(int width, int height) {
    D3D11_TEXTURE2D_DESC depthStencilDesc = {};
    depthStencilDesc.Width = width;
    depthStencilDesc.Height = height;
    depthStencilDesc.MipLevels = 1;
    depthStencilDesc.ArraySize = 1;
    depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilDesc.SampleDesc.Count = 1;
    depthStencilDesc.SampleDesc.Quality = 0;
    depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    
    HRESULT hr = device_->CreateTexture2D(&depthStencilDesc, nullptr, &depthStencilBuffer_);
    if (FAILED(hr)) {
        spdlog::error("Failed to create depth stencil buffer");
        return false;
    }
    
    hr = device_->CreateDepthStencilView(depthStencilBuffer_.Get(), nullptr, &depthStencilView_);
    if (FAILED(hr)) {
        spdlog::error("Failed to create depth stencil view");
        return false;
    }
    
    return true;
}

} // namespace StoneAndSword
```

### Step 4.2: Renderer Factory

Create `Engine/Renderer/RendererFactory.cpp`:

```cpp
#include "IRenderer.h"
#include "DX11/DX11Renderer.h"
// #include "DX12/DX12Renderer.h"
// #include "Vulkan/VulkanRenderer.h"
// #include "OpenGL/OpenGLRenderer.h"
#include <spdlog/spdlog.h>

namespace StoneAndSword {

std::unique_ptr<IRenderer> CreateRenderer(RenderAPI api) {
    switch (api) {
        case RenderAPI::DirectX11:
            return std::make_unique<DX11Renderer>();
            
        // case RenderAPI::DirectX12:
        //     return std::make_unique<DX12Renderer>();
            
        // case RenderAPI::Vulkan:
        //     return std::make_unique<VulkanRenderer>();
            
        // case RenderAPI::OpenGL:
        //     return std::make_unique<OpenGLRenderer>();
            
        default:
            spdlog::error("Unsupported render API");
            return nullptr;
    }
}

} // namespace StoneAndSword
```

---

## Phase 5: Lua Scripting Integration

### Step 5.1: Lua Engine

Create `Engine/Scripting/LuaEngine.h`:

```cpp
#pragma once
#include <string>
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>

namespace StoneAndSword {

class Engine;

class LuaEngine {
public:
    LuaEngine();
    ~LuaEngine();
    
    bool Initialize();
    void Shutdown();
    
    bool ExecuteFile(const std::string& filepath);
    bool ExecuteString(const std::string& code);
    
    void Update(float deltaTime);
    
    lua_State* GetState() { return L_; }
    
    // Bind engine API to Lua
    void RegisterEngineAPI(Engine* engine);

private:
    void RegisterStandardLibraries();
    void RegisterMathAPI();
    void RegisterECSAPI();
    
    lua_State* L_;
};

} // namespace StoneAndSword
```

Create `Engine/Scripting/LuaEngine.cpp`:

```cpp
#include "LuaEngine.h"
#include "../Core/Engine.h"
#include "../ECS/World.h"
#include <spdlog/spdlog.h>
#include <glm/glm.hpp>

namespace StoneAndSword {

LuaEngine::LuaEngine()
    : L_(nullptr)
{
}

LuaEngine::~LuaEngine() {
    Shutdown();
}

bool LuaEngine::Initialize() {
    spdlog::info("Initializing Lua engine...");
    
    L_ = luaL_newstate();
    if (!L_) {
        spdlog::error("Failed to create Lua state");
        return false;
    }
    
    RegisterStandardLibraries();
    RegisterMathAPI();
    
    spdlog::info("Lua engine initialized successfully");
    return true;
}

void LuaEngine::Shutdown() {
    if (L_) {
        lua_close(L_);
        L_ = nullptr;
    }
}

bool LuaEngine::ExecuteFile(const std::string& filepath) {
    if (luaL_dofile(L_, filepath.c_str()) != LUA_OK) {
        const char* error = lua_tostring(L_, -1);
        spdlog::error("Lua error in file '{}': {}", filepath, error);
        lua_pop(L_, 1);
        return false;
    }
    return true;
}

bool LuaEngine::ExecuteString(const std::string& code) {
    if (luaL_dostring(L_, code.c_str()) != LUA_OK) {
        const char* error = lua_tostring(L_, -1);
        spdlog::error("Lua error: {}", error);
        lua_pop(L_, 1);
        return false;
    }
    return true;
}

void LuaEngine::Update(float deltaTime) {
    // Call Lua update function if it exists
    lua_getglobal(L_, "Update");
    if (lua_isfunction(L_, -1)) {
        lua_pushnumber(L_, deltaTime);
        if (lua_pcall(L_, 1, 0, 0) != LUA_OK) {
            const char* error = lua_tostring(L_, -1);
            spdlog::error("Lua Update error: {}", error);
            lua_pop(L_, 1);
        }
    } else {
        lua_pop(L_, 1);
    }
}

void LuaEngine::RegisterStandardLibraries() {
    luaL_openlibs(L_);
}

void LuaEngine::RegisterMathAPI() {
    // Register glm::vec3
    luabridge::getGlobalNamespace(L_)
        .beginNamespace("math")
            .beginClass<glm::vec3>("vec3")
                .addConstructor<void(*)(float, float, float)>()
                .addProperty("x", &glm::vec3::x)
                .addProperty("y", &glm::vec3::y)
                .addProperty("z", &glm::vec3::z)
            .endClass()
        .endNamespace();
}

void LuaEngine::RegisterEngineAPI(Engine* engine) {
    luabridge::getGlobalNamespace(L_)
        .beginClass<Engine>("Engine")
            .addFunction("GetWorld", &Engine::GetWorld)
            .addFunction("Stop", &Engine::Stop)
        .endClass();
    
    luabridge::setGlobal(L_, engine, "Engine");
}

void LuaEngine::RegisterECSAPI() {
    // TODO: Register ECS API
}

} // namespace StoneAndSword
```

### Step 5.2: Example Game Script

Create `Game/Scripts/game.lua`:

```lua
-- Game initialization script

print("Loading Stone and Sword game...")

-- Game configuration
Config = {
    window = {
        title = "Stone and Sword",
        width = 1280,
        height = 720
    },
    world = {
        size = { x = 10000, y = 10000 },
        gridResolution = 100,
        heightVariation = 50
    }
}

-- Called once at game start
function Initialize()
    print("Initializing game...")
    -- TODO: Create world generator entity
    -- TODO: Create player character entity
end

-- Called every frame
function Update(deltaTime)
    -- Game logic here
end

-- Initialize the game
Initialize()

print("Game loaded successfully")
```

---

## Phase 6: Game Systems

### Step 6.1: Entity Component System

Create `Engine/ECS/Entity.h`:

```cpp
#pragma once
#include <cstdint>

namespace StoneAndSword {

using EntityID = uint64_t;
using ComponentTypeID = uint32_t;

constexpr EntityID INVALID_ENTITY = 0;

} // namespace StoneAndSword
```

Create `Engine/ECS/Component.h`:

```cpp
#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <memory>

namespace StoneAndSword {

// Base component (marker)
struct Component {
    virtual ~Component() = default;
};

// Transform component
struct Transform : Component {
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
    
    glm::mat4 GetMatrix() const;
};

// Mesh renderer component
class IMesh;
struct MeshRenderer : Component {
    std::shared_ptr<IMesh> mesh;
    // Material material; // TODO
};

// Camera component
struct Camera : Component {
    float fov = 60.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    bool isActive = true;
    
    glm::mat4 GetProjectionMatrix(float aspect) const;
    glm::mat4 GetViewMatrix(const Transform& transform) const;
};

} // namespace StoneAndSword
```

Create `Engine/ECS/World.h`:

```cpp
#pragma once
#include "Entity.h"
#include "Component.h"
#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>

namespace StoneAndSword {

class IRenderer;

class ECSWorld {
public:
    ECSWorld();
    ~ECSWorld();
    
    // Entity management
    EntityID CreateEntity();
    void DestroyEntity(EntityID entity);
    
    // Component management
    template<typename T>
    T* AddComponent(EntityID entity);
    
    template<typename T>
    T* GetComponent(EntityID entity);
    
    template<typename T>
    void RemoveComponent(EntityID entity);
    
    template<typename T>
    std::vector<EntityID> GetEntitiesWith();
    
    // System updates
    void Update(float deltaTime);
    void Render(IRenderer* renderer);

private:
    EntityID nextEntityID_;
    
    // Component storage: ComponentType -> (EntityID -> Component)
    std::unordered_map<std::type_index, 
        std::unordered_map<EntityID, std::unique_ptr<Component>>> components_;
        
    // Active entities
    std::vector<EntityID> entities_;
};

} // namespace StoneAndSword
```

---

## Phase 7: World Generation Port

### Step 7.1: World Generator Component

Create `Engine/WorldGen/WorldGenerator.h`:

```cpp
#pragma once
#include "../ECS/Component.h"
#include <glm/glm.hpp>
#include <vector>

namespace StoneAndSword {

struct WorldGeneratorConfig {
    int worldSizeX = 10000;
    int worldSizeY = 10000;
    float gridResolution = 100.0f;
    float heightVariation = 50.0f;
    float noiseScale = 0.01f;
    int randomSeed = 12345;
};

class IRenderer;

class WorldGenerator {
public:
    WorldGenerator(const WorldGeneratorConfig& config);
    
    void Generate(ECSWorld* world, IRenderer* renderer);
    
    void SetConfig(const WorldGeneratorConfig& config) { config_ = config; }
    const WorldGeneratorConfig& GetConfig() const { return config_; }

private:
    void GenerateTerrainMesh(std::vector<Vertex>& vertices, 
                            std::vector<uint32_t>& indices);
    
    float CalculateTerrainHeight(float x, float y);
    
    WorldGeneratorConfig config_;
};

} // namespace StoneAndSword
```

Create `Engine/WorldGen/WorldGenerator.cpp`:

```cpp
#include "WorldGenerator.h"
#include "../Renderer/IRenderer.h"
#include "../ECS/World.h"
#include <spdlog/spdlog.h>
#include <cmath>

namespace StoneAndSword {

WorldGenerator::WorldGenerator(const WorldGeneratorConfig& config)
    : config_(config)
{
}

void WorldGenerator::Generate(ECSWorld* world, IRenderer* renderer) {
    spdlog::info("Generating world: {}x{}", config_.worldSizeX, config_.worldSizeY);
    
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    
    GenerateTerrainMesh(vertices, indices);
    
    // Create mesh
    auto mesh = renderer->CreateMesh();
    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->Upload();
    
    // Create terrain entity
    EntityID terrainEntity = world->CreateEntity();
    auto* transform = world->AddComponent<Transform>(terrainEntity);
    transform->position = glm::vec3(0.0f, 0.0f, 0.0f);
    
    auto* meshRenderer = world->AddComponent<MeshRenderer>(terrainEntity);
    meshRenderer->mesh = mesh;
    
    spdlog::info("World generated: {} vertices, {} triangles", 
                 vertices.size(), indices.size() / 3);
}

void WorldGenerator::GenerateTerrainMesh(std::vector<Vertex>& vertices, 
                                        std::vector<uint32_t>& indices) {
    int numVerticesX = static_cast<int>(config_.worldSizeX / config_.gridResolution) + 1;
    int numVerticesY = static_cast<int>(config_.worldSizeY / config_.gridResolution) + 1;
    
    vertices.reserve(numVerticesX * numVerticesY);
    indices.reserve((numVerticesX - 1) * (numVerticesY - 1) * 6);
    
    // Generate vertices
    for (int y = 0; y < numVerticesY; ++y) {
        for (int x = 0; x < numVerticesX; ++x) {
            float worldX = x * config_.gridResolution - (config_.worldSizeX * 0.5f);
            float worldY = y * config_.gridResolution - (config_.worldSizeY * 0.5f);
            float height = CalculateTerrainHeight(worldX, worldY);
            
            Vertex vertex;
            vertex.position = glm::vec3(worldX, height, worldY);
            vertex.normal = glm::vec3(0.0f, 1.0f, 0.0f); // Will be calculated later
            vertex.texCoord = glm::vec2(
                static_cast<float>(x) / (numVerticesX - 1) * 10.0f,
                static_cast<float>(y) / (numVerticesY - 1) * 10.0f
            );
            
            // Height-based color
            float colorValue = (128.0f + height) / 255.0f;
            vertex.color = glm::vec4(colorValue, colorValue, colorValue, 1.0f);
            
            vertices.push_back(vertex);
        }
    }
    
    // Generate indices
    for (int y = 0; y < numVerticesY - 1; ++y) {
        for (int x = 0; x < numVerticesX - 1; ++x) {
            uint32_t bottomLeft = y * numVerticesX + x;
            uint32_t bottomRight = bottomLeft + 1;
            uint32_t topLeft = (y + 1) * numVerticesX + x;
            uint32_t topRight = topLeft + 1;
            
            // First triangle
            indices.push_back(bottomLeft);
            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            
            // Second triangle
            indices.push_back(bottomRight);
            indices.push_back(topLeft);
            indices.push_back(topRight);
        }
    }
}

float WorldGenerator::CalculateTerrainHeight(float x, float y) {
    // Simple multi-octave noise using sine waves
    float height = 0.0f;
    float frequency = config_.noiseScale;
    float amplitude = config_.heightVariation;
    
    for (int octave = 0; octave < 3; ++octave) {
        height += std::sin(x * frequency) * std::cos(y * frequency) * amplitude;
        frequency *= 2.0f;
        amplitude *= 0.5f;
    }
    
    return height;
}

} // namespace StoneAndSword
```

---

## Phase 8: Character Controller Port

### Step 8.1: Character Controller Component

Create `Engine/Gameplay/CharacterController.h`:

```cpp
#pragma once
#include "../ECS/Component.h"
#include <glm/glm.hpp>

namespace StoneAndSword {

struct CharacterController : Component {
    float movementSpeed = 5.0f;
    float rotationSpeed = 2.0f;
    float jumpForce = 10.0f;
    
    glm::vec3 velocity = glm::vec3(0.0f);
    bool isGrounded = true;
};

class CharacterControllerSystem {
public:
    void Update(ECSWorld* world, float deltaTime);
    
private:
    void ProcessInput(EntityID entity, CharacterController* controller, 
                     Transform* transform, float deltaTime);
    void ApplyGravity(CharacterController* controller, float deltaTime);
};

} // namespace StoneAndSword
```

---

## Phase 9: Polish and Documentation

### Step 9.1: Build System

Create comprehensive CMakeLists.txt files for each module.

### Step 9.2: Documentation

Create the following documentation files:
- BUILD_GUIDE.md - How to build the engine
- API_REFERENCE.md - Complete API documentation
- SCRIPTING_API.md - Lua API reference
- TUTORIAL.md - Getting started tutorial

### Step 9.3: Example Game

Create a complete example game that demonstrates:
- World generation
- Character movement
- Camera control
- Lua scripting

---

## Implementation Checklist

- [ ] Phase 1: Foundation Setup
  - [ ] Create directory structure
  - [ ] Setup CMake build system
  - [ ] Install dependencies via vcpkg
  
- [ ] Phase 2: Core Engine Framework
  - [ ] Implement Engine class
  - [ ] Implement Window class (Win32)
  - [ ] Implement game loop
  - [ ] Create main entry point
  
- [ ] Phase 3: Rendering Abstraction
  - [ ] Define IRenderer interface
  - [ ] Define IMesh interface
  - [ ] Define IShader interface
  - [ ] Define ITexture interface
  
- [ ] Phase 4: Rendering Backends
  - [ ] Implement DirectX 11 renderer
  - [ ] Implement DirectX 11 mesh
  - [ ] Implement DirectX 11 shader
  - [ ] Implement Vulkan renderer (optional)
  - [ ] Implement OpenGL renderer (optional)
  
- [ ] Phase 5: Lua Scripting Integration
  - [ ] Integrate Lua 5.4
  - [ ] Setup LuaBridge3
  - [ ] Register engine API
  - [ ] Create example scripts
  
- [ ] Phase 6: Game Systems
  - [ ] Implement ECS framework
  - [ ] Implement Transform component
  - [ ] Implement MeshRenderer component
  - [ ] Implement Camera component
  - [ ] Implement render system
  
- [ ] Phase 7: World Generation Port
  - [ ] Port WorldGenerator from UE
  - [ ] Implement terrain mesh generation
  - [ ] Implement height calculation
  - [ ] Test world generation
  
- [ ] Phase 8: Character Controller Port
  - [ ] Port CharacterController from UE
  - [ ] Implement input handling
  - [ ] Implement movement physics
  - [ ] Implement camera system
  
- [ ] Phase 9: Polish and Documentation
  - [ ] Write BUILD_GUIDE.md
  - [ ] Write API_REFERENCE.md
  - [ ] Write SCRIPTING_API.md
  - [ ] Create tutorial project
  - [ ] Test on multiple systems

---

## Timeline Estimates

- **Phase 1-2**: 2-3 weeks (Core framework)
- **Phase 3-4**: 3-4 weeks (Rendering system)
- **Phase 5**: 1-2 weeks (Lua integration)
- **Phase 6**: 2-3 weeks (ECS and game systems)
- **Phase 7**: 1-2 weeks (World generation port)
- **Phase 8**: 1-2 weeks (Character controller port)
- **Phase 9**: 1-2 weeks (Polish and documentation)

**Total**: 11-18 weeks (3-4.5 months)

---

## Next Steps

1. Start with Phase 1: Set up the project structure
2. Install all dependencies
3. Create the basic CMake build system
4. Begin implementing the core engine framework

For more details, see:
- **ENGINE_ARCHITECTURE.md** - Overall architecture
- **DEPENDENCIES.md** - Complete dependency list
- **API_REFERENCE.md** - API documentation (to be created)
