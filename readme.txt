MIPS Assembler Program
Marcus Tedesco
Nov. 23, 2013
CS 2506 - Virginia Tech
Professor McQuain

Included in this tar:
	-makefile
	-assembler.c
	-assembler.h
	-readme.txt
	-pledge.txt

***To build just run: make 		(do not need to run make assembler)

Use any of the following commands to run:
	assemble <input file> <output file>
	assemble –symbols <input file> <output file>
	assemble –list <input file> <output file>

As far as I can tell my program should not fail or seg fault when running any
of the test files. However, I have had a problem with file writing. I think it
is due to the permissions of the containing directory on my local machine. I 
think it should not have a problem on the rlogin system. If by chance it does
have a problem with writing please create files called:
	intermediate.txt
	instructions.txt
And create a file named the same as the output file. It will rewrite any of the 
contents. I don't think this will be a problem.

I can produce the correct binary output for almost every instruction. The exceptions
are instructions that at have negative values that require 2's complement to be 
calculated and instructions that shift a binary number. It will not produce errors or
crash if these are encountered, it will just have either the wrong binary number or
it will be filled with spacer 0's.

My biggest struggle on the this huge project was string manipulation. I found C char 
arrays and pointers to be very confusing when copying, concatenating and parsing. My 
data section is a little bit off for any instruction set that has an .asciiz string. 
It will get most of the binary lines correct but it sometimes leaves the last 1 or 2 
lines out. Again, this wont crash the program but the binary lines following it in 
the output will be offset by 1 or 2. This program does not process the arrays with 
values seperated by commas. I forgot that that was an option when I wrote that part 
of the parser. It should not crash the program it will just mean that the labels and 
values following it will be off by the size the of the array. 

The program should work correctly for any of the 3 ways to invoke it. -list works 
correctly and its formatted almost identical to the example output. The only exception
is that the actual instruction is delimited by ~'s instead of spaces. I hope this still
suffices for the 10% extra credit. 

Overall, I think my program works well. I took this class last semester and completely 
failed this project (hence why I am retaking the class). I think I have a much better 
understanding of MIPS and the C language now. This was a VERY hard project that I 
invested a huge amount of time into but it is satisfying to have created something that
works correctly in most cases. 

-Marcus 

