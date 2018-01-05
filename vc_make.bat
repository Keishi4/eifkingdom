@rem Visual C/C++ version
cl /Ox /MD /c /Wall /wd4710 /wd4711 d:\usr\src\eif\EIFORIA.C >compile.log
rc /r eiforia.rc
link /MACHINE:X86 /SUBSYSTEM:CONSOLE EIFORIA.obj eiforia.res /OUT:VC\EIFORIA.EXE