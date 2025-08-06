project "imgui"
   kind "StaticLib"
   language "C++"

   targetdir ("binaries/%{prj.name}")
   objdir ("objs-int/%{prj.name}")

   files{
      "src/main/**.h",
      "src/backend/imgui_impl_glfw.h",
      "src/backend/imgui_impl_opengl3.h",
      "src/backend/imgui_impl_opengl3_loader.h",
      "src/main/**.cpp",
      "src/backend/imgui_impl_glfw.cpp",
      "src/backend/imgui_impl_opengl3.cpp",
   }

   includedirs{
      "src/main",
      "src/backend",
      "$(SolutionDir)/Engine/3rdPartyLibs/GLFW/include"
   }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{
			"_CRT_SECURE_NO_WARNINGS" --pre-defined macro to remove all warnings
		}

      buildoptions
      {
         "/utf-8"
      }

   filter "configurations:Debug"
        runtime "Debug"
        symbols "On" 

   filter "configurations:Release"
        runtime "Release"
        optimize "On" 
