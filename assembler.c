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
		strcpy(dataLines[j].line, "\0");
		printf("dataLine[%d]: %s\n", j, dataLines[j].line);	
	}

	fillLabelList(stripedFile, myLabels);
	fillDataLines(stripedFile, dataLines);

	int i;
	for(i = 0; i < sizeof(myLabels)/sizeof(struct Label); i++){
		printf("myLabels[%d] label: %s\n", i, myLabels[i].label);
		printf("myLabels[%d] location: %d\n", i, myLabels[i].location);
		printf("myLabels[%d] TorD: %d\n", i, myLabels[i].TorD);
	}

	for(j = 0; j < sizeof(dataLines)/sizeof(struct DataBinaryLine); j++){
		printf("dataLine[%d]: %s\n", j, dataLines[j].line);	
	}

	binaryToFile(stripedFile, outFile, myLabels);
    //do the same thing for labels
	//int numLabels = labelCount(stripedFile);
	//declare struct Label myLabels[numLabels];
	//initalize labels
	//fillLabelList(myLabels);
	//loop through myInstruc with executeInstruc()
	//binaryToFile(outFile, myLabels);
	

	/*
	for(i = 0; i < sizeof(myInstruc)/sizeof(struct Instruc); i++){
		printf("myInstruc[%d]: %s\n", i, myInstruc[i].command);
	}

	int k;
	for(k = 0; k < sizeof(reg)/sizeof(reg[0]); k++){
		printf("reg[%d]: %d\n", k, reg[k]);
	}

	int current = 0;
	while(current < sizeof(myInstruc)/sizeof(struct Instruc)){
		current = execInstruc(myInstruc[current].command, current);
	}

	for(k = 0; k < sizeof(reg)/sizeof(reg[0]); k++){
		printf("reg[%d]: %d\n", k, reg[k]);
	}

	FILE *ofp;
	char * out = "ascii.txt";

	ofp = fopen(out, "w+");

	if (ofp == NULL) {
	  fprintf(stderr, "Can't open output file %s!\n", out);
	  exit(1);
	}

	char testString[] = "The sum of numbers in array is: ";
	char * test = malloc(sizeof(char)*8);
	//char * temp = malloc(sizeof(char)*32);

	int z;
	int count = 0;
	int index = 0;

	//make this array the size of the number of characters in the string/4
	//if(sizeof(testString)/sizeof(char)%4 != 0)
	//	struct DataBinaryLine data[sizeof(testString)/sizeof(char)+1];
	//else
	//	struct DataBinaryLine data[sizeof(testString)/sizeof(char)];

	struct DataBinaryLine data[sizeof(testString)/sizeof(char)+1];
	for(j = 0; j < sizeof(data)/sizeof(struct DataBinaryLine)+1; j++){
		data[j].line[0] = '\0';	
	}

	for(z = 0; z < sizeof(testString)/sizeof(char) ; z++){
		if(count >=4){
			//might add '\0' to this
			fprintf(ofp, "%s\n", data[index].line);
			index++;
			count = 0;
		}
		printf("character: %c\n",testString[z]);
		convertAsciiToBin(testString[z], test, 8);
		char * temp = strcat(test,data[index].line);
		printf("temp: %s\n",temp);
		strcpy(data[index].line,temp);
		printf("line: %s\n",data[index].line);
		count++;*/
/*
		if(testString[z] != '\0'){
			convertBaseVersion(testString[z], 2, test, 8);
			printf("%s",test);
			if(count == 3){
				count = -1;
				printf("\n");
			}
			count++;
		}*/
/*	}

	printf("line outside: %s\n",data[index].line);
	//char * temp2 = malloc(sizeof(char)*32);
	char temp2[32];
	temp2[0] = '\0';
	printf("temp2: %s\n",temp2);

	if(strlen(data[index].line) < 32)
	{
		int n = 32 - strlen(data[index].line);
		for(i = 0; i < n; i++){
			strcat(temp2,"0");
			printf("temp2: %s\n",temp2);
		}
	}

	strcat(temp2,data[index].line);
	strcpy(data[index].line,temp2);

	fprintf(ofp, "%s\n", data[index].line);
*/
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

