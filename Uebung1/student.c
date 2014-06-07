/**
	

	Project: List
	File: student.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include "student.h"

struct Student {
	char *firstName;
	char *sureName;
	char *courseName;
	int matriculationNumber;
};

///////////////////////////////////////////////////////////////////////////////
//
// Helper functions
//
///////////////////////////////////////////////////////////////////////////////

static
char* createStringClone(const char* str) {
	if(str == NULL) return NULL;
	
	int strLen = strlen(str);
	char* strClone = (char *) malloc(strLen + 1);
	
	strncpy(strClone, str, strLen);
	strClone[strLen] = (char) 0;
	
	return strClone;
}


static
void handleNewStringSetter(char **oldString, const char* newStr) {
	if(*oldString != NULL) { 
		free(*oldString);
	}
	*oldString = createStringClone(newStr);
}


///////////////////////////////////////////////////////////////////////////////
//
// DATA STRACTURE Implementation
//
///////////////////////////////////////////////////////////////////////////////

Student Student_create(char *firstName, char *sureName, char *courseName,
			int matriculationNumber) {

	Student student = malloc(sizeof(struct Student));
	memset(student, 0 , sizeof(struct Student));
	
	Student_setFirstName(student, firstName);
	Student_setSureName(student, sureName);
	Student_setCoursName(student, courseName);
	Student_setMatriculationNumber(student, matriculationNumber);

	return student;
}

void Student_destroy(Student student) {
	if(!student) return;
	
	if((student->firstName) != NULL) {
		free(student->firstName);
	}

	if((student->sureName) != NULL) { 
		free(student->sureName);
	}

	if((student->courseName) != NULL) { 
		free(student->courseName);
	}

	free(student);
}


///////////////////////////////////////////////////////////////////////////////
//
// DATA STRACTURE Getter & Setter
//
///////////////////////////////////////////////////////////////////////////////

const char* Student_getFirstName(Student student) {
	return student->firstName;
}

void Student_setFirstName(Student student, const char *firstName) {
	handleNewStringSetter(&(student->firstName), firstName);
}

const char* Student_getSureName(Student student) {
	return student->sureName;
}

void Student_setSureName(Student student, const char *sureName) {
	handleNewStringSetter(&(student->sureName), sureName);
}

const char* Student_getCourseName(Student student) {
	return student->courseName;
}
void Student_setCoursName(Student student, const char *courseName) {
	handleNewStringSetter(&(student->courseName), courseName);
}

int Student_getMatriculationNumber(Student student) {
	return student->matriculationNumber;
}

void Student_setMatriculationNumber(Student student, int matriculationNumber) {
	student->matriculationNumber = matriculationNumber;
}

///////////////////////////////////////////////////////////////////////////////
//
// DATA STRACTURE Node_ClearHandler
//
///////////////////////////////////////////////////////////////////////////////


bool Student_DestroyHandler(NodePtr node, size_t index, void *data) {
	if(node) {
		Student_destroy(Node_getData(node));
	}
	return true;
}

bool Student_PrintHandler(NodePtr node, size_t index, void *data) {
	if(node) {
		Student_print(Node_getData(node));
	}
	return true;
}

int Student_DefaultSortComperator(NodePtr firstNode, NodePtr secondNode) {

	Student firstStudent = Node_getData(firstNode);
	Student secondStudent = Node_getData(secondNode);
	const char *firstCourse = Student_getCourseName(firstStudent);
	const char *secondCourse = Student_getCourseName(secondStudent);
	int firstMatricleNr = Student_getMatriculationNumber(firstStudent);
	int secondMatricleNr = Student_getMatriculationNumber(firstStudent);

	int cmpCourseName = strcmp(firstCourse, secondCourse);
	int cmpMatriculationNr = (firstMatricleNr > secondMatricleNr) ?
			1
		:
			(firstMatricleNr < secondMatricleNr) ? -1  : 0;

	return (!cmpCourseName) ?
			cmpMatriculationNr
		:
			cmpCourseName;
};


///////////////////////////////////////////////////////////////////////////////
//
// DATA STRACTURE print
//
///////////////////////////////////////////////////////////////////////////////

void Student_print(Student student) {
	if(!student) return;

	printf("%s = %s %s\n", "Name", student->firstName, student->sureName);
	printf("%s = s0%d\n", "Matriculation number", student->matriculationNumber);
	printf("%s = %s \n", "Course", student->courseName);
	printf("\n");

}

void Student_printAll(List studentList) {
	if(!studentList) return;
	List_ForEach(studentList, Student_PrintHandler, NULL);
}


