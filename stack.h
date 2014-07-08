/**
 * This file contains the interface to the stack data structure.
 *
 * The interface contains only the public access function to
 * the data structure hence the user of this stack could
 * not access the intern stack data structure directly.
 * The data structure have to be provided by the
 * implementation of the stack data structure.
 * This prevents that the internal state data structure can
 * corrupted by the outside. Furthermore this allows
 * to change the intern data structure without changing the
 * code which uses the stack.
 *
 *
 * @file stack.h
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "list.h"

/**
 * The handle to a specific Stack which have to be assigned to
 * to a Stack function in order to work with the specific Stack.
 *
 * The handle is implemented as incomplete type which means
 * the user of this interface could not use the type Stack
 * as pointer. Hence a user of the stack have to use
 * type 'stack' only as handle of a specific Stack.
 *
 */
typedef struct List* Stack;

/**
 * Creates a empty stack and specifies a optional destroyHandler
 * which should deallocate the memory of the elements in the stack.
 *
 * The caller of constructor function responsible to deallocate the new stack by
 * using ::Stack_destroy.
 *
 * @param[in] destroyHandler 		A opional NodeHandler which is reponsible for deallocating
 * 						 			the allocated memory of the data attribute of a node.
 *
 * @return 	The stack handle to the successfully created stack otherwise NULL.
 */
Stack Stack_create(NodeHandler destroyHandler);

/**
 * Deallocate a specified stack and destroies each element of this stack.
 *
 * This operation uses the destroyHandler which was assigned in the Stack_create operation,
 * to deallocate the memory of each date element if a destroyHandler was assigned.
 *
 * @param[in] stack The specified stack which should be destroyed.
 */
void Stack_destroy(Stack stack);

/**
 * Returns the size of a specified stack.
 *
 * @param[in] stack The specified stack for which the size should be returned.
 */
int Stack_getSize(Stack stack);

/**
 * Inserts a specified data element on top of a specified stack.
 *
 * @param[in] stack The specified stack which should be expanded by the element data.
 * @param[in] data The new data element which should inserted into the stack.
 */
void Stack_push(Stack stack, void* data);

/**
 * Removes and return the data element which lies on top of the stack.
 *
 * @param[in] stack The specified stack which should contains the data element which should be removed.
 * @return the remove data element or null if the stack is empty.
 */
void* Stack_pop(Stack stack);

#endif /* STACK_H_ */
s
