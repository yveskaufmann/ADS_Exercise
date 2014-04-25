/**
	
	Project: List
	File: list.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include "list.h"

List * List_create() {
	List *list = (List *) malloc(sizeof(List));
	if(list == NULL) {
		return 0;
	}

	list->elementCount = 0;
	list->root = NULL;
	list->head = NULL;
	list->onBeforeRemove = NULL;

	return list;
}

Node *List_createNode(List *list, void *data) {
	Node *newNode = (Node*) malloc(sizeof(Node));
	if(newNode == NULL) {
		return NULL;
	}
	newNode->data = data;
	newNode->pNext = NULL;
	newNode->pPrev = NULL;
	newNode->attachedList = list;

	return newNode;
}

void List_addFirst(List *list, void *data) {
	Node *newNode = List_createNode(list, data);
	if(newNode == NULL) {
		return;
	}
	List_insertNodeAt(list,newNode, list->root, BEFORE);
}

void List_addLast(List *list, void *data) {
	Node *newNode = List_createNode(list, data);
	if(newNode == NULL) {
		return;
	}
	List_insertNodeAt(list,newNode, list->head, AFTER);
}

Node *List_insertNodeAt(List *list, Node *newNode, Node *position, NodeInsertDirection dir) {

	if(list == NULL || newNode == NULL ) {
		return NULL;
	}

	if( newNode->attachedList != NULL && newNode->attachedList != list) { // is the specified node already attached to a list ?
		return NULL;
	}

	// is the list empty ?
	if(list->root == NULL) {
		newNode->attachedList = list;
		list->head = newNode;
		list->root = newNode;
		list->elementCount++;
		return newNode;
	}

	if( position == NULL || position->attachedList != list) { // is the specified position node attached to this list ?
		return NULL;
	}

	newNode->attachedList = list;
	if(dir == AFTER) {
		Node *oldNextNode = position->pNext;
		position->pNext = newNode;

		newNode->pPrev = position;
		newNode->pNext = oldNextNode;
		if(oldNextNode) {
			oldNextNode->pPrev = newNode;
		} else {
			list->head = newNode;
		}
	}

	if(dir == BEFORE) {
		Node *oldPrevNode = position->pPrev;
		position->pPrev = newNode;

		newNode->pPrev = oldPrevNode;
		newNode->pNext = position;
		if(oldPrevNode) {
			oldPrevNode->pNext = newNode;
		} else {
			list->root = newNode;
		}
	}
	list->elementCount++;

	return NULL;
}

Node* List_getNode(List *list, int index) {

	if(!list || !list->root || index < 0 || index >= list->elementCount) {
		return NULL;
	}

	if(index == 0) {
		return list->root;
	}

	if(index == list->elementCount - 1) {
		return list->head;
	}

	/**
	 * This idea is descriped like this:
	 * This linear search has a simple improvement if the requested
	 * index lies in the left half of the list then the search
	 * start from the start of the list otherwise the search start
	 * from the end of the list. This results in O(n/2).
	 */
	Node *currentNode = NULL;
	size_t offset = 0;
	size_t piviot = (size_t)(list->elementCount / 2);

	if(index < piviot) {
		currentNode = list->root;
		offset = offsetof(Node, pNext);
	} else {
		currentNode = list->head;
		offset = offsetof(Node, pPrev);
		index = (list->elementCount - 1) - index;
	}

	while(currentNode != NULL && --index >= 0) {
		 // retrieve dynamicaly the pPrev or pNext field.
		 // NOTE: A pointer to a structure act as pointer pointer.
		currentNode = *(Node**)((char*)currentNode + offset);
	}
	return index < 0 ? currentNode : NULL;

}

void List_clear(List *list) {

	if(!list || !list->root) {
		return;
	}

	List_deleteAllNodes(list);
	free(list);
}


void List_ForEach(List *list, NodeHandler nodeHandler) {
	if(!list || !list->root || list->elementCount == 0 || !nodeHandler) {
		return;
	}

	Node *currentNode = list->root;
	Node *nextNode = NULL;
	size_t index = 0;
	while(NULL != currentNode) {
		nextNode = currentNode->pNext;
		if(nodeHandler(currentNode, index) == ABORT) {
			break;
		}
		currentNode = nextNode;
		index++;
	}
}

Node* List_detachNode(List *list, Node* node) {
	if(!node || list->elementCount <= 0 || node->attachedList != list) {
		return node;
	}

	Node *next = node->pNext;
	Node *prev = node->pPrev;
	node->pNext = NULL;
	node->pPrev = NULL;
	node->attachedList = NULL;

	list->elementCount--;

	if(!next && !prev) { // is last node ?
		list->head = NULL;
		list->root = NULL;
	}
	else if(!prev) { // is start node ?
		list->root = next;
		next->pPrev = NULL;
	}
	else if(!next) { // is end node ?
		list->head = prev;
		prev->pNext = NULL;
	}
	else { // is inside node ?
		prev->pNext = next;
		next->pPrev = prev;
	}

	return node;
}

Node* List_detachNodeAtIndex(List *list, int index) {
	Node *node = List_getNode(list, index);
	return List_detachNode(list, node);
}

int List_deleteNode(List *list, Node *node) {
	node = List_detachNode(list, node);

	if(NULL == node) {
		return false;
	}

	if(list->onBeforeRemove != NULL) {
		list->onBeforeRemove(node, 0);
	}

	free(node);

	return true;
}

int List_deleteNodeAtIndex(List *list, int index) {
	Node *node = List_getNode(list, index);
	return List_deleteNode(list, node);
}

void List_deleteAllNodes(List *list) {

	NodeHandlerReturnValue removeNode(Node *node, size_t index) {
		return List_deleteNode(list, node);
	}

	List_ForEach(list, removeNode);
}



