-----------------------------------------------------------------------------------------------------------------------
local paths     = {}
-----------------------------------------------------------------------------------------------------------------------
paths.root      = path.getabsolute("..")
paths.source    = paths.root   .. "/Source"
paths.common    = paths.source .. "/Common"
paths.test      = paths.source .. "/TestModule"
paths.game      = paths.source .. "/Game"
-----------------------------------------------------------------------------------------------------------------------
paths.sfml      = {}
paths.sfml.root = paths.root .. "/SFML-2.6.1"
paths.sfml.bin  = paths.sfml.root .. "/bin"
paths.sfml.inc  = paths.sfml.root .. "/include"
paths.sfml.lib  = paths.sfml.root .. "/lib"
-----------------------------------------------------------------------------------------------------------------------
paths.build     = paths.root .. "/.bin"
paths.genPrj    = paths.root .. "/.gen/prj"
paths.genDebug  = paths.root .. "/.gen/bin/Debug/Bomberman"
paths.genRelease= paths.root .. "/.gen/bin/Release/Bomberman"
-----------------------------------------------------------------------------------------------------------------------
return paths