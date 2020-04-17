require("mingw64")

workspace "WS_cstarter"
    configurations { "Debug", "Release" }
    platforms { "l64", "w64"}
    filter { "platforms:l64" }
        system "linux"
        architecture "x64"

    filter { "platforms:w64" }
        system "windows"
        architecture "x64"
        toolset ("mingw64")
        --entrypoint "WinMainCRTStartup"

project "cstarter"
    location "build/cstarter/"
    --kind "ConsoleApp"
    kind "WindowedApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"
    --links { "allegro", "allegro_ttf", "allegro_font", "allegro_color", "allegro_primitives" }

    files { "./src/**.h", "./src/**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        --warnings "Extra"
        enablewarnings { "all" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
