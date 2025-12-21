# Build Troubleshooting Guide

## Issue: "StoneAndSword could not be compiled. Try rebuilding from source manually."

This error occurs when opening the project for the first time or after changes to the C++ code. This guide will help you resolve it.

## Why This Happens

When you open `StoneAndSword.uproject`, Unreal Engine checks for pre-compiled binaries. Since this is a source-controlled project, the `Binaries/` folder is excluded (in `.gitignore`), so you'll always see this prompt on first open.

The compilation failure typically occurs due to:
1. Missing Visual Studio C++ tools
2. Incorrect Unreal Engine version
3. Missing or corrupt intermediate files
4. Insufficient permissions

## Quick Fix (Recommended)

### Step 1: Generate Visual Studio Project Files

**Option A: Using Windows Explorer**
1. Close Unreal Editor (if open)
2. Navigate to your project folder
3. **Right-click** on `StoneAndSword.uproject`
4. Select **"Generate Visual Studio project files"**
5. Wait for completion (30-60 seconds)

**Option B: Using Command Line**
```powershell
# Navigate to your Unreal Engine installation
cd "C:\Program Files\Epic Games\UE_5.6\Engine\Build\BatchFiles"

# Generate project files (replace path with your project location)
.\GenerateProjectFiles.bat "C:\Path\To\Your\Stone-And-Sword-UE\StoneAndSword.uproject"
```

### Step 2: Build from Visual Studio

1. Open `StoneAndSword.sln` (should now be in your project folder)
2. In Visual Studio:
   - Set configuration to **"Development Editor"**
   - Set platform to **"Win64"**
   - Right-click on **"StoneAndSword"** project
   - Select **"Build"**
3. Wait for compilation to complete (2-5 minutes first time)
4. Check the Output window for any errors

### Step 3: Open the Project

1. Double-click `StoneAndSword.uproject`
2. Unreal Editor should now open without errors
3. If prompted again, the modules should now build successfully

## Prerequisites Checklist

Make sure you have all required software installed:

- [ ] **Unreal Engine 5.6 or 5.6.1** from Epic Games Launcher
- [ ] **Visual Studio 2022** (or 2019)
  - Workload: "Game development with C++"
  - Component: "Unreal Engine Installer"
  - Component: "C++ profiling tools" (optional but recommended)
- [ ] **Windows 10 SDK** (10.0.19041.0 or later)
  - Included with Visual Studio "Game development with C++" workload

### Verify Visual Studio Installation

1. Open **Visual Studio Installer**
2. Click **"Modify"** on your Visual Studio installation
3. Ensure **"Game development with C++"** workload is checked
4. Under "Individual components", verify:
   - C++ core features
   - MSVC v143 - VS 2022 C++ x64/x86 build tools (or v142 for VS 2019)
   - Windows 10 SDK

## Alternative Build Methods

### Method 1: Using UnrealBuildTool Directly

```powershell
# Navigate to UE installation
cd "C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\DotNET\UnrealBuildTool"

# Build the module
.\UnrealBuildTool.exe StoneAndSwordEditor Win64 Development -Project="C:\Path\To\StoneAndSword.uproject" -WaitMutex -FromMsBuild
```

### Method 2: Using Unreal Editor with Verbose Logging

1. Launch Unreal Editor from command line with logging:
```powershell
"C:\Program Files\Epic Games\UE_5.6\Engine\Binaries\Win64\UnrealEditor.exe" "C:\Path\To\StoneAndSword.uproject" -log
```
2. This will show detailed compilation output
3. Look for specific errors in the log window

### Method 3: Clean Build

Sometimes intermediate files get corrupted. Try a clean build:

```powershell
# In your project folder
# Delete intermediate and binary files
Remove-Item -Recurse -Force Binaries, Intermediate, Saved, .vs

# Regenerate project files
# Right-click StoneAndSword.uproject > Generate Visual Studio project files

# Open and build in Visual Studio
```

## Common Issues and Solutions

### Issue 1: "Cannot open include file: 'CoreMinimal.h'"

**Cause**: Visual Studio can't find Unreal Engine headers

