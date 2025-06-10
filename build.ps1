function Show-BuildHelp {
    Write-ColoredMessage "`nC++ Project Build Helper" "Cyan"
    Write-ColoredMessage "======================" "Cyan"
    Write-ColoredMessage "`nDescription:" "White"
    Write-ColoredMessage "This script helps you build and run C++ CMake projects with debugging support." "Gray"

    Write-ColoredMessage "`nAvailable Commands:" "White"
    Write-ColoredMessage "1. Build-And-Run              - Build and run the project (interactive mode)" "Yellow"
    Write-ColoredMessage "2. Build-And-Run -Clean       - Clean build directory before building" "Yellow"
    Write-ColoredMessage "3. Build-And-Run -Config X    - Build with specific configuration (Debug/Release)" "Yellow"
    Write-ColoredMessage "4. Build-And-Run -BuildDir X  - Use custom build directory" "Yellow"
    Write-ColoredMessage "5. Build-And-Run -Debug       - Run with Visual Studio debugger" "Yellow"
    Write-ColoredMessage "6. Show-BuildHelp             - Display this help message" "Yellow"

    Write-ColoredMessage "`nDebug Options:" "White"
    Write-ColoredMessage "1. -Debug                    - Launch Visual Studio debugger" "Gray"
    Write-ColoredMessage "2. -DebugBreak <line>        - Set breakpoint at specific line" "Gray"
    Write-ColoredMessage "3. -DebugFile <file>         - Specify file to debug" "Gray"
}

function Write-ColoredMessage {
    param (
        [string]$Message,
        [string]$Color = "White"
    )
    Write-Host $Message -ForegroundColor $Color
}

function Clean-BuildDirectory {
    param (
        [string]$BuildDir = "build"
    )
    if (Test-Path $BuildDir) {
        Write-ColoredMessage "Cleaning build directory..." "Yellow"
        Remove-Item -Path $BuildDir -Recurse -Force
    }
    New-Item -ItemType Directory -Path $BuildDir | Out-Null
    Write-ColoredMessage "Build directory cleaned and recreated." "Green"
}

function Start-VSDebugger {
    param (
        [string]$ExePath,
        [string]$SourceFile = "",
        [int]$BreakLine = 0
    )

    $vsPath = "${env:ProgramFiles}\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
    if (-not (Test-Path $vsPath)) {
        $vsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
    }

    if (Test-Path $vsPath) {
        Write-ColoredMessage "Launching Visual Studio debugger..." "Cyan"
        if ($SourceFile -and $BreakLine -gt 0) {
            & $vsPath /debugexe $ExePath /command "Debug.BreakAt $SourceFile $BreakLine"
        } else {
            & $vsPath /debugexe $ExePath
        }
    } else {
        Write-ColoredMessage "Visual Studio not found. Please install Visual Studio with C++ support." "Red"
    }
}

function Build-And-Run {
    param (
        [string]$BuildDir = "build",
        [switch]$Clean,
        [string]$Config,
        [switch]$Help,
        [switch]$Debug,
        [string]$DebugFile = "",
        [int]$DebugBreak = 0
    )

    if ($Help) {
        Show-BuildHelp
        return
    }

    Write-ColoredMessage "`nC++ Project Builder" "Cyan"
    Write-ColoredMessage "=================" "Cyan"

    # Force Debug configuration if debugging is requested
    if ($Debug -and $Config -ne "Debug") {
        Write-ColoredMessage "Debug mode requested. Switching to Debug configuration." "Yellow"
        $Config = "Debug"
    }

    # If config not provided, ask user
    if (-not $Config) {
        Write-ColoredMessage "`nBuild Configuration" "Cyan"
        Write-ColoredMessage "1. Debug   - Include debug symbols and no optimization" "White"
        Write-ColoredMessage "2. Release - Optimized build for best performance" "White"
        $choice = Read-Host "`nChoose configuration (1/2)"

        $Config = switch($choice) {
            "1" { "Debug" }
            "2" { "Release" }
            default {
                Write-ColoredMessage "Invalid choice. Using Release configuration." "Yellow"
                "Release"
            }
        }
    }

    Write-ColoredMessage "`nBuild Settings:" "White"
    Write-ColoredMessage "- Configuration: $Config" "Gray"
    Write-ColoredMessage "- Build Directory: $BuildDir" "Gray"
    Write-ColoredMessage "- Clean Build: $Clean" "Gray"
    Write-ColoredMessage "- Debug Mode: $Debug" "Gray"
    if ($Debug -and $DebugFile) {
        Write-ColoredMessage "- Debug File: $DebugFile" "Gray"
        Write-ColoredMessage "- Break Line: $DebugBreak" "Gray"
    }

    # Clean if requested
    if ($Clean) {
        Clean-BuildDirectory $BuildDir
    }
    elseif (-not (Test-Path $BuildDir)) {
        Write-ColoredMessage "`nCreating build directory..." "Yellow"
        New-Item -ItemType Directory -Path $BuildDir | Out-Null
    }

    Push-Location $BuildDir

    try {
        # Configure project with debug symbols if debugging
        Write-ColoredMessage "`nConfiguring CMake project..." "Cyan"
        $cmakeArgs = "-DCMAKE_BUILD_TYPE=$Config"
        if ($Debug) {
            $cmakeArgs += " -DCMAKE_CXX_FLAGS_DEBUG='/Zi /Od /DEBUG'"
        }
        Write-ColoredMessage "Running: cmake .. $cmakeArgs" "Gray"
        cmake .. $cmakeArgs
        if ($LASTEXITCODE -ne 0) {
            throw "CMake configuration failed."
        }

        # Build project
        Write-ColoredMessage "`nBuilding project..." "Cyan"
        Write-ColoredMessage "Running: cmake --build . --config $Config" "Gray"
        cmake --build . --config $Config
        if ($LASTEXITCODE -ne 0) {
            throw "Build failed."
        }

        # Find executable
        Write-ColoredMessage "`nLocating executable..." "Cyan"
        $exe = Get-ChildItem -Recurse -Filter "*.exe" | Where-Object { $_.FullName -match $Config }

        if ($exe) {
            Write-ColoredMessage "`nExecutable found: $($exe.Name)" "Green"

            if ($Debug) {
                Start-VSDebugger -ExePath $exe.FullName -SourceFile $DebugFile -BreakLine $DebugBreak
            } else {
                Write-ColoredMessage "`nProgram Output" "Cyan"
                Write-ColoredMessage "=============" "Cyan"
                & $exe.FullName
                Write-ColoredMessage "=============" "Cyan"
                Write-ColoredMessage "Program execution completed successfully." "Green"
            }
        } else {
            throw "Executable not found in $BuildDir"
        }
    }
    catch {
        Write-ColoredMessage "`nError: $_" "Red"
        Write-ColoredMessage "Build failed. Use 'Build-And-Run -Help' for usage information." "Yellow"
    }
    finally {
        Pop-Location
    }
}

# Show help message when script is loaded
Write-ColoredMessage "`nC++ Build Script loaded successfully!" "Green"
Write-ColoredMessage "Use 'Build-And-Run -Help' to see available commands." "Yellow"
Write-ColoredMessage "Examples:" "White"
Write-ColoredMessage "  Build-And-Run -Clean -Config Release" "Gray"
Write-ColoredMessage "  Build-And-Run -Debug -DebugFile main.cpp -DebugBreak 10`n" "Gray"
