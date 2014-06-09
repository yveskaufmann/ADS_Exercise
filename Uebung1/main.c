/**
	
	Project: List
	File: main.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include <stdio.h>
#include "list.h"
#include "student.h"


int main(int argc, char **argv) {
	
	List list = List_create(Student_DestroyHandler);

	List_addLast(list, Student_create("Yves", "Kaufmann", "Algorithmen", 544361));
	List_addLast(list, Student_create("Ksenia", "Mbjorova", "BWL", 52135));
	List_addLast(list, Student_create("Ksenia", "Majorova", "BWL", 5134));
	List_addLast(list, Student_create("Ksenia", "Majordva", "BWL", 534));
	List_addLast(list, Student_create("Ksenia", "Majdrova", "BWL", 5443));
	List_addLast(list, Student_create("Ksenia", "Mbjorova", "BWL", 52));

	List_addLast(list, Student_create("Marcus", "bla", "Algorithmen", 544366));
	List_addLast(list, Student_create("ABA", "XMK", "Algorithmen", 544367));

	Student_printAll(list);
	printf("========================\n");
	List_mergeSort(list, Student_DefaultSortComperator);
	Student_printAll(list);
	List_destroy(list);
	return 0;
}



