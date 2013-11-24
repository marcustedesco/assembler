/* MIPS Assembler Program 
   Marcus Tedesco
   #905373051
   Professor McQuain
*/

#include "assembler.h"

//#define debug
//#define displayI

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

	struct Instruc myInstruc[numInstruc];

	int j;
	for(j = 0; j < sizeof(myInstruc)/sizeof(struct Instruc); j++){
		myInstruc[j].command = malloc(sizeof(char)*256);
		myInstruc[j].command = "\0";	
	}

    fillInstrucList(myInstruc);

    int numLabels = labelCount(stripedFile);
    int numDataLines = sizeOfDataBinary(stripedFile);

    //printf("number of label 32 bit arrays to allocate: %d\n", numLabels);

    struct Label myLabels[numLabels];

	for(j = 0; j < sizeof(myLabels)/sizeof(struct Label); j++){
		myLabels[j].label = malloc(sizeof(char)*128);
		myLabels[j].label = "\0";	
	}

	struct DataBinaryLine dataLines[numDataLines];

	for(j = 0; j < sizeof(dataLines)/sizeof(struct DataBinaryLine); j++){
		dataLines[j].line = malloc(sizeof(char)*32);
		strcpy(dataLines[j].line, "\0");
	}

	fillLabelList(stripedFile, myLabels);
	fillDataLines(stripedFile, dataLines);

	#ifdef debug
	int i;
		for(i = 0; i < sizeof(myLabels)/sizeof(struct Label); i++){
			printf("myLabels[%d] label: %s\n", i, myLabels[i].label);
			printf("myLabels[%d] location: %d\n", i, myLabels[i].location);
			printf("myLabels[%d] TorD: %d\n", i, myLabels[i].TorD);
		}

		for(j = 0; j < sizeof(dataLines)/sizeof(struct DataBinaryLine); j++){
			printf("dataLine[%d]: %s\n", j, dataLines[j].line);	
		}
	#endif

	instrucToFile(stripedFile, outFile, myLabels, numLabels, dataLines, numDataLines);
    
    //do the same thing for labels
	//int numLabels = labelCount(stripedFile);
	//declare struct Label myLabels[numLabels];
	//initalize labels
	//fillLabelList(myLabels);
	//loop through myInstruc with executeInstruc()
	//binaryToFile(outFile, myLabels);

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

	#ifdef debug
		printFile(inputFile);
	#endif

	char * stripedFile = stripExtra(inputFile);
	
	#ifdef debug
		printFile(stripedFile);
	#endif

	int numInstruc = instrucCountAndFile(stripedFile);

	struct Instruc myInstruc[numInstruc];

	int j;
	for(j = 0; j < sizeof(myInstruc)/sizeof(struct Instruc); j++){
		myInstruc[j].command = malloc(sizeof(char)*256);
		myInstruc[j].command = "\0";	
	}

    fillInstrucList(myInstruc);

    int numLabels = labelCount(stripedFile);
    //int numDataLines = sizeOfDataBinary(stripedFile);

    //printf("number of label 32 bit arrays to allocate: %d\n", numLabels);

    struct Label myLabels[numLabels];

	for(j = 0; j < sizeof(myLabels)/sizeof(struct Label); j++){
		myLabels[j].label = malloc(sizeof(char)*128);
		myLabels[j].label = "\0";	
	}

	fillLabelList(stripedFile, myLabels);

	#ifdef debug
		int i;
		for(i = 0; i < sizeof(myLabels)/sizeof(struct Label); i++){
			printf("myLabels[%d] label: %s\n", i, myLabels[i].label);
			printf("myLabels[%d] location: %d\n", i, myLabels[i].location);
			printf("myLabels[%d] TorD: %d\n", i, myLabels[i].TorD);
		}
	#endif

	symbolsToFile(outFile, myLabels, numLabels);
}

