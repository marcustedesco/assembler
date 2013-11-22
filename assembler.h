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

struct DataBinaryLine {
	char line[32];
};

//struct Instruc * myInstruc; 

int32_t reg[32];

//this is a test
void convertBaseVersion(char input, int base, char *output, int digits);

void run (char * inputFile, char * outFile);
void run_symbol (char * inputFile, char * outFile);
void run_list (char * inputFile, char * outFile);
char * stripExtra(char * inputFile);
char * cleanStr(char * line);
char * removeComment(char * line);
void printFile(char * filename);
int instrucCountAndFile(char * filename);
int isInstruc(char * line);
void fillInstrucList(struct Instruc list[]);//struct Instruc *list);
char * getInstrucBinary(char * line);
int execInstruc(char * line, int current);
int getRegNum(char* reg);
char * intToBinChar(int num, int length);

#endif
