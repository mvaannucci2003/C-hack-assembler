This is the Hack Computer assembler built entirely with c.

The main driver file is main. This file takes inherits from all other files to run the parser and read the inputed 
files to convert assembly into machine code for our computer to read and execute in the Nand2Tetris IDE.
To properly run this assembler you must run ./main ```YOUR FILE NAME```inside the CLI. You need to insert a valid 
asm file for the parser will throw a error at you stating that the file is incorrect. You also need to provide the file
during the command execution or the assembler will not start.

Once you run the assembler with a valid file, you will get a output that parses the instructions and stores them in the 
hash array, this associates the respective symbol to the instruction of each instruction line to be converted to machine code.
You will also find that running this program makes another copy file of the original asm file you inputed with the ```.hack```suffix 
at the end of it. This is your machine code translation from the assembly instructions which you can take to the Nand2Tetris IDE and run your freshly 
converted program.

I also provide various sample asm files so you can test the program's functionality as well as a Pong game that you can run in IDE as well.

Please feel free to contribute or provide feedback on where I can improve here, this was my first time using c and plan to build other
mock projects and contribute to open-source to improve my skills in this language.
