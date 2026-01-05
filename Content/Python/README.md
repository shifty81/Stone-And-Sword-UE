# Python Automation Scripts

This folder contains Python scripts to automate project setup in Unreal Engine.

## setup_project_assets.py

Automatically creates all necessary assets for the project to be playable:
- DefaultEmpty.umap (main level with lighting and sky)
- M_Terrain.uasset (terrain material with grass texture)
- Updates DefaultEngine.ini configuration

### Usage

#### Method 1: Run from Python Console (Recommended)

1. Open the project in Unreal Engine 5.6
2. Open **Window > Developer Tools > Output Log**
3. In the Output Log's command line, type:
   ```python
   py Content/Python/setup_project_assets.py
   ```
4. Press Enter and watch the setup progress
5. Restart Unreal Editor when prompted
6. Press Play to test!

#### Method 2: Run from Python Script Editor

1. Open **Tools > Scripting > Python Script Editor**
2. Open `Content/Python/setup_project_assets.py`
3. Click **Execute**
4. Follow the instructions in the Output Log

#### Method 3: Set as Startup Script

1. Open **Edit > Editor Preferences**
2. Search for "Python"
3. Under **Python > Startup Scripts**, click **+** to add a new script
4. Browse to `Content/Python/setup_project_assets.py`
5. The script will run automatically next time you open the editor

### What It Does

The script performs the following actions:

1. **Creates DefaultEmpty.umap** in `Content/Maps/`
   - Adds Directional Light (sun)
   - Adds Sky Atmosphere
   - Adds Sky Light
   - Adds Exponential Height Fog
   - Adds Post Process Volume
   - Adds Player Start at (0, 0, 200)

2. **Creates M_Terrain material** in `Content/Materials/`
   - Loads T_Grass texture
   - Connects it to Base Color
   - Configures as Opaque, Default Lit

3. **Updates DefaultEngine.ini**
   - Sets GameDefaultMap to /Game/Maps/DefaultEmpty
   - Sets EditorStartupMap to /Game/Maps/DefaultEmpty

### Troubleshooting

**"Python is not enabled"**
- Go to **Edit > Plugins**
- Search for "Python Editor Script Plugin"
- Enable it and restart the editor

**"Module 'unreal' has no attribute..."**
- Make sure you're running this from within Unreal Engine
- The `unreal` module is only available in Unreal's Python environment

**Script doesn't create assets**
- Check the Output Log for error messages
- Ensure you have write permissions to the Content folder
- Try creating assets manually following QUICK_START.md

**Assets already exist**
- The script will skip creating existing assets
- If you want to recreate them, delete them first and run the script again

### Manual Alternative

If the Python script doesn't work for any reason, you can create assets manually:
- Follow the step-by-step instructions in **QUICK_START.md**
- Takes approximately 10 minutes
- No programming required

## Requirements

- Unreal Engine 5.6 or 5.6.1
- Python Editor Script Plugin (enabled by default in UE 5.6)
- Write permissions to the project's Content folder

## Support

For issues or questions:
1. Check the Output Log in Unreal Editor for detailed error messages
2. Review QUICK_START.md for manual setup instructions
3. See TROUBLESHOOTING_BUILD.md for build-related issues
4. Open a GitHub issue with your error log
