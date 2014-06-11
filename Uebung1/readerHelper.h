/**
	
	Project: List
	File: readerHelper.h
	Purpose: 

	@author fxdapokalypse
	@version 1.0 10.06.2014
*/

#ifndef READERHELPER_H_
#define READERHELPER_H_

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

size_t readline(char *prompt, char* buffer, size_t maxBytesToRead);

int readInteger(const char *prompt, int min, int max);

char readChar(char *prompt);
#endif /* READERHELPER_H_ */