void run_list (char * inputFile, char * outFile){
	#ifdef debug
		printf("--In run_list--\n");
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

	struct Instruc myInstruc[numInstruc];

	int j;
	for(j = 0; j < sizeof(myInstruc)/sizeof(struct Instruc); j++){
		myInstruc[j].command = malloc(sizeof(char)*256);
		myInstruc[j].command = "\0";	
	}

    fillInstrucList(myInstruc);
    #ifdef debug
	    for(j = 0; j < sizeof(myInstruc)/sizeof(struct Instruc); j++){
			printf("myInstruc[%d]: %s", j,  myInstruc[j].command);	
		}
	#endif

    int numLabels = labelCount(stripedFile);
    int numDataLines = sizeOfDataBinary(stripedFile);

    struct Label myLabels[numLabels];

	for(j = 0; j < sizeof(myLabels)/sizeof(struct Label); j++){
		myLabels[j].label = malloc(sizeof(char)*128);
		myLabels[j].label = "\0";	
	}

	struct DataBinaryLine dataLines[numDataLines];

	for(j = 0; j < sizeof(dataLines)/sizeof(struct DataBinaryLine); j++){
		dataLines[j].line = malloc(sizeof(char)*32);
		strcpy(dataLines[j].line, "\0");
	}

	fillLabelList(stripedFile, myLabels);
	fillDataLines(stripedFile, dataLines);

	#ifdef debug
		int i;
		for(i = 0; i < sizeof(myLabels)/sizeof(struct Label); i++){
			printf("myLabels[%d] label: %s\n", i, myLabels[i].label);
			printf("myLabels[%d] location: %d\n", i, myLabels[i].location);
			printf("myLabels[%d] TorD: %d\n", i, myLabels[i].TorD);
		}

		for(j = 0; j < sizeof(dataLines)/sizeof(struct DataBinaryLine); j++){
			printf("dataLine[%d]: %s\n", j, dataLines[j].line);	
		}
	#endif

	listToFile(outFile, myLabels, numLabels, dataLines, numDataLines, myInstruc, numInstruc);
}

void convertAsciiToBin(char ascii, char *output, int digits) { 
	int i, remainder; 
	char digitsArray[2] = "01";

	for (i = digits; i > 0; i--) { 
		remainder = ascii % 2; 
		ascii = ascii / 2; 
		output[i - 1] = digitsArray[remainder]; 
	} 

	output[digits] = '\0'; 
}

/* returns intermediate filename */
char * stripExtra(char * inputFile){
	#ifdef debug
		printf("--In stripExtra--\n");
		printf("	inputFile %s!\n", inputFile);
	#endif


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

		char keys[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.";
		int j = strcspn (line,keys);

		if(strcmp(line,"\n") != 0 && j < strcspn(line,"#")){

		  line = cleanStr(line); 

		  //add the pseudo instructions if blt or ble
		  if(strstr(line,"blt") != NULL  && strstr(line,"bltz") == NULL){
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

				char tempLine[256];
				strcpy(tempLine, "slt~$at~");
				strcat(tempLine, two);
				strcat(tempLine, "~");
				strcat(tempLine, three);
				strcat(tempLine, "\0");

				fprintf(ofp, "%s\n", tempLine);

				char tempLine2[256];
				strcpy(tempLine2, "bne~$at~$zero~");
				strcat(tempLine2, four);
				strcat(tempLine, "\0");

				fprintf(ofp, "%s\n", tempLine2);

		  }else if(strstr(line,"ble") != NULL && strstr(line,"blez") == NULL){
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

				char tempLine[256];
				strcpy(tempLine, "slt~$at~");
				strcat(tempLine, three);
				strcat(tempLine, "~");
				strcat(tempLine, two);
				strcat(tempLine, "\0");

				fprintf(ofp, "%s\n", tempLine);

				char tempLine2[256];
				strcpy(tempLine2, "beq~$at~$zero~");
				strcat(tempLine2, four);
				strcat(tempLine, "\0");

				fprintf(ofp, "%s\n", tempLine2);

		  }else{
		  	fprintf(ofp, "%s\n", line);
		  }
		}
	}

	printf("\n");

	fclose(ifp);
	fclose(ofp);

	return intermediate;
}

