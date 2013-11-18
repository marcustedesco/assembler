/* MIPS Assembler Program 
   Marcus Tedesco
   #905373051
   Professor McQuain
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "assembler.h"

#define debug

void run(char * inputFile, char * outFile)
{
	#ifdef debug
		printf("--In run--\n");
		printf("	inputFile %s!\n", inputFile);
		printf("	outFile %s!\n", outFile);
	#endif

	FILE *fp;
	fp = fopen(inputFile,"r");

	if (fp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", inputFile);
  		exit(1);
	}
/*
	int regs[32];
	Symbol syms[128];	
	
	int j = 0;
	for(j = 0; j < sizeof(regs)/sizeof(regs[0]); j++){
		regs[j] = 0;
		//printf("#%d: %lu\n",j,regs[j]);	
	}

	

	char text[128][128];
	int textI = 0;
	int textUsage = 0;
	//char sym[128][128];
	int symI = 0;
	int symUsage = 0;

	char tmp[128] = "";
	//0 if in the text portion, 1 if in the data section
	int TorDselect = -1;
	//sstrcpy(text[0],"");
	while(fgets(tmp,128,fp) != NULL){
		char line[128];
		memset(line,'\0',32);
		strcpy(line,tmp);
		puts(line);
		if(firstCharComment(line) == 0){
			continue;
		}
		if(line[0] == '#' || line[0] == '\n' || line == "" || line == NULL){
			continue;
		}
		if(strncmp(line,".text",5) == 0){
			TorDselect = 0;
			printf("TEXT\n");
		}
		else if(strncmp(line,".data",5) == 0){
                        TorDselect = 1;
                        printf("DATA\n");
                }
		else if(TorDselect == 0){
			if(textI < sizeof(text)/sizeof(text[0])){
				//take out whitespace of line  
				char key[] = ":";
				int i;
				strcpy(line,cleanStr(line));
				i = strcspn (line,key);
				if(!(i < strlen(line))){
					strcpy(text[textI],line);
					textI++;
					textUsage++;
				}
				else{
					if(symI < sizeof(syms)/sizeof(syms[0])){	
						char tmp[128];
						memset(tmp,'\0',128);		
						memmove(tmp,line,i);
						strcpy(syms[symI].name,tmp);
						syms[symI].index = textI;	
						syms[symI].TorD = 0;		
						symI++;
						symUsage++;
					}
					else{
						//reallocate
						continue;
					}
				}
			}
			else
				//reallocate
				continue;
		}
		else if(TorDselect == 1){
			
			if(symI < sizeof(syms)/sizeof(syms[0])){
				//take out whitespace of line  
				char tmp[128];
				strcpy(tmp,removeComment(line));
				puts(tmp);
				//strcpy(sym[symI],cleanStr(line));
				//textI++;
				//textUsage++;
				char key[] = ":";
				int i;
				i = strcspn (tmp,key);
				char dataName[32];
				//strncat(result, tmp, i);
				memset(dataName,'\0',32);		
				memmove(dataName,tmp,i);		
				char type[32];
				memset(type,'\0',32);	
				
				//strcpy(sym[symI],result);
				//remove this
				//symI++;
				//symUsage++;
				//if(
			}
		}
		
		memset(tmp,'\0',128);
	}

	printf("PRINT TEXT----------------------------\n");
	int i;
	for(i = 0; i < textUsage; i++){ //sizeof(text)/sizeof(text[0])
		printf("#%d: %s\n",i,text[i]);
		//puts(text[i]);
	}
	printf("PRINT DATA----------------------------\n");
	for(i = 0; i < symUsage; i++){ //sizeof(text)/sizeof(text[0])
		printf("#%d: %s\n",i,syms[i].name);
		//puts(text[i]);
	}
	
	//executeCommands(regs, text, textUsage);	

	printf("PRINT REGS----------------------------\n");
	for(j = 0; j < sizeof(regs)/sizeof(regs[0]); j++){
		//regs[j] = 0;
		//printf("#%d: %d\n",j,regs[j]);	
	}
	
	//printf("register# %d\n",getRegNum("$sp"));

	//printBinary(regs, text, textUsage, outFile);

/**
    int i;
  char buffer [33];clear
  printf ("Enter a number: ");
  scanf ("%d",&i);
  printf ("Entered number: %d\n", i);
  sprintf(buffer,"%x",i);
  printf ("hex: %s\n",buffer);
  printf ("hexadecimal: %x\n",i);
  return 0;
*/

	fclose(fp);

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