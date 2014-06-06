/**
	

	Project: List
	File: student.h
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "list.h"

typedef struct Student Student;
struct Student {
	char *firstName;
	char *sureName;
	char *courseName;
	int martikelNumber;
};

Student *Student_create(char *firstName, char *sureName, char *courseName, int matriculationNumber);

void Student_clear(Student *student);
bool Student_NodeClearHandler(NodePtr node, size_t index, void *data);

void Student_print(Student *student);
void Student_printNode(NodePtr node);
void Student_printAll(List students);


#endif /* _STUDENT_H_ */
