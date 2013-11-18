// On my honor:
//
// - I have not discussed the Java language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used Java language code obtained from another student,
// or any other unauthorized source, either modified or unmodified.
//
// - If any Java language code or documentation used in my program
// was obtained from another source, such as a text book or course
// notes, that has been clearly noted with a proper citation in
// the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Automated Grader.
//
// Pledge: On my honor, I have neither given nor received unauthorized
// aid on this assignment.
//
// Marcus Tedesco

#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"

int main ( int argc, char *argv[] )
{
	if(argv[1] == NULL || argv[2] == NULL){
		printf("Input and output file name arguments necessary.\n");
		exit(1);
	}

	printf("Hello I'm the MIPS Assembler\n");
	
	run(argv[1], argv[2]);
}
