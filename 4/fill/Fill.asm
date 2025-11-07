// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(MAIN)
@KBD
D=M
@BLACK
D;JGT
@WHITE
D;JEQ
(BLACK)
D=-1
@FILL
0;JMP
(WHITE)
D=0
@FILL
0;JMP
(FILL)
@COLOR
M=D
@SCREEN
D=A
@POINTER
M=D
@8192
D=D+A
@END
M=D
(LOOP)
@COLOR
D=M
@POINTER
A=M
M=D
@POINTER
M=M+1
D=M
@END
D=D-M
@LOOP
D;JLT
@MAIN
0;JMP