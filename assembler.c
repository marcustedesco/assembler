/* MIPS Assembler program */

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


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "assembler.h"

void run(char * inputFile, char * outFile)
{
	FILE *fp;
	fp = fopen(inputFile,"r");

	if (fp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", inputFile);
  		exit(1);
	}

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
	for(i = 0; i < textUsage/*sizeof(text)/sizeof(text[0])*/; i++){
		printf("#%d: %s\n",i,text[i]);
		//puts(text[i]);
	}
	printf("PRINT DATA----------------------------\n");
	for(i = 0; i < symUsage/*sizeof(text)/sizeof(text[0])*/; i++){
		printf("#%d: %s\n",i,syms[i].name);
		//puts(text[i]);
	}
	
	executeCommands(regs, text, textUsage);	

	printf("PRINT REGS----------------------------\n");
	for(j = 0; j < sizeof(regs)/sizeof(regs[0]); j++){
		//regs[j] = 0;
		//printf("#%d: %d\n",j,regs[j]);	
	}
	
	//printf("register# %d\n",getRegNum("$sp"));

	printBinary(regs, text, textUsage, outFile);

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

void executeCommands(int *reg, char commands[128][128], int usage){
	int i = 0;
	for(i = 0; i < usage; i++){
		char command[128];
		memset(command,'\0',128);		
		memmove(command,commands[i],128);
		printf("command: %s\n",command);

		char key[] = "~";
		char * piece;
		
		piece = strtok (command,key);
/*		
		int i;
		i = strcspn (command,key);
		char tmp[128];
		memset(tmp,'\0',128);		
		memmove(tmp,command,i);
*/
		if(strcmp(piece,"lw") == 0){
			printf("load word\n");
			piece = strtok (NULL, key);
			printf ("next piece: %s\n",piece);
			
		}
		else if(strcmp(piece,"sw") == 0){
			printf("store word\n");
		}
		else if(strcmp(piece,"lui") == 0){
			printf("load immediate upper half\n");
		}
		else if(strcmp(piece,"la") == 0){
			printf("load address\n");
		}
		else if(strcmp(piece,"li") == 0){
			printf("load immediate\n");
		}
		else if(strcmp(piece,"add") == 0){
			printf("add\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);

			//take out 1, test to see if works
			reg[rd] = reg[rs] + reg[rt] + 1;
			
		}
		else if(strcmp(piece,"sub") == 0){
			printf("subtract\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);

			//take out 1, test to see if works
			reg[rd] = reg[rs] - reg[rt] - 1;
		}
		else if(strcmp(piece,"addi") == 0){
			printf("add immediate signed\n");
		}
		else if(strcmp(piece,"addiu") == 0){
			printf("add immediate unsigned\n");
		}
		else if(strcmp(piece,"or") == 0){
			printf("or\n");
			
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);
		}
		else if(strcmp(piece,"and") == 0){
			printf("and\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);
			
			printf("rs to got to binary: %i\n",rs);
			printf("rt to got to binary: %i\n",rt);
			char rsBin[16];
			strcpy(rsBin,intToBinChar(rs,16));
			int j = 0;
			printf("LEGNTH: %d\n",strlen(rsBin));
			for(j=strlen(rsBin); j>=0;j--)
        			printf("%c",rsBin[j]);

			
			char rtBin[16];
			strcpy(rtBin,intToBinChar(rt,16));
			printf("LEGNTH: %d\n",strlen(rtBin));
			for(j=strlen(rtBin); j>=0;j--)
        			printf("%c",rtBin[j]);
			

			char result[16];
			strcpy(result,compareBin(rsBin, rtBin, 1));
			
			for(j=strlen(result); j>=0;j--)
        			printf("%c",result[j]);
			
		}
		else if(strcmp(piece,"ori") == 0){
			printf("or immediate\n");
		}
		else if(strcmp(piece,"andi") == 0){
			printf("and immediate\n");
		}
		else if(strcmp(piece,"slt") == 0){
			printf("set register\n");
		}
		else if(strcmp(piece,"slti") == 0){
			printf("set register immediate\n");
		}
		else if(strcmp(piece,"sll") == 0){
			printf("logical shift left\n");
		}
		else if(strcmp(piece,"srl") == 0){
			printf("logical shift right\n");
		}
		else if(strcmp(piece,"nop") == 0){
			printf("no operation\n");
			continue;
		}
		else if(strcmp(piece,"beq") == 0){
			printf("branch equals\n");
		}
		else if(strcmp(piece,"bne") == 0){
			printf("branch not equals\n");
		}
		else if(strcmp(piece,"bltz") == 0){
			printf("branch less than 0\n");
		}
		else if(strcmp(piece,"blez") == 0){
			printf("branch less than equals 0\n");
		}
		else if(strcmp(piece,"blt") == 0){
			printf("branch than rt\n");
		}
		else if(strcmp(piece,"ble") == 0){
			printf("branch less than equals rt\n");
		}
		else if(strcmp(piece,"j") == 0){
			printf("jump\n");
		}
		else if(strcmp(piece,"jr") == 0){
			printf("jump rs\n");
		}
		else if(strcmp(piece,"jal") == 0){
			printf("jump target\n");
		}
		else if(strcmp(piece,"syscall") == 0){
			printf("system call\n");
		}
		else{
			printf("Command not found.\n");		
		}
	}

	
	//return reg;
}

//or: instruc = 0 
//and: instruc = 1
char * compareBin(char first[], char second[], int instruc){
	char *result[16];
	memset(result,'\0',16);		
	puts("~~~~~~~~~~~~~~~~~~~~~COMPARE~~~~~~~~~~~~~~~~~~~~~~\n");
	int j = 0; 	
	//for(j=0; first[j] != 0;j--)
        //	printf("%c",first[j]);
	puts("\nCOMPARE FIST\n");
	//for(j=strlen(first); j>=0;j--)
        //	printf("%c",first[j]);
	if(instruc == 0){
		//do something
	}
	else if(instruc == 1){
        	printf("LEGNTH: %d\n",strlen(first));
		//printf("LEGNTH: %d\n",strlen(second));
		int i = 0;
		/*for(i = 0; i < strlen(first); i++){
			//printf("%c",first[i]);
			puts("IN THE COMPARE LOOP");
			if(first[i] == '1' && second[i] == '1')
				result[i] = '1';
			else
				result[i] = '0';
		}*/
	}
	return result;
}

char * intToBinChar(int num, int length){

   int rem,i,b,j,quotient;
   char binaryNumber[length];

   //memset(binaryNumber, '\0',16);

   for(i = 0; i < length; i++){

        if(num == 0)
           binaryNumber[i]='0';
        else{

           rem = num % 2;

           if(rem == 0)
                  binaryNumber[i]='0';
           else
                  binaryNumber[i]='1';
          num=num/2;
        }


   }

	puts("\nINTtoBIN\n");
    for(j=length-1; j>=0;j--)
        printf("%c",binaryNumber[j]);

    puts("\n");
    return binaryNumber;
}

/*********************************************************
  **********************PRINT*****************************
  ********************************************************
**/
void printBinary(int *reg, char commands[128][128], int usage, char * outFile){

	FILE *ofp;
	ofp = fopen(outFile,"w");

	if (ofp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", outFile);
  		exit(1);
	} 

	fprintf(ofp,"TEST\n");
	
	int i = 0;
	for(i = 0; i < usage; i++){
		char command[128];
		memset(command,'\0',128);		
		memmove(command,commands[i],128);
		printf("command: %s\n",command);

		char key[] = "~";
		char * piece;
		
		piece = strtok (command,key);

		if(strcmp(piece,"lw") == 0){
			printf("load word\n");
			piece = strtok (NULL, key);
			printf ("next piece: %s\n",piece);
			fprintf(ofp, "load word");
			
		}
		else if(strcmp(piece,"sw") == 0){
			printf("store word\n");
		}
		else if(strcmp(piece,"lui") == 0){
			printf("load immediate upper half\n");
		}
		else if(strcmp(piece,"la") == 0){
			printf("load address\n");
		}
		else if(strcmp(piece,"li") == 0){
			printf("load immediate\n");
		}
		else if(strcmp(piece,"add") == 0){
			printf("add\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);

			//take out 1, test to see if works
			reg[rd] = reg[rs] + reg[rt] + 1;

			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "%i",rt);
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "00000");
			fprintf(ofp, "100000");
			fprintf(ofp, "\n");
			
		}
		else if(strcmp(piece,"sub") == 0){
			printf("subtract\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);

			//take out 1, test to see if works
			reg[rd] = reg[rs] - reg[rt] - 1;

			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "%i",rt);
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "00000");
			fprintf(ofp, "100010");
			fprintf(ofp, "\n");
		}
		else if(strcmp(piece,"addi") == 0){
			printf("add immediate signed\n");
		}
		else if(strcmp(piece,"addiu") == 0){
			printf("add immediate unsigned\n");
		}
		else if(strcmp(piece,"or") == 0){
			printf("or\n");
			
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);

			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "%i",rt);
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "00000");
			fprintf(ofp, "100101");
			fprintf(ofp, "\n");
		}
		else if(strcmp(piece,"and") == 0){
			printf("and\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);
			
			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "%i",rt);
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "00000");
			fprintf(ofp, "100100");
			fprintf(ofp, "\n");
			
		}
		else if(strcmp(piece,"ori") == 0){
			printf("or immediate\n");
		}
		else if(strcmp(piece,"andi") == 0){
			printf("and immediate\n");
		}
		else if(strcmp(piece,"slt") == 0){
			printf("set register\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);
			
			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "%i",rt);
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "00000");
			fprintf(ofp, "101010");
			fprintf(ofp, "\n");
		}
		else if(strcmp(piece,"slti") == 0){
			printf("set register immediate\n");
		}
		else if(strcmp(piece,"sll") == 0){
			printf("logical shift left\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//sa
			piece = strtok (NULL, key);
			int sa; 
			sa = getRegNum(piece);
			
			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "%i",sa);
			fprintf(ofp, "000000");
			fprintf(ofp, "\n");
		}
		else if(strcmp(piece,"srl") == 0){
			printf("logical shift right\n");
			printf("logical shift left\n");
			//rd
			piece = strtok (NULL, key);
			int rd; 
			rd = getRegNum(piece);
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//sa
			piece = strtok (NULL, key);
			int sa; 
			sa = getRegNum(piece);
			
			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			fprintf(ofp, "00000");
			fprintf(ofp, "%i",rd);
			fprintf(ofp, "%i",sa);
			fprintf(ofp, "000010");
			fprintf(ofp, "\n");
		}
		else if(strcmp(piece,"nop") == 0){
			printf("no operation\n");
			fprintf("00000000000000000000000000000000");
			continue;
		}
		else if(strcmp(piece,"beq") == 0){
			printf("branch equals\n");
			//rs
			piece = strtok (NULL, key);
			int rs; 
			rs = getRegNum(piece);
			//rt
			piece = strtok (NULL, key);
			int rt; 
			rt = getRegNum(piece);
			//offset
			piece = strtok (NULL, key);
			//int offset; 
			//offset = getRegNum(piece);
			
			fprintf(ofp, "00100");
			fprintf(ofp, "%i",rs); //intToBinChar(rs,5));
			//fprintf(ofp, "00000");
			fprintf(ofp, "%i",rt);
			fprintf(ofp, "%s",offset);
			//fprintf(ofp, "000010");
			fprintf(ofp, "\n");
		}
		else if(strcmp(piece,"bne") == 0){
			printf("branch not equals\n");
		}
		else if(strcmp(piece,"bltz") == 0){
			printf("branch less than 0\n");
		}
		else if(strcmp(piece,"blez") == 0){
			printf("branch less than equals 0\n");
		}
		else if(strcmp(piece,"blt") == 0){
			printf("branch than rt\n");
		}
		else if(strcmp(piece,"ble") == 0){
			printf("branch less than equals rt\n");
		}
		else if(strcmp(piece,"j") == 0){
			printf("jump\n");
		}
		else if(strcmp(piece,"jr") == 0){
			printf("jump rs\n");
		}
		else if(strcmp(piece,"jal") == 0){
			printf("jump target\n");
		}
		else if(strcmp(piece,"syscall") == 0){
			printf("system call\n");
		}
		else{
			printf("Command not found.\n");		
		}
	}

	fclose(ofp);
}

//0 if first character is #, 1 if not)
int firstCharComment(char line[]){
	int i = 0;
	
	for(i = 0; i < strlen(line); i++){
		if(line[i] == '\n' || line[i] == '\t')
			continue;
		else if(line[i] == '#')
			return 0;
		else
			return 1;
	}

	return 0;

}

char* cleanStr(char line[]){
	strcpy(line,removeComment(line));
	char delims[] = " ,\n\t";
	char * pch;
	char result[128];
	memset(result,'\0',128);
	pch = strtok (line, delims);
	while (pch != NULL)
	{
	    //printf ("~~~~~~~~~%s\n",pch);
	    strcat(result,pch);
	    strcat(result,"~");
	    pch = strtok (NULL, delims);
	}

	return result;
}

char * removeComment(char line[]){
	char key[] = "#";
  	int i;
  	i = strcspn (line,key);
	char temp[128];
	memset(temp,'\0',128);
	//strncat(temp, line, i); 
	memmove(temp,line,i);	
	return temp;
}

int getRegNum(char reg[]){
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

}
