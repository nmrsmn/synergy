project "Snake"
	location "./"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/src/**.h", 
        "%{prj.location}/src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Synergy/src/",
        "%{wks.location}/Synergy/libs/"
    }

    sysincludedirs
    {
    	"%{includes.spdlog}",
    	"%{includes.glfw}",
		"%{includes.glm}",
		"%{includes.stb}"
    }

    links
    {
        "Synergy"
    }

    postbuildcommands {
		"{COPY} assets/ %{cfg.targetdir}/assets/"
    }

    filter "configurations:Debug"
        defines "SYNERGY_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "SYNERGY_RELEASE"
        runtime "Release"
        optimize "on"

    filter "system:windows"
        systemversion "latest"

    filter "system:linux"
        systemversion "latest"

    filter "system:macosx"
        systemversion "latest"
    
        links
        {
            "CoreFoundation.framework",
            "Cocoa.framework",
            "OpenGL.framework",
            "IOKit.framework",
            "CoreVideo.framework"
        }