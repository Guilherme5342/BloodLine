project (AppName)
    kind "ConsoleApp"
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
        "src",

        -- Include Core
        "../tmxlite/include",
        "../" ..CoreName.. "/include",
        SDLIncludePath
    }


    links {
        CoreName,
        "tmxlite",
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf",
    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    --postbuildcommands{
    --    "{COPYDIR} %{prj.location}/res %{cfg.targetdir}/res",
    --}

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }
        libdirs {
            WindowsSDLPath.. "/lib",
            WindowsSDLPath.."/lib/%{cfg.architecture}"
        }
        --postbuildcommands{
        --    "{COPYFILE} " ..WindowsSDLPath.. "/bin/** %{cfg.targetdir}",
        --    "{COPYDIR} %{prj.location}/res %{cfg.targetdir}/res",
        --}
    filter "configurations:Debug"
        defines { "DEBUG", "D_DEBUG_", "DTMXLITE_STATIC" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE", "NDEBUG", "DNDEBUG", "DTMXLITE_STATIC" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST", "TMXLITE_STATIC_LIB", "DNDEBUG", "DTMXLITE_STATIC" }
        runtime "Release"
        optimize "On"
        symbols "Off"