# Quick Start - Get Playing in 10 Minutes!

This is the fastest way to get a playable scene running in Unreal Engine 5.6.

## What You'll Get

✅ A flat procedurally generated world with grass texture  
✅ A third-person character with camera  
✅ WASD + Mouse movement controls  
✅ Jump capability  
✅ Automatic lighting and sky setup  
✅ A fully playable test scene  

## Prerequisites

- **Unreal Engine 5.6** (or 5.6.1) installed from Epic Games Launcher
- **Visual Studio 2022** with "Game Development with C++" workload
- **10 minutes** of your time

## Step 1: Open the Project (2 minutes)

1. Clone or download this repository
2. Navigate to the project folder
3. **Right-click** on `StoneAndSword.uproject`
4. Select **"Generate Visual Studio project files"**
5. Wait for completion (30-60 seconds)
6. **Double-click** `StoneAndSword.uproject` to open in Unreal Editor
7. Click **"Yes"** when prompted to rebuild modules
8. Wait for compilation (2-5 minutes first time)

> **⚠️ If compilation fails**, see **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)** for detailed solutions.
> You can also use the automated build script: `.\BuildProject.ps1`

## Step 2: Create the Default Map (5 minutes)

### A. Create Empty Level

1. In Unreal Editor, go to **File > New Level**
2. Choose **"Empty Level"**

### B. Add Basic Components

**Lighting:**
1. **Place Actors** panel (bottom left) > Search **"Directional Light"**
2. Drag into viewport
3. In Details panel: Set **Intensity** to `10.0`, enable **Atmosphere Sun Light**

**Sky:**
1. Search **"Sky Atmosphere"** in Place Actors, drag into viewport
2. Search **"Sky Light"**, drag into viewport
3. In Sky Light Details: Click **"Recapture"**

**Player Start:**
1. Search **"Player Start"**, drag into viewport
2. In Details panel: Set Location to `X=0, Y=0, Z=200`

### C. Save the Map

1. Press **Ctrl+S**
2. Save to: `Content/Maps/DefaultEmpty`

### D. Set as Default Map

1. **Edit > Project Settings**
2. Go to **Maps & Modes**
3. Set **Editor Startup Map**: `/Game/Maps/DefaultEmpty`
4. Set **Game Default Map**: `/Game/Maps/DefaultEmpty`
5. Verify **Default GameMode**: `StoneAndSwordGameModeBase`

## Step 3: Create Basic Material (3 minutes)

1. In **Content Browser**, navigate to `Content/Materials/`
2. **Right-click** > **Material** > Name it **"M_Terrain"**
3. **Double-click** to open Material Editor
4. In Content Browser, navigate to `Content/Textures/`
5. **Drag** `T_Grass` into the Material Graph
6. **Connect** T_Grass RGB output to the **Base Color** pin on the main material node
7. Click **Save** and **Apply**
8. Close Material Editor

## Step 4: Test It! (30 seconds)

1. Click the **Play** button (or press **Alt+P**)
2. You should see:
   - A flat terrain appears beneath you
   - Blue sky with atmospheric lighting
   - Your character (capsule shape)
3. **Test controls:**
   - **W/A/S/D**: Move around
   - **Mouse**: Look around
   - **Spacebar**: Jump
   - **ESC**: Stop playing

## Troubleshooting

### No Terrain Appears?
- Check **Window > Output Log** for errors
- Verify the GameMode is set to `StoneAndSwordGameModeBase`
- The WorldSetupManager should auto-spawn and create terrain

### Character Falls Through Ground?
- Increase Player Start Z position to `500`
- The terrain generates at Z=0 with slight variation

### Can't Move?
- Verify input mappings in **Project Settings > Input**
- They should already be configured in `Config/DefaultInput.ini`

### Compile Errors?
- See **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)** for comprehensive solutions
- Try the automated build script: `.\BuildProject.ps1 -Clean`
- Make sure Visual Studio 2022 is installed with "Game development with C++" workload
- Try closing UE, regenerating project files, and reopening

## What's Happening Automatically?

The project uses C++ code to automatically set up the world:

1. **StoneAndSwordGameModeBase** - Spawns a WorldSetupManager
2. **WorldSetupManager** - Creates lighting, sky, and WorldGenerator
3. **WorldGenerator** - Generates a 10km x 10km flat terrain with slight variation
4. **WorldPlayerCharacter** - Provides third-person camera and movement

All of this happens automatically when you press Play!

## Next Steps

### Add Proper Character Model
See `SETUP_INSTRUCTIONS.md` section "Adding Proper Animations" for:
- Using Unreal's Third Person Template content
- Importing from Mixamo (free animations)
- Creating custom character meshes

### Customize Terrain
Edit in **WorldGenerator** actor properties:
- **World Size X/Y**: Larger worlds
- **Grid Resolution**: More/less detail
- **Height Variation**: More dramatic terrain
- **Terrain Material**: Change to different materials

### Add More Features
- Import more textures (stone, dirt, sand)
- Create biomes (forest, desert, mountains)
- Add vegetation spawning
- Implement game mechanics (combat, inventory, etc.)

## Files You Created

After following this guide, you'll have:
- ✅ `Content/Maps/DefaultEmpty.umap` - Your default level
- ✅ `Content/Materials/M_Terrain.uasset` - Grass material
- ✅ Updated Config/DefaultEngine.ini (via Project Settings)

## Need More Help?

- **Detailed Guide**: See `SETUP_INSTRUCTIONS.md` for comprehensive step-by-step instructions
- **Build Guide**: See `BUILD_GUIDE.md` for packaging and distribution
- **Project Overview**: See `README.md` for architecture and features
- **Output Log**: In Unreal, go to **Window > Developer Tools > Output Log** to see what's happening

## Summary

You now have:
✅ A working UE 5.6 project  
✅ Procedural world generation  
✅ Playable character with controls  
✅ Basic lighting and materials  
✅ Ready to iterate and expand!

**Time invested**: ~10 minutes  
**Result**: A fully playable prototype you can build upon!

Happy game development! 🎮
