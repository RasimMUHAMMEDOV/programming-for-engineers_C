# programming-for-Engineers_C
C programming language project

Typing of the Bombs (C Terminal Game)

What the Project Does: Typing of the Bombs is an ASCII-based terminal arcade game where players defend a city from falling bombs dropped by an overhead plane. To destroy each bomb before impact, the player must accurately type the deactivation codeword displayed beside it.

Technologies: C programming language, Windows API (<windows.h>, <conio.h> for non-blocking keyboard input via _kbhit() and _getch()), system("cls") for frame rendering, and standard file I/O (<stdio.h>).

Main Features: Real-time ASCII animations, dynamic left-shifting word peeling as letters are typed, progressive difficulty (codewords scale from 3 to 10 letters every 5 bombs), accuracy-based scoring, and an ESC-triggered menu supporting saving/loading game state structs to files.

How to Run It: Open the project in Visual Studio on Windows (or compile via gcc main.c -o TypingOfTheBombs.exe), ensure city.txt, plane.txt, bomb.txt, and codewords.txt are in the executable's directory, and press Ctrl + F5 or run ./TypingOfTheBombs.exe.

What I Learned: I learned how to build a continuous real-time game loop in C using non-blocking console I/O, modularize code across multiple functions, manage dynamic ASCII rendering, and serialize C struct data to external files for save/load functionality.
