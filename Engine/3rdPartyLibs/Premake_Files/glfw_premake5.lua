project "GLFW"
   kind "StaticLib"
   language "C"

   targetdir ("binaries/%{prj.name}")
   objdir ("objs-int/%{prj.name}")

   files
   {
      "include/GLFW/glfw3.h",
	  "include/GLFW/glfw3native.h",
	  "src/glfw_config.h",
      "src/context.c",
	  "src/init.c",
	  "src/input.c",
	  "src/monitor.c",
	  "src/win32_module",
	  "src/platform.c",
	  "src/vulkan.c",
	  "src/window.c",
      "src/null_*.*",
      -- Win32 backend
      "src/win32_*.*",
	  "src/wgl_context.c",
	  "src/egl_context.c",
	  "src/osmesa_context.c"
   }

	filter "system:windows"
	    buildoptions{"-std=c11", "-lgdi32"}
		systemversion "latest"
		staticruntime "On"

		defines 
		{ 
			"_GLFW_WIN32",            --pre-defined macro
			"_CRT_SECURE_NO_WARNINGS" --pre-defined macro to remove all warnings
		}

   filter "configurations:Debug"
        runtime "Debug"
        symbols "On" 

   filter "configurations:Release"
        runtime "Release"
        optimize "On" 
