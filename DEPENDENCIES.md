# Dependencies and Requirements

## Overview

This document lists all dependencies required to build the custom C++ game engine with Lua scripting support and multiple rendering backends.

## Required Dependencies

### 1. Development Tools

#### Compiler and Build System
- **Visual Studio 2019 or 2022** (Windows)
  - Component: Desktop development with C++
  - Component: C++ CMake tools for Windows
  - Component: Windows 10 SDK (10.0.19041.0 or later)
  - Download: https://visualstudio.microsoft.com/
  
- **CMake 3.20 or later**
  - Used for cross-platform build configuration
  - Download: https://cmake.org/download/
  
- **Git**
  - For version control and dependency management
  - Download: https://git-scm.com/

#### Optional but Recommended
- **Ninja Build System**
  - Faster builds than MSBuild
  - Download: https://ninja-build.org/
  
- **vcpkg** (Recommended)
  - C++ package manager for dependency management
  - GitHub: https://github.com/microsoft/vcpkg

### 2. Core Engine Dependencies

#### Lua Scripting (Required)
- **Lua 5.4.6**
  - Scripting language runtime
  - License: MIT
  - Website: https://www.lua.org/
  - Integration: Source code included in project
  
- **LuaBridge3** or **Sol2** (Choose one)
  - **LuaBridge3** (Recommended)
    - Modern C++17 Lua binding library
    - License: MIT
    - GitHub: https://github.com/kunitoki/LuaBridge3
    - Version: 3.0+
  
  - **Sol2** (Alternative)
    - Header-only C++ Lua binding
    - License: MIT
    - GitHub: https://github.com/ThePhD/sol2
    - Version: 3.3.0+

#### Mathematics Library (Required)
- **GLM (OpenGL Mathematics) 0.9.9.8+**
  - Header-only C++ mathematics library
  - License: MIT
  - GitHub: https://github.com/g-truc/glm
  - Features: Vectors, matrices, quaternions, transforms
  - Install via vcpkg: `vcpkg install glm`

### 3. Rendering Dependencies

#### DirectX 11 (Windows)
- **Windows SDK 10.0.19041.0+**
  - Included with Visual Studio
  - Headers: d3d11.h, d3dcompiler.h
  - Libraries: d3d11.lib, d3dcompiler.lib, dxgi.lib
  
#### DirectX 12 (Windows)
- **Windows SDK 10.0.19041.0+**
  - Included with Visual Studio
  - Headers: d3d12.h, d3dx12.h
  - Libraries: d3d12.lib, dxgi.lib, dxguid.lib
  
- **DirectX 12 Agility SDK** (Optional, for latest features)
  - NuGet: Microsoft.Direct3D.D3D12
  - Version: 1.610.0+

#### Vulkan (Cross-platform)
- **Vulkan SDK 1.3.268+**
  - Download: https://vulkan.lunarg.com/
  - Components:
    - Vulkan runtime
    - Validation layers
    - Shader compiler (glslc)
    - Vulkan Memory Allocator (VMA)
  - License: Apache 2.0
  
- **VulkanMemoryAllocator (VMA)**
  - GitHub: https://github.com/GPUOpen-LibrariesAndSDKs/VulkanMemoryAllocator
  - License: MIT
  - Install via vcpkg: `vcpkg install vulkan-memory-allocator`

#### OpenGL (Cross-platform)
- **GLAD 4.5+ or GLEW**
  - **GLAD** (Recommended)
    - OpenGL loader generator
    - Website: https://glad.dav1d.de/
    - License: MIT/Public Domain
  
  - **GLEW** (Alternative)
    - OpenGL Extension Wrangler
    - Website: http://glew.sourceforge.net/
    - Install via vcpkg: `vcpkg install glew`

### 4. Windowing and Input

#### Option 1: Native Win32 API (Recommended for Windows-only)
- **Windows SDK**
  - Included with Visual Studio
  - No additional dependencies

#### Option 2: GLFW (Cross-platform)
- **GLFW 3.3.8+**
  - Multi-platform library for OpenGL/Vulkan
  - License: zlib/libpng
  - Website: https://www.glfw.org/
  - Install via vcpkg: `vcpkg install glfw3`
  - Features: Window creation, input, OpenGL context

#### Option 3: SDL2 (Cross-platform, full-featured)
- **SDL2 2.28.0+**
  - Simple DirectMedia Layer
  - License: zlib
  - Website: https://www.libsdl.org/
  - Install via vcpkg: `vcpkg install sdl2`
  - Features: Window, input, audio, threading

### 5. Asset Loading

#### Image Loading (Required)
- **stb_image 2.28+**
  - Header-only image loader
  - License: MIT/Public Domain
  - GitHub: https://github.com/nothings/stb
  - Formats: PNG, JPG, TGA, BMP, PSD, GIF, HDR, PIC
  - Integration: Single header file

