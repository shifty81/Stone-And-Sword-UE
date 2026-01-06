# Stone and Sword - Game Engine Project

> **⚠️ FIRST TIME OPENING THE PROJECT?** When you see "missing modules" prompt, **CLICK YES**! See **[FIRST_TIME_SETUP.md](FIRST_TIME_SETUP.md)** for what to do.

> **❓ "Can I open this in Unreal Engine?"** YES! See **[WHATS_LEFT.md](WHATS_LEFT.md)** for exactly what you need to do (5-10 minutes of asset creation).

> **📚 New to this project?** Check out **[DOCUMENTATION_INDEX.md](DOCUMENTATION_INDEX.md)** to find the right guide for you!

> **🔧 Getting "StoneAndSword could not be compiled" error?** See **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)** for solutions or use the automated build script: `.\BuildProject.ps1`

## 🚀 Quick Start (Get Playing in 10 Minutes!)

**The project opens in Unreal Engine 5.6 right now!** You just need to create 2 simple assets:

### Option 1: Automated (5 minutes) ⚡
1. Open the project in Unreal Engine 5.6
2. Run: `py Content/Python/setup_project_assets.py`
3. Restart editor and press Play!

**See:** [Content/Python/README.md](Content/Python/README.md)

### Option 2: Manual (10 minutes) 📝
Follow **[QUICK_START.md](QUICK_START.md)** to manually:
- Create a level with lighting and sky
- Create a terrain material
- Test your procedurally generated world

**For comprehensive setup instructions**, see **[SETUP_INSTRUCTIONS.md](SETUP_INSTRUCTIONS.md)**.  
**To understand the full project**, see **[PROJECT_STATUS.md](PROJECT_STATUS.md)**.  
**To see what's needed**, see **[WHATS_LEFT.md](WHATS_LEFT.md)**.

## 🎮 Project Overview

Stone and Sword is evolving from an Unreal Engine 5.4 project to a **custom C++ game engine** with **Lua scripting** support and modern rendering backends (**DirectX 11/12**, **Vulkan**, **OpenGL**).

### Current State (Unreal Engine 5.6.1)
- ✅ Complete C++ source code for procedural world generation
- ✅ First-person character controller with camera
- ✅ Automatic world setup system
- ✅ WASD movement, mouse look, jump mechanics
- ✅ FPS-style controls and rotation
- ✅ Basic terrain textures (grass, stone, dirt, normal maps)
- ✅ Ready to open in Unreal Engine 5.6 and start building
- ⚠️ **Requires creating map and materials in Unreal Editor** (10-minute setup, see QUICK_START.md)

### Target State (Custom Engine)
- 🎯 C++ core engine with modular architecture
- 🎯 Lua scripting for game logic
- 🎯 Multiple rendering backends (DirectX 11/12, Vulkan, OpenGL)
- 🎯 Entity Component System (ECS)
- 🎯 Cross-platform potential
- 🎯 Lightweight and performant
- 🎯 Designed as a framework for building other games

## 📚 Documentation

### Getting Started with Unreal Engine 5.6

1. **[QUICK_START.md](QUICK_START.md)** ⚡ **START HERE!**
   - 10-minute fast-track setup
   - Create your first playable scene
   - Test movement and controls
   - Minimal steps to get playing

2. **[CHARACTER_SETUP_GUIDE.md](CHARACTER_SETUP_GUIDE.md)** 🎮 **Add Visible Arms! (Optional)**
   - Add optional first-person arms/hands with animations
   - Use free store assets (UE First Person Template, Mixamo, Marketplace)
   - Fully C++ FPS gameplay (already implemented)
   - Pure FPS works by default (no visible body needed)
   - Step-by-step for each method (5-20 minutes)

3. **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)** 🔧 **Build Issues?**
   - Complete guide to fixing "StoneAndSword could not be compiled" errors
   - Step-by-step solutions for all common build problems
   - Automated build script included
   - Prerequisites checklist and verification

4. **[SETUP_INSTRUCTIONS.md](SETUP_INSTRUCTIONS.md)** 📖
   - Comprehensive setup guide
   - Detailed explanations for each step
   - Adding proper animations and character models
   - Customization options
   - Troubleshooting guide

5. **[QUICKSTART.md](QUICKSTART.md)** (Legacy)
   - Original quick start guide
   - Building and packaging instructions
   - Advanced customization

### Custom Engine Documentation

This repository also contains **comprehensive documentation** for transitioning to a custom engine:

1. **[ENGINE_ARCHITECTURE.md](ENGINE_ARCHITECTURE.md)** ⭐
   - Complete architecture design
   - System diagrams and data flow
   - Technology stack
   - Design patterns
   - Performance considerations

2. **[DEPENDENCIES.md](DEPENDENCIES.md)**
   - Complete list of required libraries
   - Version compatibility matrix
   - Installation guide (vcpkg)
   - License compliance information
   - Platform requirements

