all: dirs vc_std\eiforia.exe


std: dirs vc_std\eiforia.exe

vc_std\eiforia.exe: vc_std\eiforia.obj vc_std\eiforia.res
	link /MACHINE:X86 /SUBSYSTEM:CONSOLE vc_std\EIFORIA.obj vc_std\eiforia.res /OUT:vc_std\EIFORIA.EXE

vc_std\eiforia.obj: EIFORIA.C intro.h help.h win32_helper.h
	cl /Ox /MD /c /arch:IA32 /Wall /wd4710 /wd4711 EIFORIA.C /Fovc_std\eiforia.obj >vc_std\compile.log

vc_std\eiforia.res: eiforia.rc
	rc /r /Fovc_std\eiforia.res eiforia.rc

dirs:
	if not exist vc_std md vc_std

clean:
	del /f /q vc_std\*.*
	rmdir vc_std
