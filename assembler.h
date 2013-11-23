#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

struct Instruc {
	char * command;
}; 

struct DataBinaryLine {
	char line[32];
};

struct Label {
	char * label;
	//1 if a text label, 0 if a data label
	int location;
	int TorD;
};

int32_t reg[32];

void run (char * inputFile, char * outFile);
void run_symbol (char * inputFile, char * outFile);
void run_list (char * inputFile, char * outFile);
char * stripExtra(char * inputFile);
char * cleanStr(char * line);
char * removeComment(char * line);
void printFile(char * filename);
int instrucCountAndFile(char * filename);
int labelCount(char * filename);
int sizeOfDataBinary(char * filename);
int isInstruc(char * line);
void convertAsciiToBin(char ascii, char *output, int digits);
void fillInstrucList(struct Instruc list[]);//struct Instruc *list);
void fillLabelList(char * filename, struct Label list[]);
void fillDataLines(char * filename, struct DataBinaryLine data[]);
int getLabelIndex(char * label, struct Label list[]);
char * getInstrucBinary(char * line, struct Label list[]);
void binaryToFile(char * inFile, char * outFile, struct Label list[]);
int execInstruc(char * line, int current);
int getRegNum(char* reg);
char * intToBinChar(int num, int length);

#endif
