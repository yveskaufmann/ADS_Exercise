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
	fflush(stdin);
	if((fgets(buffer, maxBytesToRead, stdin)) == NULL) {
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

char* readKeyWords(const char *prompt, char *enteredKeyWord, size_t bufferSize, size_t countOfKeys, ...) {


	// prepare key word list format string
	va_list keyWords;

	int lenOfKeyListFormat = (4 * countOfKeys + 1);
	char *promptKeyListFormatStr = malloc(lenOfKeyListFormat);
	promptKeyListFormatStr[lenOfKeyListFormat - 1] =  '\0';
	bool hasInvalidKeyWord = true;

	// generate format string
	int offset = 0;
	for(int i = 0; i < countOfKeys; i++) {
		char *formatDesc = ", %s";
		if(offset == 0) {
			formatDesc = "%s";
		}
		strcpy(promptKeyListFormatStr + offset, formatDesc);
		if(offset == 0) {
			offset+=2;
		} else {
			offset+=4;
		}
	}

	// read keyword
	while(hasInvalidKeyWord) {
		va_start(keyWords, countOfKeys);
		printf("%s [", prompt);
		vprintf(promptKeyListFormatStr, keyWords);
		printf("]: ");

		hasInvalidKeyWord = true;
		readline(NULL, enteredKeyWord, bufferSize);
		for(int i = 0; i < countOfKeys && hasInvalidKeyWord; i++) {
			char *keyWord = va_arg(keyWords, char*);
			hasInvalidKeyWord = strcmp(keyWord, enteredKeyWord) != 0;
		}
		va_end(keyWords);

		if(hasInvalidKeyWord) {
			printf("Invalid keyword entered \"%s\", please try it again.\n", enteredKeyWord);
		}

	}
	printf("\n");
	free(promptKeyListFormatStr);

	return enteredKeyWord;

}


