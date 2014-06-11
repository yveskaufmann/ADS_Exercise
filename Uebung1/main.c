/**

 Project: List
 File: main.c
 Purpose:

 @author fxdapokalypse
 @version 1.0 09.04.2014
 */

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "student.h"
#include "readerHelper.h"

#define MAIN_CMD '?'
#define PRINT_CMD 'p'
#define ADD_CMD 'a'
#define DEL_CMD 'd'
#define FILTER_CMD 'f'
#define SORT_BUBBLESORT_CMD 's'
#define SORT_MERGESORT_CMD 'S'
#define QUIT_CMD 'q'
#define YES_CMD 'y'
#define NO_CMD 'n'

#define FIRSTNAME_STUDENTS_PROPERTY 'f'
#define SURENAME_STUDENTS_PROPERTY 's'
#define COURSE_STUDENTS_PROPERTY 'c'
#define MATRICULATION_NR_STUDENTS_PROPERTY 'm'
#define STUDENT_INSERT_START 's'
#define STUDENT_INSERT_END 'e'

static
List createSampleStudentList();

static
void addStudent(List list);

static
void removeStudent(List list);

static
void filterStudent(List list);

int main(int argc, char **argv) {

	char cmd = '?';
	List students = createSampleStudentList();
	for(;;) {
		switch(cmd) {
			case MAIN_CMD:
				printf("\t\tLinked List Example: Students\n");
				printf("\t\t=============================\n");
				printf("\n");
				printf("\t%c - %s\n", ADD_CMD, "Adds a new student to the student list.");
				printf("\t%c - %s\n", DEL_CMD, "Removes a student from the student list.");
				printf("\t%c - %s\n", FILTER_CMD, "Filters the list of students.");
				printf("\t%c - %s\n", PRINT_CMD, "Prints the list of students.");
				printf("\t%c - %s\n", SORT_BUBBLESORT_CMD, "Sorts students in ascending sort order with bubble sort.");
				printf("\t%c - %s\n", SORT_MERGESORT_CMD, "Sorts students in descending sort order with merge sort.");
				printf("\t%c - %s\n", QUIT_CMD, "Exits this application.");
				printf("\t%c - %s\n", MAIN_CMD, "Shows the application help page");
				printf("\n");
				cmd = PRINT_CMD;
				continue;
			break;
			case ADD_CMD:
				addStudent(students);
				cmd = PRINT_CMD;
				continue;
			break;
			case DEL_CMD:
				removeStudent(students);
				cmd = PRINT_CMD;
				continue;
			break;
			case FILTER_CMD:
				filterStudent(students);
			break;
			case PRINT_CMD:
				Student_printAll(students);
			break;
			case SORT_BUBBLESORT_CMD:
				List_sort(students, Student_DefaultSortComperator, ASC);
				cmd = PRINT_CMD;
				continue;
			break;
			case SORT_MERGESORT_CMD:
				List_mergeSort(students, Student_DefaultSortComperator, DESC);
				cmd = PRINT_CMD;
				continue;
			break;
			case QUIT_CMD:
				List_destroy(students);
				exit(EXIT_SUCCESS);
			break;
			default:
				printf("Unknown command \"%c\" entered.\n", cmd);
				cmd = '?';
				continue;
			break;
		}

		printf("\nWhat you wanna do [%c, %c, %c, %c, %c, %c, %c, %c]?\n",
				ADD_CMD, DEL_CMD, FILTER_CMD, PRINT_CMD, SORT_BUBBLESORT_CMD, SORT_MERGESORT_CMD, QUIT_CMD, MAIN_CMD);
		cmd = readChar(NULL);
		printf("\n");

	}

	return 0;
}

static
List createSampleStudentList() {
	List list = List_create(true, Student_DestroyHandler);

	List_addFirst(list,Student_create("Yves", "Kaufmann", "Algorithmen", 544361));
	List_addLast(list, Student_create("Ksenia", "Mbjorova", "BWL", 52135));
	List_addLast(list, Student_create("Ksenia", "Majorova", "BWL", 5134));
	List_addLast(list, Student_create("Ksenia", "Majordva", "BWL", 534));
	List_addLast(list, Student_create("Ksenia", "Majdrova", "BWL", 5443));
	List_addFirst(list, Student_create("Ksenia", "Mbjorova", "BWL", 52));
	List_addLast(list, Student_create("Marcus", "bla", "Algorithmen", 544366));
	List_addLast(list, Student_create("ABA", "XMK", "Algorithmen", 544367));

	return list;
}

