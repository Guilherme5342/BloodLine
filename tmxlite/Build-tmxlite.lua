project "tmxlite"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    files {
        "./**.h",
        "./**.cpp",
        "./**.hpp",
        "./**.cc",
        "./**.c++"
    }

    includedirs{
        "include"
    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}/" .._ACTION)
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG", "D_DEBUG_", "DTMXLITE_STATIC"}
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