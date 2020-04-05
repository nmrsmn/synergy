workspace "Synergy"
	architecture "x64"
	configurations { "Debug", "Release" }
	startproject "Sandbox"

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

dependencies = {}
dependencies["spdlog"] = "Synergy/libs/spdlog/include"

group "Dependencies"

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
    	"%{dependencies.spdlog}"
    }

	defines
	{
		"SYNERGY_STATIC_LIBRARY"
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
        	"%{dependencies.spdlog}"
        }

        links
        {
            "Synergy"
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