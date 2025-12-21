# Project Verification Checklist

Use this checklist to verify that the Stone and Sword project is set up correctly and ready to use.

## ✅ Pre-Setup Verification

Before opening the project, verify you have:

- [ ] **Unreal Engine 5.6** (or 5.6.1) installed
  - Check: Epic Games Launcher > Library > Engine Versions
  - If not installed, download and install from Epic Games Launcher
  
- [ ] **Visual Studio 2022** with C++ game development workload
  - Check: Open Visual Studio Installer
  - Verify "Game Development with C++" workload is installed
  - If not, modify installation and add it
  
- [ ] **Windows 10 SDK** (comes with Visual Studio)
  - Should be installed automatically with VS 2022
  
- [ ] **Git** (optional but recommended)
  - Check: Open command prompt, run `git --version`
  - Download from https://git-scm.com if needed

## ✅ Repository Files Verification

Verify the following files and directories exist:

### Required Files
- [ ] `StoneAndSword.uproject` - Project file
- [ ] `Config/DefaultEngine.ini` - Engine configuration
- [ ] `Config/DefaultGame.ini` - Game configuration
- [ ] `Config/DefaultInput.ini` - Input configuration
- [ ] `Config/DefaultEditor.ini` - Editor configuration

### Source Code
- [ ] `Source/StoneAndSword/StoneAndSword.h` - Module header
- [ ] `Source/StoneAndSword/StoneAndSword.cpp` - Module implementation
- [ ] `Source/StoneAndSword/StoneAndSword.Build.cs` - Build configuration
- [ ] `Source/StoneAndSword/StoneAndSwordGameModeBase.h` - Game mode header
- [ ] `Source/StoneAndSword/StoneAndSwordGameModeBase.cpp` - Game mode implementation
- [ ] `Source/StoneAndSword/WorldPlayerCharacter.h` - Character header
- [ ] `Source/StoneAndSword/WorldPlayerCharacter.cpp` - Character implementation
- [ ] `Source/StoneAndSword/WorldGenerator.h` - World generator header
- [ ] `Source/StoneAndSword/WorldGenerator.cpp` - World generator implementation
- [ ] `Source/StoneAndSword/WorldSetupManager.h` - Setup manager header
- [ ] `Source/StoneAndSword/WorldSetupManager.cpp` - Setup manager implementation
- [ ] `Source/StoneAndSword.Target.cs` - Game target
- [ ] `Source/StoneAndSwordEditor.Target.cs` - Editor target

### Content
- [ ] `Content/Textures/T_Grass.tga` - Grass texture
- [ ] `Content/Textures/T_Stone.tga` - Stone texture
- [ ] `Content/Textures/T_Dirt.tga` - Dirt texture
- [ ] `Content/Textures/T_Normal.tga` - Normal map
- [ ] `Content/Maps/` - Maps directory (created)
- [ ] `Content/Materials/` - Materials directory (created)
- [ ] `Content/Animations/` - Animations directory (created)

### Documentation
- [ ] `README.md` - Main project documentation
- [ ] `QUICK_START.md` - Quick start guide
- [ ] `SETUP_INSTRUCTIONS.md` - Detailed setup instructions
- [ ] `Content/README.md` - Content directory documentation

## ✅ Project Generation Verification

After right-clicking `StoneAndSword.uproject` and selecting "Generate Visual Studio project files":

- [ ] `StoneAndSword.sln` file was created
- [ ] `.vs/` directory was created (hidden by default)
- [ ] `Intermediate/` directory was created
- [ ] No error messages appeared during generation
- [ ] Process completed with "Successfully generated project files"

## ✅ First Launch Verification

When opening `StoneAndSword.uproject` for the first time:

### Compilation Phase
- [ ] Unreal Editor prompts "Missing StoneAndSword Modules" with "Yes" button
- [ ] Click "Yes" to rebuild
- [ ] Visual Studio Build Tools window appears (or minimized in taskbar)
- [ ] Compilation completes without errors
- [ ] Editor launches successfully

### Expected Compilation Time
- [ ] First build: 2-5 minutes (normal)
- [ ] Subsequent builds: 30-60 seconds (normal)

### Editor Launch
- [ ] Unreal Editor opens with no critical errors
- [ ] "World" message says "Entry" or similar default map
- [ ] Content Browser is visible (bottom panel)
- [ ] Viewport is visible (center)
- [ ] Details panel is visible (right side)
- [ ] Output Log shows no critical errors (Window > Developer Tools > Output Log)

## ✅ Project Configuration Verification

Once in the editor:

### Project Settings
1. Go to **Edit > Project Settings**
2. Verify the following:

**Maps & Modes**
- [ ] Default GameMode is set to `StoneAndSwordGameModeBase`
- [ ] GameDefaultMap is `/Engine/Maps/Entry` (temporary, will be changed)
- [ ] EditorStartupMap is `/Engine/Maps/Entry` (temporary, will be changed)

**Input**
- [ ] Action Mapping "Jump" exists (Spacebar, Gamepad Face Button Bottom)
- [ ] Axis Mapping "MoveForward" exists (W=1.0, S=-1.0, Gamepad Left Y)
- [ ] Axis Mapping "MoveRight" exists (D=1.0, A=-1.0, Gamepad Left X)
- [ ] Axis Mapping "Turn" exists (Mouse X, Gamepad Right X)
- [ ] Axis Mapping "LookUp" exists (Mouse Y=-1.0, Gamepad Right Y)

**Plugins**
- [ ] ProceduralMeshComponent plugin is enabled
- [ ] Landmass plugin is enabled
- [ ] Water plugin is enabled

### Content Browser
- [ ] Navigate to `Content/Textures/`
- [ ] Verify T_Grass, T_Stone, T_Dirt, T_Normal textures are visible
- [ ] Double-click a texture to preview it
- [ ] Textures display correctly

