CoreName = "GalapagosEngine-Core"
AppName = "Bloodline"
OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
WindowsSDLPath = "C:/SDL32"
SDLIncludePath = "C:/SDL32/include"

workspace "Bloodline"
   architecture "x86"
   configurations { "Debug", "Release", "Dist" }
   startproject "Bloodline"

   filter "system:linux"
      pic "On"
   -- Workspace-wide build options for MSVC
   filter {"system:windows", "action:vs2022"}
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

   filter "configurations:Debug"
      buildoptions { "-Wall", "-O0" }
      defines { "DEBUG" } -- Definições de flags para uso no modo debug 'equivalente a usar -D'.
      symbols "On" -- 'equivalente a usar -g'
      runtime "Debug"
   
   filter "configurations:Release"
      symbols "Off" -- Retira -g
      optimize "On"  -- 'equivalente a usar -O2'
      defines { "NDEBUG" }
      runtime "Release"

group "Core"
	include (CoreName.. "/Build-" ..CoreName.. ".lua")
group ""

include (AppName.. "/Build-" ..AppName.. ".lua")