# Lua Scripting API Reference

## Overview

The Stone and Sword engine integrates Lua 5.4 for game scripting, providing a powerful and flexible way to create game logic without recompiling C++ code.

## Getting Started

### Hello World Script

Create `Game/Scripts/hello.lua`:

```lua
-- Simple hello world script
print("Hello from Lua!")

function Initialize()
    print("Game initializing...")
end

function Update(deltaTime)
    -- Called every frame
    -- deltaTime is in seconds
end
```

Load the script from C++:
```cpp
engine.GetLuaEngine()->ExecuteFile("Game/Scripts/hello.lua");
```

## Core API

### Engine Module

Access the main engine instance:

```lua
-- Get engine instance (automatically available as global)
Engine:GetWorld()      -- Returns ECSWorld
Engine:GetRenderer()   -- Returns Renderer
Engine:GetInput()      -- Returns InputManager
Engine:Stop()          -- Stop the engine
```

### Math Module

Vector and matrix operations using GLM:

```lua
-- Create vectors
local position = math.vec3(0, 0, 0)
local direction = math.vec3(1, 0, 0)

-- Access components
print(position.x, position.y, position.z)

-- Modify components
position.x = 10
position.y = 5
position.z = -3

-- Create quaternions
local rotation = math.quat(1, 0, 0, 0)  -- w, x, y, z

-- Create matrices
local transform = math.mat4(1.0)  -- Identity matrix
```

### World Module

Entity and component management:

```lua
-- Create an entity
local entity = World:CreateEntity()

-- Add components
local transform = World:AddTransform(entity)
transform.position = math.vec3(0, 0, 0)
transform.rotation = math.quat(1, 0, 0, 0)
transform.scale = math.vec3(1, 1, 1)

-- Add mesh renderer
local renderer = World:AddMeshRenderer(entity)
renderer.mesh = CreateCubeMesh()

-- Get component
local transform = World:GetTransform(entity)

-- Remove component
World:RemoveTransform(entity)

-- Destroy entity
World:DestroyEntity(entity)
```

### Input Module

Handle keyboard and mouse input:

```lua
-- Keyboard input
if Input:IsKeyPressed(Key.W) then
    -- Move forward
end

if Input:IsKeyDown(Key.Space) then
    -- Jump
end

if Input:IsKeyReleased(Key.Escape) then
    -- Pause menu
end

-- Mouse input
if Input:IsMouseButtonPressed(MouseButton.Left) then
    -- Shoot
end

local mouseX, mouseY = Input:GetMousePosition()
local deltaX, deltaY = Input:GetMouseDelta()

-- Gamepad input
if Input:IsGamepadConnected(0) then
    local leftX = Input:GetGamepadAxis(0, GamepadAxis.LeftX)
    local leftY = Input:GetGamepadAxis(0, GamepadAxis.LeftY)
    
    if Input:IsGamepadButtonPressed(0, GamepadButton.A) then
        -- Jump
    end
end
```

## Component API

### Transform Component

Position, rotation, and scale:

```lua
-- Create/Get transform
local transform = World:AddTransform(entity)

-- Position
transform.position = math.vec3(10, 0, 5)
transform.position.x = 20

-- Rotation (quaternion)
transform.rotation = math.quat(1, 0, 0, 0)

-- Scale
transform.scale = math.vec3(2, 2, 2)

-- Get world matrix
local matrix = transform:GetMatrix()

-- Transform direction from local to world space
local worldDir = transform:TransformDirection(math.vec3(0, 0, 1))
```

### MeshRenderer Component

Render a mesh with a material:

```lua
-- Add mesh renderer
local meshRenderer = World:AddMeshRenderer(entity)

-- Set mesh
meshRenderer.mesh = CreateSphereMesh(1.0, 32, 32)

-- Set material (optional)
meshRenderer.material = CreateMaterial("Shaders/Basic.shader")
```

### Camera Component

Control the game camera:

```lua
-- Add camera
local camera = World:AddCamera(entity)

-- Camera properties
camera.fov = 60.0           -- Field of view in degrees
camera.nearPlane = 0.1      -- Near clipping plane
camera.farPlane = 1000.0    -- Far clipping plane
camera.isActive = true      -- Active camera renders to screen

-- Get projection matrix
local projMatrix = camera:GetProjectionMatrix(aspectRatio)

-- Get view matrix
local viewMatrix = camera:GetViewMatrix(transform)
```

### RigidBody Component (Physics)

Add physics simulation:

```lua
-- Add rigid body
local rigidBody = World:AddRigidBody(entity)

-- Properties
rigidBody.mass = 1.0
rigidBody.friction = 0.5
rigidBody.restitution = 0.3
rigidBody.isKinematic = false
rigidBody.useGravity = true

-- Apply forces
rigidBody:ApplyForce(math.vec3(0, 100, 0))
rigidBody:ApplyImpulse(math.vec3(10, 0, 0))
rigidBody:ApplyTorque(math.vec3(0, 1, 0))

-- Get/Set velocity
local velocity = rigidBody:GetVelocity()
rigidBody:SetVelocity(math.vec3(0, 5, 0))
```