void convertAsciiToBin(char ascii, char *output, int digits) { 
	int i, remainder; 
	char digitsArray[17] = "01";

	for (i = digits; i > 0; i--) { 
		remainder = ascii % 2; 
		ascii = ascii / 2; 
		output[i - 1] = digitsArray[remainder]; 
	} 

	output[digits] = '\0'; 
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
char * stripExtra(char * inputFile){
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

		char keys[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.";
		int j = strcspn (line,keys);

		if(strcmp(line,"\n") != 0 && j < strcspn(line,"#")){//strchr(line,'#')-line != 0){
			
			//char * lineCopy = strdup(line);
		  	//removes the whitespace at the beginning of the line
		  	
		  	/*int i = strcspn (line,keys);
		  	if(i != 0){
		  		//line = strncpy(line, line+i, strlen(line-i));
		  		//strncpy(line, lineCopy+i, strlen(line-i));
		  		memmove(line, line+i, strlen(line));
		  		strcat(line,"\0");
		  	}*/

		 // printf("LINE BEFORE CALLING	IS: %s\n",line);
		  	//line = removeComment(line);
		  	//strcpy(line,removeComment(line));
		  line = cleanStr(line); //removeComment(line);
		  //printf("Clean line: %s\n",line);

		  //add the pseudo instructions if blt or ble
		  if(strstr(line,"blt") != NULL){
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

		  }else if(strstr(line,"ble") != NULL){
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
	//printf("*************going into clean String: \t%s\n", line);
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
	//char * temp = &result[0];

	//printf("leaving clean String:%s\n", line);
	return strdup(result);
}

char * removeComment(char * line){
	char key[] = "#";
  	int i;
  	i = strcspn (line,key);
	char clean[256];
	strncpy(clean,line,i);
	clean[i] = '\0';
	//char * temp = &clean[0];
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
	//changed to 40 from 32 to supported adding instruction at end
	#ifdef displayI
		char * binary = malloc(sizeof(char)*40);
	#endif
	#ifndef displayI
		char * binary = malloc(sizeof(char)*32);
	#endif
	
	while (!feof(ifp)) {
	  if (fgets (line, 256, ifp)!=NULL){
	    char * lineCopy = malloc(strlen(line)+1);
	    strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	  	//int isInstr = isInstruc(line);
	    if(inText == 0 && isInstruc(line) == 0){//(isInstr == 0 || isInstr == 1)){
	    	//isInstruc takes a pointer so the value is change on return
	    	//if(isInstr == 0){
	    		//printf("linecopy before printing to intermeidate:%s\n", lineCopy);
	    		fprintf(ofp, "%s", lineCopy);
	    		count++;
	    	//}
	    	//else{
	    	//	printf("***linecopy before printing to intermeidate*****:%s\n", lineCopy);
	    	//	fprintf(ofp, "%s", lineCopy);
	    	//	fprintf(ofp, "%s", "the pseudo code");
	    	//	count+2;
	    	//}
	    	//binary = getInstrucBinary(lineCopy);
	    	//printf("binary %s: 			%s\n", lineCopy, binary);
	    	//fprintf(ofp2, "%s\n", binary);

	    	
	    }
	  }
	}

	fclose(ifp);
	fclose(ofp);
	//fclose(ofp2);

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
			//for the fillLabel(), keep track of the line number to know the address
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
	    	//remember to replace the '~' with ' ' when printing!
	    	if(strstr(lineCopy, ".asciiz") != NULL){
	    		char * str;
	    		str = strtok(lineCopy,"\"");
	    		str = strtok(NULL, "\"");
	    		//printf("(ascii) token string is: %s\n", str);
	    		//printf("size of string is: %d\n", sizeof(str)/sizeof(char));
	    		//printf("length of string is: %d\n", strlen(str));
	    		if((strlen(str)+1)%4 != 0){
	    			count = count + ((strlen(str)+1)/4)+1;
	    			//printf("(/4!=0)added %d to count\n", ((strlen(str)+1)/4)+1);
	    		}
	    		else{
	    			count = count + ((strlen(str)+1)/4);
	    			//printf("(/4==0)added %d to count\n", ((strlen(str)+1)/4));
	    		}
	    	}
	    	else if(strstr(lineCopy, ".word") != NULL){
	    		char * str;
	    		str = strtok(lineCopy,"~\n");
	    		str = strtok(NULL, "~\n");
	    		str = strtok(NULL, "~\n");
	    		//printf("(word) token string is: %s\n", str);
	    		if(strchr(str,':') != NULL){
	    			char * number;
	    			number = strtok(str,":\n");
	    			number = strtok(NULL,":\n");
	    			//printf("(word) token number is: %s\n", str);
	    			//printf("number to add is: %d\n", atoi(number));
	    			count+= atoi(number);
	    		}else{
	    			count++;
	    			//printf("count increased by 1\n");
	    		}
	    	}
	    }
	  }
	}

	fclose(ifp);

	return count;
}

void binaryToFile(char * inFile, char * outFile, struct Label * list){
	#ifdef debug
		printf("--In binaryToFile--\n");
		printf("	outputFile %s!\n", filename);
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
			fprintf(ofp, "%s\n", getInstrucBinary(lineCopy, list));
	    }
	    if(inText == 1 && strstr(line,".data") == NULL){
	    	fprintf(ofp, "%s\n", "data");
	    }
	  }
	}

	fclose(ifp);
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
	    char * lineCopy = strdup(line);//malloc(strlen(line));
	    //strcpy(lineCopy, line);
	  	if(strstr(line,".text") != NULL)
	  		inText = 0;
	  	if(strstr(line,".data") != NULL)
	  		inText = 1;
	    if(inText == 1 && strstr(line,".data") == NULL){
	    	
	    	if(strstr(lineCopy, ".asciiz") != NULL){
	    		printf("LineCopy inside of ascii: %s\n", lineCopy);
	    		char * quote = malloc(sizeof(char)*256);
	    		quote = strtok(lineCopy,"\"");
	    		quote = strtok(NULL, "\"");
	    		printf("quote inside of ascii: %s\n", quote);

	    		int z;
	    		char * temp = malloc(sizeof(char)*32);
	    		//temp[0] ='\0';
	    		strcpy(temp,"\0");
	    		for(z = 0; z < strlen(quote); z++){
	    			byte[0] = '\0';
	    			printf("quote[%d]: %c\n", z, quote[z]);
	    			printf("temp before:\t%s\n", temp);
	    			printf("byte before:\t%s\n", byte);
	    			convertAsciiToBin(quote[z], byte, 8);
	    			printf("byte after:\t%s\n", byte);
	    			strcat(temp,byte);
	    			printf("temp after:\t%s\n", temp);


	    			if(byteCount > 3){
	    				byteCount = 0;
	    				strcpy(&data[lineIndex].line[0], strdup(temp));
	    				//strcat(data[lineIndex].line, "\0");
	    				data[lineIndex].line[31] = '\0';
	    				strcpy(temp,"\0");
	    				lineIndex++;
	    			}

	    			byteCount++;
	    		}
	    	}


/*
   		 	if(strstr(lineCopy2, ".asciiz") != NULL){
	    		char * str;
	    		str = strtok(lineCopy2,"\"");
	    		str = strtok(NULL, "\"");

	    		printf("This should be the whole ascii string: %s\n", str);

	    		char temp[32];
	    		strcpy(temp, "TESTTTTTTTT");

	    		int z;
	    		for(z = 0; z < strlen(str) ; z++){
	    			printf("-------------Going into loop-------------\n");
	    			printf("data[%d].line: %s\n", lineIndex, data[lineIndex].line);
	    			printf("temp on %d: %s\n", lineIndex, temp);
	    			strcpy(byte,"\0");
	    			printf("byte before: %s\n", byte);
	    			printf("Current character: %c\n", str[z]);

	    			printf("temp on %d BEFORE if: %s\n", lineIndex, temp);
	    			if(byteCount > 3){
	    				byteCount = 0;
	    				printf("++++++temp to set the line on %d: %s\n", lineIndex, temp);
	    				strcpy(data[lineIndex].line, strdup(temp));
	    				strcat(data[lineIndex].line, "\0");
	    				printf("after the set data[%d].line: %s\n", lineIndex, data[lineIndex].line);
	    				lineIndex++;
	    				temp[0] = '\0';
	    			}
	    			//change this so it reverses
	    			//strcat(data[lineIndex].line, byte);
	    			convertAsciiToBin(str[z], byte, 8);
	    			printf("byte after: %s\n", byte);
	    			strcat(temp, strdup(byte));
	    			byteCount++;
	    		}
	    	}*/
	    /*
	    	if(strstr(lineCopy2, ".asciiz") != NULL){
	    		char * str;
	    		str = strtok(lineCopy2,"\"");
	    		str = strtok(NULL, "\"");

	    		printf("This should be the whole ascii string: %s\n", str);
	    		//need to replace all the '~' with ' '
	    		int z;
	    		for(z = 0; z < strlen(str) ; z++){
	    			printf("---------Beginning loop------------------\n");
	    			strcpy(byte, "\0");
	    			printf("z: %d\n", z);
	    			printf("index: %d\n", index);
	    			printf("count: %d\n", count);
	    			printf("byte: %s\n", byte);
	    			printf("^^^^^^^^^^^^^^^^^^^^\n");
					if(count >=4){
						//might add '\0' to this
						//fprintf(ofp, "%s\n", data[index].line);
						index++;
						count = 0;
					}
					printf("character: %c\n",str[z]);
					convertAsciiToBin(str[z], byte, 8);
					char * temp = strcat(byte,data[index].line);
					printf("byte after strcat: %s\n",byte);
					strcpy(data[index].line,temp);
					printf("line[%d]: %s\n", index, data[index].line);
					count++;

					printf("-----------Ending loop------------\n");
				}

				printf("line outside: %s\n",data[index].line);
				//char * temp2 = malloc(sizeof(char)*32);
				char temp2[32];
				temp2[0] = '\0';
				printf("temp2: %s\n",temp2);

				if(strlen(data[index].line) < 32)
				{
					int n = 32 - strlen(data[index].line);
					int i;
					for(i = 0; i < n; i++){
						strcat(temp2,"0");
						printf("temp2: %s\n",temp2);
					}
					strcat(temp2,data[index].line);
					strcpy(data[index].line,temp2);
					index++;
				}
	    	}
	    	*/
	    	else if(strstr(lineCopy, ".word") != NULL){
	    		/*char * str;
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
	    		}*/
	    	}
	    }
	  }
	}

	fclose(ifp);
	printf("#################################################CLOSED IN FILL DATA\n");
	printf("data[0]%s\n", data[0].line);
	printf("Size of data: %d\n", sizeof(data)/sizeof(data[0]));
	int j;
	for(j = 0; j < sizeof(data)/sizeof(struct DataBinaryLine); j++){
		printf("in Fill dataLine[%d]: %s\n", j, data[j].line);	
	}

	return;
}

