workspace "ProceduralTerrainGeneration"
	architecture "x64"
	startproject "ProceduralTerrainGeneration"
	configurations {"Debug", "Release"}

	outputdir = "%{cfg.architecture}/%{cfg.buildcfg}"

	include "Dependencies/glfw"
	include "Dependencies/glad"


project "ProceduralTerrainGeneration"
	location "ProceduralTerrainGeneration"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"ProceduralTerrainGeneration/src/**.cpp",
		"ProceduralTerrainGeneration/src/**.h",
	}

	includedirs
	{
		"Dependencies/glfw/include",
		"Dependencies/glad/include",
		"Dependencies/glm",
	}

	links
	{
		"glfw",
		"glad",
		"opengl32.lib",
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"