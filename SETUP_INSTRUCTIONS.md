# Setup Instructions for Basic Playable Scene

This guide will walk you through setting up a basic playable scene in Unreal Engine 5.6 with the Stone and Sword project.

## Prerequisites

1. **Unreal Engine 5.6** (or 5.6.1) installed via Epic Games Launcher
2. **Visual Studio 2022** with C++ game development workload
3. **Git** (for version control)

## Step 1: Open the Project in Unreal Engine

1. Navigate to the project directory
2. Right-click on `StoneAndSword.uproject`
3. Select **"Generate Visual Studio project files"** (first time only)
4. Wait for the process to complete
5. Double-click `StoneAndSword.uproject` to open in Unreal Editor
6. When prompted to rebuild modules, click **"Yes"**
7. Wait for the C++ code to compile (this may take several minutes)

## Step 2: Create the Default Map

### 2.1 Create Empty Level

1. In the Unreal Editor, go to **File > New Level**
2. Select **"Empty Level"** from the dialog
3. An empty black scene will appear

### 2.2 Add Basic Lighting

1. In the **Place Actors** panel (Window > Place Actors if not visible), search for **"Directional Light"**
2. Drag **Directional Light** into the viewport
3. Set the light's location to `(0, 0, 1000)`
4. Set the light's rotation to `(-50, 0, 0)` for a natural sun angle
5. In the Details panel:
   - Set **Intensity** to `10.0`
   - Enable **Atmosphere Sun Light** (checkbox)

### 2.3 Add Sky Atmosphere

