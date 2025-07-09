workspace "ARBITRARY"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

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
       "Engine/src/3rdPartyLibs"
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