# TODO: Assets to Create in Unreal Editor

This file tracks the assets you need to create in the Unreal Editor to complete the project setup.

## Quick Checklist (10 minutes total)

Follow `QUICK_START.md` for step-by-step instructions.

### Maps (5 minutes)
- [ ] **DefaultEmpty.umap** - Main level
  - Location: `Content/Maps/DefaultEmpty.umap`
  - Create: File > New Level > Empty Level
  - Add: Directional Light, Sky Atmosphere, Sky Light, Player Start
  - Save to: Content/Maps/DefaultEmpty

### Materials (3 minutes)
- [ ] **M_Terrain** - Basic terrain material
  - Location: `Content/Materials/M_Terrain.uasset`
  - Create: Right-click > Material
  - Connect: T_Grass texture to Base Color
  - Save and compile

### Configuration (2 minutes)
- [ ] **Set Default Maps** in Project Settings
  - Editor Startup Map: `/Game/Maps/DefaultEmpty`
  - Game Default Map: `/Game/Maps/DefaultEmpty`
  - Default GameMode: `StoneAndSwordGameModeBase` (should be set)

## Optional Assets (Improve Quality)

### Additional Materials (10 minutes)
- [ ] **M_Terrain_Stone** - Stone material using T_Stone
- [ ] **M_Terrain_Dirt** - Dirt material using T_Dirt
- [ ] **MI_Terrain_Grass** - Material Instance of M_Terrain
- [ ] **MI_Terrain_Rocky** - Material Instance with stone blend

### Animation Blueprint (15 minutes)
- [ ] **ABP_PlayerCharacter** - Animation Blueprint
  - **NEW!** See **[CHARACTER_SETUP_GUIDE.md](CHARACTER_SETUP_GUIDE.md)** for detailed instructions
  - Skeleton: Import from Mixamo or use Third Person Template
  - State Machine: Idle, Walk, Run, Jump
  - Animation Assets: Download from Mixamo or use starter content

### Character Mesh (20 minutes)
- [ ] **SK_PlayerCharacter** - Skeletal Mesh
  - **NEW!** See **[CHARACTER_SETUP_GUIDE.md](CHARACTER_SETUP_GUIDE.md)** for detailed instructions
  - Import from Mixamo (free)
  - Or use Third Person Template character
  - Assign to WorldPlayerCharacter in C++ or Blueprint
  - **C++ support added**: Can set CharacterMeshAsset and AnimationBlueprintClass properties

### Environment Assets (Optional, as needed)
- [ ] **SM_Tree** - Tree static mesh
- [ ] **SM_Rock** - Rock static mesh
- [ ] **SM_Grass_Cluster** - Grass foliage mesh
- [ ] **BP_TreeSpawner** - Blueprint for spawning trees

## Already Included (No Action Needed)

✅ All C++ source code
✅ Configuration files (Input, Engine, Game)
✅ Base textures (T_Grass, T_Stone, T_Dirt, T_Normal)
✅ Build configuration files
✅ Documentation

## Why Binary Assets Aren't Included

Unreal Engine content files (.uasset, .umap) are:
- **Binary formats** - Not human-readable
- **Large files** - Several MB each
- **Version-specific** - May not work across UE versions
- **Best created fresh** - Ensures compatibility with your setup

By creating them yourself:
- ✅ Ensures compatibility with your UE version
- ✅ Smaller repository size
- ✅ You learn the asset creation workflow
- ✅ Customizable from the start

## Estimated Time

| Task | Time | Priority |
|------|------|----------|
| Basic Level | 5 min | **Required** |
| Basic Material | 3 min | **Required** |
| Configuration | 2 min | **Required** |
| **Total Minimum** | **10 min** | - |
| Additional Materials | 10 min | Optional |
| Animation Blueprint | 15 min | Optional |
| Character Mesh | 20 min | Optional |
| **Total Full Setup** | **55 min** | - |

## Getting Started

1. **Minimum Setup** (10 minutes)
   - Follow `QUICK_START.md`
   - Create DefaultEmpty map
   - Create M_Terrain material
   - Set default maps in Project Settings
   - Press Play and test!

2. **Full Setup** (55 minutes)
   - Follow `SETUP_INSTRUCTIONS.md`
   - Create all optional assets
   - Import character and animations
   - Customize and polish

3. **Advanced Customization** (ongoing)
   - Add more biomes and materials
   - Create custom character models
   - Implement gameplay mechanics
   - Build and package your game

## Status Tracking

Mark your progress as you create assets:

**Session 1: Minimum Viable Setup** ⏱️ 10 min
- [ ] Created DefaultEmpty.umap
- [ ] Created M_Terrain material
- [ ] Set default maps in Project Settings
- [ ] Tested with Play button - character moves on terrain

**Session 2: Enhanced Visuals** ⏱️ 15 min
- [ ] Created additional terrain materials
- [ ] Created material instances
- [ ] Improved lighting setup
- [ ] Added post-processing

**Session 3: Character Setup** ⏱️ 30 min
- [ ] Downloaded/imported character mesh
- [ ] Downloaded/imported animations
- [ ] Created animation blueprint
- [ ] Assigned to player character
- [ ] Tested movement with animations

**Session 4: Environment** ⏱️ Variable
- [ ] Imported environment assets
- [ ] Created spawner blueprints
- [ ] Populated world with objects
- [ ] Optimized performance

## Help and Resources

- **Quick Setup**: `QUICK_START.md`
- **Detailed Instructions**: `SETUP_INSTRUCTIONS.md`
- **Verification**: `VERIFICATION_CHECKLIST.md`
- **Content Structure**: `Content/README.md`
- **Project Overview**: `README.md`

## Free Asset Resources

### Character Models & Animations
- **Mixamo** - https://www.mixamo.com (Free, Adobe account required)
  - Hundreds of characters
  - Thousands of animations
  - Auto-rigging service

### Textures
- **Quixel Megascans** - Free for UE users via Quixel Bridge
- **Texture Haven** - https://texturehaven.com
- **FreePBR** - https://freepbr.com

### Models
- **Sketchfab** - https://sketchfab.com (Filter by "Downloadable" + "Free")
- **Kenney Assets** - https://kenney.nl (Free, game-ready assets)
- **CGTrader Free** - https://www.cgtrader.com/free-3d-models

### Sounds (Future)
- **Freesound** - https://freesound.org
- **Sonniss GDC** - Free annual sound pack
- **OpenGameArt** - https://opengameart.org

## Support

Having trouble?
1. Check Output Log in Unreal Editor
2. Review troubleshooting in `SETUP_INSTRUCTIONS.md`
3. Verify all steps in `VERIFICATION_CHECKLIST.md`
4. Open a GitHub issue with details

---

**Current Project State**: Ready for asset creation  
**Next Step**: Follow `QUICK_START.md` to create your first playable scene  
**Time to Playable**: 10 minutes  

Let's build something awesome! 🎮
