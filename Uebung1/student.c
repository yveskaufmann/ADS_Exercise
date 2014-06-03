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

NodeHandlerReturnValue Student_NodeClearHandler(Node *node, size_t index, void *data) {
	if(node) {
		Student_clear(node->data);
	}
	return CONTINUE;
}

void Student_print(Student *student) {
	if(!student) return;

	printf("%s = %s %s\n", "Name", student->firstName, student->sureName);
	printf("%s = s0%d\n", "Matriculation number", student->martikelNumber);
	printf("%s = %s\n", "Course", student->courseName);
	printf("\n");

}
void Student_printNode(Node *node) {
	if(!node) return;
	Student_print(node->data);
}

void Student_printAll(List *studentList) {
	if(!studentList) return;
	List_ForEach(studentList, (NodeHandler) Student_printNode, NULL);
}

void Student_Search(List *studentList, )
