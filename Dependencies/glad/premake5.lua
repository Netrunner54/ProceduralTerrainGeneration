project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"
    
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	   files
	   {
	       "src/glad.c",
	       "include/glad/glad.h",
	       "include/KHR/khrplatform.h"
	   }
	
	   includedirs{
	       "include"
	   }
	
	
	   filter "configurations:Debug"
	       runtime "Debug"
	       symbols "on"
	
	   filter "configurations:Release"
	       runtime "Release"
	       optimize "on"