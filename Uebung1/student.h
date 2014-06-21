/**
	

	Project: List
	File: student.h
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <strings.h>
#include <math.h>

#include "list.h"

typedef struct Student* Student;

Student Student_create(char *firstName, char *sureName, char *courseName, int matriculationNumber);
void Student_destroy(Student student);

const char* Student_getFirstName(Student student);
void Student_setFirstName(Student student, const char *firstName);

const char* Student_getSureName(Student student);
void Student_setSureName(Student student, const char *sureName);

const char* Student_getCourseName(Student student);
void Student_setCoursName(Student student, const char *courseName);

int Student_getMatriculationNumber(Student student);
void Student_setMatriculationNumber(Student student, int matriculationNumber);

bool Student_DestroyHandler(NodePtr node, size_t index, void *data);
bool Student_PrintHandler(NodePtr node, size_t index, void *data);

int Student_CourseComperator(NodePtr firstNode, NodePtr secondNode);
int Student_MarticelNrComperator(NodePtr firstNode, NodePtr secondNode);
int Student_DefaultSortComperator(NodePtr firstNode, NodePtr secondNode);

void Student_print(Student student);
void Student_printAll(List students);

List Student_findAllByFirstName(List list, const char* name);
List Student_findAllBySureName(List list, const char* name);
List Student_findAllByCourseName(List list, const char* name);
List Student_findAllByMatriculationNumber(List list,int matriculationNumber);

#endif /* _STUDENT_H_ */
