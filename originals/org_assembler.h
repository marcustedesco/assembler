#ifndef ORG_ASSEMBLER_H
#define ORG_ASSEMBLER_H
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char name[128];
	int index;
	//0 if in text array, 1 if in data array
	int TorD;
} Symbol;

void run (char * inputFile, char * outFile);
char* cleanStr(char line[]);
char * removeComment(char line[]);
int getRegNum(char reg[]);
void executeCommands(int *reg, char commands[128][128], int usage);
void printBinary(int *reg, char commands[128][128], int usage, char * outFile);
char * intToBinChar(int num, int length);
char * compareBin(char first[], char second[], int instruc);

#endif