char * cleanStr(char * line){
	#ifdef debug
		printf("--In cleanStr--\n");
		printf("	line %s!\n", line);
	#endif
	line = removeComment(line);
	char delims[] = " ,\n\t";
	char * pch;
	char result[128];
	pch = strtok (line, delims);
	while (pch != NULL)
	{
	    strcat(result,pch);
	    strcat(result,"~");
	    pch = strtok (NULL, delims);
	}
	result[strlen(result)-1] = '\0';
	return strdup(result);
}

char * removeComment(char * line){
	char key[] = "#";
  	int i;
  	i = strcspn (line,key);
	char clean[256];
	strncpy(clean,line,i);
	clean[i] = '\0';
	return strdup(clean);
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
	char * intermediate = "instructions.txt";

	ofp = fopen(intermediate, "w+");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", intermediate);
	  exit(1);
	}
	char line[256];
	int count = 0;
	int inText = 1;
	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = malloc(strlen(line));
	    strcat(lineCopy, "\0");
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 0 && isInstruc(line) == 0){
	    	//isInstruc takes a pointer so the value is change on return
	    	fprintf(ofp, "%s", lineCopy);
	    	count++;
	    }
	  }
	}

	fclose(ifp);
	fclose(ofp);

	return count;
}

//should count just the number of myLabels
int labelCount(char * filename){
	#ifdef debug
		printf("--In labelCount--\n");
		printf("	inputFile %s!\n", filename);
	#endif

	FILE *ifp;
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	
	char line[256];
	int count = 0;
	int inText = -1;

	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 0 && isInstruc(line) != 0){
			if(strchr(lineCopy,':') != NULL){
	   		 	count++;
			}
	    }
	    if(inText == 1 && strstr(line,".data") == NULL){
	    	if(strchr(lineCopy,':') != NULL){
	   		 	count++;
			}
	    }
	  }
	}

	fclose(ifp);

	return count;
}

//Calculates the allocation of data section
//Returns the size of DataBinaryLine array
int sizeOfDataBinary(char * filename){
	#ifdef debug
		printf("--In sizeOfDataBinary--\n");
		printf("	inputFile %s!\n", filename);
	#endif

	FILE *ifp;
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	
	char line[256];
	int count = 0;
	int inText = -1;

	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 1){
	    	if(strstr(lineCopy, ".asciiz") != NULL){
	    		char * str;
	    		str = strtok(lineCopy,"\"");
	    		str = strtok(NULL, "\"");
	    	
	    		if((strlen(str)+1)%4 != 0){
	    			count = count + ((strlen(str)+1)/4)+1;
	    		}
	    		else{
	    			count = count + ((strlen(str)+1)/4);
	    		}
	    	}
	    	else if(strstr(lineCopy, ".word") != NULL){
	    		char * str;
	    		str = strtok(lineCopy,"~\n");
	    		str = strtok(NULL, "~\n");
	    		str = strtok(NULL, "~\n");
	    		if(strchr(str,':') != NULL){
	    			char * number;
	    			number = strtok(str,":\n");
	    			number = strtok(NULL,":\n");
	    			count+= atoi(number);
	    		}else{
	    			count++;
	    		}
	    	}
	    }
	  }
	}

	fclose(ifp);

	return count;
}

void instrucToFile(char * inFile, char * outFile, struct Label list[], int numLabels, struct DataBinaryLine data[], int numDataLines){
	#ifdef debug
		printf("--In binaryToFile--\n");
		printf("	outputFile %s!\n", outFile);
	#endif

	FILE *ifp;
	ifp = fopen(inFile,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", inFile);
  		exit(1);
	}

	FILE *ofp;
	
	ofp = fopen(outFile, "w+");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", outFile);
	  exit(1);
	}
	
	char line[256];
	int inText = -1;

	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL){
	  		fprintf(ofp, "\n");
	  		inText = 1;
	  	}
	    if(inText == 0 && isInstruc(line) == 0){
			fprintf(ofp, "%s\n", getInstrucBinary(lineCopy, list, numLabels));
	    }
	  }
	}

	int i;
	for(i = 0; i < numDataLines; i++){
		fprintf(ofp, "%s\n", data[i].line);
	}

	fclose(ifp);
	fclose(ofp);

	return;
}

