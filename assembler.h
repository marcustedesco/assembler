#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum Type {ADD, SUB};

struct Instruc {
	enum Type type;
	char* command;
}; 

int32_t reg[32];

void run (char * inputFile, char * outFile);
void run_symbol (char * inputFile, char * outFile);
void run_list (char * inputFile, char * outFile);
char * stripExtra(char * inputFile);
void printFile(char * filename);
int instrucCountAndFile(char * filename);
int isInstruc(char * line);
void fillInstruc(struct Instruc *list);
char * getInstrucBinary(char * line);
int getRegNum(char* reg);
char * intToBinChar(int num, int length);
/*char* cleanStr(char line[]);
char * removeComment(char line[]);
int getRegNum(char reg[]);
void executeCommands(int *reg, char commands[128][128], int usage);
void printBinary(int *reg, char commands[128][128], int usage, char * outFile);
char * intToBinChar(int num, int length);
char * compareBin(char first[], char second[], int instruc);*/

#endif
