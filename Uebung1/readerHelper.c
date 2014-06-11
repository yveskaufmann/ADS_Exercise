/**
	
	Project: List
	File: readerHelper.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 10.06.2014
*/

#include "readerHelper.h"

size_t readline(char *prompt, char* buffer, size_t maxBytesToRead) {
	
	if(prompt != NULL) {
		printf("%s : ", prompt);
	}

	if((fgets(buffer, maxBytesToRead, stdin)) == NULL) {
		perror("Readline failed");
		return -1;
	}
	size_t size = strlen(buffer);
	if(size > 0 && buffer[size - 1] == '\n') {
		size--;
		buffer[size] = '\0';
	}
	return size;
}


int readInteger(const char *prompt, int min, int max) {
	char integerAsString[12]; // 12 digits are more than enough because a integer[ log10(2^32) ~ 10]  can only handle approximatly 10 digits.
	int integerValue = -1;
	int countOfDigits = 0;
	for(;;) {
		printf("%s [%d - %d]: ", prompt, min, max);
		countOfDigits = readline(NULL, integerAsString, 12 - 1);
		if(countOfDigits == 1 && integerAsString[0] == '0') {
			return 0;
		}

		integerValue = atoi(integerAsString);
		if(integerValue == 0 || integerValue < min || integerValue > max) {
			printf("Invalid number \"%s\" entered, please try it again.\n", integerAsString);
		} else {
			break;
		}
	}
	return integerValue;
}

char readChar(char *prompt) {
	if(prompt != NULL) {
		printf("%s : ", prompt);
	}
	char enteredChar = getchar();
	// flush input stream buffer
	char c;
	while((c = getchar() != '\n') && c != EOF); // FLUSHING

	return enteredChar;
}