void listToFile(char * outFile, struct Label list[], int numLabels, struct DataBinaryLine data[], int numDataLines, struct Instruc instrucs[], int numInstruc){
	#ifdef debug
		printf("--In listToFile--\n");
		printf("	outputFile %s!\n", outFile);
	#endif

	FILE *ofp;
	
	ofp = fopen(outFile, "w+");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", outFile);
	  exit(1);
	}
	
	int i;
	for(i = 0; i < numInstruc; i++){
		int j;
		for(j = 0; j < numLabels; j++){
			if(list[j].location == i && list[j].TorD == 1){
				fprintf(ofp, "\t\t\t\t\t\t\t\t\t\t\t\t%s:\n", list[j].label);
			}
		}

		char hex[8];
		sprintf(hex,"%X", (i*4));

		fprintf(ofp, "%s", "0x");
		int k;
		for(k = 0; k < 8-strlen(hex); k++)
			fprintf(ofp, "%c", '0');
		fprintf(ofp, "%s\t", hex);
		fprintf(ofp, "%s\t", getInstrucBinary(strdup(instrucs[i].command), list, numLabels));
		fprintf(ofp, "%s", instrucs[i].command);

	}

	fprintf(ofp, "\n");	

	for(i = 0; i < numDataLines; i++){
		int j;
		for(j = 0; j < numLabels; j++){
			if(list[j].location == i && list[j].TorD == 0){
				fprintf(ofp, "%s:\n", list[j].label);
			}
		}

		char hex[8];
		sprintf(hex,"%X", ((i*4)+8192));

		fprintf(ofp, "%s", "0x");
		int k;
		for(k = 0; k < 8-strlen(hex); k++)
			fprintf(ofp, "%c", '0');
		fprintf(ofp, "%s\t", hex);

		fprintf(ofp, "%s\n", data[i].line);
	}

	fclose(ofp);

	return;
}

void symbolsToFile(char * outFile, struct Label list[], int numLabels){
	#ifdef debug
		printf("--In symbolsToFile--\n");
		printf("	outputFile %s!\n", outFile);
	#endif


	FILE *ofp;
	
	ofp = fopen(outFile, "w+");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", outFile);
	  exit(1);
	}

	fprintf(ofp, "%s\t\t%s\n", "Address", "Symbol");
	fprintf(ofp, "%s\n", "---------------------------");

	int i;
	for(i = 0; i < numLabels; i++){

		int location = getLabelIndex(list[i].label, list, numLabels);
		char hex[8];
		sprintf(hex,"%X", location);
		//printf("Hex array %d is: %s\n", location, hex);
		//printf("size of hex array is: %d\n", strlen(hex));

		fprintf(ofp, "%s", "0x");
		int j;
		for(j = 0; j < 8-strlen(hex); j++)
			fprintf(ofp, "%c", '0');
		fprintf(ofp, "%s\t%s\n", hex, list[i].label);
	}

	fclose(ofp);

	return;
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
			return 1;
			//return 0;
		}
		else if(strcmp(piece,"ble") == 0){
			return 1;
			//return 0;
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

	return -1;
}

//this assumes that the instructions are in their own file of just instructions
void fillInstrucList(struct Instruc list[]){
	#ifdef debug
		printf("--In fillInstrucList--\n");
	#endif

	FILE *ifp;
	char* filename = "instructions.txt";
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	char line[256];
	int index = 0;

	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	  	if(strcmp(line,"\n") != 0){
			list[index].command = strdup(line);	
			strcat(list[index].command, "\0");
	    	index++;
	    }
	  }
	}

	return;
}

