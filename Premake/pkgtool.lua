paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "PackageTool"
	language "C++"
	cppdialect "C++17"
    characterset "MBCS"
    kind "ConsoleApp"
    targetname "PackageTool"   
	
    includedirs
    {
        paths.source,
    }

    files
    {
		paths.source .. "/PackageTool/**.hpp",
		paths.source .. "/PackageTool/**.cpp",
		paths.source .. "/LogModule/**.hpp",
        paths.source .. "/LogModule/**.cpp",
		paths.common .. "/StringUtils.hpp",
		paths.common .. "/StringUtils.cpp",
    }
-----------------------------------------------------------------------------------------------------------------------