static
void addStudent(List list) {
	char firstname[255];
	char surename[255];
	char coursename[255];
	char insertPosition;
	int matriculationNumber;
	Student student = NULL;

	do {
		printf("Please enter the properties for the new student:	\n");
		readline("Firsname", firstname, 255);
		readline("Surename", surename, 255);
		readline("Course", coursename, 255);
		matriculationNumber = readInteger("Matriculation number", 0, INT_MAX);
		printf("\n");
		printf("Please choose the insert position for the new student: \n");
		printf("%c - %s\n", STUDENT_INSERT_START, "Start: inserts the new student at the start of the list.");
		printf("%c - %s\n", STUDENT_INSERT_END, "END: inserts the new student at the end of the list.");
		insertPosition = readChar("Insert Position");
		printf("\nAre you happy with your inputs [%c, %c]?\n", YES_CMD, NO_CMD);
	} while(readChar(NULL) == NO_CMD);

	student = Student_create(firstname, surename, coursename, matriculationNumber);

	if(insertPosition == STUDENT_INSERT_START) {
		List_addFirst(list, student);
	} else {
		List_addLast(list, student);
	}
}

static
void removeStudent(List list) {
	int countOfStudents = List_getSize(list);
	if(countOfStudents == 0) {
		printf("The List of students is empty.");
		return;
	}
	int studentIndex = readInteger("Index of the student which should be removed", 0, countOfStudents - 1);
	List_deleteNodeAtIndex(list, studentIndex);
}

static
void filterStudent(List list) {
	char desiredFilterProperty = 0;
	char filterText[255];
	int matriculationFilter = 0;
	List filteredStudents = NULL;

	printf("%c - %s\n", FIRSTNAME_STUDENTS_PROPERTY, "Filters by the firstname.");
	printf("%c - %s\n", SURENAME_STUDENTS_PROPERTY, "Filters by the lastname.");
	printf("%c - %s\n", COURSE_STUDENTS_PROPERTY,  "Filters by the course.");
	printf("%c - %s\n", MATRICULATION_NR_STUDENTS_PROPERTY,  "Filters by the Matriculation number.");
		
	desiredFilterProperty = readChar("Please choose a propertywhich you wanna use for students filtering?");
	//readKeyWords("Please choose a propertywhich you wanna use for students filtering?",filterText, 255, 4,
	//		FIRSTNAME_STUDENTS_PROPERTY, SURENAME_STUDENTS_PROPERTY, COURSE_STUDENTS_PROPERTY, MATRICULATION_NR_STUDENTS_PROPERTY );
	
	switch(desiredFilterProperty) {
		case FIRSTNAME_STUDENTS_PROPERTY:
			readline("Please enter your firsname filter value", filterText, 255);
			filteredStudents = Student_findAllByFirstName(list, filterText);
		break;
		case SURENAME_STUDENTS_PROPERTY:
			readline("Please enter your surename filter value", filterText, 255);
			filteredStudents = Student_findAllBySureName(list, filterText);
		break;
		case COURSE_STUDENTS_PROPERTY:
			readline("Please enter your course filter value", filterText, 255);
			filteredStudents = Student_findAllByCourseName(list, filterText);
		break;
		case MATRICULATION_NR_STUDENTS_PROPERTY:
			matriculationFilter = readInteger("Please enter your matriculation number filter value", 0, INT_MAX);
			filteredStudents = Student_findAllByMatriculationNumber(list, matriculationFilter);
		break;
		default:
			printf("The entered student property is invalid \"%c\" is invalid.\n", desiredFilterProperty);
			return;
		break;
			
	}

	printf("Filtered Students: \n");
	if(List_getSize(filteredStudents) <= 0) {
		printf("No students were found.\n");
	} else {
		Student_printAll(filteredStudents);
	}

	List_destroy(filteredStudents);
}