void fillLabelList(char * filename, struct Label list[]){
	#ifdef debug
		printf("--In fillLabelList--\n");
		printf("	inputFile %s!\n", filename);
	#endif

	FILE *ifp;
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	
	char line[256];
	int index = 0;
	int inText = -1;
	int instCount = 0;
	int dataCount = 0;

	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	  	if(inText == 0 && isInstruc(line) == 0){
	  		instCount++;
	  	}
	    else if(inText == 0){
			//for the fillLabel(), keep track of the line number to know the address
			if(strchr(lineCopy,':') != NULL){
	   		 	list[index].label = strtok(lineCopy,":");
	   		 	//printf("Text label: %s\n", list[index].label);
	   		 	list[index].TorD = 1;
	   		 	list[index].location = instCount;
	   		 	index++;
			}
	    }
	    if(inText == 1 && strstr(line,".data") == NULL){
	    	char * lineCopy2 = strdup(lineCopy);
	    	list[index].label = strtok(lineCopy,":");
   		 	//printf("Data label: %s\n", list[index].label);
   		 	list[index].TorD = 0;
   		 	list[index].location = dataCount;
   		 	index++;

   		 	//printf("LineCOPY2: %s\n", lineCopy2);

	    	if(strstr(lineCopy2, ".asciiz") != NULL){
	    		char * str;
	    		str = strtok(lineCopy2,"\"");
	    		str = strtok(NULL, "\"");

	    		if((strlen(str)+1)%4 != 0){
	    			dataCount = dataCount + ((strlen(str)+1)/4)+1;
	    			//printf("(/4!=0)added %d to count\n", ((strlen(str)+1)/4)+1);
	    		}
	    		else{
	    			dataCount = dataCount + ((strlen(str)+1)/4);
	    			//printf("(/4==0)added %d to count\n", ((strlen(str)+1)/4));
	    		}
	    	}
	    	else if(strstr(lineCopy2, ".word") != NULL){
	    		char * str;
	    		str = strtok(lineCopy2,"~\n");
	    		str = strtok(NULL, "~\n");
	    		str = strtok(NULL, "~\n");
	    		//printf("(word) token string is: %s\n", str);
	    		if(strchr(str,':') != NULL){
	    			char * number;
	    			number = strtok(str,":\n");
	    			number = strtok(NULL,":\n");
	    			//printf("(word) token number is: %s\n", str);
	    			//printf("number to add is: %d\n", atoi(number));
	    			dataCount+= atoi(number);
	    		}else{
	    			dataCount++;
	    			//printf("count increased by 1\n");
	    		}
	    	}
	    }
	  }
	}

	fclose(ifp);

	return;
}

