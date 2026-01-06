# Character Setup Guide - Adding Visible Character with Animations

## Overview

The **WorldPlayerCharacter** is fully implemented in C++ with complete gameplay functionality:
- ✅ Third-person camera system
- ✅ WASD movement controls
- ✅ Mouse look/camera rotation
- ✅ Jump mechanics
- ✅ All gameplay logic in C++

This guide shows you how to add a **visible character mesh with animations** using free store assets.

## Quick Answer

**YES!** You can easily add a visible character with animations using:
1. **Unreal Engine Marketplace** - Free character packs
2. **Mixamo** - Free characters and animations (Adobe account)
3. **Third Person Template** - Built into Unreal Engine

**The entire gameplay loop is already implemented in C++** - you just need to assign visual assets!

---

## Method 1: Using Unreal Engine Third Person Template (Easiest - 5 minutes)

The fastest way is to use the mannequin from UE's Third Person Template:

### Steps:

1. **Open your project** in Unreal Engine 5.6

2. **Add Third Person Content** (if not already added):
   - Go to **Edit > Plugins**
   - Search for "Third Person"
   - Enable "Third Person Template" if available
   - OR: Create a new Third Person project temporarily, then migrate assets

3. **Create a Blueprint of WorldPlayerCharacter**:
   - In Content Browser, right-click in a folder (e.g., `Content/Blueprints/`)
   - Select **Blueprint Class**
   - Search for `WorldPlayerCharacter` in the parent class picker
   - Name it `BP_PlayerCharacter`

4. **Open BP_PlayerCharacter** and configure:
   - In the **Details** panel, find the **Mesh** section
   - Set **Character Mesh Asset** to `SKM_Manny` (or `SKM_Quinn` for female)
   - Set **Animation Blueprint Class** to `ABP_Manny` (or `ABP_Quinn`)
   - **Compile** and **Save**

5. **Set as Default Pawn**:
   - Open **Edit > Project Settings**
   - Go to **Maps & Modes** > **Default Modes**
   - Under **Selected GameMode** (StoneAndSwordGameModeBase)
   - Set **Default Pawn Class** to `BP_PlayerCharacter`

6. **Test**:
   - Press **Play** (Alt+P)
   - You should see a visible character with running/jumping animations!

---

## Method 2: Using Mixamo (Free Characters - 15 minutes)

Mixamo provides free high-quality characters and animations:

### Step 1: Download Character from Mixamo