### CharacterController Component

Character movement and collision:

```lua
-- Add character controller
local controller = World:AddCharacterController(entity)

-- Properties
controller.movementSpeed = 5.0
controller.rotationSpeed = 2.0
controller.jumpForce = 10.0

-- Check if grounded
if controller.isGrounded then
    -- Can jump
end

-- Move character
controller:Move(math.vec3(1, 0, 0) * deltaTime * controller.movementSpeed)
```

## World Generation API

### WorldGenerator

Generate procedural terrain:

```lua
-- Create world generator configuration
local config = {
    worldSizeX = 10000,
    worldSizeY = 10000,
    gridResolution = 100,
    heightVariation = 50,
    noiseScale = 0.01,
    randomSeed = 12345
}

-- Create world generator
local generator = WorldGenerator(config)

-- Generate world
generator:Generate(World, Renderer)

-- Change configuration
config.worldSizeX = 20000
generator:SetConfig(config)
generator:Generate(World, Renderer)
```

### Custom Terrain Height Function

Override the default height calculation:

```lua
-- Custom height function
function CalculateHeight(x, y)
    -- Simple sine wave terrain
    return math.sin(x * 0.01) * math.cos(y * 0.01) * 50.0
end

-- Apply custom height function
generator:SetHeightFunction(CalculateHeight)
```

## Resource API

### Mesh Creation

Create meshes programmatically:

```lua
-- Create cube mesh
local cubeMesh = CreateCubeMesh(
    1.0,    -- size
    true    -- generate UVs
)

-- Create sphere mesh
local sphereMesh = CreateSphereMesh(
    1.0,    -- radius
    32,     -- rings
    32      -- sectors
)

-- Create plane mesh
local planeMesh = CreatePlaneMesh(
    10.0,   -- width
    10.0,   -- height
    10,     -- subdivisions X
    10      -- subdivisions Y
)

-- Load mesh from file
local mesh = LoadMesh("Assets/Models/character.obj")
```

### Texture Loading

Load and manage textures:

```lua
-- Load texture
local texture = LoadTexture("Assets/Textures/stone.png")

-- Create texture from data
local textureData = CreateTextureData(512, 512, TextureFormat.RGBA8)
local texture = CreateTexture(textureData)

-- Texture properties
texture:SetFilterMode(FilterMode.Linear)
texture:SetWrapMode(WrapMode.Repeat)
```

### Material Creation

Create and configure materials:

```lua
-- Create material
local material = CreateMaterial("Shaders/Standard.shader")

-- Set properties
material:SetColor("baseColor", math.vec4(1, 1, 1, 1))
material:SetFloat("metallic", 0.5)
material:SetFloat("roughness", 0.5)

-- Set textures
material:SetTexture("albedoMap", LoadTexture("Assets/Textures/albedo.png"))
material:SetTexture("normalMap", LoadTexture("Assets/Textures/normal.png"))
```

### Audio

Play sounds and music:

```lua
-- Load sound
local sound = LoadSound("Assets/Audio/jump.wav")

-- Play sound
sound:Play()
sound:Stop()
sound:Pause()

-- Sound properties
sound:SetVolume(0.8)
sound:SetPitch(1.0)
sound:SetLooping(false)

-- 3D positional audio
sound:SetPosition(math.vec3(10, 0, 5))
sound:SetMaxDistance(100.0)
```

## Advanced Features

### Custom Components

Define custom components in Lua:

```lua
-- Define custom component
HealthComponent = {
    health = 100,
    maxHealth = 100,
    
    TakeDamage = function(self, amount)
        self.health = math.max(0, self.health - amount)
        if self.health <= 0 then
            self:Die()
        end
    end,
    
    Heal = function(self, amount)
        self.health = math.min(self.maxHealth, self.health + amount)
    end,
    
    Die = function(self)
        print("Entity died!")
        -- Handle death
    end
}

-- Add to entity
local health = World:AddLuaComponent(entity, "HealthComponent", HealthComponent)

-- Use component
health:TakeDamage(20)
health:Heal(10)
```

### Event System

Subscribe to and emit events:

```lua
-- Subscribe to event
Events:Subscribe("PlayerDied", function(data)
    print("Player died at position:", data.position)
end)

-- Emit event
Events:Emit("PlayerDied", {
    position = math.vec3(10, 0, 5),
    killer = "Enemy"
})

-- Unsubscribe
Events:Unsubscribe("PlayerDied", handlerId)
```

### Coroutines

Use Lua coroutines for complex sequences:

```lua
-- Define coroutine
function SpawnWave()
    for i = 1, 10 do
        SpawnEnemy()
        coroutine.yield(1.0)  -- Wait 1 second
    end
end

-- Start coroutine
local wave = coroutine.create(SpawnWave)
Coroutines:Start(wave)
```

### Save/Load System

Serialize game state:

