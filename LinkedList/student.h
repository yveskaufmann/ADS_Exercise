/**
 * This file contains the interface of the data structure
 * of a student.
 *
 * The interface contains only the public access function to
 * the data structure hence the user of this student could
 * not access the intern node data structure directly.
 * The data structure have to be provided by the
 * implementation of the student data structure.
 * This prevents that the internal state data structure can
 * corrupted by the outside. Furthermore this allows
 * to change the intern data structure without changing the
 * code which uses the student.
 *
 *
 * @file student.h
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include "list.h"

/**
 * The handle to a specific student which have to be assigned to
 * to a student function in order to work with the specific student.
 *
 * The handle is implemented as incomplete type which means
 * the user of this interface could not use the type Student
 * as pointer. Hence a user of the student have to use
 * type 'Student' only as handle of a specific student.
 *
 */
typedef struct Student* Student;

/**
 * Creates a new student with a specified firstName, sureName, course of studies and
 * his matriculation number.
 *
 * The memory of the firstName,sureName and courseName will be duplicated by this function
 * in order to securely store this strings. But a caller is reponsible to provide
 * only null terminated strings.
 *
 * A caller is reponsible to deallocate the created Student by him self with
 * the function ::Student_destroy.
 *
 * @param[in] firstName				A null terminated string which contains the first name of this student.
 * @param[in] sureName				A null terminated string which contains the sure name of this student.
 * @param[in] courseName			A null terminated string which contains the name of the course
 * 									of studies of this student.
 * @param[in] matriculationNumber	The matriculation number of this student as integer value.
 * @return
 */
Student Student_create(char *firstName, char *sureName, char *courseName, int matriculationNumber);

/**
 * Deallocates a specified student which was created by the function ::Student_create.
 *
 * @param student The student which should be deallocated.
 */
void Student_destroy(Student student);

/**
 * Accessor function which returns the first name
 * of a specified student as null terminated string.
 *
 * @param[in]	student 	The specified student.
 * @return 	The first name of the specified student as null terminated string.
 */
const char* Student_getFirstName(Student student);

/**
 * Setter function which sets the the first name of a
 * specified student with a null terminated string.
 *
 * @param[in] student	The specified student which should obtain the first name as null terminated string.
 * @param[in] firstName	The first name of the specified student as null terminated string.
 */
void Student_setFirstName(Student student, const char *firstName);

/**
 * Accessor function which returns the sure name
 * of a specified student as null terminated string.
 *
 * @param[in]	student 	The specified student.
 * @return 	The sure name of the specified student as null terminated string.
 */
const char* Student_getSureName(Student student);

/**
 * Setter function which sets the the sure name of a
 * specified student with a null terminated string.
 *
 * @param[in] student	The specified student which should obtain the sure name as null terminated string.
 * @param[in] sureName	The sure name of the specified student as null terminated string.
 */
void Student_setSureName(Student student, const char *sureName);

/**
 * Accessor function which returns the course name
 * of studies of a specified student as null terminated string.
 *
 * @param[in]	student 	The specified student.
 * @return 	The course name of studies of the specified
 * 			student as null terminated string.
 */
const char* Student_getCourseName(Student student);

/**
 * Setter function which sets the the course name
 * of studies of a specified student with a null terminated string.
 *
 * @param[in] student		The specified student which should obtain course name
 * 							of studies as null terminated string.
 * @param[in] courseName	The course name of studies of the specified student
 * 							as null terminated string.
 */
void Student_setCoursName(Student student, const char *courseName);

/**
 * Accessor function which returns the matriculation number
 * of a specified student as integer value.
 *
 * @param[in]	student 	The specified student.
 * @return 	The  matriculation number of the specified
 * 			student as integer value.
 */
int Student_getMatriculationNumber(Student student);

/**
 * Setter function which sets the the matriculation number
 * of a specified student with a integer value.
 *
 * @param[in] student				The specified student which should obtain the
 * 									matriculation number as integer value.
 * @param[in] matriculationNumber	The matriculation number of the specified student
 * 									as integer value.
 */
void Student_setMatriculationNumber(Student student, int matriculationNumber);

/**
 * A ::NodeHandler which is reponsible to deallocate the memory
 * of student which was created by ::Student_create. This Destroy_Handler
 * could be provided to a ::List in order to deallocate ::Student's inside
 * a ::List.
 *
 * @param[in]	node	The node which contains the student which should be deallocated.
 * @param[in] 	index	The sequence number/position of the node called 'node' which have to be destroied.
 * 						But the index is not used by this handler.
 * @param[in] 	data	A optional pointer which is passed by the caller of a nodeHandler in order
 * 						to parameterize the node handler. But this value is not used by this handler.
 * @param[in] data
 * @return true every time because its a DestroyHandler see ::NodeHandler for more details.
 */
bool Student_DestroyHandler(Node node, size_t index, void *data);

