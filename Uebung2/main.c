/**
	
	Project: List
	File: main.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 06.06.2014
*/

#include <stdlib.h>

#include <stdio.h>
#include "stack.h"

int main(int argc, char **argv) {
	
	Stack stack;

	Stack_Create(&stack, 100);
	
	Stack_push(&stack, 10);
	Stack_push(&stack, 20);

	StackElement *p = NULL;
	
	while((p = Stack_pop(&stack)) != NULL) printf("%d\n", *p);
	

	Stack_Clear(&stack);
	return 0;
}