```lua
-- Save game state
local saveData = {
    playerPosition = transform.position,
    playerHealth = health.health,
    score = 1000
}

SaveSystem:Save("savegame.json", saveData)

-- Load game state
local loadData = SaveSystem:Load("savegame.json")
transform.position = loadData.playerPosition
health.health = loadData.playerHealth
```

## Complete Example: Player Controller

```lua
-- Player controller script

-- Configuration
local PlayerConfig = {
    movementSpeed = 5.0,
    rotationSpeed = 2.0,
    jumpForce = 10.0,
    health = 100
}

-- Player state
local player = {
    entity = nil,
    transform = nil,
    controller = nil,
    health = PlayerConfig.health
}

-- Initialize player
function InitializePlayer()
    -- Create player entity
    player.entity = World:CreateEntity()
    
    -- Add components
    player.transform = World:AddTransform(player.entity)
    player.transform.position = math.vec3(0, 10, 0)
    
    player.controller = World:AddCharacterController(player.entity)
    player.controller.movementSpeed = PlayerConfig.movementSpeed
    player.controller.rotationSpeed = PlayerConfig.rotationSpeed
    player.controller.jumpForce = PlayerConfig.jumpForce
    
    -- Add mesh renderer
    local meshRenderer = World:AddMeshRenderer(player.entity)
    meshRenderer.mesh = CreateCubeMesh(1.0, true)
    
    -- Add camera
    local camera = World:AddCamera(player.entity)
    camera.fov = 60.0
    camera.isActive = true
    
    print("Player initialized!")
end

-- Update player
function UpdatePlayer(deltaTime)
    if not player.entity then return end
    
    -- Movement input
    local moveDir = math.vec3(0, 0, 0)
    
    if Input:IsKeyPressed(Key.W) then
        moveDir.z = moveDir.z + 1
    end
    
    if Input:IsKeyPressed(Key.S) then
        moveDir.z = moveDir.z - 1
    end
    
    if Input:IsKeyPressed(Key.A) then
        moveDir.x = moveDir.x - 1
    end
    
    if Input:IsKeyPressed(Key.D) then
        moveDir.x = moveDir.x + 1
    end
    
    -- Normalize movement direction
    if moveDir.x ~= 0 or moveDir.z ~= 0 then
        -- Apply movement
        player.controller:Move(moveDir * deltaTime * player.controller.movementSpeed)
    end
    
    -- Jump input
    if Input:IsKeyDown(Key.Space) and player.controller.isGrounded then
        player.controller:Jump()
    end
    
    -- Mouse look
    local mouseDelta = Input:GetMouseDelta()
    player.transform.rotation = player.transform.rotation * 
        math.quat(math.vec3(0, mouseDelta.x * player.controller.rotationSpeed * deltaTime, 0))
end

-- Main game loop hooks
function Initialize()
    InitializePlayer()
end

function Update(deltaTime)
    UpdatePlayer(deltaTime)
end
```

## Best Practices

### 1. Performance

```lua
-- Cache frequently accessed components
local transform = World:GetTransform(entity)  -- Once
-- Use transform multiple times

-- Avoid creating new objects in Update()
-- Bad:
function Update(deltaTime)
    local pos = math.vec3(0, 0, 0)  -- Created every frame!
end

-- Good:
local pos = math.vec3(0, 0, 0)  -- Created once
function Update(deltaTime)
    pos.x = 0
    pos.y = 0
    pos.z = 0
end
```

### 2. Error Handling

```lua
-- Use pcall for safe execution
local success, error = pcall(function()
    -- Code that might fail
    DoSomething()
end)

if not success then
    print("Error:", error)
end
```

### 3. Module Organization

```lua
-- Player.lua
local Player = {}

function Player:new()
    local obj = {}
    setmetatable(obj, self)
    self.__index = self
    return obj
end

function Player:Initialize()
    -- Initialize player
end

function Player:Update(deltaTime)
    -- Update player
end

return Player

-- Usage in main script:
local Player = require("Player")
local player = Player:new()
```

### 4. Configuration Files

```lua
-- Config.lua
return {
    player = {
        movementSpeed = 5.0,
        jumpForce = 10.0
    },
    world = {
        size = 10000,
        gridResolution = 100
    }
}

-- Load config:
local config = dofile("Game/Scripts/Config.lua")
print(config.player.movementSpeed)
```

## Debugging

### Print Debugging

```lua
-- Simple print
print("Value:", variable)

-- Formatted print
print(string.format("Position: (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z))
```

### Inspect Tables

```lua
function PrintTable(tbl, indent)
    indent = indent or 0
    for k, v in pairs(tbl) do
        print(string.rep("  ", indent) .. tostring(k) .. ": " .. tostring(v))
        if type(v) == "table" then
            PrintTable(v, indent + 1)
        end
    end
end
```

### Assert for Validation

```lua
assert(entity ~= nil, "Entity is nil!")
assert(transform ~= nil, "Transform component not found!")
```

## Next Steps

- See **TUTORIAL.md** for step-by-step game creation
- See **API_REFERENCE.md** for C++ API documentation
- See **IMPLEMENTATION_GUIDE.md** for engine internals
- Check `Game/Scripts/Examples/` for more script examples