/**
 * A ::NodeHandler which is reponsible to print the students in a list
 * to the STDOUT by using the function ::List_ForEach.
 *
 * @param[in]	node	The node which contains the student which should be printed to the stdout.
 * @param[in] 	index	The sequence number/position of the node called 'node' which have to be destroied.
 * 						But the index is not used by this handler.
 * @param[in] 	data	A optional pointer which is passed by the caller of a nodeHandler in order
 * 						to parameterize the node handler. But this value is not used by this handler.
 * @return true every time because its a NodeHandler see ::NodeHandler for more details.
 */
bool Student_PrintHandler(Node node, size_t index, void *data);

/**
 * A ::NodeComperator which compares the two containing students
 * in firstNode and secondNode lexically by the name of the course
 * of studies.
 *
 * This ::NodeComperator is intended to used by the list sort functions
 * ::List_sort and ::List_mergeSort in order to sort a list of students
 * by his course of studies.
 *
 * @param[in] firstNode		The first node which contains the first student which should to be compared.
 * @param[in] secondNode	The second node which contains the second student which should to be compared.
 * @return a negative integer, zero, or a positive integer as the first node is less than, equal to, or greater than the node.
 */
int Student_CourseComperator(Node firstNode, Node secondNode);

/**
 * A ::NodeComperator which compares the two containing students
 * in firstNode and secondNode by his matriculation number.
 *
 * This ::NodeComperator is intended to used by the list sort functions
 * ::List_sort and ::List_mergeSort in order to sort a list of students
 * by his matriculation number.
 *
 * @param[in] firstNode		The first node which contains the first student which should to be compared.
 * @param[in] secondNode	The second node which contains the second student which should to be compared.
 * @return a negative integer, zero, or a positive integer as the first node is less than, equal to, or greater than the node.
 */
int Student_MarticelNrComperator(Node firstNode, Node secondNode);

/**
 * A ::NodeComperator which compares the two containing students
 * in firstNode and secondNode lexically by his name of the course
 * and his matriculation number.
 *
 * This ::NodeComperator is intended to used by the list sort functions
 * ::List_sort and ::List_mergeSort in order to sort a list of students
 * by his name of the course and his matriculation number.
 *
 * @param[in] firstNode		The first node which contains the first student which should to be compared.
 * @param[in] secondNode	The second node which contains the second student which should to be compared.
 * @return a negative integer, zero, or a positive integer as the first node is less than, equal to, or greater than the node.
 */
int Student_DefaultSortComperator(Node firstNode, Node secondNode);

/**
 * Prints a specified student to the stdout.
 *
 * @param[in] student	The student which should be printed on to the stdout.
 */
void Student_print(Student student);

/**
 * Prints all students to the stdout of a specified list
 * which contains only students.
 *
 * @param[in] students	The list of students whichshould be printed on to the stdout.
 */
void Student_printAll(List_t students);

/**
 * Searches any studens in a specified list by his first name.
 *
 * This function makes use of the function ::List_findAllNodes and
 * find all students which first names are starting with \a name. Note
 * this function ignores the case of the first name.
 *
 * @param[in] list	The specified list in which the students should be searched.
 * @param[in] name	The filter criteria for the first name.
 *
 * @return	A list of students which first names matches \a name.
 */
List_t Student_findAllByFirstName(List_t list, const char* name);

/**
 * Searches any studens in a specified list by his sure name.
 *
 * This function makes use of the function ::List_findAllNodes and
 * find all students which sure names are starting with \a name. Note
 * this function ignores the case of the sure name.
 *
 * @param[in] list	The specified list in which the students should be searched.
 * @param[in] name	The filter criteria for the sure name.
 *
 * @return	A list of students which sure names matches \a name.
 */
List_t Student_findAllBySureName(List_t list, const char* name);

/**
 * Searches any studens in a specified list by his course of studies.
 *
 * This function makes use of the function ::List_findAllNodes and
 * find all students which name of course of studies are starting with \a name. Note
 * this function ignores the case of the course name.
 *
 * @param[in] list	The specified list in which the students should be searched.
 * @param[in] name	The filter criteria for the course name.
 *
 * @return	A list of students which course names matches \a name.
 */
List_t Student_findAllByCourseName(List_t list, const char* name);

/**
 * Searches any studens in a specified list by his matriculation number.
 *
 * This function makes use of the function ::List_findAllNodes and
 * find all students which matriculation number starts with \a matriculationNumber.
 * The function compare two matriculation numbers by his digits which means
 * a caller could entered 544 and could find the matriculation number 5443561.
 *
 * @param[in] list				The specified list in which the students should be searched.
 * @param matriculationNumber	The filter criteria for the matriculationNumber.
 * @return	A list of students which matriculation number matches \a matriculationNumber.
 */
List_t Student_findAllByMatriculationNumber(List_t list,int matriculationNumber);

#endif /* _STUDENT_H_ */
