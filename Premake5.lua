workspace "FZLib"
	startproject "FZLib"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}
	
	helperDir = "FZLib/Helpers/"

	project "FZLib"
		location "FZLib"
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "off"
    systemversion "latest"  

    targetdir ("Dist/log/")
    objdir ("Dist/log/")

    pchheader "pch.h"
    pchsource "%{prj.name}/EntryPoint/pch.cpp"
	
	prebuildcommands
	{
		"{MKDIR} %[Dist/lib/%{cfg.buildcfg}/%{cfg.architecture}/]",
		"{MKDIR} %[Dist/include/]",
		"{MKDIR} %[Dist/include/FZLib]",
		"{MKDIR} %[Dist/include/FZLib/Helpers]",
		"{COPYFILE} %["..helperDir.."/**.h] %[Dist/include/FZLib/Helpers/]",
	}

	defines
	{
		"FZLIB_EXPORTS",
	}

    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }

	includedirs
    {
        "%{prj.name}",
        "%{prj.name}/EntryPoint",
    }

	postbuildcommands 
	{ 
		"{COPYFILE} %[Dist/log/**.lib] %[Dist/lib/%{cfg.buildcfg}/%{cfg.architecture}/]",
		"{COPYFILE} %[Dist/log/**.dll] %[Dist/lib/%{cfg.buildcfg}/%{cfg.architecture}/]",
		"{DELETE} %[Dist/log/**.dll] %[Dist/log/**.lib]",
		"{DELETE} %[Dist/log/**.obj] %[Dist/log/**.ilk] %[Dist/log/**.exp]",
		"{DELETE} %[Dist/log/**.idb] %[Dist/log/**.pdb] %[Dist/log/**.pch]",
	}

    filter "system:Windows"
    defines
    {
        "FZ_PLATFORM_WINDOWS",
    }

    filter "configurations:Debug"
        defines "FZ_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "FZ_RELEASE"
        runtime "Release"
        optimize "On"

