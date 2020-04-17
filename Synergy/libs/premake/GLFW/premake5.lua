project "GLFW"
    location "../../GLFW"
    kind "StaticLib"
    language "C"
    staticruntime "on"

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.location}/include/GLFW/glfw3.h",
        "%{prj.location}/include/GLFW/glfw3native.h",
        "%{prj.location}/src/glfw_config.h",
        "%{prj.location}/src/context.c",
        "%{prj.location}/src/init.c",
        "%{prj.location}/src/input.c",
        "%{prj.location}/src/monitor.c",
        "%{prj.location}/src/vulkan.c",
        "%{prj.location}/src/window.c"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

    filter "system:windows"
        systemversion "latest"
        
        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }
        
        files
        {
            "%{prj.location}/src/win32_init.c",
            "%{prj.location}/src/win32_joystick.c",
            "%{prj.location}/src/win32_monitor.c",
            "%{prj.location}/src/win32_time.c",
            "%{prj.location}/src/win32_thread.c",
            "%{prj.location}/src/win32_window.c",
            "%{prj.location}/src/wgl_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
        }

    filter "system:linux"
        pic "on"
        systemversion "latest"
        
        defines
        {
            "_GLFW_X11"
        }
        
        files
        {
            "%{prj.location}/src/x11_init.c",
            "%{prj.location}/src/x11_monitor.c",
            "%{prj.location}/src/x11_window.c",
            "%{prj.location}/src/xkb_unicode.c",
            "%{prj.location}/src/posix_time.c",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/glx_context.c",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c",
            "%{prj.location}/src/linux_joystick.c"
        }

    filter "system:macosx"
        pic "on"
        systemversion "latest"
        
        defines
        {
            "_GLFW_COCOA"
        }
        
        files
        {
            "%{prj.location}/src/cocoa_init.m",
            "%{prj.location}/src/cocoa_joystick.h",
            "%{prj.location}/src/cocoa_joystick.m",
            "%{prj.location}/src/cocoa_monitor.m",
            "%{prj.location}/src/cocoa_platform.h",
            "%{prj.location}/src/cocoa_time.c",
            "%{prj.location}/src/cocoa_window.m",
            "%{prj.location}/src/posix_thread.c",
            "%{prj.location}/src/nsgl_context.m",
            "%{prj.location}/src/egl_context.c",
            "%{prj.location}/src/osmesa_context.c"
        }
        
        links
        {
            "CoreFoundation.framework",
            "Cocoa.framework",
            "OpenGL.framework",
            "IOKit.framework",
            "CoreVideo.framework"
        }
