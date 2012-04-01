@ECHO OFF

RMDIR /S /Q Deploy
MKDIR Deploy
XCOPY Solution\Debug\TileTest.exe Deploy

XCOPY Solution\shaders Deploy\shaders\
XCOPY Solution\textures Deploy\textures\
