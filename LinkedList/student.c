/**
 * This file contains the implementation of the data structure
 * of a student.
 *
 * @file student.h
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */


/**
 * Provides a replacement implementation of the function strncasecmp
 * because this function is not provided by the gcc compiler.
 */
#ifndef strncasecmp
#include <ctype.h>
#include <stddef.h>
#include <string.h>
static
int strncasecmp (const char *s1, const char *s2, size_t n) {
	int cmp = 0;
	char ch1;
	char ch2;
	for(int i = 0; i < n && cmp == 0; i++) {

		if(s1[i] == '\0' || s2[i] == '\0') {
			cmp = strncmp(s1 + i, s2 + i, 1);
			break;
		}

		ch1 = isupper(s1[i]) ? tolower(s1[i]) : s1[i];
		ch2 = isupper(s2[i]) ? tolower(s2[i]) : s2[i];
		cmp = strncmp(&ch1, &ch2, 1);
	}
	return cmp;
}
#endif


/**
 * @def Computes the maximum of \a X and \a Y.
 */
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#include "student.h"

/**
 * The struct for the student data structure.
 */
struct Student {

	/**
	 * The first name of a student as null terminated string.
	 */
	char *firstName;

	/**
	 * The sure name of a student as null terminated string.
	 */
	char *sureName;
	/**
	 * The coure name of student as null terminated string.
	 */
	char *courseName;
	/**
	 * The matriculation number of a student as integer value.
	 */
	int matriculationNumber;
};

//----------------------------------------------------------------------------
// Helper functions
//----------------------------------------------------------------------------

/**
 * Creates a clone of specified null terminated string
 * and returns the pointer of the new created clone.
 *
 * The caller of this function is responsible to deallocate the
 * copied string by him self.
 *
 * @param[in] str	The null terminated string which should be duplicated.
 * @return	The pointer to the new created string copy.
 */
static
char* createStringClone(const char* str) {
	if(str == NULL) return NULL;
	
	int strLen = strlen(str);
	char* strClone = (char *) malloc((strLen + 1) * sizeof(char));
	if(strClone == NULL) {
		perror("String clone failed");
		return NULL;
	}

	strncpy(strClone, str, strLen);
	strClone[strLen] = '\0';
	
	return strClone;
}

/**
 * Helper function which set the a new value to a string attribute of a ::Student.
 * This helper ensures that the old value of string attrbute is deallocated before
 * the new value is set.
 *
 * @param[in] oldString	The old string of the String attribute which should changed.
 * @param[in] newStr	The new string of the String attribute which should changed.
 */
static
void handleNewStringSetter(char **oldString, const char* newStr) {
	if(*oldString != NULL) { 
		free(*oldString);
	}
	*oldString = createStringClone(newStr == NULL ? " " : newStr);
}

/**
 * Helper function which performs a string comparison which
 * checks if \a str startsWith \a strOther. This function
 * ignores the case of the strings.
 *
 * @param[in] str		A null terminated string.
 * @param[in] strOther	A null terminated string.
 * @return True if \a str startsWith \a strOther.
 */
static
bool testIfStringMatches(const char* str, const char* strOther) {
	int lenStr = strlen(str);
	int lenStrOther = strlen(strOther);

	return 0 == strncasecmp(str, strOther, MIN(lenStr, lenStrOther));
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
		perror("Student creation failed");
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
	printf("%-15s %-15s  %-20s  s0%-10d",student->firstName, student->sureName,student->courseName,student->matriculationNumber);
	printf("\n");

}

void Student_printAll(List studentList) {
	if(!studentList) return;
	printf("Count of students: %d\n", List_getSize(studentList));
	printf("%-15s %-15s  %-20s  %-12s\n","First-Name", "Sure-Name", "Course-Name", "Matriculation-Number");
	printf("\n");
	List_ForEach(studentList, Student_PrintHandler, NULL);
}

//----------------------------------------------------------------------------
// DATA STRACTURE find
//----------------------------------------------------------------------------

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

	int countOfDigitsOfDesiredMtr = log(matriculationNumber) / log(10);

	bool filterNodes(Node node, size_t index, void *data) {
		Student student = Node_getData(node);
		int mtrNumber = Student_getMatriculationNumber(student);
		int countOfDigits = log(mtrNumber) / log(10);

		if(countOfDigitsOfDesiredMtr > countOfDigits) return false;
		if(countOfDigitsOfDesiredMtr == countOfDigits) return matriculationNumber == mtrNumber;

		// lets compare the number only the left most digits which are fit into
		// the desired mtrNumber.
		return ((int)( mtrNumber / pow(10, countOfDigits - countOfDigitsOfDesiredMtr))) == matriculationNumber;
	}

	return List_findAllNodes(list, filterNodes, NULL);
}


