workspace "Synergy"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Sandbox"

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

includes = {}
includes["spdlog"] = "Synergy/libs/spdlog/include"
includes["glfw"] = "Synergy/libs/GLFW/include"

libraries = {}
libraries["gflw"] = "build/bin/" .. outputdir .. "/GLFW"

group "Dependencies"

	include "Synergy/libs/premake/GLFW"

group ""

project "Synergy"
	location "Synergy"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src/"
	}

    sysincludedirs
    {
    	"%{includes.spdlog}",
    	"%{includes.glfw}"
    }

    libdirs
    {
    	"%{libraries.glfw}"
    }

	defines
	{
		"SYNERGY_STATIC_LIBRARY"
	}

	links
	{
		"GLFW"
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

group "Examples"

	project "Sandbox"
		location "Sandbox"
        kind "ConsoleApp"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("build/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("build/obj/" .. outputdir .. "/%{prj.name}")

        files
        {
            "%{prj.name}/src/**.h", 
            "%{prj.name}/src/**.cpp"
        }

        includedirs
        {
            "Synergy/src/"
        }

        sysincludedirs
        {
        	"%{includes.spdlog}",
    		"%{includes.glfw}"
        }

        links
        {
            "Synergy",
            "GLFW"
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