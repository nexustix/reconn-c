require("mingw64")

workspace "WS_reconn"
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

project "libreconn"
  location "build/libreconn/"
  kind "SharedLib"
  language "C"

  targetdir "lib/reconn"

  files { "./src/_reconn/**.h", "./src/_reconn/**.c" }

project "reconn"
    location "build/reconn/"
    --kind "ConsoleApp"
    kind "WindowedApp"
    language "C"
    targetdir "bin/%{cfg.buildcfg}"

    libdirs { "./lib/libreconn"}
    includedirs { "./src/_reconn/" }
    --links { "allegro", "allegro_ttf", "allegro_font", "allegro_color", "allegro_primitives" }
    links { "reconn" }

    files { "./src/reconn/**.h", "./src/reconn/**.c" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
        --warnings "Extra"
        enablewarnings { "all" }
        disablewarnings { "parentheses" }

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
