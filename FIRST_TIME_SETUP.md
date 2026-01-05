# First Time Setup - What to Do When You See "Missing Modules" Prompt

## 📋 The Prompt You're Seeing

When you double-click `StoneAndSword.uproject`, you see:

```
The following modules are missing or built with a different engine version:
    StoneAndSword

Would you like to rebuild them now?
    [Yes]  [No]
```

## ✅ What to Do: Click **"Yes"**

**This is normal!** Click **"Yes"** to rebuild the modules.

### What Happens Next

1. **If build succeeds** (most common):
   - Wait 2-5 minutes for compilation
   - Unreal Editor will open automatically
   - ✅ You're done! Continue to [Next Steps](#next-steps)

2. **If build fails** (less common):
   - You'll see: "StoneAndSword could not be compiled. Try rebuilding from source manually."
   - ℹ️ Don't panic! See [If Build Fails](#if-build-fails) below

## ❓ Why Does This Happen?

This prompt appears because:
- This is a **C++ project** (not Blueprint-only)
- The compiled binaries (`Binaries/` folder) are **not included in the repository** (to keep it lightweight)
- Unreal Engine needs to **compile the C++ code** on your machine the first time you open it

**This is completely normal and expected behavior for C++ Unreal Engine projects!**

## 🔧 If Build Fails

If you see "StoneAndSword could not be compiled", try these solutions in order:

### Quick Fix #1: Use the Automated Build Script (Easiest)

1. Close Unreal Editor (if open)
2. In the project folder, double-click: **`BuildProject.bat`**
3. Wait for it to complete (2-5 minutes)
4. Double-click `StoneAndSword.uproject` again

### Quick Fix #2: Generate Visual Studio Project Files

1. Close Unreal Editor (if open)
2. **Right-click** on `StoneAndSword.uproject` (in Windows Explorer)
3. Select **"Generate Visual Studio project files"**
4. Wait for completion (30-60 seconds)
5. Open `StoneAndSword.sln` in Visual Studio
6. In Visual Studio:
   - Set configuration to **"Development Editor"**
   - Set platform to **"Win64"**
   - Build → Build Solution (or press Ctrl+Shift+B)
7. Wait for compilation (2-5 minutes)
8. Double-click `StoneAndSword.uproject` again

### Quick Fix #3: Check Prerequisites

Make sure you have:
- ✅ **Unreal Engine 5.6** (or 5.6.1) installed
- ✅ **Visual Studio 2022** (or 2019) with "Game Development with C++" workload
- ✅ At least **8GB RAM** (16GB recommended)
- ✅ At least **10GB free disk space**

**To install "Game Development with C++" workload:**
1. Open **Visual Studio Installer**
2. Click **"Modify"** on your VS installation
3. Check **"Game development with C++"**
4. Click **"Modify"** and wait for installation

### Still Not Working?

See the comprehensive troubleshooting guide: **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)**

It covers 20+ common scenarios and solutions.

## 🎮 Next Steps (After Successful Build)

Once Unreal Editor opens successfully, you need to create two simple assets to play the game:

### Option 1: Quick Start (10 minutes)
Follow **[QUICK_START.md](QUICK_START.md)** to manually create:
- A level with lighting and sky
- A basic terrain material

### Option 2: Automated Setup (5 minutes)
1. In Unreal Editor, open the Python console: **Tools → Execution Python Script**
2. Or run: `py Content/Python/setup_project_assets.py`

## 📚 Additional Resources

- **[README.md](README.md)** - Project overview and documentation index
- **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)** - Comprehensive build troubleshooting
- **[QUICK_START.md](QUICK_START.md)** - Get playing in 10 minutes
- **[PROJECT_STATUS.md](PROJECT_STATUS.md)** - What works and what doesn't

## 💡 Summary

1. ✅ **Click "Yes"** when you see the "missing modules" prompt
2. ✅ This is **normal behavior** for C++ projects
3. ✅ Wait 2-5 minutes for compilation
4. ✅ If it fails, use **`BuildProject.bat`** or see **[TROUBLESHOOTING_BUILD.md](TROUBLESHOOTING_BUILD.md)**
5. ✅ After successful build, follow **[QUICK_START.md](QUICK_START.md)** to create the level and material

---

**Still confused?** Open an issue on GitHub with:
- Windows version
- Visual Studio version  
- Unreal Engine version
- The exact error message you're seeing