**Solution**:
1. Regenerate Visual Studio project files
2. In Visual Studio, go to **Tools > Options > Projects and Solutions > VC++ Directories**
3. Verify Unreal Engine paths are included
4. Restart Visual Studio

### Issue 2: "MSB3073: The command ... exited with code 6"

**Cause**: UnrealBuildTool encountered an error

**Solution**:
1. Check the Output window for the actual error
2. Usually indicates a C++ syntax error or missing dependency
3. Scroll up in the output to find the first error message

### Issue 3: "LNK1104: cannot open file 'UnrealEditor-StoneAndSword.lib'"

**Cause**: Previous build artifacts are corrupted

**Solution**:
```powershell
# Delete build artifacts
Remove-Item -Recurse -Force Binaries\Win64, Intermediate\Build

# Rebuild from Visual Studio
```

### Issue 4: "C4819: The file contains a character that cannot be represented"

**Cause**: Source file encoding issue

**Solution**:
1. Open the problematic file in Visual Studio
2. Go to **File > Advanced Save Options**
3. Select **"Unicode (UTF-8 with signature) - Codepage 65001"**
4. Save and rebuild

### Issue 5: "ProceduralMeshComponent module not found"

**Cause**: Plugin not enabled in project

**Solution**:
This shouldn't happen as the plugin is enabled in the `.uproject` file, but if it does:
1. Open the project (even if it shows errors)
2. Go to **Edit > Plugins**
3. Search for **"Procedural Mesh Component"**
4. Ensure it's **enabled**
5. Restart the editor

### Issue 6: "UE 5.6 is not installed"

**Cause**: Engine association mismatch

**Solution**:
1. Right-click `StoneAndSword.uproject`
2. Select **"Switch Unreal Engine version..."**
3. Select your installed version (5.6 or 5.6.1)
4. Try opening again

## Detailed Error Diagnosis

If the above solutions don't work, you need to find the specific error:

### Step 1: Build in Visual Studio with Detailed Output

1. Open `StoneAndSword.sln` in Visual Studio
2. Go to **Tools > Options > Projects and Solutions > Build and Run**
3. Set **"MSBuild project build output verbosity"** to **"Detailed"**
4. Build the project
5. Look for the **first** error in the Output window (scroll to the top)

### Step 2: Check for Specific C++ Errors

Common C++ compilation errors:
- **Syntax errors**: Missing semicolons, brackets, etc.
- **Undefined symbols**: Missing `#include` statements
- **Linker errors**: Missing libraries or wrong library versions
- **Type mismatches**: Incorrect function signatures

### Step 3: Check Module Dependencies

Verify all required modules are listed in `StoneAndSword.Build.cs`:
- Core
- CoreUObject
- Engine
- InputCore
- ProceduralMeshComponent
- Landscape
- Slate
- SlateCore

## Build Logs Location

If you need to share error logs for help:

- **Visual Studio Output**: Copy from the Output window
- **UE Editor Log**: `Saved/Logs/UnrealEditor.log`
- **Build Log**: `Saved/Logs/UnrealBuildTool.log`

## Engine Version Compatibility

This project is designed for:
- ✅ **Unreal Engine 5.6**
- ✅ **Unreal Engine 5.6.1**

If you're using a different version:

### Option 1: Install Compatible Version
Download UE 5.6 or 5.6.1 from Epic Games Launcher

### Option 2: Migrate to Your Version
```json
// Edit StoneAndSword.uproject
{
  "EngineAssociation": "5.5", // Change to your version
  ...
}
```
**Warning**: This may require code changes if API differences exist.

## Verify Successful Build

After building successfully, you should see:
- `Binaries/Win64/UnrealEditor-StoneAndSword.dll` (and .pdb)
- `Binaries/Win64/UnrealEditor-StoneAndSword-Win64-Debug.dll` (if Debug build)

Check file sizes:
- DLL should be 500KB - 5MB depending on build configuration
- If file size is 0 or very small, the build failed

## Manual Build Script

Create this PowerShell script as `BuildProject.ps1` in your project folder:

```powershell
# BuildProject.ps1 - Manual build script for StoneAndSword

param(
    [string]$Configuration = "Development",
    [string]$UEPath = "C:\Program Files\Epic Games\UE_5.6"
)

Write-Host "Building StoneAndSword..." -ForegroundColor Cyan

# Get project path
$ProjectPath = Get-Location
$ProjectFile = Join-Path $ProjectPath "StoneAndSword.uproject"

if (-not (Test-Path $ProjectFile)) {
    Write-Host "Error: StoneAndSword.uproject not found!" -ForegroundColor Red
    exit 1
}

# Clean old files
Write-Host "Cleaning intermediate files..." -ForegroundColor Yellow
if (Test-Path "Binaries") { Remove-Item -Recurse -Force Binaries -ErrorAction SilentlyContinue }
if (Test-Path "Intermediate") { Remove-Item -Recurse -Force Intermediate -ErrorAction SilentlyContinue }

# Generate project files
Write-Host "Generating Visual Studio project files..." -ForegroundColor Yellow
$GenProjectBat = Join-Path $UEPath "Engine\Build\BatchFiles\GenerateProjectFiles.bat"
& $GenProjectBat -project="$ProjectFile" -game

# Build using UnrealBuildTool
Write-Host "Building StoneAndSword module..." -ForegroundColor Yellow
$UBT = Join-Path $UEPath "Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
& $UBT StoneAndSwordEditor Win64 $Configuration -Project="$ProjectFile" -WaitMutex

if ($LASTEXITCODE -eq 0) {
    Write-Host "Build succeeded!" -ForegroundColor Green
    Write-Host "You can now open StoneAndSword.uproject" -ForegroundColor Green
} else {
    Write-Host "Build failed with exit code $LASTEXITCODE" -ForegroundColor Red
    Write-Host "Check the output above for errors" -ForegroundColor Red
    exit 1
}
```

Usage:
```powershell
# Default build (Development)
.\BuildProject.ps1

# Debug build
.\BuildProject.ps1 -Configuration Debug

# Custom UE path
.\BuildProject.ps1 -UEPath "D:\UnrealEngine\UE_5.6"
```

## Still Having Issues?

If none of these solutions work:

1. **Capture the full error message**:
   - Build in Visual Studio with Detailed output
   - Copy the first error and surrounding context (10-20 lines)

2. **Check system specifications**:
   - Windows 10/11 64-bit
   - 16GB+ RAM recommended (8GB minimum)
   - 50GB+ free disk space
   - SSD recommended for better build performance

3. **Try a minimal test**:
   - Create a new C++ project in UE 5.6
   - If that works, compare the setup with this project
   - If that fails, reinstall Visual Studio or Unreal Engine

4. **Check permissions**:
   - Ensure you have write permissions to the project folder
   - Try running Visual Studio as Administrator

5. **Antivirus/Security**:
   - Some antivirus software blocks compilation
   - Temporarily disable or add exceptions for:
     - Visual Studio
     - Unreal Engine
     - Your project folder

## Success Checklist

After successful build, verify:
- [ ] No errors in Visual Studio Output window
- [ ] `Binaries/Win64/UnrealEditor-StoneAndSword.dll` exists and has size > 500KB
- [ ] Opening `StoneAndSword.uproject` doesn't show rebuild prompt
- [ ] Unreal Editor opens successfully
- [ ] No errors in Output Log (Window > Developer Tools > Output Log)
- [ ] Can press Play button and see the scene

## Additional Resources

- **Unreal Engine Documentation**: [Building Unreal Engine from Source](https://docs.unrealengine.com/5.6/en-US/building-unreal-engine-from-source/)
- **Visual Studio Setup**: [Setting Up Visual Studio for Unreal Engine](https://docs.unrealengine.com/5.6/en-US/setting-up-visual-studio-development-environment-for-cplusplus-projects-in-unreal-engine/)
- **Project Structure**: See `PROJECT_OVERVIEW.md` in this repository
- **Quick Start**: See `QUICK_START.md` for getting the game running

## Report an Issue

If you've followed all steps and still can't build:
1. Open an issue on GitHub
2. Include:
   - Windows version
   - Visual Studio version
   - Unreal Engine version
   - Full error message from Visual Studio Output
   - Steps you've already tried