1. Go to **[mixamo.com](https://www.mixamo.com)**
2. Sign in with Adobe account (free)
3. Browse **Characters** and select one you like
4. Click **Download**:
   - Format: **FBX for Unreal (.fbx)**
   - Pose: **T-Pose**
   - Download

### Step 2: Download Animations from Mixamo

Download these essential animations:
1. **Idle**
   - Search "Idle" → Select "Idle"
   - Download: FBX for Unreal, **Without Skin**, 30 FPS

2. **Walk**
   - Search "Walking" → Select "Walking"
   - Download: FBX for Unreal, **Without Skin**, 30 FPS

3. **Run**
   - Search "Running" → Select "Running"
   - Download: FBX for Unreal, **Without Skin**, 30 FPS

4. **Jump**
   - Search "Jump" → Select "Jumping"
   - Download: FBX for Unreal, **Without Skin**, 30 FPS

### Step 3: Import into Unreal Engine

1. **Create folders** in Content Browser:
   - `Content/Characters/Mixamo/`
   - `Content/Characters/Mixamo/Animations/`

2. **Import the Character**:
   - Drag character FBX into `Content/Characters/Mixamo/`
   - Import settings:
     - ✅ Import Mesh
     - ✅ Import Skeleton
     - ✅ Import Materials
     - ✅ Import Textures
     - Skeletal Mesh: Create new
   - Click **Import All**

3. **Import Animations**:
   - Drag animation FBXs into `Content/Characters/Mixamo/Animations/`
   - For each animation:
     - Select the **Skeleton** you just imported
     - Click **Import All**

### Step 4: Create Animation Blueprint

1. **Create Animation Blueprint**:
   - Right-click in `Content/Characters/Mixamo/`
   - Select **Animation > Animation Blueprint**
   - Choose your imported **Skeleton**
   - Name it `ABP_MixamoCharacter`

2. **Open ABP_MixamoCharacter**:

3. **In AnimGraph**:
   - Create a **State Machine**:
     - Right-click → Add **New State Machine**
     - Name it "Locomotion"
     - Connect output to **Final Animation Pose**

4. **Open State Machine**:
   - Create 3 states: **Idle**, **Walk**, **Jump**
   - Connect Entry → Idle
   - Add transitions between states

5. **Configure Each State**:
   - **Idle State**: Add your Mixamo Idle animation
   - **Walk State**: Add your Mixamo Walk/Run animation
   - **Jump State**: Add your Mixamo Jump animation

6. **In EventGraph** (Optional):
   - Get character velocity and speed for blend spaces
   - Set variables for state machine transitions

7. **Compile** and **Save**

### Step 5: Apply to WorldPlayerCharacter

Same as Method 1, Step 3-5:
- Create `BP_PlayerCharacter` blueprint
- Set **Character Mesh Asset** to your Mixamo mesh
- Set **Animation Blueprint Class** to `ABP_MixamoCharacter`
- Set as default pawn in Project Settings

---

## Method 3: Using UE Marketplace Assets (Free Options)

### Free Character Packs on UE Marketplace:

1. **Stylized Character Kit**
2. **Paragon Characters** (Epic's free characters)
3. **Animation Starter Pack** (includes mannequin + animations)

### Steps:

1. Open **Epic Games Launcher**
2. Go to **Unreal Engine > Marketplace**
3. Filter by **Free** assets
4. Search for character packs
5. Add to project
6. Follow same setup as Method 1 or 2

---

## Verification Checklist

After setup, verify everything works:

- [ ] Character mesh is visible in the world
- [ ] Camera follows character correctly
- [ ] WASD movement works
- [ ] Mouse look works
- [ ] Character animates when moving
- [ ] Jump animation plays when jumping
- [ ] Character rotates toward movement direction

---

## C++ Gameplay Loop Confirmation

**The entire gameplay loop is implemented in C++:**

✅ **Input Handling** (C++):
```cpp
// WorldPlayerCharacter.cpp - SetupPlayerInputComponent
PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
PlayerInputComponent->BindAxis("MoveForward", this, &AWorldPlayerCharacter::MoveForward);
PlayerInputComponent->BindAxis("MoveRight", this, &AWorldPlayerCharacter::MoveRight);
PlayerInputComponent->BindAxis("Turn", this, &AWorldPlayerCharacter::Turn);
PlayerInputComponent->BindAxis("LookUp", this, &AWorldPlayerCharacter::LookUp);
```

✅ **Movement Logic** (C++):
```cpp
// WorldPlayerCharacter.cpp - MoveForward/MoveRight
void AWorldPlayerCharacter::MoveForward(float Value)
{
    if ((Controller != nullptr) && (Value != 0.0f))
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value * MovementSpeedMultiplier);
    }
}
```

✅ **Camera System** (C++):
```cpp
// WorldPlayerCharacter.cpp - Constructor
CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
```

✅ **Character Movement** (C++):
```cpp
// WorldPlayerCharacter.cpp - Constructor
GetCharacterMovement()->bOrientRotationToMovement = true;
GetCharacterMovement()->MaxWalkSpeed = 600.0f;
GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;
```

**No Blueprint logic is required!** Blueprints are only used to:
1. Assign visual assets (mesh and animations)
2. Optionally override default values

---

## Advanced Customization (Optional)

### Adjusting Character Position/Rotation

If the character mesh doesn't align properly, adjust in C++ or Blueprint:

**In C++ (WorldPlayerCharacter.cpp):**
```cpp
// Already configured for standard UE characters:
GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
```

**In Blueprint:**
- Open `BP_PlayerCharacter`
- Select **Mesh** component
- Adjust **Location** and **Rotation** in Transform section

### Adjusting Camera Distance

**In C++ (WorldPlayerCharacter.cpp):**
```cpp
CameraBoom->TargetArmLength = 400.0f; // Change to desired distance
```

**In Blueprint:**
- Open `BP_PlayerCharacter`
- Select **CameraBoom** component
- Change **Target Arm Length**

### Adjusting Movement Speed

**In C++ (WorldPlayerCharacter.cpp):**
```cpp
GetCharacterMovement()->MaxWalkSpeed = 600.0f; // Change to desired speed
```

**In Blueprint:**
- Open `BP_PlayerCharacter`
- Find **Character Movement** component
- Change **Max Walk Speed**

---

## Troubleshooting

### Character is invisible
**Problem**: No mesh assigned or mesh not set correctly

**Solution**:
1. Check that **Character Mesh Asset** is set in BP_PlayerCharacter
2. Verify the skeletal mesh imported correctly
3. Check that mesh has materials assigned

### Character has no animations
**Problem**: Animation Blueprint not assigned or not configured

**Solution**:
1. Check that **Animation Blueprint Class** is set in BP_PlayerCharacter
2. Verify animation blueprint has animations imported
3. Check skeleton matches between mesh and animations

### Character mesh is rotated wrong
**Problem**: Different character rigs have different default rotations

**Solution**:
1. Adjust **Mesh Rotation** in BP_PlayerCharacter
2. Common values: -90° or 90° on Z-axis (Yaw)

### Character slides instead of walking
**Problem**: Animations not playing or speed mismatch

**Solution**:
1. Check animation blueprint state machine
2. Verify character velocity is driving animation states
3. Adjust animation playback speed to match movement speed

### Camera is too close/far
**Problem**: Default camera distance doesn't match your character

**Solution**:
1. Adjust **CameraBoom > Target Arm Length**
2. Typical values: 300-600 units

---

## Summary

**Question 1: Can I have a visible player character with animations using store assets?**
✅ **YES!** Very easily:
- UE Third Person Template (5 min)
- Mixamo (15 min, free)
- UE Marketplace (varies, many free options)

**Question 2: Is the gameplay loop implemented in C++?**
✅ **YES!** 100% implemented:
- Input handling
- Movement logic
- Camera system
- Jump mechanics
- Character controller

**You only need to assign visual assets** - all gameplay code is complete in C++!

---

## Resources

### Free Character Sources
- **Mixamo**: https://www.mixamo.com (Free, Adobe account)
- **UE Marketplace**: https://www.unrealengine.com/marketplace (Filter: Free)
- **Sketchfab**: https://sketchfab.com (Many free rigged characters)

### Unreal Engine Documentation
- **Character Setup**: https://docs.unrealengine.com/5.6/en-US/character-setup-in-unreal-engine/
- **Animation Blueprint**: https://docs.unrealengine.com/5.6/en-US/animation-blueprints-in-unreal-engine/
- **Importing Characters**: https://docs.unrealengine.com/5.6/en-US/importing-skeletal-mesh-characters-in-unreal-engine/

### Project Documentation
- **QUICK_START.md** - Get the project running
- **PROJECT_OVERVIEW.md** - Understand the architecture
- **TODO_ASSETS.md** - What assets to create

---

## Next Steps

1. **Choose your method** (Third Person Template recommended for quickest start)
2. **Follow the steps** to add character mesh and animations
3. **Test in Play mode**
4. **Customize** appearance, animations, and settings as desired
5. **Start building your game!** All gameplay systems are ready in C++

Happy developing! 🎮
