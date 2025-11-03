# Build Guide: Stone and Sword Custom Engine

## Overview

This guide explains how to build the Stone and Sword custom C++ game engine with Lua scripting support and multiple rendering backends.

## Prerequisites

### Required Software

1. **Visual Studio 2022** (or 2019)
   - Workload: Desktop development with C++
   - Component: C++ CMake tools for Windows
   - Component: Windows 10 SDK (10.0.19041.0 or later)
   - Download: https://visualstudio.microsoft.com/

2. **CMake 3.20+**
   - Download installer from: https://cmake.org/download/
   - Add to PATH during installation

3. **Git**
   - Download from: https://git-scm.com/
   - Needed for vcpkg and source control

4. **vcpkg** (Recommended for dependency management)
   - Will be installed in setup steps below

### Optional Software

- **Ninja Build System** - Faster builds
  - Download: https://ninja-build.org/
  - Extract to C:\Ninja and add to PATH

- **Vulkan SDK** - If building Vulkan backend
  - Download: https://vulkan.lunarg.com/
  - Version 1.3.268 or later

## Quick Start

### Option 1: Automated Setup (Recommended)

```powershell
# Clone the repository
git clone https://github.com/yourusername/Stone-And-Sword-UE.git
cd Stone-And-Sword-UE

# Run the setup script
.\Tools\Setup.ps1

# Build the project
.\Tools\Build.ps1 -Configuration Release

# Run the game
.\Build\bin\Release\StoneAndSword.exe
```

### Option 2: Manual Setup

Follow the detailed steps below for manual configuration.

## Detailed Build Instructions

### Step 1: Install vcpkg

```powershell
# Create a directory for vcpkg (can be anywhere)
cd C:\
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# Bootstrap vcpkg
.\bootstrap-vcpkg.bat

# Integrate with Visual Studio
.\vcpkg integrate install

# Set environment variable for future use
[System.Environment]::SetEnvironmentVariable('VCPKG_ROOT', 'C:\vcpkg', 'User')
```

### Step 2: Install Dependencies

```powershell
cd C:\vcpkg

# Essential dependencies
.\vcpkg install glm:x64-windows
.\vcpkg install lua:x64-windows
.\vcpkg install spdlog:x64-windows
.\vcpkg install nlohmann-json:x64-windows
.\vcpkg install fmt:x64-windows

# Windowing library (choose one)
.\vcpkg install glfw3:x64-windows

# OpenGL support (if using OpenGL backend)
.\vcpkg install glew:x64-windows

# Audio support (optional)
.\vcpkg install openal-soft:x64-windows

# Physics support (optional)
.\vcpkg install physx:x64-windows

# Model loading (optional)
.\vcpkg install assimp:x64-windows

# Vulkan support (if using Vulkan backend)
.\vcpkg install vulkan-memory-allocator:x64-windows
```

This will take some time (10-30 minutes depending on your system).

### Step 3: Install Vulkan SDK (Optional)

Only needed if building with Vulkan backend support:

1. Download Vulkan SDK from https://vulkan.lunarg.com/
2. Run the installer
3. Default installation location: `C:\VulkanSDK\1.3.268.0`
4. The installer will set the `VULKAN_SDK` environment variable

Verify installation:
```powershell
echo $env:VULKAN_SDK
# Should output: C:\VulkanSDK\1.3.268.0
```

### Step 4: Clone Repository

```powershell
# Clone the repository
git clone https://github.com/yourusername/Stone-And-Sword-UE.git
cd Stone-And-Sword-UE
```

### Step 5: Configure with CMake

```powershell
# Create build directory
mkdir Build
cd Build

# Configure with CMake (using Visual Studio generator)
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
         -DCMAKE_BUILD_TYPE=Release `
         -DBUILD_WITH_DX11=ON `
         -DBUILD_WITH_DX12=ON `
         -DBUILD_WITH_VULKAN=ON `
         -DBUILD_WITH_OPENGL=ON

# Or using Ninja for faster builds
cmake .. -G Ninja `
         -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
         -DCMAKE_BUILD_TYPE=Release `
         -DBUILD_WITH_DX11=ON
```

### Step 6: Build

#### Using CMake
```powershell
# Build Release configuration
cmake --build . --config Release

# Build Debug configuration
cmake --build . --config Debug

# Build with multiple CPU cores (faster)
cmake --build . --config Release -- /m
```

#### Using Visual Studio IDE
```powershell
# Open the solution in Visual Studio
start StoneAndSword.sln

# Then in Visual Studio:
# 1. Select "Release" or "Debug" configuration
# 2. Press Ctrl+Shift+B to build
# 3. Or: Build > Build Solution
```

#### Using Ninja
```powershell
ninja
```

### Step 7: Run

```powershell
# Run the game
.\bin\Release\StoneAndSword.exe

# Or from Visual Studio: Press F5 (Debug) or Ctrl+F5 (Run without debugging)
```

