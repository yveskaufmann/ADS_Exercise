/**
 * This file contains the declaration of helper function
 * for reading from the stdin especially for reading
 * the user input inside a terminal.
 *
 * @file readerHelper.h
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#ifndef READERHELPER_H_
#define READERHELPER_H_


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Prompts the user for input and reads a line from the stdin
 * and returns the count of readed characters this count doesn't includes
 * the termination character.
 *

 * @param[in] 	prompt			A optional prompt message which should showed
 * 								to the user before starting the read procedure.
 * @param[out] 	buffer			A buffer which should obtain the readed line,
 * 								the buffer have to be provided by the caller.
 * @param[in] 	maxBytesToRead	The maximum number of characters which should
 * 								readed from the stdin, \a maxBytesToRead have to
 * 								be smaller than @code sizeof(buffer) @endcode.
 *
 * @return The count of readed characters this count doesn't includes the termination character.
 */
size_t readline(char *prompt, char* buffer, size_t maxBytesToRead);

/**
 * Prompts the user for input and reads a integer value from the stdin
 * and returns the readed number. The Function ensures that the entered value
 * is a number and is greater than or equal than min and less or equal than max.
 *
 * @param[in] 	prompt	A optional prompt message which should showed
 * 						to the user before starting the read procedure.
 * @param[in] 	min		The start of the interval of a valid number.
 * @param[in] 	max		The end of the interval of a valid number.
 *
 * @return	The number which was entered by the user.
 */
int readInteger(const char *prompt, int min, int max);

/**
 * Prompts the user for input and reads a charactor value from the stdin
 * and returns the readed character.
 *
 * @param[in] 	prompt	A optional prompt message which should showed
 * 						to the user before starting the read procedure.
 *
 * @return	The character value which was entered by the user.
 */
char readChar(char *prompt);

#endif /* READERHELPER_H_ */