#### Font Rendering (Optional)
- **stb_truetype**
  - Header-only TrueType font rasterizer
  - License: MIT/Public Domain
  - GitHub: https://github.com/nothings/stb
  - Integration: Single header file

#### 3D Model Loading (Optional)
- **Assimp 5.3.0+**
  - Asset Import Library
  - License: BSD-3-Clause
  - Website: https://www.assimp.org/
  - Install via vcpkg: `vcpkg install assimp`
  - Formats: FBX, OBJ, glTF, COLLADA, etc.

### 6. Audio System (Optional)

#### OpenAL Soft (Recommended)
- **OpenAL Soft 1.23.0+**
  - 3D audio rendering
  - License: LGPL
  - Website: https://openal-soft.org/
  - Install via vcpkg: `vcpkg install openal-soft`
  
#### Audio File Loading
- **libsndfile** or **dr_libs**
  - **libsndfile**
    - License: LGPL
    - Install via vcpkg: `vcpkg install libsndfile`
  
  - **dr_libs** (Lightweight alternative)
    - Header-only audio decoders
    - License: Public Domain
    - GitHub: https://github.com/mackron/dr_libs

### 7. Physics Engine (Optional)

#### Option 1: PhysX 5.3.0+ (Recommended)
- **NVIDIA PhysX 5**
  - Professional physics engine
  - License: BSD-3-Clause
  - GitHub: https://github.com/NVIDIAGameWorks/PhysX
  - Features: Rigid bodies, collisions, joints, cloth, particles

#### Option 2: Bullet Physics 3.25+
- **Bullet Physics**
  - Open-source physics SDK
  - License: zlib
  - Website: https://pybullet.org/wordpress/
  - Install via vcpkg: `vcpkg install bullet3`

#### Option 3: Box2D (2D only)
- **Box2D 2.4.1+**
  - 2D physics engine
  - License: MIT
  - Website: https://box2d.org/
  - Install via vcpkg: `vcpkg install box2d`

### 8. Utility Libraries

#### JSON Parsing (Configuration files)
- **nlohmann/json 3.11.2+**
  - Modern C++ JSON library
  - License: MIT
  - GitHub: https://github.com/nlohmann/json
  - Install via vcpkg: `vcpkg install nlohmann-json`

#### Logging
- **spdlog 1.12.0+**
  - Fast C++ logging library
  - License: MIT
  - GitHub: https://github.com/gabime/spdlog
  - Install via vcpkg: `vcpkg install spdlog`

#### String Formatting (C++17/20)
- **fmt 10.1.0+**
  - String formatting library
  - License: MIT
  - GitHub: https://github.com/fmtlib/fmt
  - Install via vcpkg: `vcpkg install fmt`
  - Note: Included in C++20 as std::format

## Dependency Installation Guide

### Using vcpkg (Recommended)

#### 1. Install vcpkg
```powershell
# Clone vcpkg
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# Bootstrap vcpkg
.\bootstrap-vcpkg.bat

# Integrate with Visual Studio
.\vcpkg integrate install
```

#### 2. Install Dependencies
```powershell
# Core dependencies
.\vcpkg install glm:x64-windows
.\vcpkg install lua:x64-windows

# Rendering (choose based on needs)
.\vcpkg install glfw3:x64-windows
.\vcpkg install glew:x64-windows

# Vulkan (if using Vulkan backend)
.\vcpkg install vulkan-memory-allocator:x64-windows

# Audio
.\vcpkg install openal-soft:x64-windows

# Physics (optional)
.\vcpkg install physx:x64-windows

# Utilities
.\vcpkg install nlohmann-json:x64-windows
.\vcpkg install spdlog:x64-windows
.\vcpkg install fmt:x64-windows

# Model loading (optional)
.\vcpkg install assimp:x64-windows
```

#### 3. CMake Integration
```cmake
# In CMakeLists.txt
set(CMAKE_TOOLCHAIN_FILE "path/to/vcpkg/scripts/buildsystems/vcpkg.cmake")
```

### Manual Installation

#### Lua
```powershell
# Download from lua.org
# Copy lua.h, lauxlib.h, lualib.h, luaconf.h to include/
# Link against lua54.lib
```

#### LuaBridge3
```powershell
# Header-only library
git clone https://github.com/kunitoki/LuaBridge3.git
# Copy Source/LuaBridge/ to ThirdParty/LuaBridge3/
```

#### GLM
```powershell
# Header-only library
git clone https://github.com/g-truc/glm.git
# Copy glm/ to ThirdParty/glm/
```

#### stb Libraries
```powershell
# Download stb_image.h and stb_truetype.h
# Place in ThirdParty/stb/
```

### Vulkan SDK Installation

