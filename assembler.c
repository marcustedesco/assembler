/* MIPS Assembler Program 
   Marcus Tedesco
   #905373051
   Professor McQuain
*/

#include "assembler.h"

#define debug
#define displayI

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
	
	if(myInstruc[0].type == ADD){
		//printf("THE type is the same!\n");
	}
	
	//myInstruc = malloc(sizeof(Instruc)*numInstruc);

	//fillInstruc(myInstruc[0]);

	//after all data fields have been intialized
	//call function to loop through the intermediate file
	//and call execInstruc execInstruc(char * line)
	//should return and int instead of char *
	//should return the next line to go to.
	//so maybe the instructions should be in the array first
	//with the labels in struct to look up their location
	//data fields will be field and have another struct to 
	//tell their location if necessary
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
	//char line[256];

	while (!feof(ifp)) {
	    fgets (line, 256, ifp);

		  //debug
		#ifdef debug
			if (line!=NULL)
		    	//printf("~LINE: %s", line);
		#endif

		if(strcmp(line,"\n") != 0 && strchr(line,'#')-line != 0){

		  	//removes the whitespace at the beginning of the line
		  	char keys[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.";
		  	int i = strcspn (line,keys);
		  	if(i != 0){
		  		//line = strncpy(line, line+i, strlen(line-i));
		  		strncpy(line, line+i-1, strlen(line-i));
		  		strcat(line,"\0");
		  	}

		 // printf("LINE BEFORE CALLING	IS: %s\n",line);
		  	//line = removeComment(line);
		  	//strcpy(line,removeComment(line));
		  line = cleanStr(line); //removeComment(line);
		  printf("Clean line: %s\n",line);
		  fprintf(ofp, "%s\n", line);
		}
	}

	printf("\n");

	fclose(ifp);
	fclose(ofp);

	return intermediate;
}

char * cleanStr(char * line){
	line = removeComment(line);
	//printf("LINE AFTER RETURNING FROM removeComment: %s\n",line);
	char delims[] = " ,\n\t";
	char * pch;
	char result[128];
	//memset(result,'\0',128);
	pch = strtok (line, delims);
	while (pch != NULL)
	{
	    strcat(result,pch);
	    strcat(result,"~");
	    pch = strtok (NULL, delims);
	}
	result[strlen(result)-1] = '\0';
	char * temp = &result[0];
	return strdup(temp);
}

char * removeComment(char * line){
	char key[] = "#";
  	int i;
  	i = strcspn (line,key);
	char clean[256];
	strncpy(clean,line,i);
	clean[i] = '\0';
	char * temp = &clean[0];
	return strdup(temp);
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

	FILE *ofp;
	char * intermediate = "instructions2.txt";

	ofp = fopen(intermediate, "wb");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", intermediate);
	  exit(1);
	}


	//why is this not working!
	/*FILE *ofp;
	char * outFile = "instructions.txt";

	ofp = fopen(outFile, "wb");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", outFile);
	  exit(1);
	}*/

	char line[256];
	int count = 0;
	int inText = 1;
	//changed to 40 from 32 to supported adding instruction at end
	#ifdef displayI
		char * binary = malloc(sizeof(char)*40);
	#endif
	#ifndef displayI
		char * binary = malloc(sizeof(char)*32);
	#endif
	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	  	//printf("*****************************line is: %s \n", line);
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 0 && isInstruc(line) == 0){
	    	//isInstruc takes a pointer so the value is change on return
	    	binary = getInstrucBinary(lineCopy);
	    	printf("binary %s: 			%s\n", lineCopy, binary);
	    	fprintf(ofp, "%s\n", binary);
	    	count++;
	    }
	  }
	}

	fclose(ifp);
	fclose(ofp);

	return count;
}