## Build Configurations

### Debug Build
- Includes debug symbols
- No optimizations
- Runtime checks enabled
- Larger executable size
- Slower performance
- Use for development and debugging

```powershell
cmake --build . --config Debug
```

### Release Build
- Full optimizations
- No debug symbols
- Fastest performance
- Smaller executable size
- Use for distribution

```powershell
cmake --build . --config Release
```

### RelWithDebInfo Build
- Optimizations enabled
- Debug symbols included
- Good for profiling
- Balance between Debug and Release

```powershell
cmake --build . --config RelWithDebInfo
```

## CMake Configuration Options

### Rendering Backend Options

```powershell
# Enable/disable rendering backends
-DBUILD_WITH_DX11=ON       # DirectX 11 support (default: ON)
-DBUILD_WITH_DX12=ON       # DirectX 12 support (default: ON)
-DBUILD_WITH_VULKAN=ON     # Vulkan support (default: ON if SDK found)
-DBUILD_WITH_OPENGL=ON     # OpenGL support (default: ON)
```

### Feature Options

```powershell
-DBUILD_WITH_PHYSICS=ON    # Physics engine support (default: ON if available)
-DBUILD_WITH_AUDIO=ON      # Audio system support (default: ON if available)
-DBUILD_EXAMPLES=ON        # Build example projects (default: ON)
-DBUILD_TESTS=ON           # Build unit tests (default: OFF)
```

### Advanced Options

```powershell
-DENABLE_PROFILING=ON      # Enable profiling instrumentation (default: OFF)
-DENABLE_LOGGING=ON        # Enable logging (default: ON)
-DUSE_STATIC_RUNTIME=ON    # Link against static CRT (default: OFF)
```

## Build Scripts

### Windows PowerShell Scripts

Create `Tools/Setup.ps1`:
```powershell
# Setup script for Windows
param(
    [string]$VcpkgRoot = "C:\vcpkg"
)

Write-Host "Setting up Stone and Sword Engine..." -ForegroundColor Green

# Check if vcpkg exists
if (-not (Test-Path $VcpkgRoot)) {
    Write-Host "Installing vcpkg..." -ForegroundColor Yellow
    git clone https://github.com/microsoft/vcpkg.git $VcpkgRoot
    cd $VcpkgRoot
    .\bootstrap-vcpkg.bat
    .\vcpkg integrate install
}

# Install dependencies
Write-Host "Installing dependencies..." -ForegroundColor Yellow
cd $VcpkgRoot

$packages = @(
    "glm:x64-windows",
    "lua:x64-windows",
    "spdlog:x64-windows",
    "nlohmann-json:x64-windows",
    "fmt:x64-windows",
    "glfw3:x64-windows",
    "glew:x64-windows"
)

foreach ($package in $packages) {
    Write-Host "Installing $package..." -ForegroundColor Cyan
    .\vcpkg install $package
}

Write-Host "Setup complete!" -ForegroundColor Green
```

Create `Tools/Build.ps1`:
```powershell
# Build script for Windows
param(
    [string]$Configuration = "Release",
    [string]$VcpkgRoot = "C:\vcpkg"
)

Write-Host "Building Stone and Sword Engine ($Configuration)..." -ForegroundColor Green

# Create build directory
if (-not (Test-Path "Build")) {
    New-Item -ItemType Directory -Path "Build"
}

cd Build

# Configure
Write-Host "Configuring with CMake..." -ForegroundColor Yellow
cmake .. -DCMAKE_TOOLCHAIN_FILE="$VcpkgRoot/scripts/buildsystems/vcpkg.cmake" `
         -DCMAKE_BUILD_TYPE=$Configuration

# Build
Write-Host "Building..." -ForegroundColor Yellow
cmake --build . --config $Configuration -- /m

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build successful!" -ForegroundColor Green
} else {
    Write-Host "Build failed!" -ForegroundColor Red
    exit 1
}
```

### Usage

```powershell
# Setup (first time only)
.\Tools\Setup.ps1

# Build Release
.\Tools\Build.ps1 -Configuration Release

# Build Debug
.\Tools\Build.ps1 -Configuration Debug
```

## Troubleshooting

### Issue: CMake can't find vcpkg

**Solution**:
```powershell
# Set the toolchain file explicitly
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Or set environment variable
$env:CMAKE_TOOLCHAIN_FILE = "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

### Issue: Can't find Vulkan SDK

**Solution**:
```powershell
# Set VULKAN_SDK environment variable
$env:VULKAN_SDK = "C:\VulkanSDK\1.3.268.0"

# Or disable Vulkan support
cmake .. -DBUILD_WITH_VULKAN=OFF
```

### Issue: DirectX headers not found

**Solution**:
- Install Windows SDK via Visual Studio Installer
- Ensure "Windows 10 SDK" is selected
- Version 10.0.19041.0 or later

