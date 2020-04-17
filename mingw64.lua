premake.tools.mingw64         = {}

local mingw64                 = premake.tools.mingw64
local gcc                     = premake.tools.gcc

mingw64.getcflags             = gcc.getcflags
mingw64.getcxxflags           = gcc.getcxxflags
mingw64.getforceincludes      = gcc.getforceincludes
mingw64.getldflags            = gcc.getldflags
mingw64.getcppflags           = gcc.getcppflags
mingw64.getdefines            = gcc.getdefines
mingw64.getincludedirs        = gcc.getincludedirs
mingw64.getLibraryDirectories = gcc.getLibraryDirectories
mingw64.getlinks              = gcc.getlinks
mingw64.getmakesettings       = gcc.getmakesettings

mingw64.getundefines          = gcc.getundefines
mingw64.getrunpathdirs        = gcc.getrunpathdirs

function mingw64.gettoolname (cfg, tool)
  local prefix = "/usr/bin/x86_64-w64-mingw32-"
  if     tool == "cc" then
    name = prefix .. "gcc"
  elseif tool == "cxx" then
    name = prefix .. "g++"
  elseif tool == "ar" then
    name = prefix .. "ar"
  else
    name = nil
  end
  return name
end
