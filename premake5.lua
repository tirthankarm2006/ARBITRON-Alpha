workspace "ARBITRONIC"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

include "Engine/3rdPartyLibs/GLFW"
include "Engine/3rdPartyLibs/glad_OpenGL"
include "Engine/3rdPartyLibs/spdlog"
include "Engine/3rdPartyLibs/imgui"
include "Engine/3rdPartyLibs/stb"

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
       "$(SolutionDir)/src/",
       "$(SolutionDir)/Engine/src/Core",
       "$(SolutionDir)/Engine/src/Editor",
       "$(SolutionDir)/Engine/3rdPartyLibs",
       "$(SolutionDir)/Engine/3rdPartyLibs/GLFW/include",
       "$(SolutionDir)/Engine/3rdPartyLibs/glad_OpenGL/include",
       "$(SolutionDir)/Engine/3rdPartyLibs/spdlog/include",
       "$(SolutionDir)Engine/3rdPartyLibs/imgui/src/main/",
       "$(SolutionDir)Engine/3rdPartyLibs/imgui/src/backend",
       "$(SolutionDir)Engine/3rdPartyLibs/Glm",
       "$(SolutionDir)Engine/data/Shaders",
       "$(SolutionDir)Engine/data",
       "$(SolutionDir)Engine/3rdPartyLibs/Assimp/include",
       "$(SolutionDir)Engine/3rdPartyLibs/Assimp/build/include",
       "$(SolutionDir)Engine/3rdPartyLibs/Assimp/build/include/assimp"
    }
    
    libdirs{
        "$(SolutionDir)Engine/3rdPartyLibs/Assimp/build/lib/Debug"
    }

    pchheader "ARBpch.h"
    pchsource "Engine/src/Core/ARBpch.cpp"

    links
    {
        "GLFW", --linking the project with name "GLFW",
        "GLAD",
        "opengl32.lib",
        "spdlog",
        "imgui",
        "assimp-vc142-mtd.lib",
        "STB"
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
        defines "AB_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "AB_RELEASE"
        optimize "On"