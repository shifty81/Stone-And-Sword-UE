# Content Directory Structure

This directory contains all Unreal Engine content assets for the Stone and Sword project.

## Directory Layout

```
Content/
├── Maps/              # Level files (.umap)
│   └── DefaultEmpty   # Main default level (you'll create this)
├── Materials/         # Material assets (.uasset)
│   └── M_Terrain      # Terrain material (you'll create this)
├── Textures/          # Texture files
│   ├── T_Grass.tga    # Grass texture (provided)
│   ├── T_Stone.tga    # Stone texture (provided)
│   ├── T_Dirt.tga     # Dirt texture (provided)
│   └── T_Normal.tga   # Normal map texture (provided)
├── Blueprints/        # Blueprint assets
│   └── (future)       # Blueprint classes if needed
└── Animations/        # Animation assets
    └── (future)       # Animation blueprints and sequences
```

## What's Included

### Textures (Ready to Use)

- **T_Grass.tga** - Basic grass texture (512x512)
- **T_Stone.tga** - Stone/rock texture (512x512)
- **T_Dirt.tga** - Dirt/soil texture (512x512)
- **T_Normal.tga** - Generic normal map (512x512)

These textures are provided as TGA files and can be imported into Unreal Engine or used directly.

## What You Need to Create

### Maps

You need to create at least one level:

**DefaultEmpty.umap** - The main playable level
- Location: `Content/Maps/DefaultEmpty.umap`
- Create via: File > New Level > Empty Level
- See: `QUICK_START.md` for instructions

### Materials

You need to create materials that reference the textures:

**M_Terrain** - Basic terrain material
- Location: `Content/Materials/M_Terrain.uasset`
- Create via: Right-click in Content Browser > Material
- Connect T_Grass texture to Base Color
- See: `QUICK_START.md` for instructions

**Optional additional materials:**
- M_Terrain_Stone (using T_Stone)
- M_Terrain_Dirt (using T_Dirt)
- Material instances for variations

### Animations (Optional)

For placeholder animations, you can:
- Use Unreal's default character animations
- Import from Mixamo (free)
- Use Third Person Template content
- See: `SETUP_INSTRUCTIONS.md` for animation setup

## Why Are Content Files Not Included?

Unreal Engine content files (.uasset, .umap) are **binary files** that:
- Are large (several MB each)
- Change frequently during development
- Are best created fresh in the Unreal Editor
- May have version compatibility issues

Instead, we provide:
- ✅ All C++ source code (in `Source/`)
- ✅ Base textures (in `Content/Textures/`)
- ✅ Configuration files (in `Config/`)
- ✅ Detailed setup instructions (see `QUICK_START.md`)

This approach:
- Keeps the repository small
- Ensures compatibility with your UE version
- Lets you customize from the start
- Takes only 10 minutes to set up

## Creating Your Content

### Quick Method (10 minutes)
Follow `QUICK_START.md` for the fastest setup.

### Detailed Method (30 minutes)
Follow `SETUP_INSTRUCTIONS.md` for comprehensive instructions.

### Automated Method (Future)
We may add automation scripts to generate these assets programmatically.

## File Organization Best Practices

When adding your own content:

### Naming Conventions
- **Textures**: Prefix with `T_` (e.g., `T_Grass`)
- **Materials**: Prefix with `M_` (e.g., `M_Terrain`)
- **Material Instances**: Prefix with `MI_` (e.g., `MI_Terrain_Grass`)
- **Blueprints**: Prefix with `BP_` (e.g., `BP_PlayerCharacter`)
- **Meshes**: Prefix with `SM_` (static) or `SK_` (skeletal)

### Directory Structure
- Keep related assets together
- Use subdirectories for large projects
- Example: `Content/Environment/Rocks/`, `Content/Characters/Player/`

### Version Control
The `.gitignore` is configured to:
- ✅ Track: Source code, config files, text documentation
- ✅ Track: Raw texture files (TGA, PNG)
- ❌ Ignore: Compiled binaries, built data, cache files
- ⚠️ Caution: Binary assets (.uasset, .umap) can be tracked but grow repository size

## Adding New Textures

To add more textures:

1. Place texture files (TGA, PNG, etc.) in `Content/Textures/`
2. Open Unreal Editor
3. Navigate to Content/Textures in Content Browser
4. They should appear automatically (or click Import)
5. Create materials that reference these textures

## Next Steps

1. **Create the default level**: See `QUICK_START.md` Step 2
2. **Create the terrain material**: See `QUICK_START.md` Step 3
3. **Test your scene**: Press Play in Unreal Editor
4. **Iterate and expand**: Add more features, textures, materials

## Need Help?

- **Quick Setup**: See `QUICK_START.md`
- **Detailed Setup**: See `SETUP_INSTRUCTIONS.md`
- **Project Overview**: See `README.md`
- **Unreal Docs**: https://docs.unrealengine.com/5.6/

## Summary

✅ Textures are provided and ready to use  
⚠️ Maps and materials need to be created (10 minutes)  
📖 Detailed instructions available in `QUICK_START.md`  
🎮 You'll have a playable scene very quickly!
