@ECHO OFF

RMDIR /S /Q Deploy
MKDIR Deploy
XCOPY Solution\Debug\*.exe Deploy

XCOPY Solution\shaders Deploy\shaders\
XCOPY Solution\textures Deploy\textures\
XCOPY Solution\fonts Deploy\fonts\
PAUSE