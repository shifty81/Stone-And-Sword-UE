"""
Automated Project Setup Script for Stone and Sword
This script creates all necessary assets to make the project immediately playable.
Run this from Unreal Engine's Python console or as a startup script.

Usage:
1. Open Unreal Editor
2. Window > Developer Tools > Output Log
3. Type: py Content/Python/setup_project_assets.py
   OR
4. Edit > Editor Preferences > Python > Startup Scripts > Add this file
"""

import unreal

def log(message):
    """Print to Unreal's output log"""
    unreal.log(f"[ProjectSetup] {message}")

def log_warning(message):
    """Print warning to Unreal's output log"""
    unreal.log_warning(f"[ProjectSetup] {message}")

def log_error(message):
    """Print error to Unreal's output log"""
    unreal.log_error(f"[ProjectSetup] {message}")

def create_default_map():
    """Create the default empty map with basic lighting and sky"""
    log("Creating default map...")
    
    # Create new level
    editor_level_lib = unreal.EditorLevelLibrary()
    
    # Check if map already exists
    map_path = "/Game/Maps/DefaultEmpty"
    if unreal.EditorAssetLibrary.does_asset_exist(map_path):
        log(f"Map already exists at {map_path}, skipping creation")
        return True
    
    # Create new empty level
    new_world = editor_level_lib.new_level("/Game/Maps/DefaultEmpty")
    if not new_world:
        log_error("Failed to create new level")
        return False
    
    # Get the world
    world = unreal.EditorLevelLibrary.get_editor_world()
    
    # Spawn Directional Light
    directional_light = editor_level_lib.spawn_actor_from_class(
        unreal.DirectionalLight,
        location=unreal.Vector(0, 0, 1000),
        rotation=unreal.Rotator(-50, 0, 0)
    )
    if directional_light:
        # Configure directional light
        light_component = directional_light.get_component_by_class(unreal.DirectionalLightComponent)
        if light_component:
            light_component.set_intensity(10.0)
            light_component.set_atmosphere_sun_light(True)
        log("Created Directional Light")
    
    # Spawn Sky Atmosphere
    sky_atmosphere = editor_level_lib.spawn_actor_from_class(
        unreal.SkyAtmosphere,
        location=unreal.Vector(0, 0, 0)
    )
    if sky_atmosphere:
        log("Created Sky Atmosphere")
    
    # Spawn Sky Light
    sky_light = editor_level_lib.spawn_actor_from_class(
        unreal.SkyLight,
        location=unreal.Vector(0, 0, 0)
    )
    if sky_light:
        # Configure sky light
        sky_light_component = sky_light.get_component_by_class(unreal.SkyLightComponent)
        if sky_light_component:
            sky_light_component.set_intensity(1.0)
            sky_light_component.recapture_sky()
        log("Created Sky Light")
    
    # Spawn Exponential Height Fog
    height_fog = editor_level_lib.spawn_actor_from_class(
        unreal.ExponentialHeightFog,
        location=unreal.Vector(0, 0, 0)
    )
    if height_fog:
        log("Created Exponential Height Fog")
    
    # Spawn Post Process Volume
    post_process = editor_level_lib.spawn_actor_from_class(
        unreal.PostProcessVolume,
        location=unreal.Vector(0, 0, 0)
    )
    if post_process:
        post_process.set_actor_property("bUnbound", True)
        log("Created Post Process Volume")
    
    # Spawn Player Start
    player_start = editor_level_lib.spawn_actor_from_class(
        unreal.PlayerStart,
        location=unreal.Vector(0, 0, 200)
    )
    if player_start:
        log("Created Player Start")
    
    # Save the map
    success = unreal.EditorAssetLibrary.save_loaded_asset(world)
    if success:
        log(f"Successfully created and saved map at {map_path}")
        return True
    else:
        log_error("Failed to save map")
        return False

