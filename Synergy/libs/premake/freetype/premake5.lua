project "freetype"
    location "../../freetype"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

    defines {
        "_LIB",
        "FT2_BUILD_LIBRARY"
    }

    sysincludedirs {
        "%{prj.location}/include"
    }

    files
    {
        "%{prj.location}/src/**.c",
        "%{prj.location}/src/**.h",
        "%{prj.location}/include/**.h"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