void fillDataLines(char * filename, struct DataBinaryLine data[]) {
	
	#ifdef debug
		printf("--In fillDataLines--\n");
		printf("	inputFile %s!\n", filename);
	#endif

	FILE *ifp;
	ifp = fopen(filename,"r");

	if (ifp == NULL) {
  		fprintf(stderr, "Can't open input file %s!\n", filename);
  		exit(1);
	}

	
	char line[256];
	int inText = -1;
	int byteCount = 0;
	int lineIndex = 0;
	char byte[8];
	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = strdup(line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 1 && strstr(line,".data") == NULL){
	    	//use the reverse loop from int to binary and reverse the string in groups of 4 chars, add " "
	    	if(strstr(lineCopy, ".asciiz") != NULL){
	    		char * quote = malloc(sizeof(char)*256);
	    		char * reverseQuote = malloc(sizeof(char)*256);
	    		strcpy(reverseQuote,"\0");
	    		quote = strtok(lineCopy,"\"");
	    		quote = strtok(NULL, "\"");
	    		strcat(quote,"\0");

	    		int k;
	    		int count = 0;
	    		char tempo[5];
	    		for(k = 0; k < strlen(quote); k++){
		    		if(count == 0){
			    		strcpy(tempo, "\0");
			    		//fix this
			    		if(k+4 >= strlen(quote))
			    			strncpy(tempo,quote+k,strlen(quote)-(k));
			    		else
			    			strncpy(tempo,quote+k,4);
			    		tempo[4] = '\0';
			    		char tempo2[4];
			    		tempo2[0] = '\0';
			    		strncpy(tempo2,reverseStr(tempo),4);
			    		tempo2[4] = '\0';
			    		strcat(reverseQuote,tempo2);
		    		}
		    		count++;
		    		if(count > 3)
		    			count = 0;
		    	}
		   
	    		int z;
	    		char * temp = malloc(sizeof(char)*32);
	    		strcpy(temp,"\0");
	    		for(z = 0; z < strlen(reverseQuote); z++){
	    			
	    			
	    			if(byteCount > 3){
	    				byteCount = 0;
	    				strcpy(data[lineIndex].line, strdup(temp));
	    				strcat(data[lineIndex].line,"\0");
	    				strcpy(temp,"\0");
	    				lineIndex++;
	    			}

	    			int ascii = reverseQuote[z];
	    			if(reverseQuote[z] != '\0' && reverseQuote[z] != '\n' && reverseQuote[z] != '\t' && ascii != 5){
		    			if(reverseQuote[z] != '~')
		    				convertAsciiToBin(reverseQuote[z], byte, 8);
		    			else
		    				convertAsciiToBin(' ', byte, 8);
		    			strcat(temp,strdup(byte));
		    			byte[0] = '\0';

	    				byteCount++;
	    			}
	    		}
	    	}else if(strstr(lineCopy, ".word") != NULL){
	    		char * str;
	    		str = strtok(lineCopy,"~\n");
	    		str = strtok(NULL, "~\n");
	    		str = strtok(NULL, "~\n");
	    		if(strchr(str,':') != NULL){
	    			char * number;
	    			number = strtok(str,":\n");
	    			number = strtok(NULL,":\n");
					int size = atoi(number);

					int i;
					for(i = 0; i < size; i++){
						strcpy(data[i+lineIndex].line, strdup(intToBinChar(atoi(str),32)));
						strcat(data[i+lineIndex].line, "\0");
					}
					lineIndex+=size;

	    		}else if(strchr(str,':') != NULL){
	    			//do the stuff for commas
	    		}else{
	    			strcpy(data[lineIndex].line, strdup(intToBinChar(atoi(str),32)));
					strcat(data[lineIndex].line, "\0");

					lineIndex++;	    			
	    		}
	    	}
	    }
	  }
	}

	fclose(ifp);
	
	#ifdef debug
	int j;
		for(j = 0; j < numDataLines; j++){
			printf("in Fill dataLine[%d]: %s\n", j, data[j].line);	
		}
	#endif

	return;
}

char * reverseStr(char * str){
	char temp[strlen(str)+1];
	int i;
	for(i = 0; i < strlen(str); i++){
		temp[i] = str[strlen(str)-1-i];
	}

	temp[i+1] = '\0';

	return strdup(temp);
}

