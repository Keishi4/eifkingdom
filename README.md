# eifkingdom

Kingdom Eiforia game is a console kingdom manager simulation game (simple).

Version 1.2 was originaly written in C/C++ targeted for unknown (for me) DOS compiler
by Ponpa Dmitriy. I have adapted this version with almost no changes (just fixed a 
couple of minor bugs regarding missed input/output) to be able to run on 32-bit Windows
systems.

Version 1.2.0.1 is able to run on any 32-bit (and 64-bit also) Windows with exception
of Windows NT 3.1. If you are about to execute the game on such oldies like Windows NT 3.5x
or Windows 95 you also need ```msvcrt.dll``` at least version 4.0.

Gameplay language is russian.

The game is built using Tiny C compiler with resource file compiled using mingw32 ```windres``` tool.
