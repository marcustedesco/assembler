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
	char * line;
};

struct Label {
	char * label;
	int location;
	//1 if a text label, 0 if a data label
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
void fillInstrucList(struct Instruc list[]);
void fillLabelList(char * filename, struct Label list[]);
void fillDataLines(char * filename, struct DataBinaryLine data[]);
int getLabelIndex(char * label, struct Label list[], int numLabels);
char * getInstrucBinary(char * line, struct Label list[], int numLabels);
void instrucToFile(char * inFile, char * outFile, struct Label list[], int numLabels, struct DataBinaryLine data[], int numDataLines);
void listToFile(char * outFile, struct Label list[], int numLabels, struct DataBinaryLine data[], int numDataLines, struct Instruc instrucs[], int numInstruc);
void symbolsToFile(char * outFile, struct Label list[], int numLabels);
char * reverseStr(char * str);
int execInstruc(char * line, int current);
int getRegNum(char* reg);
char * intToBinChar(int num, int length);

#endif
