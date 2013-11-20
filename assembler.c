/* MIPS Assembler Program 
   Marcus Tedesco
   #905373051
   Professor McQuain
*/

#include "assembler.h"

#define debug

void run(char * inputFile, char * outFile)
{
	#ifdef debug
		printf("--In run--\n");
		printf("	inputFile %s!\n", inputFile);
		printf("	outFile %s!\n", outFile);
	#endif

	#ifdef debug
		printFile(inputFile);
	#endif

	char * stripedFile = stripExtra(inputFile);
	
	#ifdef debug
		printFile(stripedFile);
	#endif

	int numInstruc = instrucCountAndFile(stripedFile);

	#ifdef debug
		printf("Number of instructions in .text section: %d!\n", numInstruc);
	#endif

	//Instruc * myInstruc[numInstruc];

	struct Instruc myInstruc[numInstruc];
	myInstruc[0].command = "helppppp";
	myInstruc[0].type = ADD;
	printf("This is the command: %s!\n", myInstruc[0].command);
	printf("This is the enum type: %d!\n", myInstruc[0].type);

	if(myInstruc[0].type == ADD){
		printf("THE type is the same!\n");
	}
	
	printf("register 0 is: %d!\n", reg[0]);

	char* binary = intToBinChar(3, 6);

	printf("3 in binary is: %s!\n", binary);
	//myInstruc = malloc(sizeof(Instruc)*numInstruc);

	//fillInstruc(&myInstruc);

}

void run_symbol (char * inputFile, char * outFile){
	#ifdef debug
		printf("--In run_symbol--\n");
		printf("	inputFile %s!\n", inputFile);
		printf("	outFile %s!\n", outFile);
	#endif

	FILE *fp;
	fp = fopen(inputFile,"r");

	if (fp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", inputFile);
  		exit(1);
	}

	fclose(fp);

}

void run_list (char * inputFile, char * outFile){
	#ifdef debug
		printf("--In run_list--\n");
		printf("	inputFile %s!\n", inputFile);
		printf("	outFile %s!\n", outFile);
	#endif

	FILE *fp;
	fp = fopen(inputFile,"r");

	if (fp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", inputFile);
  		exit(1);
	}

	fclose(fp);

}

/* returns intermediate filename */
char* stripExtra(char * inputFile){
	FILE *ifp;
	ifp = fopen(inputFile,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", inputFile);
  		exit(1);
	}

	FILE *ofp;
	char * intermediate = "intermediate.txt";

	ofp = fopen(intermediate, "wb");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", intermediate);
	  exit(1);
	}

	char * line = malloc(sizeof(char)*256);

	while (!feof(ifp)) {
	  fgets (line, 256, ifp);

	  //debug
	  if (line!=NULL)
	    printf("%s", line);

	  if(strcmp(line,"\n") != 0 && strchr(line,'#')-line != 0){
	  	//removes the whitespace at the beginning of the line
	  	char keys[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.";
	  	int i = strcspn (line,keys);
	  	if(i != 0)
	  		line = strncpy(line, line+i, strlen(line));

	  	//removes the comments
	  	char tag[] = "#";
	  	i = strcspn(line,tag);
	  	//char * locateTag = strchr(line,'#');
	  	if(i == strlen(line))
	  		fprintf(ofp, "%s", line);
	  	else{
	  		//change this to remove the comments at the end
	  		//also remove all tabs like after .text, main, etc...
	  		fprintf(ofp, "%s", line);
	  		/*printf("found comment at char# %d!\n", i);
	  		char * substring = malloc(sizeof(char)*i);
	  		line = strncpy(substring, line, strlen(substring));
	  		printf("THIS IS THE LINE WITHOUT COMMENT: %s!\n", substring);
	  		fprintf(ofp, "%s\n", line);*/
	  		/*char substring[256];
	  		strncpy(substring, line, strlen(line)-strlen(locateTag));
	  		printf("THIS IS THE SUBSTRING:%s", substring);
	  		fprintf(ofp, "%s", substring);*/
	  	}
	  }
	 /* if (strcmp(str,"\n") == 0)
	  	printf("^This line is just a NEWLINE*******************************************\n");
	  if(strchr(str,'#') != NULL && strchr(str,'#')-str == 0)
	  	printf("^This line has starts with #*******************************************\n");
	  if(strchr(str,' ') != NULL && strchr(str,' ')-str == 0)
	  	printf("^This line starts with a space*******************************************\n");*/
	}

	printf("\n");

	fclose(ifp);
	fclose(ofp);

	return intermediate;
}