def create_terrain_material():
    """Create the basic terrain material using the grass texture"""
    log("Creating terrain material...")
    
    material_path = "/Game/Materials/M_Terrain"
    
    # Check if material already exists
    if unreal.EditorAssetLibrary.does_asset_exist(material_path):
        log(f"Material already exists at {material_path}, skipping creation")
        return True
    
    # Create material asset
    asset_tools = unreal.AssetToolsHelpers.get_asset_tools()
    material_factory = unreal.MaterialFactoryNew()
    
    material = asset_tools.create_asset(
        asset_name="M_Terrain",
        package_path="/Game/Materials",
        asset_class=unreal.Material,
        factory=material_factory
    )
    
    if not material:
        log_error("Failed to create material asset")
        return False
    
    # Load grass texture
    grass_texture = unreal.load_asset("/Game/Textures/T_Grass")
    if not grass_texture:
        log_warning("Could not load grass texture, material will be created without texture")
    else:
        # Create texture sample node
        texture_sample = unreal.MaterialEditingLibrary.create_material_expression(
            material,
            unreal.MaterialExpressionTextureSample,
            -400, 0
        )
        texture_sample.texture = grass_texture
        
        # Connect to Base Color
        unreal.MaterialEditingLibrary.connect_material_property(
            texture_sample, "RGB",
            unreal.MaterialProperty.MP_BASE_COLOR
        )
        log("Connected grass texture to Base Color")
    
    # Save material
    unreal.EditorAssetLibrary.save_loaded_asset(material)
    log(f"Successfully created terrain material at {material_path}")
    return True

def configure_project_settings():
    """Configure project settings to use the created assets"""
    log("Configuring project settings...")
    
    # Get project settings
    editor_engine = unreal.get_editor_subsystem(unreal.UnrealEditorSubsystem)
    
    # Note: Project settings for default maps are configured in DefaultEngine.ini
    # This Python script confirms they exist
    
    map_path = "/Game/Maps/DefaultEmpty"
    if unreal.EditorAssetLibrary.does_asset_exist(map_path):
        log("Default map is ready. Update DefaultEngine.ini to use it:")
        log("  GameDefaultMap=/Game/Maps/DefaultEmpty")
        log("  EditorStartupMap=/Game/Maps/DefaultEmpty")
    else:
        log_warning("Default map not found, please run create_default_map() first")
    
    return True

def update_engine_config():
    """Update DefaultEngine.ini to use the created map"""
    log("Updating engine configuration...")
    
    import configparser
    import os
    
    # Get project directory
    project_dir = unreal.Paths.project_dir()
    config_path = os.path.join(project_dir, "Config", "DefaultEngine.ini")
    
    if not os.path.exists(config_path):
        log_error(f"Config file not found: {config_path}")
        return False
    
    try:
        # Read the config file
        with open(config_path, 'r') as f:
            lines = f.readlines()
        
        # Update the map settings
        new_lines = []
        in_maps_section = False
        updated_game_map = False
        updated_editor_map = False
        
        for line in lines:
            if line.strip().startswith('[/Script/EngineSettings.GameMapsSettings]'):
                in_maps_section = True
                new_lines.append(line)
            elif line.strip().startswith('[') and in_maps_section:
                in_maps_section = False
                new_lines.append(line)
            elif in_maps_section:
                if line.strip().startswith('GameDefaultMap='):
                    new_lines.append('GameDefaultMap=/Game/Maps/DefaultEmpty\n')
                    updated_game_map = True
                elif line.strip().startswith('EditorStartupMap='):
                    new_lines.append('EditorStartupMap=/Game/Maps/DefaultEmpty\n')
                    updated_editor_map = True
                else:
                    new_lines.append(line)
            else:
                new_lines.append(line)
        
        # Write back
        with open(config_path, 'w') as f:
            f.writelines(new_lines)
        
        if updated_game_map and updated_editor_map:
            log("Successfully updated DefaultEngine.ini with new map paths")
            log("Please restart Unreal Editor for changes to take effect")
            return True
        else:
            log_warning("Could not find map settings to update in config")
            return False
            
    except Exception as e:
        log_error(f"Error updating config: {str(e)}")
        return False

def setup_project():
    """Main setup function - creates all necessary assets"""
    log("=" * 60)
    log("Starting Stone and Sword Project Setup")
    log("=" * 60)
    
    success = True
    
    # Step 1: Create default map
    if not create_default_map():
        success = False
    
    # Step 2: Create terrain material
    if not create_terrain_material():
        success = False
    
    # Step 3: Update config
    if not update_engine_config():
        log_warning("Config update failed, you may need to manually update DefaultEngine.ini")
    
    # Summary
    log("=" * 60)
    if success:
        log("✓ Project setup completed successfully!")
        log("")
        log("Next steps:")
        log("1. Restart Unreal Editor for config changes to take effect")
        log("2. Press the Play button to test your procedural world")
        log("3. Use WASD to move, Mouse to look, Spacebar to jump")
        log("")
        log("For more information, see QUICK_START.md")
    else:
        log_error("✗ Project setup completed with errors")
        log("Please check the errors above and try manual setup")
        log("See QUICK_START.md for manual setup instructions")
    log("=" * 60)
    
    return success

# Auto-run if executed as main script
if __name__ == "__main__":
    setup_project()
