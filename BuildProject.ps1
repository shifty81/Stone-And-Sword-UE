# BuildProject.ps1 - Build script for StoneAndSword Unreal Engine project
# This script automates the build process for the StoneAndSword game module
# Usage: .\BuildProject.ps1 [-Configuration Development|Debug|Shipping] [-Clean] [-UEPath "path"]

param(
    [ValidateSet("Development", "Debug", "Shipping", "DebugGame")]
    [string]$Configuration = "Development",
    
    [switch]$Clean,
    
    [string]$UEPath = "",
    
    [switch]$Help
)

# Display help information
if ($Help) {
    Write-Host @"
BuildProject.ps1 - Build script for StoneAndSword

USAGE:
    .\BuildProject.ps1 [OPTIONS]

OPTIONS:
    -Configuration <config>   Build configuration (Development, Debug, Shipping, DebugGame)
                             Default: Development
    
    -Clean                   Clean intermediate files before building
    
    -UEPath <path>           Path to Unreal Engine installation
                             Default: Auto-detect from registry or common paths
    
    -Help                    Show this help message

EXAMPLES:
    # Build with default settings (Development)
    .\BuildProject.ps1
    
    # Clean build in Debug configuration
    .\BuildProject.ps1 -Configuration Debug -Clean
    
    # Build with custom UE path
    .\BuildProject.ps1 -UEPath "D:\Epic Games\UE_5.6"
    
    # Build for shipping (optimized for distribution)
    .\BuildProject.ps1 -Configuration Shipping

"@
    exit 0
}

# Color functions
function Write-Success { param([string]$Message) Write-Host $Message -ForegroundColor Green }
function Write-Error-Message { param([string]$Message) Write-Host $Message -ForegroundColor Red }
function Write-Warning { param([string]$Message) Write-Host $Message -ForegroundColor Yellow }
function Write-Info { param([string]$Message) Write-Host $Message -ForegroundColor Cyan }
function Write-Step { param([string]$Message) Write-Host "`n==> $Message" -ForegroundColor Magenta }

# Script start
Write-Host "`n╔══════════════════════════════════════════════════════════╗" -ForegroundColor Cyan
Write-Host "║         StoneAndSword Build Script v1.0                 ║" -ForegroundColor Cyan
Write-Host "╚══════════════════════════════════════════════════════════╝`n" -ForegroundColor Cyan

# Get project path and validate
$ProjectPath = Get-Location
$ProjectFile = Join-Path $ProjectPath "StoneAndSword.uproject"

Write-Info "Project Path: $ProjectPath"
Write-Info "Configuration: $Configuration"

if (-not (Test-Path $ProjectFile)) {
    Write-Error-Message "`n❌ Error: StoneAndSword.uproject not found in current directory!"
    Write-Warning "Please run this script from the project root directory.`n"
    exit 1
}

Write-Success "✓ Project file found"

# Auto-detect Unreal Engine installation
function Find-UnrealEngine {
    if ($UEPath -and (Test-Path $UEPath)) {
        return $UEPath
    }
    
    Write-Info "Searching for Unreal Engine 5.6 installation..."
    
    # Common installation paths
    $CommonPaths = @(
        "C:\Program Files\Epic Games\UE_5.6",
        "C:\Program Files\Epic Games\UE_5.6.1",
        "D:\Epic Games\UE_5.6",
        "D:\Program Files\Epic Games\UE_5.6",
        "C:\Program Files (x86)\Epic Games\UE_5.6"
    )
    
    foreach ($Path in $CommonPaths) {
        if (Test-Path $Path) {
            Write-Success "✓ Found Unreal Engine at: $Path"
            return $Path
        }
    }
    
    # Try to find from registry (Epic Games Launcher)
    try {
        $RegPath = "HKLM:\SOFTWARE\EpicGames\Unreal Engine"
        if (Test-Path $RegPath) {
            $Versions = Get-ChildItem $RegPath
            foreach ($Version in $Versions) {
                $InstallPath = (Get-ItemProperty $Version.PSPath).InstalledDirectory
                if ($InstallPath -and (Test-Path $InstallPath)) {
                    Write-Success "✓ Found Unreal Engine at: $InstallPath"
                    return $InstallPath
                }
            }
        }
    } catch {
        # Registry lookup failed, continue with manual detection
    }
    
    Write-Error-Message "`n❌ Error: Could not find Unreal Engine 5.6 installation!"
    Write-Warning @"

Please specify the path manually using -UEPath parameter:
    .\BuildProject.ps1 -UEPath "C:\Your\Path\To\UE_5.6"

Or install Unreal Engine 5.6 from Epic Games Launcher.
"@
    exit 1
}

$UEPath = Find-UnrealEngine

# Validate UE installation
$UBT = Join-Path $UEPath "Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe"
$GenProjectBat = Join-Path $UEPath "Engine\Build\BatchFiles\GenerateProjectFiles.bat"

