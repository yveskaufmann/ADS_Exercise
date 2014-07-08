/**
 * This file contains a simple console application
 * which demonstrates the usage of the stack data structure.
 *
 * In this example the stack stores some students and the application
 * provides following options:
 *
 *	- create new students and inserts the into the stack
 *	- remove students from the stack
 *	- print the students in the stack the stdout
 *
 * @file main.c
 * @author Yves Kaufmann
 * @date 09 Jul 2014
 */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "student.h"
#include "readerHelper.h"

#define MAIN_CMD '?'
#define ADD_CMD 'a'
#define DEL_CMD 'd'
#define QUIT_CMD 'q'
#define YES_CMD 'y'
#define NO_CMD 'n'
#define PRINT_CMD 'p'


/**
 * Call the menu for creation and inserting of
 * a new student into a specified stack.
 *
 * @param[in] stack The stack which should obtain the new student.
 */
static
void pushStudent(Stack stack);

/**
 * Call the menu for deletion of student
 * inside the specified stack.
 *
 * @param[in] stack The stack which contains the to be remove student.
 */
static
void popStudent(Stack stack);

/**
 * The main entry point of the demonstatron application.
 *
 * @param argc An integer argument count of the command line arguments.
 * @param argv An argument vector of the command line arguments.
 * @return  An integer 0 upon exit success.s
 */
int main(int argc, char **argv) {
	char cmd = '?';
	Stack studentsStack = Stack_create(Student_DestroyHandler);
	for(;;) {
		switch(cmd) {
			case MAIN_CMD:
				printf("\t\tStacked Students Example\n");
				printf("\t\t=============================\n");
				printf("\n");
				printf("\t%c - %s\n", ADD_CMD, "Push a new student to the student stack.");
				printf("\t%c - %s\n", DEL_CMD, "Pops a student from the student stack.");
				printf("\t%c - %s\n", QUIT_CMD, "Exits this application.");
				printf("\t%c - %s\n", MAIN_CMD, "Shows the application help page");
				printf("\n");
				cmd = PRINT_CMD;
				continue;
			break;
			case ADD_CMD:
				pushStudent(studentsStack);
				cmd = PRINT_CMD;
				continue;
			break;
			case DEL_CMD:
				popStudent(studentsStack);
				cmd = PRINT_CMD;
				continue;
			break;
			case PRINT_CMD:
				Student_printAll(studentsStack);
			break;
			case QUIT_CMD:
				List_destroy(studentsStack);
				exit(EXIT_SUCCESS);
			break;
			default:
				printf("Unknown command \"%c\" entered.\n", cmd);
				cmd = '?';
				continue;
			break;
		}

		printf("\nWhat you wanna do [%c, %c, %c, %c, %c]?\n",
				ADD_CMD, DEL_CMD, PRINT_CMD, QUIT_CMD, MAIN_CMD);
		cmd = readChar(NULL);
		printf("\n");

	}

	return 0;
}

static
void pushStudent(Stack stack) {
	char firstname[255];
	char surename[255];
	char coursename[255];
	int matriculationNumber;
	Student student = NULL;

	do {
		printf("Please enter the properties for the new student:	\n");
		readline("Firstname", firstname, 255);
		readline("Surename", surename, 255);
		readline("Course", coursename, 255);
		matriculationNumber = readInteger("Matriculation number", 0, INT_MAX);
		printf("\nAre you happy with your inputs [%c, %c]?\n", YES_CMD, NO_CMD);
	} while(readChar(NULL) == NO_CMD);

	student = Student_create(firstname, surename, coursename, matriculationNumber);
	Stack_push(stack, student);

}

static
void popStudent(Stack stack) {
	void *student = Stack_pop(stack);
	if(student == NULL) {
		printf("The Stack of students is empty.\n\n");
		return;
	}
	
	printf("Popped student: ");
	Student_print(student);	
	printf("\n");
	Student_destroy(student);
}