3. **[IMPLEMENTATION_GUIDE.md](IMPLEMENTATION_GUIDE.md)** ⭐
   - Step-by-step implementation guide
   - 9 phases from foundation to polish
   - Complete code examples
   - Best practices
   - Timeline estimates (11-18 weeks)

4. **[BUILD_GUIDE.md](BUILD_GUIDE.md)**
   - Detailed build instructions
   - CMake configuration
   - Troubleshooting guide
   - Build scripts
   - Distribution packaging

5. **[SCRIPTING_API.md](SCRIPTING_API.md)**
   - Complete Lua API reference
   - Engine bindings
   - Component API
   - Example scripts
   - Best practices

6. **[MIGRATION_CHECKLIST.md](MIGRATION_CHECKLIST.md)** ⭐
   - Comprehensive functionality checklist
   - Missing functionality analysis
   - Priority matrix
   - Effort estimates
   - Success criteria

### Legacy Documentation (Unreal Engine)

- **[PROJECT_OVERVIEW.md](PROJECT_OVERVIEW.md)** - Original UE architecture
- **[QUICKSTART.md](QUICKSTART.md)** - UE quick start guide
- **[MATERIALS.md](MATERIALS.md)** - UE material guide
- **[TESTING.md](TESTING.md)** - UE testing guide
- **[CREATING_DEFAULT_MAP.md](CREATING_DEFAULT_MAP.md)** - UE map setup

## 🏗️ Architecture Overview

### Custom Engine Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                    STONE AND SWORD ENGINE                        │
│            Custom C++ Game Engine with Lua Scripting             │
└─────────────────────────────────────────────────────────────────┘

                              ▼
┌──────────────────────────────────────────────────────────────────┐
│  Application Layer    │  Window, Game Loop, Event System         │
├──────────────────────────────────────────────────────────────────┤
│  Scripting Layer      │  Lua 5.4 + LuaBridge3                    │
├──────────────────────────────────────────────────────────────────┤
│  Game Systems         │  ECS, World Gen, Character, Physics      │
├──────────────────────────────────────────────────────────────────┤
│  Rendering Layer      │  Renderer Interface, Materials, Meshes   │
├──────────────────────────────────────────────────────────────────┤
│  Graphics Backends    │  DirectX 11/12, Vulkan, OpenGL           │
├──────────────────────────────────────────────────────────────────┤
│  Platform Layer       │  Windows API, File I/O, Threading        │
└──────────────────────────────────────────────────────────────────┘
```

### Key Features

- 🎨 **Multiple Rendering Backends**
  - DirectX 11 (primary)
  - DirectX 12 (modern)
  - Vulkan (cross-platform)
  - OpenGL (compatibility)

- 🔧 **Modern C++ Core**
  - C++17/20 standards
  - Entity Component System
  - Smart pointers and RAII
  - Multi-threaded architecture

- 📝 **Lua Scripting**
  - High-level game logic
  - Hot-reloadable scripts
  - Full engine API access
  - Easy prototyping

- 🌍 **Procedural World Generation**
  - Port of existing UE system
  - 12 distinct biome types (Tropical Jungle, Desert, Mountains, etc.)
  - Huge biome worlds (3-10x scalable)
  - Perlin noise-based height maps (Fractional Brownian Motion)
  - Multi-octave detail control
  - Biome-specific terrain characteristics
  - Multi-scene architecture for boat/ferry traversal
  - Material splatting

- 🎮 **Character Controller**
  - WASD movement
  - Mouse look
  - Jump mechanics
  - Gamepad support

## 🚀 Quick Start

### Option 1: Use Existing Unreal Engine Project

```bash
# Clone repository
git clone https://github.com/shifty81/Stone-And-Sword-UE.git
cd Stone-And-Sword-UE

# Open in Unreal Engine
# Double-click StoneAndSword.uproject

# Or generate Visual Studio project
# Right-click StoneAndSword.uproject > Generate Visual Studio project files
```

### Option 2: Start Custom Engine Development

```bash
# 1. Read the documentation
# Start with ENGINE_ARCHITECTURE.md and IMPLEMENTATION_GUIDE.md

# 2. Install dependencies
# See DEPENDENCIES.md for complete list

# 3. Follow implementation guide
# IMPLEMENTATION_GUIDE.md provides step-by-step instructions