char * getInstrucBinary(char * line, struct Label list[], int numLabels){
	#ifdef debug
	printf("-----------------------------------------------\n");
		printf("--In getInstrucBinary--\n");
		printf("	instruc to convert to binary: %s!\n", line);
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
		char * offset = strtok(three,"()");
		char * rs = strtok(NULL,"()");

		strcpy(binary,"100011");
		//rs
		strcat(binary,intToBinChar(getRegNum(rs),5));	
		//rt	
		strcat(binary,intToBinChar(getRegNum(two),5));
		//offset
		strcat(binary,intToBinChar(atoi(offset),16));	
		#ifdef displayI
			strcat(binary,"\tlw");
		#endif
	}
	else if(strcmp(one,"sw") == 0){
		char * offset = strtok(three,"()");
		char * rs = strtok(NULL,"()");

		strcpy(binary,"101011");
		//rs
		strcat(binary,intToBinChar(getRegNum(rs),5));	
		//rt	
		strcat(binary,intToBinChar(getRegNum(two),5));
		//offset
		strcat(binary,intToBinChar(atoi(offset),16));
		#ifdef displayI
			strcat(binary,"\tsw");
		#endif
	}
	else if(strcmp(one,"la") == 0){
		strcpy(binary,"001000");
		//$zero
		strcat(binary,intToBinChar(getRegNum("$zero"),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary, intToBinChar(getLabelIndex(three, list, numLabels),16));
		#ifdef displayI
			strcat(binary,"\tla");
		#endif
	}
	else if(strcmp(one,"li") == 0){
		strcpy(binary,"001001");
		//$zero
		strcat(binary,intToBinChar(getRegNum("$zero"),5));
		//rd
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,intToBinChar(atoi(three),16));
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
		strcat(binary, intToBinChar(getLabelIndex(four, list, numLabels),16));
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
		//this is wrong. must be shifted
		strcat(binary, intToBinChar(getLabelIndex(four, list, numLabels),16));
		#ifdef displayI
			strcat(binary,"\tbne");
		#endif
	}
	else if(strcmp(one,"bltz") == 0){
		strcpy(binary,"000001");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary, intToBinChar(getLabelIndex(three, list, numLabels),16));
		#ifdef displayI
			strcat(binary,"\tbltz");
		#endif
	}
	else if(strcmp(one,"blez") == 0){
		strcpy(binary,"000110");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary, intToBinChar(getLabelIndex(three, list, numLabels),16));
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
		//Calulate the instruction index
		//strcat(binary,"instr_indexxxxxx");
		strcat(binary,"00000000000000000000000000");
		#ifdef displayI
			strcat(binary,"\tj");
		#endif
	}
	else if(strcmp(one,"jr") == 0){
		strcpy(binary,"000000");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"0000000000");
		//I dont know what hint is actually supposed to be so I will fill in with 0's
		//strcat(binary,"hintx");
		strcat(binary,"00000");
		strcat(binary,"001000");
		#ifdef displayI
			strcat(binary,"\tjr");
		#endif
	}
	else if(strcmp(one,"jal") == 0){
		strcpy(binary,"000011");
		//Calulate the instruction index
		//strcat(binary,"instr_indexxxxxx");
		strcat(binary,"00000000000000000000000000");
		#ifdef displayI
			strcat(binary,"\tjal");
		#endif
	}
	else if(strcmp(one,"syscall") == 0){
		strcpy(binary,"000000");
		//these 0's may not be right but thats what the spec example looks like
		strcat(binary,"00000000000000000000");
		strcat(binary,"001100");
		#ifdef displayI
			strcat(binary,"\tsyscall");
		#endif
	}

	strcat(binary,"\0");
	return strdup(binary);
}

int getLabelIndex(char * label, struct Label list[], int numLabels){
	int i;
	for(i = 0; i < numLabels; i++){
		if(strcmp(label, list[i].label) == 0){
			if(list[i].TorD == 0){
				return (list[i].location*4)+8192;
			}
			else{
				return (list[i].location*4);
			}
		}
	}

	return 0;
}

/*
 * Executes the instructions and stores the proper values in the registers
 * Returns: index of the next instruction 
 */
