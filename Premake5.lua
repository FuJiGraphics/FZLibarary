workspace "FZLib"
	startproject "FZLib"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}
	
	outputDir = "Dist/%{cfg.buildcfg}/"
	helperDir = "FZLib/Helpers/"

	project "FZLib"
		location "FZLib"
		kind "SharedLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "off"
    systemversion "latest"  

    targetdir (outputDir.."/log/")
    objdir (outputDir.."/log/")

    pchheader "pch.h"
    pchsource "%{prj.name}/EntryPoint/pch.cpp"
	
	prebuildcommands
	{
		"{MKDIR} %["..outputDir.."/lib/%{cfg.architecture}/]",
		"{MKDIR} %["..outputDir.."/include/]",
		"{COPYFILE} %["..helperDir.."/**.h] %["..outputDir.."/include/]",
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
		"{COPYFILE} %["..outputDir.."/log/**.lib] %["..outputDir.."/lib/%{cfg.architecture}/]",
		"{COPYFILE} %["..outputDir.."/log/**.dll] %["..outputDir.."/lib/%{cfg.architecture}/]",
		"{DELETE} %["..outputDir.."/log/**.dll] %["..outputDir.."/log/**.lib]",
		"{DELETE} %["..outputDir.."/log/**.obj] %["..outputDir.."/log/**.ilk] %["..outputDir.."/log/**.exp]",
		"{DELETE} %["..outputDir.."/log/**.idb] %["..outputDir.."/log/**.pdb] %["..outputDir.."/log/**.pch]",
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

