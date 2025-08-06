project "STB"
   kind "StaticLib"
   language "C++"

   targetdir ("binaries/%{prj.name}")
   objdir ("objs-int/%{prj.name}")

   files
   {
      "stb_image.cpp",
	  "stb_image.h"
   }

	filter "system:windows"
	    cppdialect "C++17"
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_CRT_SECURE_NO_WARNINGS" --pre-defined macro to remove all warnings
		}

   filter "configurations:Debug"
        runtime "Debug"
        symbols "On" 

   filter "configurations:Release"
        runtime "Release"
        optimize "On" 
