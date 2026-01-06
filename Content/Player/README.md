# Player Character Models

This folder contains the character models for the Stone and Sword game.

## Available Models

- **male.blend** - Male character model (Blender file)
- **female.blend** - Female character model (Blender file)

## Importing Blender Files into Unreal Engine

### Prerequisites
- Unreal Engine 5.6 or higher
- The male.blend and female.blend files should be placed in this directory

### Import Steps

#### Step 1: Import via Unreal Editor (Recommended)

1. **Open the Unreal Editor** with the StoneAndSword project
2. **Navigate to Content Browser** > Content > Player folder
3. **Import the Blender files**:
   - Click **Import** button (or right-click > Import to /Game/Player/)
   - Select both `male.blend` and `female.blend`
   - Click **Open**

4. **Configure Import Settings**:
   - **Skeletal Mesh**: ✅ Enabled (for animated characters)
   - **Import Animations**: ✅ Enabled (if animations are embedded)
   - **Import Materials**: ✅ Enabled
   - **Import Textures**: ✅ Enabled
   - **Skeleton**: Create New Skeleton (or use existing if compatible)
   - **Transform**:
     - Scale: Set to `100.0` (Blender to UE conversion)
     - Rotation: Adjust if needed (Blender Y-up to UE Z-up)
   - Click **Import All**

5. **Verify Import**:
   - You should see new assets in Content/Player/:
     - `SK_Male` (Skeletal Mesh)
     - `SK_Female` (Skeletal Mesh)
     - `SK_Male_Skeleton` (Skeleton)
     - `SK_Female_Skeleton` (Skeleton)
     - Materials and textures

#### Step 2: Create Character Blueprints

Now create blueprints for both characters:

##### Male Character Blueprint

1. **Create Blueprint**:
   - Right-click in Content/Player/ folder
   - **Blueprint Class** > Search for `WorldPlayerCharacter`
   - Name it: `BP_MaleCharacter`

2. **Configure Blueprint**:
   - Open `BP_MaleCharacter`
   - Select **Mesh (Inherited)** component in Components panel
   - In Details panel:
     - **Skeletal Mesh Asset**: Set to `SK_Male`
     - **Location**: Set to `X=0, Y=0, Z=-96` (align with capsule)
     - **Rotation**: Set to `X=0, Y=0, Z=-90` (face forward)
   - **Show Body In First Person**: ✅ Already enabled by default
   - **Compile** and **Save**

##### Female Character Blueprint

1. **Create Blueprint**:
   - Right-click in Content/Player/ folder
   - **Blueprint Class** > Search for `WorldPlayerCharacter`
   - Name it: `BP_FemaleCharacter`

2. **Configure Blueprint**:
   - Open `BP_FemaleCharacter`
   - Select **Mesh (Inherited)** component
   - In Details panel:
     - **Skeletal Mesh Asset**: Set to `SK_Female`
     - **Location**: Set to `X=0, Y=0, Z=-96`
     - **Rotation**: Set to `X=0, Y=0, Z=-90`
   - **Show Body In First Person**: ✅ Already enabled
   - **Compile** and **Save**

#### Step 3: Set Default Character

Choose which character to use by default:

1. **Open Project Settings**: Edit > Project Settings
2. **Go to Maps & Modes**
3. **Under Selected GameMode** (StoneAndSwordGameModeBase)
4. **Set Default Pawn Class** to either:
   - `BP_MaleCharacter` (for male character)
   - `BP_FemaleCharacter` (for female character)
5. **Save** and close Project Settings

#### Step 4: Test the Character

1. **Press Play** (Alt+P) in the editor
2. You should now see your character body when looking down
3. Test movement with **W/A/S/D** keys
4. Test looking around with **Mouse**
5. Test jumping with **Spacebar**

## Adding Animations (Optional)

If your Blender files don't include animations, you can add them:

### Option 1: Mixamo (Free)

1. Go to [mixamo.com](https://www.mixamo.com)
2. Export your character from Blender as FBX
3. Upload to Mixamo
4. Download animations (Idle, Walk, Run, Jump)
5. Import animations into Unreal, using the same skeleton

### Option 2: Blender Animations

If you created animations in Blender:

1. Ensure animations are on the same armature
2. Re-import the .blend file with **Import Animations** enabled
3. Animations will appear in Content/Player/

### Creating Animation Blueprint

1. **Create Animation Blueprint**:
   - Right-click in Content/Player/
   - **Animation > Animation Blueprint**
   - Choose your character's skeleton
   - Name it: `ABP_PlayerCharacter`

2. **Set up basic animation logic**:
   - Create a State Machine with Idle, Walk, Run states
   - Use character velocity to transition between states
   - See Unreal Engine documentation for details

3. **Apply to Character**:
   - Open BP_MaleCharacter or BP_FemaleCharacter
   - Select Mesh component
   - Set **Anim Class** to `ABP_PlayerCharacter`
   - Compile and Save

## Character Switching System (Optional)

To allow players to choose between male/female characters:

1. Create a **Character Selection Menu** blueprint
2. Create a **Game Instance** class to store character choice
3. In the Game Mode, spawn the selected character type
4. Save preference using **Save Game** system

## Troubleshooting

### Character is too small/large
- Adjust import scale (try 1.0, 10.0, or 100.0)
- Or adjust mesh scale in the Blueprint

### Character is facing wrong direction
- Rotate mesh Z-axis by -90 degrees in Blueprint
- Or fix in Blender (Y-forward, Z-up)

### Character is floating or underground
- Adjust mesh Z-location in Blueprint
- Typical value: Z=-96 (half of capsule height)

### Can't see character in first-person
- Verify `bShowBodyInFirstPerson = true` (now default)
- Check that mesh is assigned in Blueprint
- Check mesh visibility settings

### Character has no animations
- Verify animations were imported
- Create and assign Animation Blueprint
- Check skeleton compatibility

### Materials look wrong
- Re-import with "Import Materials" enabled
- Check texture file paths
- Create/fix materials manually if needed

## File Structure

After import, your folder should look like:

```
Content/Player/
├── README.md (this file)
├── male.blend (Blender source file)
├── female.blend (Blender source file)
├── SK_Male.uasset (Skeletal Mesh)
├── SK_Female.uasset (Skeletal Mesh)
├── SK_Male_Skeleton.uasset (Skeleton)
├── SK_Female_Skeleton.uasset (Skeleton)
├── BP_MaleCharacter.uasset (Blueprint)
├── BP_FemaleCharacter.uasset (Blueprint)
├── ABP_PlayerCharacter.uasset (Animation Blueprint - if created)
└── Materials/
    └── (Character materials and textures)
```

## Next Steps

1. Place male.blend and female.blend files in this folder
2. Import the Blender files following the steps above
3. Create the character Blueprints
4. Set one as the default pawn
5. Test in-game
6. Add animations if needed
7. Customize materials and appearance

## References

- **CHARACTER_SETUP_GUIDE.md** - Additional first-person setup options
- **QUICK_START.md** - Basic project setup
- [Unreal Engine FBX Import](https://docs.unrealengine.com/5.6/en-US/fbx-content-pipeline-in-unreal-engine/)
- [Blender to Unreal](https://docs.unrealengine.com/5.6/en-US/importing-blender-content-into-unreal-engine/)