1. Search for **"Sky Atmosphere"** in Place Actors
2. Drag it into the viewport (location doesn't matter)
3. Search for **"Sky Light"** in Place Actors
4. Drag it into the viewport
5. In the Sky Light's Details panel:
   - Set **Source Type** to "SLS Captured Scene"
   - Click **"Recapture"** button
   - Set **Intensity** to `1.0`

### 2.4 Add Exponential Height Fog (Optional but recommended)

1. Search for **"Exponential Height Fog"** in Place Actors
2. Drag it into the viewport
3. Keep default settings

### 2.5 Add Post Process Volume (Optional but recommended)

1. Search for **"Post Process Volume"** in Place Actors
2. Drag it into the viewport at location `(0, 0, 0)`
3. In Details panel:
   - Check **"Infinite Extent (Unbound)"**
   - Under Exposure settings, set **Exposure Compensation** to `0.0`

### 2.6 Save the Map

1. Press **Ctrl+S** (or File > Save Current Level)
2. Navigate to `Content/Maps/` directory
3. Name the file **"DefaultEmpty"**
4. Click **Save**

## Step 3: Create Basic Terrain Material

### 3.1 Create Material

1. In the **Content Browser**, navigate to `Content/Materials/`
2. Right-click in empty space and select **Material**
3. Name it **"M_Terrain"**
4. Double-click to open the Material Editor

### 3.2 Configure Material

1. In the Material Editor, locate the main material node
2. Add the grass texture:
   - In Content Browser, navigate to `Content/Textures/`
   - Drag **T_Grass** texture into the Material Graph
   - Connect the **RGB** output to **Base Color**
3. Add normal map (optional):
   - Drag **T_Normal** texture into the Material Graph
   - Connect the **RGB** output to **Normal**
4. Set material properties:
   - In the main material node details:
   - **Blend Mode**: Opaque
   - **Shading Model**: Default Lit
5. Click **Save** and close the Material Editor

### 3.3 Create Material Instance (Optional but recommended)

1. Right-click on **M_Terrain** in Content Browser
2. Select **Create Material Instance**
3. Name it **"MI_Terrain_Grass"**
4. This allows you to adjust settings without recompiling the shader

## Step 4: Create Character Animation Blueprint

### 4.1 Create Animation Blueprint

1. In Content Browser, navigate to `Content/Animations/`
2. Right-click and select **Animation > Animation Blueprint**
3. For **Parent Class**, choose **AnimInstance**
4. For **Target Skeleton**, select **None** (we'll use a placeholder)
5. Name it **"ABP_PlayerCharacter"**

### 4.2 Configure Animation Blueprint (Basic Setup)

1. Double-click **ABP_PlayerCharacter** to open
2. In the **AnimGraph** tab:
   - You'll see the default Output Pose node
   - For now, we'll leave this with just a default stance
3. In the **Event Graph** tab:
   - The default update animation events are already there
4. Click **Compile** and **Save**

**Note**: For now, this is a placeholder. The character will use a default T-pose or A-pose. You can add proper animations later by importing animation assets or using Unreal's starter content.

## Step 5: Configure the World Generator

The world generator is already set up in C++ code. We just need to ensure it spawns correctly.

### 5.1 Test World Generator Manually (Optional)

1. In the level viewport, go to **Place Actors** panel
2. Search for **"WorldGenerator"** (this is our custom C++ class)
3. Drag it into the viewport at location `(0, 0, 0)`
4. Select the WorldGenerator actor
5. In Details panel, configure:
   - **World Size X**: `10000` (10km)
   - **World Size Y**: `10000` (10km)
   - **Grid Resolution**: `100.0`
   - **Height Variation**: `50.0`
   - **Auto Generate On Begin Play**: ✓ (checked)
   - **Terrain Material**: Select `M_Terrain` (or `MI_Terrain_Grass`)

### 5.2 Configure Automatic Setup (Recommended)

The project includes an automatic setup manager that will spawn everything for you:

1. The **StoneAndSwordGameModeBase** is already configured to spawn a **WorldSetupManager**
2. The WorldSetupManager will automatically:
   - Spawn the WorldGenerator with default settings
   - Apply the terrain material
   - Set up lighting and sky if not present
3. You don't need to manually place these actors if using the auto-setup

## Step 6: Add Player Start

1. In Place Actors panel, search for **"Player Start"**
2. Drag it into the viewport
3. Set location to `(0, 0, 200)` - this puts the player above where the terrain will generate
4. Keep default rotation `(0, 0, 0)`

## Step 7: Configure Project Settings

### 7.1 Set Default Maps

1. Go to **Edit > Project Settings**
2. Navigate to **Maps & Modes**
3. Set **Editor Startup Map**: `/Game/Maps/DefaultEmpty`
4. Set **Game Default Map**: `/Game/Maps/DefaultEmpty`
5. Set **Default GameMode**: `StoneAndSwordGameModeBase` (should already be set)

### 7.2 Verify Default Pawn

1. Still in Project Settings > Maps & Modes
2. Under **Default Modes** section, expand **StoneAndSwordGameModeBase**
3. Ensure **Default Pawn Class** is set to `WorldPlayerCharacter` (should be set in C++)

### 7.3 Configure Input (should already be done)

1. Go to **Project Settings > Input**
2. Verify the following mappings exist:
   - **Action Mappings**:
     - Jump: Spacebar, Gamepad Face Button Bottom
   - **Axis Mappings**:
     - MoveForward: W (1.0), S (-1.0), Gamepad Left Y
     - MoveRight: D (1.0), A (-1.0), Gamepad Left X
     - Turn: Mouse X, Gamepad Right X
     - LookUp: Mouse Y (inverted), Gamepad Right Y

## Step 8: Update Config Files (Alternative to Editor)

If you prefer to edit configuration files directly, update `Config/DefaultEngine.ini`:

```ini
[/Script/EngineSettings.GameMapsSettings]
GameDefaultMap=/Game/Maps/DefaultEmpty
EditorStartupMap=/Game/Maps/DefaultEmpty
GlobalDefaultGameMode=/Script/StoneAndSword.StoneAndSwordGameModeBase
```

## Step 9: Test the Scene

### 9.1 Test in Editor

1. Click the **Play** button (or press **Alt+P**)
2. You should see:
   - A flat terrain generated beneath you
   - Sky with atmospheric lighting
   - Your character (basic capsule shape for now)
3. Test controls:
   - **WASD**: Move around
   - **Mouse**: Look around
   - **Spacebar**: Jump
   - **ESC**: Stop playing

### 9.2 Check Output Log

If something doesn't work:
1. Go to **Window > Developer Tools > Output Log**
2. Look for error messages or warnings
3. Common issues:
   - "WorldGenerator not found" - Make sure auto-spawn is enabled in GameMode
   - "No terrain material" - Make sure M_Terrain material is created
   - "Character falls through terrain" - Player Start may be too low, increase Z to 200+

## Step 10: Package the Game (Optional)

To create a standalone executable:

1. Go to **File > Package Project > Windows > Windows (64-bit)**
2. Choose an output directory
3. Wait for packaging to complete (5-15 minutes)
4. Find the `.exe` in the output folder
5. Run the game!

## What You Should Have Now

✅ A working Unreal Engine 5.6 project
✅ A default empty map with basic lighting and sky
✅ A procedural flat world with grass texture
✅ A player character with camera controls
✅ WASD + Mouse movement
✅ Jump capability
✅ A playable scene you can iterate on

## Next Steps: Adding Proper Animations

The current setup uses placeholder animations. To add proper animations:

### Option 1: Use Unreal Engine Starter Content

1. Add starter content to your project:
   - Go to **Content Browser**
   - Click the **Add** button
   - Select **Add Feature or Content Pack**
   - Choose **Third Person** content
   - This includes a character mesh with animations
2. Update WorldPlayerCharacter to use the starter character mesh
3. Update the animation blueprint to use the starter animations

### Option 2: Use Mixamo Animations (Free)

1. Go to https://www.mixamo.com
2. Download free character and animations:
   - Idle animation
   - Walk/Run animation
   - Jump animation
3. Import into Unreal:
   - In Content Browser, click **Import**
   - Select your downloaded FBX files
   - Import as Skeletal Mesh and Animations
4. Create proper Animation Blueprint with state machine:
   - Idle state
   - Walking/Running state (blend based on speed)
   - Jump state
5. Assign the new skeleton and animations to WorldPlayerCharacter

### Option 3: Simple Animated Capsule

For the absolute minimum:
1. Keep the character as a capsule (collision shape)
2. Add a simple static mesh or geometric shape
3. Use simple transform animations (scale pulse for idle, bobbing for walk)

## Customizing the World

### Change Terrain Size

1. Find WorldGenerator actor (or edit DefaultWorldSizeX/Y in WorldSetupManager)
2. Increase WorldSizeX and WorldSizeY for larger worlds
3. Adjust GridResolution for more/less detail

### Add More Textures

1. Import more textures (stone, dirt, etc.) into Content/Textures
2. Create materials for each
3. Modify WorldGenerator C++ code to apply different materials based on height/noise

### Add Biomes

1. Modify WorldGenerator::CalculateTerrainHeight() in C++
2. Add height variation
3. Create multiple material instances
4. Apply based on regions

## Troubleshooting

### Project Won't Open

- Verify UE 5.6 is installed
- Right-click .uproject > "Switch Unreal Engine version" > Select 5.6
- Try regenerating project files

### Compile Errors

- Ensure Visual Studio 2022 is installed with C++ tools
- Open the .sln file and build manually
- Check that ProceduralMeshComponent plugin is enabled

### No Terrain Appears

- Check WorldSetupManager is spawning (bAutoSpawnWorldSetupManager = true)
- Check Output Log for errors
- Manually place WorldGenerator actor and test

### Character Falls Through Terrain

- Increase Player Start Z location to 500 or higher
- Check ProceduralMesh has collision enabled
- Verify Character has collision

### Can't Move Character

- Check Input settings in Project Settings
- Verify WorldPlayerCharacter is the default pawn class
- Test with different input devices

## Support

For additional help:
- Check the README.md for project overview
- Review QUICKSTART.md for build instructions
- Check Output Log in Unreal Editor for specific errors
- Open a GitHub issue with detailed description and logs

## Summary

You now have a fully functional Unreal Engine 5.6 project with:
- ✅ Procedural world generation
- ✅ Basic materials and textures
- ✅ Player character with camera
- ✅ Movement controls (WASD + Mouse)
- ✅ Lighting and atmosphere
- ✅ Jump mechanics
- ✅ A playable test environment

From here, you can:
- Add proper character models and animations
- Enhance terrain generation
- Add gameplay mechanics
- Create additional levels
- Build and distribute your game

Happy developing!
