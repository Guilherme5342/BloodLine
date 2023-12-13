project (CoreName)
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files {
        "./**.h",
        "./**.cpp",
        "./**.hpp",
        "./**.cc",
        "./**.c++"
    }

    includedirs{
        "include",
        SDLIncludePath
    }

    links {
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf"
    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}/" .._ACTION)
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        libdirs {
            WindowsSDLPath.. "/lib",
            WindowsSDLPath.."/lib/%{cfg.architecture}"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE", "NDEBUG" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"