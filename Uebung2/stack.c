/**
 * The default implementation of a stack which uses the single and double linked list implementation.
 *
 * @file stack.c
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#include "stack.h"


Stack Stack_create(NodeHandler destroyHandler) {
	return List_create(false, destroyHandler);
}

void Stack_destroy(Stack stack) {
	List_destroy(stack);
}

int Stack_getSize(Stack stack)
{
	return List_getSize(stack);
}

void Stack_push(Stack stack, void* data) {
	List_addLast(stack, data);
}

void* Stack_pop(Stack stack) {
	int size = List_getSize(stack);

	if(size == 0) return NULL;

	Node node = List_detachNodeAtIndex(stack, size - 1);
	void* data = Node_getData(node);

	Node_destroy(node, NULL);

	return data;
}