if (-not (Test-Path $UBT)) {
    Write-Error-Message "`n❌ Error: UnrealBuildTool.exe not found at expected location!"
    Write-Warning "Expected: $UBT"
    Write-Warning "Your Unreal Engine installation may be incomplete.`n"
    exit 1
}

Write-Success "✓ UnrealBuildTool found"

# Clean intermediate files if requested
if ($Clean) {
    Write-Step "Cleaning intermediate files"
    
    $DirsToClean = @("Binaries", "Intermediate", "Saved", ".vs", "DerivedDataCache")
    
    foreach ($Dir in $DirsToClean) {
        $DirPath = Join-Path $ProjectPath $Dir
        if (Test-Path $DirPath) {
            Write-Info "Removing: $Dir"
            try {
                Remove-Item -Recurse -Force $DirPath -ErrorAction Stop
                Write-Success "  ✓ Cleaned $Dir"
            } catch {
                Write-Warning "  ⚠ Could not remove $Dir (may be in use)"
            }
        }
    }
    
    # Also clean .sln and related files
    $FilesToClean = @("*.sln", "*.suo", "*.VC.db", "*.VC.opendb")
    foreach ($Pattern in $FilesToClean) {
        $Files = Get-ChildItem -Path $ProjectPath -Filter $Pattern -ErrorAction SilentlyContinue
        foreach ($File in $Files) {
            Write-Info "Removing: $($File.Name)"
            Remove-Item $File.FullName -Force -ErrorAction SilentlyContinue
        }
    }
    
    Write-Success "`n✓ Clean complete"
}

# Generate Visual Studio project files
Write-Step "Generating Visual Studio project files"

try {
    $GenArgs = "-project=`"$ProjectFile`"", "-game", "-engine"
    $Process = Start-Process -FilePath $GenProjectBat -ArgumentList $GenArgs -NoNewWindow -Wait -PassThru
    
    if ($Process.ExitCode -eq 0) {
        Write-Success "✓ Project files generated successfully"
    } else {
        Write-Error-Message "❌ Failed to generate project files (Exit code: $($Process.ExitCode))"
        exit 1
    }
} catch {
    Write-Error-Message "❌ Error during project file generation: $_"
    exit 1
}

# Build the project
Write-Step "Building StoneAndSword ($Configuration)"

Write-Info @"
This may take several minutes on first build...
  - Core modules will compile first
  - StoneAndSword module will compile last
  - Progress will be shown below
"@

try {
    $BuildArgs = @(
        "StoneAndSwordEditor",
        "Win64",
        $Configuration,
        "-Project=`"$ProjectFile`"",
        "-WaitMutex",
        "-Verbose"
    )
    
    Write-Info "Command: UnrealBuildTool.exe $($BuildArgs -join ' ')"
    
    $Process = Start-Process -FilePath $UBT -ArgumentList $BuildArgs -NoNewWindow -Wait -PassThru
    
    if ($Process.ExitCode -eq 0) {
        Write-Success "`n✓ Build succeeded!"
    } else {
        Write-Error-Message "`n❌ Build failed with exit code: $($Process.ExitCode)"
        Write-Warning @"

Common solutions:
  1. Check the output above for specific error messages
  2. Try a clean build: .\BuildProject.ps1 -Clean
  3. Verify Visual Studio 2022 is installed with C++ tools
  4. See TROUBLESHOOTING_BUILD.md for detailed help
"@
        exit 1
    }
} catch {
    Write-Error-Message "`n❌ Error during build: $_"
    exit 1
}

# Verify build output
Write-Step "Verifying build output"

$OutputDLL = Join-Path $ProjectPath "Binaries\Win64\UnrealEditor-StoneAndSword.dll"

if (Test-Path $OutputDLL) {
    $FileInfo = Get-Item $OutputDLL
    $FileSizeMB = [math]::Round($FileInfo.Length / 1MB, 2)
    
    if ($FileInfo.Length -gt 0) {
        Write-Success "✓ Output DLL exists: UnrealEditor-StoneAndSword.dll ($FileSizeMB MB)"
        Write-Success "✓ Build verification passed"
    } else {
        Write-Warning "⚠ Warning: Output DLL exists but has 0 size"
        Write-Warning "  The build may have failed. Check the output above for errors."
    }
} else {
    Write-Warning "⚠ Warning: Could not find output DLL"
    Write-Warning "  Expected: $OutputDLL"
    Write-Warning "  The build may have failed."
}

# Success summary
Write-Host "`n╔══════════════════════════════════════════════════════════╗" -ForegroundColor Green
Write-Host "║                 BUILD COMPLETE                           ║" -ForegroundColor Green
Write-Host "╚══════════════════════════════════════════════════════════╝" -ForegroundColor Green

Write-Info @"

Next steps:
  1. Open StoneAndSword.uproject in Unreal Editor
  2. The project should now open without errors
  3. See QUICK_START.md to create your first playable scene

If you encounter issues, see TROUBLESHOOTING_BUILD.md for help.
"@