# 4. Build with CMake
# See BUILD_GUIDE.md for build instructions
```

## 📋 Implementation Roadmap

### Phase 1: Foundation (Weeks 1-4) ✅ Planned
- Project structure and CMake setup
- Core engine framework
- Window management
- Game loop

### Phase 2: Rendering (Weeks 5-8) ✅ Planned
- Rendering abstraction layer
- DirectX 11 backend
- Mesh and shader support
- Basic material system

### Phase 3: Scripting (Weeks 9-10) ✅ Planned
- Lua integration
- C++ ↔ Lua bindings
- Script loading and execution
- Hot-reloading

### Phase 4: ECS (Weeks 11-13) ✅ Planned
- Entity Component System
- Common components (Transform, MeshRenderer, Camera)
- System architecture
- Component storage

### Phase 5: World Generation (Weeks 14-15) ✅ Planned
- Port from Unreal Engine
- Terrain mesh generation
- Height calculation
- Material application

### Phase 6: Character Controller (Weeks 16-17) ✅ Planned
- Port from Unreal Engine
- Movement physics
- Camera system
- Input handling

### Phase 7: Polish (Week 18) ✅ Planned
- Bug fixes
- Optimization
- Documentation updates
- Example projects

## 🎯 Goals and Benefits

### Why Custom Engine?

1. **Full Control**
   - Complete control over architecture
   - No engine overhead
   - Tailored to specific needs

2. **Lightweight**
   - Smaller binary size
   - Faster compilation
   - Lower memory footprint

3. **Learning**
   - Deep understanding of game engines
   - Graphics programming skills
   - Architecture design experience

4. **Flexibility**
   - Lua scripting for rapid iteration
   - Multiple rendering backends
   - Easy to extend

5. **Game Creation Platform**
   - Designed to host multiple games
   - API for game developers
   - Reusable components

### Current Unreal Engine Features (To Port)

- ✅ Procedural world generation
- ✅ Character controller with camera
- ✅ Input system (keyboard, mouse, gamepad)
- ✅ Material system
- ✅ Configuration files
- ✅ Auto-setup system

## 📦 Dependencies

### Essential (MVP)
- Visual Studio 2022
- CMake 3.20+
- Windows SDK 10.0.19041+
- Lua 5.4.6
- LuaBridge3
- GLM (mathematics)
- stb_image (image loading)

### Optional
- Vulkan SDK (Vulkan backend)
- GLFW (windowing)
- OpenAL Soft (audio)
- PhysX (physics)
- Assimp (model loading)

See **[DEPENDENCIES.md](DEPENDENCIES.md)** for complete list and installation guide.

## 🛠️ Technology Stack

### Core
- **Language**: C++17/20
- **Build System**: CMake 3.20+
- **Compiler**: MSVC 2019+

### Scripting
- **Language**: Lua 5.4+
- **Binding**: LuaBridge3 or Sol2

### Graphics
- **DirectX 11**: Windows compatibility
- **DirectX 12**: Modern Windows
- **Vulkan**: Cross-platform, modern
- **OpenGL 4.5+**: Maximum compatibility

### Libraries
- **GLM**: Mathematics
- **stb_image**: Image loading
- **spdlog**: Logging
- **nlohmann/json**: Configuration

## 📊 Effort Estimates

| Component | Effort | Priority |
|-----------|--------|----------|
| Core Engine | 2-3 weeks | CRITICAL |
| DirectX 11 | 2-3 weeks | CRITICAL |
| Lua Scripting | 1-2 weeks | CRITICAL |
| ECS System | 2-3 weeks | CRITICAL |
| World Gen Port | 1-2 weeks | CRITICAL |
| Character Port | 1-2 weeks | CRITICAL |
| Input System | 1 week | CRITICAL |
| **MVP Total** | **11-18 weeks** | - |

## 🎓 Learning Resources

### For Engine Development
1. [Game Engine Architecture by Jason Gregory](https://www.gameenginebook.com/)
2. [Real-Time Rendering](https://www.realtimerendering.com/)
3. [LearnOpenGL](https://learnopengl.com/)
4. [Vulkan Tutorial](https://vulkan-tutorial.com/)

### For Graphics APIs
- **DirectX 11**: [Microsoft DirectX Documentation](https://docs.microsoft.com/en-us/windows/win32/directx)
- **DirectX 12**: [DirectX 12 Programming Guide](https://docs.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-guide)
- **Vulkan**: [Vulkan Guide](https://github.com/KhronosGroup/Vulkan-Guide)
- **OpenGL**: [docs.gl](https://docs.gl/)

### For Lua Scripting
- [Programming in Lua](https://www.lua.org/pil/)
- [LuaBridge Documentation](https://github.com/kunitoki/LuaBridge3)

## 🤝 Contributing

This project is designed as a learning resource and game engine framework. Contributions are welcome!

### How to Contribute
1. Read the documentation thoroughly
2. Follow the implementation guide
3. Test your changes
4. Submit pull requests with clear descriptions

## 📄 License

See [LICENSE](LICENSE) file for details.

## 🔗 Links

- **Repository**: https://github.com/shifty81/Stone-And-Sword-UE
- **Documentation**: See docs listed above
- **Original UE Project**: Current `main` branch

## 📞 Support

For questions or issues:
1. Check the comprehensive documentation
2. Review troubleshooting sections in BUILD_GUIDE.md
3. Open an issue on GitHub

## 🎉 Status

**Current**: Documentation complete ✅
**Next**: Begin implementation following the guide

All documentation has been created to guide the complete migration from Unreal Engine to a custom C++ game engine with Lua scripting. The project is ready for implementation!

---

**Note**: This project demonstrates the transition from a high-level engine (Unreal Engine) to a custom low-level engine, providing deep learning opportunities in game engine architecture, graphics programming, and systems design.