/* used for debugging */
void printFile(char * filename) {
	printf("\n----- IN PRINTFILE: printing %s -----\n", filename);

	FILE *ifp;
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	char line[256];

	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL)
	    printf("%s", line);
	}

	printf("\n");

	fclose(ifp);
}

int instrucCountAndFile(char * filename){
	#ifdef debug
		printf("--In instrucCountAndFile--\n");
		printf("	inputFile %s!\n", filename);
	#endif

	FILE *ifp;
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	//why is this not working!
	/*FILE *ofp;
	char * outFile = "textInstructions.txt";

	ofp = fopen(outFile, "wb");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", outFile);
	  exit(1);
	}*/

	char line[256];
	int count = 0;
	int inText = 1;

	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL)
	  	printf("*****************************line is: %s \n", line);
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 0 && isInstruc(line) == 0){
	    	//isInstruc takes a pointer so the value is change on return
	    	char * binary = getInstrucBinary(lineCopy);
	    	printf("binary for %s is: %s\n", lineCopy, binary);
	    	//fprintf(ofp, "%s", line);
	    	count++;
	    }
	}

	fclose(ifp);
	//fclose(ofp);

	return count;
}

int isInstruc(char * line){
	char * piece = strtok(line, " ");
	if(piece != NULL){
		printf ("%s\n",piece);
		if(strcmp(piece,"lw") == 0){
			return 0;			
		}
		else if(strcmp(piece,"sw") == 0){
			return 0;
		}
		else if(strcmp(piece,"la") == 0){
			return 0;
		}
		else if(strcmp(piece,"li") == 0){
			return 0;
		}
		else if(strcmp(piece,"add") == 0){
			return 0;			
		}
		else if(strcmp(piece,"sub") == 0){
			return 0;
		}
		else if(strcmp(piece,"addi") == 0){
			return 0;
		}
		else if(strcmp(piece,"addiu") == 0){
			return 0;
		}
		else if(strcmp(piece,"or") == 0){
			return 0;
		}
		else if(strcmp(piece,"and") == 0){
			return 0;			
		}
		else if(strcmp(piece,"ori") == 0){
			return 0;
		}
		else if(strcmp(piece,"andi") == 0){
			return 0;
		}
		else if(strcmp(piece,"slt") == 0){
			return 0;
		}
		else if(strcmp(piece,"slti") == 0){
			return 0;
		}
		else if(strcmp(piece,"sll") == 0){
			return 0;
		}
		else if(strcmp(piece,"srl") == 0){
			return 0;
		}
		else if(strcmp(piece,"sra") == 0){
			return 0;
		}
		else if(strcmp(piece,"nop") == 0){
			return 0;
		}
		else if(strcmp(piece,"beq") == 0){
			return 0;
		}
		else if(strcmp(piece,"bne") == 0){
			return 0;
		}
		else if(strcmp(piece,"bltz") == 0){
			return 0;
		}
		else if(strcmp(piece,"blez") == 0){
			return 0;
		}
		else if(strcmp(piece,"blt") == 0){
			return 0;
		}
		else if(strcmp(piece,"ble") == 0){
			return 0;
		}
		else if(strcmp(piece,"j") == 0){
			return 0;
		}
		else if(strcmp(piece,"jr") == 0){
			return 0;
		}
		else if(strcmp(piece,"jal") == 0){
			return 0;
		}
		else if(strcmp(piece,"syscall") == 0){
			return 0;
		}
	}

	return 1;
}

void fillInstrucList(struct Instruc *list){
	FILE *ifp;
	char* filename = "textInstructions.txt";
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	char line[256];
	int index = 0;

	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	  	  char * piece = strtok(line, " ");
		  if(piece != NULL){
			printf ("%s\n",piece);
			if(strcmp(piece,"lw") == 0){
				//list[index]->command = malloc(sizeof(char)*256);
				//list[index]->command = line;	
			}
		  }
	  }
	  index++;
	}
	return;
}