char * getInstrucBinary(char * line, struct Label list[]){
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
		strcat(binary, intToBinChar(getLabelIndex(three, list),16));
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
		strcat(binary, intToBinChar(getLabelIndex(four, list),16));
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
		strcat(binary, intToBinChar(getLabelIndex(four, list),16));
		#ifdef displayI
			strcat(binary,"\tbne");
		#endif
	}
	else if(strcmp(one,"bltz") == 0){
		strcpy(binary,"000001");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary, intToBinChar(getLabelIndex(three, list),16));
		#ifdef displayI
			strcat(binary,"\tbltz");
		#endif
	}
	else if(strcmp(one,"blez") == 0){
		strcpy(binary,"000110");
		//rs
		strcat(binary,intToBinChar(getRegNum(two),5));
		strcat(binary,"00000");
		strcat(binary, intToBinChar(getLabelIndex(three, list),16));
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
		//these 0's may not be right but thats what the spec example looks like
		strcat(binary,"00000000000000000000");
		strcat(binary,"001100");
		#ifdef displayI
			strcat(binary,"\tsyscall");
		#endif
	}

	strcat(binary,"\0");

	char * bin = &binary[0];
	return strdup(bin);
}

int getLabelIndex(char * label, struct Label list[]){
	//printf("------input into getLabelIndex: %s\n", label);
	//printf("size of label list: %d\n", sizeof(list));
	int i;
	for(i = 0; i < sizeof(list)+1; i++){
		//printf("current label to compare: %s\n", list[i].label);
		if(strcmp(label, list[i].label) == 0){
			if(list[i].TorD == 0){
				//printf("FOUND label @ %d: %s\n", (list[i].location*4)+8192, list[i].label);
				return (list[i].location*4)+8192;
			}
			else{
				//printf("FOUND label  @ %d: %s\n", (list[i].location),list[i].label);
				return list[i].location;
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

	char binary[length];

	int total = num;
	int i = 0;

	while(total  > 0){
		//printf("total: %d\n", total);
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

	//printf("i: %d\t length: %d\n", i, length);

	int j;
	for(j = i; j < length; j++){
		binary[j] = '0';
	}

	binary[j] = '\0';

//	printf("j: %d\t length: %d\n", j, length);

	//printf("binary before return: %s\n", binary);
/*
	int total = 0, index;
	char binaryNumber[length];

	for(index = length-1; index >= 0; index--){
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

	//binaryNumber[index] = '\0';
	binaryNumber[length] = '\0';
*/
	//reverse the array
	char binaryNumber[length];
	for(i = 0; i < length; i++){
		binaryNumber[i] = binary[length-1-i];
	}

	binaryNumber[i] = '\0';

    //char* bin = &binary[0];
    //return bin;*/
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