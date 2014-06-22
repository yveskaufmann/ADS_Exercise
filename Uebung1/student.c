/**
	

	Project: List
	File: student.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#include "student.h"

extern int errno;

struct Student {
	char *firstName;
	char *sureName;
	char *courseName;
	int matriculationNumber;
};

//----------------------------------------------------------------------------
// Helper functions
//----------------------------------------------------------------------------

static
char* createStringClone(const char* str) {
	if(str == NULL) return NULL;
	
	int strLen = strlen(str);
	char* strClone = (char *) malloc((strLen + 1) * sizeof(char));
	if(strClone == NULL) {
		fprintf(stderr, "String clone failed: \"%s\"", strerror(errno));
		return NULL;
	}

	strncpy(strClone, str, strLen);
	strClone[strLen] = '\0';
	
	return strClone;
}


static
void handleNewStringSetter(char **oldString, const char* newStr) {
	if(*oldString != NULL) { 
		free(*oldString);
	}
	*oldString = createStringClone(newStr == NULL ? " " : newStr);
}

//----------------------------------------------------------------------------
//
// DATA STRACTURE Implementation
//
//----------------------------------------------------------------------------

Student Student_create(char *firstName, char *sureName, char *courseName,
			int matriculationNumber) {

	Student student = malloc(sizeof(struct Student));
	if(student == NULL) {
		fprintf(stderr, "Student creation failed: \"%s\"", strerror(errno));
		return NULL;
	}

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


//----------------------------------------------------------------------------
// DATA STRACTURE Getter & Setter
//----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
// DATA STRACTURE Node_Handlers
//----------------------------------------------------------------------------


bool Student_DestroyHandler(Node node, size_t index, void *data) {
	if(node) {
		Student_destroy(Node_getData(node));
	}
	return true;
}

bool Student_PrintHandler(Node node, size_t index, void *data) {
	if(node) {
		Student_print(Node_getData(node));
	}
	return true;
}

//----------------------------------------------------------------------------
// DATA STRACTURE NodeComperators
//----------------------------------------------------------------------------

int Student_CourseComperator(Node firstNode, Node secondNode) {

	const char *firstCourse = Student_getCourseName(Node_getData(firstNode));
	const char *secondCourse = Student_getCourseName(Node_getData(secondNode));

	int firstLen = strlen(firstCourse);
	int secondLen = strlen(secondCourse);

	return strncmp(firstCourse, secondCourse, MIN(firstLen, secondLen));

};

int Student_MarticelNrComperator(Node firstNode, Node secondNode) {

	int firstMatricleNr = Student_getMatriculationNumber(Node_getData(firstNode));
	int secondMatricleNr  = Student_getMatriculationNumber(Node_getData(secondNode));

	return (firstMatricleNr > secondMatricleNr) ? 1 : (firstMatricleNr < secondMatricleNr) ? -1 : 0;
};



int Student_DefaultSortComperator(Node firstNode, Node secondNode) {
	int cmpCourseName =  Student_CourseComperator(firstNode, secondNode);
	return (cmpCourseName != 0) ?  cmpCourseName : Student_MarticelNrComperator(firstNode, secondNode);
};


//----------------------------------------------------------------------------
// DATA STRACTURE print
//----------------------------------------------------------------------------

void Student_print(Student student) {
	if(!student) return;
	printf("%-10s %-10s  %-20s  s0%-10d",student->firstName, student->sureName,student->courseName,student->matriculationNumber);
	printf("\n");

}

void Student_printAll(List studentList) {
	if(!studentList) return;
	printf("Count of students: %d\n", List_getSize(studentList));
	printf("%-10s %-10s  %-20s  %-12s\n","First-Name", "Sure-Name", "Course-Name", "Matriculation-Number");
	printf("\n");
	List_ForEach(studentList, Student_PrintHandler, NULL);
}

//----------------------------------------------------------------------------
// DATA STRACTURE find
//----------------------------------------------------------------------------

static
bool testIfStringMatches(const char* str, const char* strOther) {
	int lenStr = strlen(str);
	int lenStrOther = strlen(strOther);

	return 0 == strncasecmp(str, strOther, MIN(lenStr, lenStrOther));
}

List Student_findAllByFirstName(List list, const char* firstName) {
	bool filterNodes(Node node, size_t index, void *data) {
		Student student = Node_getData(node);
		return testIfStringMatches(data,Student_getFirstName(student));
	}
	return List_findAllNodes(list, filterNodes, (void *)firstName);
}

List Student_findAllBySureName(List list, const char* sureName) {
	bool filterNodes(Node node, size_t index, void *data) {
		Student student = Node_getData(node);
		return testIfStringMatches(data,Student_getSureName(student));
	}
	return List_findAllNodes(list, filterNodes, (void *)sureName);
}

List Student_findAllByCourseName(List list, const char* courseName) {
	bool filterNodes(Node node, size_t index, void *data) {
		Student student = Node_getData(node);
		return testIfStringMatches(data,Student_getCourseName(student));
	}
	return List_findAllNodes(list, filterNodes, (void *)courseName);
}

List Student_findAllByMatriculationNumber(List list,int matriculationNumber) {

	int countOfDigitsDesiredMtr = log(matriculationNumber) / log(10);

	bool filterNodes(Node node, size_t index, void *data) {
		Student student = Node_getData(node);
		int currentMtrNumber = Student_getMatriculationNumber(student);
		int countOfDigtsCurrentMtr = log(currentMtrNumber) / log(10);

		if(countOfDigitsDesiredMtr > countOfDigtsCurrentMtr) return false;
		if(countOfDigitsDesiredMtr == countOfDigtsCurrentMtr) return matriculationNumber == currentMtrNumber;

		return ((int)( currentMtrNumber / pow(10, countOfDigtsCurrentMtr - countOfDigtsCurrentMtr))) == matriculationNumber;
	}

	return List_findAllNodes(list, filterNodes, NULL);
}


