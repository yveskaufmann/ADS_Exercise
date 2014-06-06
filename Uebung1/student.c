/**
	

	Project: List
	File: student.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include "student.h"

Student *Student_create(char *firstName, char *sureName,
		char *courseName, int matriculationNumber) {

	Student *student = (Student*) malloc(sizeof(Student));
	student->firstName = firstName;
	student->sureName = sureName;
	student->courseName = courseName;
	student->martikelNumber = matriculationNumber;

	return student;
}

void Student_clear(Student *student) {
	if(!student) return;
	free(student);
}

bool Student_NodeClearHandler(NodePtr node, size_t index, void *data) {
	if(node) {
		Student_clear(Node_getData(node));
	}
	return true;
}

void Student_print(Student *student) {
	if(!student) return;

	printf("%s = %s %s\n", "Name", student->firstName, student->sureName);
	printf("%s = s0%d\n", "Matriculation number", student->martikelNumber);
	printf("%s = %s\n", "Course", student->courseName);
	printf("\n");

}
void Student_printNode(NodePtr node) {
	if(!node) return;
	Student_print(Node_getData(node));
}

void Student_printAll(List studentList) {
	if(!studentList) return;
	List_ForEach(studentList, (NodeHandler) Student_printNode, NULL);
}


