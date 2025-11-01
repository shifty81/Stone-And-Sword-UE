# Material Setup Guide

## Terrain Material

To create a basic terrain material in the Unreal Editor:

### Steps:
1. In Content Browser, navigate to Content/Materials
2. Right-click and create a new Material
3. Name it "M_Terrain"
4. Open the material editor

### Basic Material Setup:

#### Nodes to Add:
1. **Texture Sample** - Connect T_Grass texture
   - Connect RGB to Base Color
   
2. **Texture Sample** - Connect T_Normal texture
   - Connect RGB to Normal
   
3. **Constant** - Set to 0.5 for Roughness
   - Connect to Roughness input
   
4. **Constant** - Set to 0.0 for Metallic
   - Connect to Metallic input

### Advanced Multi-Texture Setup:

For blended terrain textures:

1. **Landscape Layer Blend** node
   - Add layers: Grass, Stone, Dirt
   - Set blend types to Weight-Blended
   
2. **Texture Samples** for each layer
   - T_Grass
   - T_Stone
   - T_Dirt
   
3. Connect each texture to corresponding layer in Layer Blend
4. Connect Layer Blend output to Base Color

### Material Properties:
- **Shading Model**: Default Lit
- **Blend Mode**: Opaque
- **Two Sided**: Disabled (for performance)
- **Used with Procedural Mesh**: Enabled (Important!)

### Applying to World Generator:
1. Save and compile the material
2. In the World Generator actor's Details panel
3. Set the "Terrain Material" property to M_Terrain
4. Regenerate the world to see changes

## Vertex Color Support

The WorldGenerator creates vertex colors based on height:
- You can use the Vertex Color node in materials
- Connect Vertex Color to Lerp nodes for height-based texturing
- Useful for automatic grass/stone/snow transitions

## Performance Tips

1. Use texture streaming for large worlds
2. Keep texture resolution reasonable (512-2048 recommended)
3. Use Material Instances for runtime parameter changes
4. Enable texture compression in import settings
5. Use LODs for distant terrain

## Example Material Graphs

### Simple Grass Material:
```
[T_Grass Texture] -> [Base Color]
[Constant(0.5)] -> [Roughness]
[Constant(0.0)] -> [Metallic]
```

### Height-Based Blending:
```
[Vertex Color] -> [Lerp(A=Grass, B=Stone, Alpha=R)] -> [Base Color]
```

### UV Tiling:
```
[TextureCoordinate(Tiling=10,10)] -> [T_Grass Texture] -> [Base Color]
```

The World Generator already applies UV tiling (10x) in the mesh generation for better texture detail.
