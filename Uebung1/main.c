/**
	
	Project: List
	File: main.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

int main(int argc, char **argv) {
	int comperator(Node *firstNode, Node *secondNode) {
		return strcmp((char*) firstNode->data, (char*) secondNode->data);
	}

	NodeHandlerReturnValue printNodes(Node *node, size_t index) {
		printf("%d - %s\n",(int) index + 1, (char*) node->data);
		return CONTINUE;
	}

	List *list = List_create();

	List_addLast(list, (void*) "4");
	List_addLast(list, (void*) "2");
	List_addLast(list, (void*) "3");
	List_addLast(list, (void*) "6");
	List_addLast(list, (void*) "5");
	List_addLast(list, (void*) "7");
	List_addLast(list, (void*) "2");
	List_addLast(list, (void*) "1");
		
	List_addLast(list, (void*) "4");
	List_addLast(list, (void*) "2");
	List_addLast(list, (void*) "3");
	List_addLast(list, (void*) "6");
	List_addLast(list, (void*) "5");
	List_addLast(list, (void*) "7");
	List_addLast(list, (void*) "2");
	List_addLast(list, (void*) "1");
	
	
	List_addLast(list, (void*) "4");
	List_addLast(list, (void*) "2");
	List_addLast(list, (void*) "3");
	List_addLast(list, (void*) "6");
	List_addLast(list, (void*) "5");
	List_addLast(list, (void*) "7");
	List_addLast(list, (void*) "2");
	List_addLast(list, (void*) "1");
	
	List_ForEach(list, printNodes);
	printf("\n");
	List_mergeSort(list, comperator);
	List_ForEach(list, printNodes);

	List_clear(list);
	return 0;
}



