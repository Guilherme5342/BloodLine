--Configurar de acordo com seu ambiente
outputdir = "build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

workspace "projeto_idj"
    architecture "x32"
    toolset "gcc"
    language "C++"
    cppdialect "C++17"
    configurations { "debug", "release" }

project "pinguim"
    location "pinguim"
    kind "ConsoleApp"

    targetdir (outputdir)

    objdir (outputdir .. "/obj")

    targetname "%{prj.name}_%{cfg.buildcfg}"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cc",
        "%{prj.name}/src/**.c++"
    }

    includedirs {
        "%{prj.name}/src",
        "C:/SDL32/include"
    }

    libdirs {
        "C:/SDL32/lib",
        "C:/SDL32/lib/%{cfg.architecture}"
    }

--[[    nuget {
        "sdl2.nuget:2.28.3",
        "sdl2.nuget.redist:2.28.3",
        "sdl2_image.nuget:2.6.3",
        "sdl2_image.nuget.redist:2.6.3",
        "sdl2_mixer.nuget:2.6.3",
        "sdl2_mixer.nuget.redist:2.6.3",
        "sdl2_ttf.nuget:2.20.2",
        "sdl2_ttf.nuget.redist:2.20.2"
    }]]--

    links
    {
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "SDL2_mixer",
        "SDL2_ttf"
    }

    postbuildcommands{
        "{COPYFILE} C:/SDL32/bin/** %{cfg.targetdir}",
        "{COPYDIR} %{prj.location}/res %{cfg.targetdir}/res",
    }

    -- Filtro para configurações específicas do sistema linux (não é necessário para Windows).
    filter "system:linux"
        pic "On"

    filter "system:windows"

    -- Filtro para configurações no modo debug.
    filter "configurations:debug"
        buildoptions { "-Wall", "-O0" }
        defines { "DEBUG" } -- Definições de flags para uso no modo debug 'equivalente a usar -D'.
        symbols "On" -- 'equivalente a usar -g'
        runtime "Debug"

    -- Filtro para configurações no modo release.
    filter "configurations:release"
        symbols "Off" -- Retira -g
        optimize "On"  -- 'equivalente a usar -O2'
        runtime "Release"