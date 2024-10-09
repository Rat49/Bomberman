local function get_sdk_version()
    local version10 = os.getWindowsRegistry("HKLM:SOFTWARE\\Wow6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion")
    if version10 ~= nil then
        return version10 .. ".0"
    end
    return ""
end
-----------------------------------------------------------------------------------------------------------------------
workspace ("Bomberman")
    configurations { "Debug", "Release", "Final" }
    
    location ("../.gen/prj")
    targetdir ("../.gen/bin/%{cfg.buildcfg}/%{prj.targetname}")
    objdir ("../.gen/obj/%{prj.name}_%{cfg.buildcfg}")

    flags ("MultiProcessorCompile")
    flags ("FatalWarnings")
    warnings ("Extra")
    architecture ("x64")
    system ("Windows")
    systemversion (get_sdk_version())

    filter ("configurations:Debug")
        defines { "_DEBUG", "SFML_STATIC", }
        symbols ("FastLink")
        optimize ("Off")
        targetsuffix "-d"
        
    filter ("configurations:Release")
        defines { "NDEBUG", "SFML_STATIC", }
        symbols ("Off")
        optimize ("Speed")

    filter ("configurations:Final")
        defines { "NDEBUG", "SFML_STATIC", "FINAL" }
        symbols ("Off")
        optimize ("Speed")
       
    filter {}
-----------------------------------------------------------------------------------------------------------------------
group ("")
    include ("game")
-----------------------------------------------------------------------------------------------------------------------