## ✅ C++ Class Visibility Verification

In the Content Browser, verify C++ classes are accessible:

1. Click **View Options** (eye icon in bottom right)
2. Enable **Show C++ Classes**
3. In the search bar, search for:
   - [ ] `WorldPlayerCharacter` - Found
   - [ ] `WorldGenerator` - Found
   - [ ] `WorldSetupManager` - Found
   - [ ] `StoneAndSwordGameModeBase` - Found

## ✅ Basic Scene Creation Verification

Follow `QUICK_START.md` to create a basic scene, then verify:

### After Creating Empty Level
- [ ] New empty level is created (black viewport)
- [ ] No default actors are present

### After Adding Directional Light
- [ ] Light appears in World Outliner
- [ ] Viewport becomes slightly brighter (not completely black)
- [ ] Light can be selected and moved

### After Adding Sky Atmosphere and Sky Light
- [ ] Sky Atmosphere appears in World Outliner
- [ ] Sky Light appears in World Outliner
- [ ] Viewport shows blue sky
- [ ] Viewport is properly lit

### After Adding Player Start
- [ ] Player Start appears in World Outliner
- [ ] Player Start icon is visible in viewport (small person icon)
- [ ] Can be selected and moved

### After Saving Map
- [ ] File saves to `Content/Maps/DefaultEmpty.umap`
- [ ] Map appears in Content Browser
- [ ] No save errors in Output Log

## ✅ Material Creation Verification

After creating the terrain material:

- [ ] M_Terrain appears in `Content/Materials/`
- [ ] Material Editor opens when double-clicked
- [ ] T_Grass texture is visible in Material Graph
- [ ] Connection from T_Grass RGB to Base Color exists
- [ ] Material compiles without errors
- [ ] Material preview shows grass texture

## ✅ Play Test Verification

After pressing Play (Alt+P):

### World Generation
- [ ] WorldSetupManager spawns (check Output Log)
- [ ] WorldGenerator spawns (check Output Log)
- [ ] Terrain mesh is generated (visible in viewport)
- [ ] Terrain appears as a flat plane
- [ ] Terrain has grass material applied (if material set)

### Player Character
- [ ] Character spawns at Player Start location
- [ ] Camera is behind character (third-person view)
- [ ] Character is visible (capsule shape)

### Controls
- [ ] **W** key moves character forward
- [ ] **S** key moves character backward
- [ ] **A** key moves character left
- [ ] **D** key moves character right
- [ ] **Mouse X** rotates camera left/right
- [ ] **Mouse Y** rotates camera up/down
- [ ] **Spacebar** makes character jump
- [ ] **ESC** stops play session

### Physics
- [ ] Character stands on terrain (doesn't fall through)
- [ ] Character collides with terrain when jumping
- [ ] Gravity affects character movement

## ✅ Output Log Verification

During play session, check Output Log for:

### Expected Messages
- [ ] "StoneAndSword module started"
- [ ] "WorldSetupManager spawned successfully"
- [ ] "Setting up world..."
- [ ] "Spawned and configured WorldGenerator"
- [ ] "Generating world with size..."
- [ ] "World generation complete: X vertices, Y triangles"

### No Critical Errors
- [ ] No red error messages
- [ ] No crash reports
- [ ] No missing class errors
- [ ] No null pointer exceptions

## ✅ Performance Verification

During play session:

### Frame Rate
- [ ] FPS is displayed (Ctrl+Shift+H or Editor Settings)
- [ ] Frame rate is above 30 FPS
- [ ] Frame rate is stable (no major stuttering)

### Memory
- [ ] No significant memory leaks
- [ ] Memory usage is reasonable (< 2GB for basic scene)

### Responsiveness
- [ ] Character responds immediately to input
- [ ] Camera follows character smoothly
- [ ] No input lag or delay

## ✅ Build Verification (Optional)

If packaging the project:

1. Go to **File > Package Project > Windows > Windows (64-bit)**
2. Choose output directory
3. Wait for packaging to complete

### Package Verification
- [ ] Package completes without errors
- [ ] Output directory contains packaged game
- [ ] `.exe` file is present
- [ ] Running `.exe` launches the game
- [ ] Game works the same as in-editor play session

## 🔧 Troubleshooting

If any verification step fails, see `SETUP_INSTRUCTIONS.md` "Troubleshooting" section.

### Common Issues

**Project won't open**
- Verify UE 5.6 is installed
- Right-click .uproject > "Switch Unreal Engine version"
- Regenerate project files

**Compile errors**
- Verify Visual Studio 2022 is installed
- Check ProceduralMeshComponent plugin is enabled
- Open .sln and build manually

**No terrain appears**
- Check Output Log for errors
- Verify WorldSetupManager is spawning
- Manually place WorldGenerator actor and test

**Character falls through terrain**
- Increase Player Start Z to 500
- Check collision is enabled on ProceduralMesh
- Verify Character has collision

**Can't move character**
- Verify input mappings in Project Settings
- Check WorldPlayerCharacter is default pawn
- Test with different input devices

## Summary

If all checkboxes are marked ✅:
- ✅ Your project is correctly set up
- ✅ All code compiles successfully
- ✅ The scene is playable
- ✅ Controls work as expected
- ✅ Ready to iterate and expand!

If some checkboxes are ❌:
- Review the troubleshooting section
- Check `SETUP_INSTRUCTIONS.md` for detailed help
- Open an issue on GitHub with specific error details

## Next Steps

Once verification is complete:
1. Customize terrain parameters
2. Add more materials and textures
3. Import character models and animations
4. Implement gameplay mechanics
5. Build and share your game!

Happy developing! 🎮