int execInstruc(char * line, int current){
	#ifdef debug
		printf("--In execInstruc--\n");
		printf("	instruc to execute: %s!\n", line);
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
		//reg[rt] = reg[reg[rs] + offset]
		//convert the offset and rs to respective string and int
		//reg[reg[getRegNum(RS)] + atoi(offset)] = reg[getRegNum(two)];
		char * offset = strtok(three,"()");
		char * rs = strtok(NULL,"()");

		reg[getRegNum(two)] = reg[reg[getRegNum(rs)] + atoi(offset)];
	}
	else if(strcmp(one,"sw") == 0){
		//reg[reg[rs] + offset] = reg[rt]
		//convert the offset and rs to respective string and int
		//reg[getRegNum(two)] = reg[reg[getRegNum(RS)] + atoi(offset)];
		char * offset = strtok(three,"()");
		char * rs = strtok(NULL,"()");

		reg[reg[getRegNum(rs)] + atoi(offset)] = reg[getRegNum(two)];
	}
	else if(strcmp(one,"la") == 0){
		//executes as a pseudo instruction addi: rt = rs+label
		//need to convert label to int value
		//reg[getRegNum(two)] = reg[getRegNum("$zero")] + LABEL;//atoi(three);
	}
	else if(strcmp(one,"li") == 0){
		//executes as a pseudo instruction addiu: rt = rs+imm16
		reg[getRegNum(two)] = reg[getRegNum("$zero")] + atoi(three);
	}
	else if(strcmp(one,"add") == 0){
		//rd = rs+rt
		reg[getRegNum(two)] = reg[getRegNum(three)] + reg[getRegNum(four)];
	}
	else if(strcmp(one,"sub") == 0){
		//rd = rs-rt
		reg[getRegNum(two)] = reg[getRegNum(three)] + reg[getRegNum(four)];
	}
	else if(strcmp(one,"addi") == 0){
		//rt = rs+imm16
		reg[getRegNum(two)] = reg[getRegNum(three)] + atoi(four);
	}
	else if(strcmp(one,"addiu") == 0){
		//rt = rs+imm16
		reg[getRegNum(two)] = reg[getRegNum(three)] + atoi(four);
	}
	else if(strcmp(one,"or") == 0){
		//rd = rs OR rt (bitwise)
		//covert rs&rt values to binary 5? bits and then convert result to int and store in rd
	}
	else if(strcmp(one,"and") == 0){
		//rd = rs AND rt (bitwise)
		//covert rs&rt values to binary 5? bits and then convert result to int and store in rd
	}
	else if(strcmp(one,"ori") == 0){
		//rd = rs OR imm16 (bitwise)
		//intToBinChar(atoi(four),16)
		//covert rs&imm16 values to binary 5? bits and then convert result to int and store in rd
	}
	else if(strcmp(one,"andi") == 0){
		//rd = rs AND imm16 (bitwise)
		//intToBinChar(atoi(four),16)
		//covert rs&imm16 values to binary 5? bits and then convert result to int and store in rd
	}
	else if(strcmp(one,"slt") == 0){
		//if(rs < rt) then rd = 1
		if(reg[getRegNum(three)] < reg[getRegNum(four)]){
			reg[getRegNum(two)] = 1;
		}else{
			reg[getRegNum(two)] = 0;
		}
	}
	else if(strcmp(one,"slti") == 0){
		//if(rs < imm16) then rd = 1
		if(reg[getRegNum(three)] < atoi(four)){
			reg[getRegNum(two)] = 1;
		}else{
			reg[getRegNum(two)] = 0;
		}
	}
	else if(strcmp(one,"sll") == 0){
		//value of rs is converted to 32 bit binary and shifted left by sa bits
		//the space is filled with 0's and the resulting number is stored in rd		
	}
	else if(strcmp(one,"srl") == 0){
		//value of rs is converted to 32 bit binary and shifted right by sa bits
		//the space is filled with 0's and the resulting number is stored in rd
	}
	else if(strcmp(one,"sra") == 0){
		//same as srl but the space is filled with the sign bit AKA bit 31
		//value of rs is converted to 32 bit binary and shifted right by sa bits
		//the space is filled with 0's and the resulting number is stored in rd
	}
	else if(strcmp(one,"nop") == 0){
		//do nothing
		//or maybe increment the count if that how i choose to do it
	}
	else if(strcmp(one,"beq") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"bne") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"bltz") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"blez") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"blt") == 0){
		//flow of control
		//this should actually never be executed if the 
		//previous functions saved the instructions correctly
	}
	else if(strcmp(one,"ble") == 0){
		//flow of control
		//this should actually never be executed if the 
		//previous functions saved the instructions correctly
	}
	else if(strcmp(one,"j") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"jr") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"jal") == 0){
		//flow of control
		//this return is going to change
		return current+1;
	}
	else if(strcmp(one,"syscall") == 0){
		//no clue what this is supposed to do
	}

	return current+1;
}

int getRegNum(char* reg){

	#ifdef debug
		printf("--In getRegNum--\n");
		printf("	Register label to get reg number: %s!\n", reg);
	#endif

	//should never send getRegNum a NULL value
	if(reg == NULL)
		return -1;

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

	char binary[length];

	int total = num;
	int i = 0;

	while(total  > 0){
		if(i < length){
			int rem = total % 2;

			if(rem == 0)
				binary[i] = '0';
			else
				binary[i] = '1';

			total = total / 2;
			i++; 
		}else
			break;
	}

	int j;
	for(j = i; j < length; j++){
		binary[j] = '0';
	}

	binary[j] = '\0';

	//reverse the array
	char binaryNumber[length];
	for(i = 0; i < length; i++){
		binaryNumber[i] = binary[length-1-i];
	}

	binaryNumber[i] = '\0';

    return strdup(binaryNumber);
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