workspace "FZLib"
	startproject "FZLib"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}
	
	helperDir = "FZLib/Helpers/"
	spdlogDir = "FZLib/Vendor/spdlog/"

	IncludeDir = {}
	IncludeDir["SPDLOG"] = "%{prj.name}/Vendor/spdlog/"

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
		"{MKDIR} %[Dist/include/spdlog]",
		"{MKDIR} %[Dist/include/spdlog/cfg]",
		"{MKDIR} %[Dist/include/spdlog/details]",
		"{MKDIR} %[Dist/include/spdlog/fmt]",
		"{MKDIR} %[Dist/include/spdlog/fmt/bundled]",
		"{MKDIR} %[Dist/include/spdlog/sinks]",
		"{COPYFILE} %["..helperDir.."/**.h] %[Dist/include/FZLib/Helpers/]",
		"{COPYFILE} %["..spdlogDir.."/include/spdlog/**.h] %[Dist/include/spdlog/]",
		"{COPYFILE} %["..spdlogDir.."/include/spdlog/cfg/**.h] %[Dist/include/spdlog/cfg/]",
		"{COPYFILE} %["..spdlogDir.."/include/spdlog/details/**.h] %[Dist/include/spdlog/details/]",
		"{COPYFILE} %["..spdlogDir.."/include/spdlog/fmt/**.h] %[Dist/include/spdlog/fmt/]",
		"{COPYFILE} %["..spdlogDir.."/include/spdlog/fmt/bundled/**.h] %[Dist/include/spdlog/fmt/bundled/]",
		"{COPYFILE} %["..spdlogDir.."/include/spdlog/sinks/**.h] %[Dist/include/spdlog/sinks/]",
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
		"%{IncludeDir.SPDLOG}/include",
    }

	libdirs 
	{ 
		"%{IncludeDir.SPDLOG}/lib/%{cfg.buildcfg}",
	}

	links
	{
		"spdlog.lib"
	}

	postbuildcommands 
	{ 
		"{COPYFILE} %[Dist/log/**.lib] %[Dist/lib/%{cfg.buildcfg}/%{cfg.architecture}/]",
		"{COPYFILE} %[Dist/log/**.dll] %[Dist/lib/%{cfg.buildcfg}/%{cfg.architecture}/]",
		"{RMDIR} %[Dist/log/]",
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

