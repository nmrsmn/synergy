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
includes["glad"] = "Synergy/libs/glad/include"
includes["glm"] = "Synergy/libs/glm"
includes["stb"] = "Synergy/libs/stb"

libraries = {}
libraries["gflw"] = "build/bin/" .. outputdir .. "/GLFW"
libraries["glad"] = "build/bin/" .. outputdir .. "/glad"

group "Dependencies"

	include "Synergy/libs/premake/GLFW"
	include "Synergy/libs/premake/glad"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/libs/glm/glm/**.hpp",
		"%{prj.name}/libs/glm/glm/**.inl",
		"%{prj.name}/libs/stb/**.cpp",
		"%{prj.name}/libs/stb/**.h"
	}

	includedirs
	{
		"%{prj.name}/src/"
	}

    sysincludedirs
    {
    	"%{includes.spdlog}",
    	"%{includes.glfw}",
    	"%{includes.glad}",
    	"%{includes.glm}",
    	"%{includes.stb}"
    }

	defines
	{
		"SYNERGY_STATIC_LIBRARY"
	}

	links
	{
		"GLFW",
		"glad"
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
            "Synergy/src/",
            "Synergy/libs/"
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