project "spdlog"
   kind "StaticLib"
   language "C++"

   targetdir ("binaries/%{prj.name}")
   objdir ("objs-int/%{prj.name}")

   files{
      "include/spdlog/**.h",
      "src/**.cpp"
   }

   includedirs{
      "include",
      "include/spdlog"
   }

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		defines 
		{
         "SPDLOG_COMPILED_LIB",
			"_CRT_SECURE_NO_WARNINGS" --pre-defined macro to remove all warnings
		}

      buildoptions
      {
         "/utf-8",
         "/MTd"
      }

   filter "configurations:Debug"
        runtime "Debug"
        symbols "On" 

   filter "configurations:Release"
        runtime "Release"
        optimize "On" 