### Issue: Build fails with linker errors

**Solution**:
```powershell
# Clean and rebuild
cmake --build . --target clean
cmake --build . --config Release

# Or delete Build directory and start over
cd ..
rm -r Build
mkdir Build
cd Build
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
cmake --build . --config Release
```

### Issue: vcpkg packages fail to install

**Solution**:
```powershell
# Update vcpkg
cd C:\vcpkg
git pull
.\bootstrap-vcpkg.bat

# Try installing again
.\vcpkg install glm:x64-windows
```

### Issue: Runtime DLL not found

**Solution**:
- For Debug builds, ensure Debug DLLs are in PATH or copied to exe directory
- For Release builds, ensure Release DLLs are available
- vcpkg typically installs DLLs to `vcpkg\installed\x64-windows\bin\`

```powershell
# Copy DLLs to exe directory
cp C:\vcpkg\installed\x64-windows\bin\*.dll Build\bin\Release\
```

## Directory Structure After Build

```
Stone-And-Sword-UE/
├── Build/                  # Build output (created during build)
│   ├── bin/               # Executables
│   │   ├── Debug/
│   │   │   └── StoneAndSword.exe
│   │   └── Release/
│   │       └── StoneAndSword.exe
│   ├── lib/               # Static libraries
│   └── CMakeFiles/        # CMake temporary files
├── Engine/                # Engine source
├── Game/                  # Game source
├── ThirdParty/           # External libraries
└── Tools/                # Build scripts
```

## Building for Distribution

### Step 1: Build Release Configuration

```powershell
cmake --build . --config Release
```

### Step 2: Copy Runtime Dependencies

```powershell
# Create distribution directory
mkdir Distribution
cd Distribution

# Copy executable
cp ../Build/bin/Release/StoneAndSword.exe .

# Copy required DLLs
cp C:\vcpkg\installed\x64-windows\bin\lua54.dll .
cp C:\vcpkg\installed\x64-windows\bin\OpenAL32.dll .
# Add other DLLs as needed

# Copy game assets
cp -r ../Game/Assets .
cp -r ../Game/Scripts .
```

### Step 3: Test Distribution

```powershell
# Test the distribution
.\StoneAndSword.exe

# If missing DLLs, use Dependency Walker or dumpbin to identify them
# dumpbin /dependents StoneAndSword.exe
```

### Step 4: Create Installer (Optional)

Use NSIS, Inno Setup, or WiX to create an installer.

## Performance Tips

### 1. Use Ninja for Faster Builds

```powershell
# Install Ninja (using vcpkg)
.\vcpkg install ninja

# Configure with Ninja
cmake .. -G Ninja -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake"

# Build (Ninja automatically uses all CPU cores)
ninja
```

### 2. Use Parallel Compilation

```powershell
# MSBuild: Use /m flag
cmake --build . --config Release -- /m

# Or set number of cores
cmake --build . --config Release -- /m:8
```

### 3. Use Precompiled Headers

Already configured in CMakeLists.txt for faster compilation.

### 4. Enable Incremental Linking (Debug)

Speeds up debug builds. Enabled by default in Debug configuration.

## Build Size Optimization

### Release Build Optimizations

```cmake
# In CMakeLists.txt
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Enable link-time optimization
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    
    # Strip symbols
    if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /OPT:REF /OPT:ICF")
    endif()
endif()
```

### Expected Build Sizes

- Debug build: 20-50 MB (with debug symbols)
- Release build: 5-20 MB (optimized)
- Distribution package: 50-200 MB (with assets)

## Continuous Integration

### GitHub Actions Example

Create `.github/workflows/build.yml`:

```yaml
name: Build

on: [push, pull_request]

jobs:
  build-windows:
    runs-on: windows-latest
    
    steps:
    - uses: actions/checkout@v3
    
    - name: Install vcpkg
      run: |
        git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
        C:\vcpkg\bootstrap-vcpkg.bat
        
    - name: Install dependencies
      run: |
        C:\vcpkg\vcpkg install glm:x64-windows lua:x64-windows spdlog:x64-windows
        
    - name: Configure CMake
      run: |
        mkdir Build
        cd Build
        cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
        
    - name: Build
      run: |
        cd Build
        cmake --build . --config Release
        
    - name: Upload artifact
      uses: actions/upload-artifact@v3
      with:
        name: StoneAndSword-Windows
        path: Build/bin/Release/StoneAndSword.exe
```

## Next Steps

After successful build:
1. See **API_REFERENCE.md** for engine API documentation
2. See **SCRIPTING_API.md** for Lua scripting guide
3. See **TUTORIAL.md** for creating your first game
4. See **IMPLEMENTATION_GUIDE.md** for development details

## Support

If you encounter issues not covered here:
1. Check the GitHub Issues page
2. Review the troubleshooting section
3. Check CMake and build logs for detailed error messages
4. Ensure all prerequisites are correctly installed
