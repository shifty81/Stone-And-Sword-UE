# Creating the Default Empty Map

This guide explains how to create the default empty map for the Stone and Sword project.

## Why This is Needed

The project uses `/Engine/Maps/Entry` as a temporary default map reference. To make the project fully self-contained, you should create a project-specific empty map.

## Steps to Create

1. Open the Unreal Editor with the Stone and Sword project
2. Go to **File > New Level**
3. Select **Empty Level**
4. Save the level:
   - Press **Ctrl+S** (or **Cmd+S** on Mac)
   - Navigate to `Content/Maps/`
   - Name it `DefaultEmpty`
   - Click **Save**

## Update the Configuration

After creating the map, update `Config/DefaultEngine.ini`:

Replace:
```ini
GameDefaultMap=/Engine/Maps/Entry
EditorStartupMap=/Engine/Maps/Entry
```

With:
```ini
GameDefaultMap=/Game/Maps/DefaultEmpty
EditorStartupMap=/Game/Maps/DefaultEmpty
```

## What This Does

- **GameDefaultMap**: The map that loads when you package and run the game
- **EditorStartupMap**: The map that opens when you launch the editor

By using a project-specific empty map:
- The project is self-contained and doesn't depend on engine maps
- The automatic world setup will work correctly every time
- You won't have issues if Unreal Engine changes its default maps

## Testing

After creating the map and updating the configuration:

1. Close and reopen the editor
2. The `DefaultEmpty` map should open automatically
3. Press Play (Alt+P)
4. The world should generate automatically

If the world doesn't generate, check that:
- The GameMode is set to `StoneAndSwordGameModeBase`
- The GameMode has "Auto Spawn World Setup Manager" enabled
- Check the Output Log for any error messages

## Alternative: Use Existing Maps

If you prefer to use your own custom map as the default:
1. Create or open your map
2. Go to **Edit > Project Settings**
3. Navigate to **Maps & Modes**
4. Set **Editor Startup Map** to your map
5. Set **Game Default Map** to your map

The automatic world setup will still work as long as the GameMode is configured correctly.
