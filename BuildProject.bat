@echo off
REM BuildProject.bat - Simple Windows batch wrapper for BuildProject.ps1
REM This script calls the PowerShell build script with proper execution policy

echo ========================================
echo StoneAndSword Build Script
echo ========================================
echo.

REM Check if PowerShell is available
where pwsh >nul 2>nul
if %ERRORLEVEL% EQU 0 (
    echo Using PowerShell Core...
    pwsh -ExecutionPolicy Bypass -File "%~dp0BuildProject.ps1" %*
) else (
    where powershell >nul 2>nul
    if %ERRORLEVEL% EQU 0 (
        echo Using Windows PowerShell...
        powershell -ExecutionPolicy Bypass -File "%~dp0BuildProject.ps1" %*
    ) else (
        echo ERROR: PowerShell not found!
        echo Please install PowerShell or PowerShell Core.
        echo.
        pause
        exit /b 1
    )
)

if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed! See errors above.
    echo For help, see TROUBLESHOOTING_BUILD.md
    echo.
    pause
    exit /b %ERRORLEVEL%
)

echo.
echo Build completed successfully!
echo You can now open StoneAndSword.uproject
echo.
pause
