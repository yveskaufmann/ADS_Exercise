/**
	
	Project: List
	File: main.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include <stdlib.h>

#include <stdio.h>
#include "list.h"

int main(int argc, char **argv) {

	NodeHandlerReturnValue printNode(Node *node, size_t index) {
		printf("%s\n", (char*)node->data);
		return CONTINUE;
	}



	List *list = List_create();

	List_addLast(list, (void*) "World0");
	List_addLast(list, (void*) "World1");
	List_addLast(list, (void*) "World2");

	List_ForEach(list, printNode);
	List_clear(list);
	return 0;
}



