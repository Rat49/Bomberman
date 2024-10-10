paths = require "paths"
-----------------------------------------------------------------------------------------------------------------------
project "Bomberman"
    language "C++"
    characterset "MBCS"
    kind "WindowedApp"
    targetname "Bomberman"
    
    postbuildcommands
    {
        "{MKDIR} " .. paths.build,
        "{DELETE} " .. paths.build .. "/%{cfg.buildtarget.name}",
		
        "{COPY} " .. paths.sfml.bin .. "/openal32.dll " .. paths.build,
		"{COPY} " .. paths.sfml.bin .. "/openal32.dll " .. paths.genDebug,
		"{COPY} " .. paths.sfml.bin .. "/openal32.dll " .. paths.genRelease,
		
		"{COPY} " .. paths.root .. "/assets " .. paths.build .. "/assets",
		"{COPY} " .. paths.root .. "/assets " .. paths.genDebug .. "/assets",
		"{COPY} " .. paths.root .. "/assets " .. paths.genRelease .. "/assets",
		"{COPY} " .. paths.root .. "/assets " .. paths.genPrj .. "/assets",
		
        "{COPY} %{cfg.buildtarget.directory}%{cfg.buildtarget.name} " .. paths.build,
    }
    
    filter ("configurations:Debug")
        links
        {
            "sfml-audio-s-d",
            "sfml-graphics-s-d",
            "sfml-network-s-d",
            "sfml-system-s-d",
            "sfml-window-s-d",
        }
    filter ("configurations:Release or Final")
        links
        {
            "sfml-audio-s",
            "sfml-graphics-s",
            "sfml-network-s",
            "sfml-system-s",
            "sfml-window-s",
        }
    filter {}    
    
    includedirs
    {
        paths.source,
        paths.sfml.inc,
    }
    
    libdirs
    {
        paths.sfml.lib,
    }
    
    links
    {
        "gdi32",
        "winmm",
        "ws2_32",
        "freetype",
        "opengl32",
        "openal32",
        "flac",
        "ogg",
        "vorbis",
        "vorbisenc",
        "vorbisfile",
    }
    
    files
    {
        paths.source .. "/**.hpp",
        paths.source .. "/**.cpp",
    }
-----------------------------------------------------------------------------------------------------------------------
