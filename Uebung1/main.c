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
	

	int comperator(NodePtr firstNode, NodePtr secondNode) {
		return strcmp((char*) Node_getData(firstNode), (char*) Node_getData(secondNode));
	}

	bool printNodes(NodePtr node, size_t index, void *data) {
		printf("%d - %s\n",(int) index + 1, (char*) Node_getData(node));
		return true;
	}

	List list = List_create();

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

	List_ForEach(list, printNodes, NULL); printf("\n");
	// List_mergeSort(list, comperator);
	List_ForEach(list, printNodes, NULL);
	List_destroy(list);
	return 0;
}




