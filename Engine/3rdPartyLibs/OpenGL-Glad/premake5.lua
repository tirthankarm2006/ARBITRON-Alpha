project "GLAD"
   kind "StaticLib"
   language "C"

   targetdir ("binaries/%{prj.name}")
   objdir ("objs-int/%{prj.name}")

   files{
      "include/glad/glad.h",
	  "include/KHR/khrplatform.h",
	  "src/glad.c"
   }

   includedirs{
      "include"
   }

	filter "system:windows"
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