/**
 * Input: line from the instruction file
 * Splits the line by '~' and '\n'
 * Returns: 0 if the line is a supported MIPS instruction
 *		    1 if the line is not valid
**/
int isInstruc(char * line){
	char * piece = strtok(line, "~\n");
	if(piece != NULL){
		//printf ("%s\n",piece);
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
	}else if(strcmp(line,"nop") == 0){
		return 0;
	}else if(strcmp(line,"syscall") == 0){
		return 0;
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
//COPY THIS TO Execute INSTRUCTIONS 
char * getInstrucBinary(char * line){
	#ifdef debug
		//printf("--In getInstrucBinary--\n");
		//printf("	instruc to convert to binary: %s!\n", line);
	#endif

	//changed to 40 from 32 to supported adding instruction at end
	#ifdef displayI
		char binary[40];
	#endif
	#ifndef displayI
		char binary[32];
	#endif

	char key[] = "~\n";
	char * one;
	char * two;
	char * three;
	char * four;
	
	one = strtok (line,key);

	if(one != NULL)
		two = strtok(NULL,key);
	if(two != NULL)
		three = strtok(NULL,key);
	if(three != NULL)
		four = strtok(NULL,key);

	if(strcmp(one,"lw") == 0){
		//this is going to need to split up the base from two or three
		strcpy(binary,"100011");
		//base
		strcat(binary,"basex");	
		//rt	
		strcat(binary,intToBinChar(getRegNum(two),5));
		//offset
		strcat(binary,"offsetxxxxxxxxxx");	
		#ifdef displayI
			strcat(binary,"\tlw");
		#endif
	}
	else if(strcmp(one,"sw") == 0){
		//this is going to need to split up the base from two or three
		strcpy(binary,"101011");
		//base
		strcat(binary,"basex");	
		//rt	
		strcat(binary,intToBinChar(getRegNum(two),5));
		//offset
		strcat(binary,"offsetxxxxxxxxxx");
		#ifdef displayI
			strcat(binary,"\tsw");
		#endif
	}
	else if(strcmp(one,"la") == 0){
		//need to figure out what this one does exactly
		strcpy(binary,"laxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		#ifdef displayI
			strcat(binary,"\tla");
		#endif
	}
	else if(strcmp(one,"li") == 0){
		//need to figure out what this one does exactly
		strcpy(binary,"lixxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		#ifdef displayI
			strcat(binary,"\tli");
		#endif
	}
	else if(strcmp(one,"add") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(four),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"100000");
		#ifdef displayI
			strcat(binary,"\tadd");
		#endif		
	}
	else if(strcmp(one,"sub") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(four),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"100010");
		#ifdef displayI
			strcat(binary,"\tsub");
		#endif
	}
	else if(strcmp(one,"addi") == 0){
		strcpy(binary,"001000");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,intToBinChar(atoi(four),16));
		#ifdef displayI
			strcat(binary,"\taddi");
		#endif
	}
	else if(strcmp(one,"addiu") == 0){
		strcpy(binary,"001001");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(two),5));
		//change this so it has to be unsigned
		strcat(binary,intToBinChar(atoi(four),16));
		#ifdef displayI
			strcat(binary,"\taddiu");
		#endif
	}
	else if(strcmp(one,"or") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(four),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"100101");
		#ifdef displayI
			strcat(binary,"\tor");
		#endif
	}
	else if(strcmp(one,"and") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(four),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"100100");	
		#ifdef displayI
			strcat(binary,"\tand");
		#endif	
	}
	else if(strcmp(one,"ori") == 0){
		//these registers are different from his spec to the MIPS spec
		strcpy(binary,"001101");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,intToBinChar(atoi(four),16));
		#ifdef displayI
			strcat(binary,"\tori");
		#endif
	}
	else if(strcmp(one,"andi") == 0){
		//these registers are different from his spec to the MIPS spec
		strcpy(binary,"001100");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,intToBinChar(atoi(four),16));
		#ifdef displayI
			strcat(binary,"\tandi");
		#endif
	}
	else if(strcmp(one,"slt") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(four),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"101010");
		#ifdef displayI
			strcat(binary,"\tslt");
		#endif
	}
	else if(strcmp(one,"slti") == 0){
		//these registers are different from his spec to the MIPS spec
		strcpy(binary,"001010");
		//rs
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,intToBinChar(atoi(four),16));
		#ifdef displayI
			strcat(binary,"\tslti");
		#endif
	}
	else if(strcmp(one,"sll") == 0){
		strcpy(binary,"000000");
		strcat(binary,"00000");
		//rt
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		//sa
		strcat(binary,intToBinChar(getRegNum(four),5));
		strcat(binary,"000000");
		#ifdef displayI
			strcat(binary,"\tsll");
		#endif	
	}
	else if(strcmp(one,"srl") == 0){
		strcpy(binary,"000000");
		strcat(binary,"00000");
		//rt
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		//sa
		strcat(binary,intToBinChar(getRegNum(four),5));
		strcat(binary,"000010");
		#ifdef displayI
			strcat(binary,"\tsrl");
		#endif
	}
	else if(strcmp(one,"sra") == 0){
		strcpy(binary,"000000");
		strcat(binary,"00000");
		//rt
		strcat(binary,intToBinChar(getRegNum(three),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		//sa
		strcat(binary,intToBinChar(getRegNum(four),5));
		strcat(binary,"000011");
		#ifdef displayI
			strcat(binary,"\tsra");
		#endif
	}
	else if(strcmp(one,"nop") == 0){
		//lots of 0's
		strcpy(binary,"00000000000000000000000000000000");
		#ifdef displayI
			strcat(binary,"\tnop");
		#endif
	}
	else if(strcmp(one,"beq") == 0){
		strcpy(binary,"000100");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(three),5));
		strcat(binary,"immediatexxxxxxx");
		#ifdef displayI
			strcat(binary,"\tbeq");
		#endif
	}
	else if(strcmp(one,"bne") == 0){
		strcpy(binary,"000101");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		//rt
		strcat(binary,intToBinChar(getRegNum(three),5));
		strcat(binary,"offsetxxxxxxxxxx");
		#ifdef displayI
			strcat(binary,"\tbne");
		#endif
	}
	else if(strcmp(one,"bltz") == 0){
		strcpy(binary,"000001");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"offsetxxxxxxxxxx");	
		#ifdef displayI
			strcat(binary,"\tbltz");
		#endif
	}
	else if(strcmp(one,"blez") == 0){
		strcpy(binary,"000110");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary,"immediatexxxxxxx");
		#ifdef displayI
			strcat(binary,"\tblez");
		#endif
	}
	else if(strcmp(one,"blt") == 0){
		//This is not in the MIPS reference 
		strcpy(binary,"bltxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		#ifdef displayI
			strcat(binary,"\tblt");
		#endif
	}
	else if(strcmp(one,"ble") == 0){
		//This is not in the MIPS reference
		strcpy(binary,"blexxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
		#ifdef displayI
			strcat(binary,"\tble");
		#endif
	}
	else if(strcmp(one,"j") == 0){
		strcpy(binary,"000010");
		strcat(binary,"instr_indexxxxxx");
		#ifdef displayI
			strcat(binary,"\tj");
		#endif
	}
	else if(strcmp(one,"jr") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"0000000000");
		strcat(binary,"hintx");
		strcat(binary,"001000");
		#ifdef displayI
			strcat(binary,"\tjr");
		#endif
	}
	else if(strcmp(one,"jal") == 0){
		strcpy(binary,"000011");
		strcat(binary,"instr_indexxxxxx");
		#ifdef displayI
			strcat(binary,"\tjal");
		#endif
	}
	else if(strcmp(one,"syscall") == 0){
		strcpy(binary,"000000");
		strcat(binary,"codexxxxxxxxxxxxxxxx");
		strcat(binary,"001100");
		#ifdef displayI
			strcat(binary,"\tsyscall");
		#endif
	}

	strcat(binary,"\0");

	char * bin = &binary[0];
	return strdup(bin);
}

char * execInstruc(char * line){
	return "execute";
}

int getRegNum(char* reg){

	#ifdef debug
		printf("--In getRegNum--\n");
		printf("	Register label to get reg number: %s!\n", reg);
	#endif

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
	//for now, until labels are implemented
	if(num == -1)
		return "label";

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