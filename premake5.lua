--2025 Liam Rousselle
--2025 TomTek

local k_StandardBuildDirectory = "Binaries/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"
local k_StandardIntermediateDirectory = "Intermediate/%{cfg.buildcfg}/%{cfg.system}/%{cfg.architecture}/"

--Returns local path of where project builds should go via appName
local function GetBuildDirectory( appName )
    return ( k_StandardBuildDirectory .. appName )
end
--Returns local path of where project intermediate files should go via appName
local function GetIntermediateDirectory( appName )
    return ( k_StandardIntermediateDirectory .. appName )
end

--===============================================================--
-- TomTek-Game-Engine
-- Solution
--===============================================================--
workspace "TomTek-Game-Engine"
    architecture "x64"
    startproject "TomTek-Runtime"

    configurations
    {
        "Debug",
        "Release",
    }

    filter "platforms:x64"
        architecture "x64"
    
    filter "platforms:AnyCPU"
        architecture "x86_64"
    
    filter {}

group "Executables"
project "TomTek-Runtime"
    location "Executables/TomTekRuntime"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    targetdir ( GetBuildDirectory("%{prj.name}") )
    objdir ( GetIntermediateDirectory("%{prj.name}") )

    files
    {
        "%{prj.location}/Source/**.cpp",
        "%{prj.location}/Source/**.hpp",
        "%{prj.location}/Source/**.h",
    }

    includedirs
    {
        "%{prj.location}/Source",
        "%{wks.location}/Systems/TomTekEngine/Source",
    }

    links
    {
        "TomTek-Engine",
    }

    filter "platforms:AnyCPU"
        flags { "ExcludeFromBuild" }
    
    filter {}

group "Systems"
project "TomTek-Engine"
    location "Systems/TomTekEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"

    targetdir ( GetBuildDirectory("%{prj.name}") )
    objdir ( GetIntermediateDirectory("%{prj.name}") )

    files
    {
        "%{prj.location}/Source/**.cpp",
        "%{prj.location}/Source/**.hpp",
        "%{prj.location}/Source/**.h",
    }

    includedirs
    {
        "%{prj.location}/Source",
        "$(VULKAN_SDK)/Include",
    }

    libdirs
    {
        "$(VULKAN_SDK)/Lib",
    }

    links
    {
        "vulkan-1",
    }

    filter "platforms:AnyCPU"
        flags { "ExcludeFromBuild" }
    
    filter {}