char * getInstrucBinary(char * line){
	#ifdef debug
		printf("--In getInstrucBinary--\n");
		printf("	instruc to convert to binary: %s!\n", line);
	#endif

	char key[] = " ";
	char * piece;
	
	piece = strtok (line,key);

	if(strcmp(piece,"add") == 0){
		printf("add-----------------------------------------------------------------------\n");
		//rd
		piece = strtok (NULL, key);
		//do not keep this part!
		char * temp = malloc(strlen(piece)-1);
		temp = strncpy(temp, piece, 3);
		int rd; 
		rd = getRegNum(temp);
		//rd = getRegNum(piece);
		printf("rd: %d\n", rd);
		//rs
		piece = strtok (NULL, key);
		char * temp2 = malloc(strlen(piece)-1);
		temp2 = strncpy(temp2, piece, 3);
		int rs; 
		rs = getRegNum(temp2);
		//rs = getRegNum(piece);
		printf("rs: %d\n", rs);
		//rt
		piece = strtok (NULL, key);
		int rt; 
		rt = getRegNum(piece);
		printf("rt: %d\n", rt);

		//printf("does some add stuff\n");
		printf("00000");
		printf("%s", intToBinChar(rs,5));
		printf("%s", intToBinChar(rt,5));
		printf("%s", intToBinChar(rd,5));
		printf("00000");
		printf("100000");
		printf("\n");
	}

	return "add";
}

int getRegNum(char* reg){

	printf("reg value to get num: %s\n", reg);

	if(strcmp(reg,"$zero") == 0)
		return 0;
	else if(strcmp(reg,"$at") == 0)
		return 1;
	else if(strcmp(reg,"$v0") == 0)
		return 2;
	else if(strcmp(reg,"$v1") == 0)
		return 3;
	else if(strcmp(reg,"$a0") == 0)
		return 4;
	else if(strcmp(reg,"$a1") == 0)
		return 5;
	else if(strcmp(reg,"$a2") == 0)
		return 6;
	else if(strcmp(reg,"$a3") == 0)
		return 7;
	else if(strcmp(reg,"$t0") == 0)
		return 8;
	else if(strcmp(reg,"$t1") == 0)
		return 9;
	else if(strcmp(reg,"$t2") == 0)
		return 10;
	else if(strcmp(reg,"$t3") == 0)
		return 11;
	else if(strcmp(reg,"$t4") == 0)
		return 12;
	else if(strcmp(reg,"$t5") == 0)
		return 13;
	else if(strcmp(reg,"$t6") == 0)
		return 14;
	else if(strcmp(reg,"$t7") == 0)
		return 15;	
	else if(strcmp(reg,"$s0") == 0)
		return 16;
	else if(strcmp(reg,"$s1") == 0)
		return 17;
	else if(strcmp(reg,"$s2") == 0)
		return 18;
	else if(strcmp(reg,"$s3") == 0)
		return 19;
	else if(strcmp(reg,"$s4") == 0)
		return 20;
	else if(strcmp(reg,"$s5") == 0)
		return 21;
	else if(strcmp(reg,"$s6") == 0)
		return 22;
	else if(strcmp(reg,"$s7") == 0)
		return 23;
	else if(strcmp(reg,"$t8") == 0)
		return 24;
	else if(strcmp(reg,"$t9") == 0)
		return 25;
	else if(strcmp(reg,"$k0") == 0)
		return 26;
	else if(strcmp(reg,"$k1") == 0)
		return 27;
	else if(strcmp(reg,"$gp") == 0)
		return 28;
	else if(strcmp(reg,"$sp") == 0)
		return 29;
	else if(strcmp(reg,"$fp") == 0 || strcmp(reg,"$s8") == 0)
		return 30;
	else if(strcmp(reg,"$ra") == 0)
		return 31;
	else
		return -1;
}

char * intToBinChar(int num, int length){
	int total = 0, index;
	char binaryNumber[length];

	for(index = 0; index < length; index++){
		if(num > 0){
			total = num % 2;
			num = num / 2;
			if(total == 0)
				binaryNumber[index] = '0';
			else if(total == 1)
				binaryNumber[index] = '1';
		}
		else
			binaryNumber[index] = '0';
	}

	binaryNumber[index] = '\0';

	//reverse the array
	char binary[length];
	int i;
	for(i = 0; i < length; i++){
		binary[i] = binaryNumber[length-1-i];
	}

	binary[i] = '\0';

    char* bin = &binary[0];
    return bin;
}

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