1. Download from https://vulkan.lunarg.com/
2. Run installer
3. Set environment variable: `VULKAN_SDK=C:\VulkanSDK\1.3.268.0`
4. Add to PATH: `%VULKAN_SDK%\Bin`

## Version Compatibility Matrix

| Component | Minimum Version | Recommended Version | Notes |
|-----------|----------------|---------------------|-------|
| Visual Studio | 2019 (16.11) | 2022 (17.8) | C++17/20 support |
| CMake | 3.20 | 3.27+ | Modern CMake features |
| Windows SDK | 10.0.19041 | 10.0.22621 | DX11/12 support |
| Lua | 5.4.0 | 5.4.6 | Latest stable |
| LuaBridge3 | 3.0 | 3.0+ | C++17 required |
| GLM | 0.9.9.8 | 1.0.0+ | Header-only |
| Vulkan SDK | 1.3.0 | 1.3.268+ | Latest features |
| GLFW | 3.3 | 3.3.8+ | Window management |
| OpenAL Soft | 1.21 | 1.23+ | Audio system |
| spdlog | 1.10 | 1.12+ | Logging |

## Platform-Specific Requirements

### Windows 10/11 (Primary Target)

**Minimum**:
- Windows 10 version 1903 (build 18362)
- DirectX 11 capable GPU
- 4 GB RAM
- 2 GB disk space

**Recommended**:
- Windows 10 version 22H2 or Windows 11
- DirectX 12 / Vulkan capable GPU
- 8 GB RAM
- 5 GB disk space
- SSD for fast loading

### GPU Requirements

#### DirectX 11
- Feature Level 11.0 or higher
- Most GPUs from 2010 onwards

#### DirectX 12
- Feature Level 12.0 or higher
- NVIDIA: GTX 600 series or newer
- AMD: GCN architecture or newer
- Intel: HD Graphics 4000 or newer

#### Vulkan
- Vulkan 1.2+ support
- NVIDIA: GTX 600 series or newer
- AMD: GCN architecture or newer
- Intel: HD Graphics 4000 or newer

#### OpenGL
- OpenGL 4.5+ support
- Most modern GPUs

## Build Size Estimates

### Source Code
- Engine source: ~50 MB
- Third-party headers: ~20 MB
- Documentation: ~5 MB

### Dependencies (Compiled)
- Lua: ~1 MB
- GLM: ~5 MB (headers)
- GLFW: ~2 MB
- OpenAL: ~3 MB
- Physics (PhysX): ~50 MB
- Vulkan SDK: ~500 MB

### Total Development Environment
- ~1-2 GB (without Visual Studio)
- ~10-15 GB (with Visual Studio and all SDKs)

## Runtime Dependencies (Distribution)

For distributing the compiled game, include:

### Minimum (DirectX 11)
- Game executable: ~5-20 MB
- Lua DLL (if dynamic): ~500 KB
- OpenAL DLL (if using audio): ~2 MB
- D3D11 runtime (included in Windows 10+)
- **Total: ~10-25 MB**

### With All Features
- Game executable: ~10-30 MB
- Lua DLL: ~500 KB
- OpenAL DLL: ~2 MB
- Physics DLL (PhysX): ~10 MB
- Vulkan loader (if using Vulkan): ~2 MB
- **Total: ~25-50 MB**

### Assets (Game-specific)
- Textures: 50-500 MB
- Models: 10-200 MB
- Audio: 50-200 MB
- Scripts: 1-10 MB
- **Total: ~100-1000 MB**

## License Compliance

### Permissive Licenses (No restrictions)
- MIT: Lua, LuaBridge3, GLM, spdlog, fmt, stb
- BSD-3: PhysX, Assimp
- zlib: GLFW, Bullet

### Copyleft Licenses (Source distribution required if modified)
- LGPL: OpenAL Soft
  - Can be dynamically linked without restrictions
  - Source required only if you modify OpenAL itself

### Public Domain
- stb libraries: No restrictions

## Conclusion

### Essential Dependencies (Minimum viable engine)
1. Visual Studio 2022
2. CMake 3.20+
3. Windows SDK 10.0.19041+
4. Lua 5.4.6
5. LuaBridge3
6. GLM
7. stb_image
8. Win32 API (built-in)
9. DirectX 11 (built-in with Windows)

### Recommended Setup
- All essential dependencies
- GLFW for windowing
- OpenAL Soft for audio
- spdlog for logging
- nlohmann/json for config
- PhysX for physics

### Full-Featured Setup
- All recommended dependencies
- Vulkan SDK
- Assimp for model loading
- Additional stb libraries
- Physics engine of choice

## Next Steps

After installing dependencies:
1. See **BUILD_GUIDE.md** for build instructions
2. See **IMPLEMENTATION_GUIDE.md** for development walkthrough
3. See **API_REFERENCE.md** for engine API documentation
