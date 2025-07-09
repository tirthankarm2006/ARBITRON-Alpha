workspace "ARBITRARY"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

include "Engine/3rdPartyLibs/GLFW"

project "ENGINE"
    location "Engine"
    kind "ConsoleApp"
    language "C++"

    targetdir ("Engine/binaries/Main")
    objdir    ("Engine/binaries/objs_int")

    files{
        "Engine/src/**.h",
        "Engine/src/**.cpp",
        "Engine/src/**.c"
    }

    includedirs{
       "Engine/src/",
       "Engine/src/Core",
       "Engine/src/Editor",
       "Engine/3rdPartyLibs",
       "Engine/3rdPartyLibs/GLFW/include"
    }

    pchheader "ABpch.h"
    pchsource "Engine/src/Core/ABpch.cpp"

    links
    {
        "GLFW", --linking the project with name "GLFW"
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        buildoptions
        {
            "/utf-8"
        }

    filter "configurations:Debug"
        defines "AS_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AS_RELEASE"
        optimize "On"