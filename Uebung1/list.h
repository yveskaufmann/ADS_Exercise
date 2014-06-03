/**
	

	Project: List
	File: list.h
	Purpose: 

	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>
#include <stddef.h>

#define true  1
#define false 0

typedef struct Node Node;
typedef struct List List;

typedef enum {
	AFTER,
	BEFORE
} NodeInsertDirection;

typedef enum {
	CONTINUE = true,
	ABORT = false
} NodeHandlerReturnValue;


typedef NodeHandlerReturnValue (*NodeHandler) (Node *node, size_t index, void *data);
typedef int (*NodeComperator) (Node *prevNode, Node *nextNode);


/**
 * Type definition for a list segment type
 */
struct Node {
	Node *pNext;
	Node *pPrev;
	List *attachedList;
	void *data;
};

/**
 * Type definition for a list segment type
 */
struct List {
	Node *root;
	Node *head;
	size_t elementCount;
	NodeHandler onBeforeRemove;
};

/**
 * Just create and initialize root element of the list.
 *
 *
 * @return Pointer to the allocated root List.
 */
List *List_create();

/**
 * Deallocate each element of the list.
 *
 * @param *list the pointer to the list which should be cleared.
 */
void List_clear(List *list);

/**
 * <p>
 * Allocate a new node with a specified pointer and
 * return the address of the create node.
 * <br>
 * </p>
 *
 * @param list the list pointer for which this node is created.
 * @param data the pointer for the data.
 * @return
 */
Node *List_createNode(List *list, void *data);

/**
 *
 * @param list
 * @param newNode
 * @param position
 * @param dir
 * @return
 */
Node *List_insertNodeAt(List *list, Node *newNode, Node *position, NodeInsertDirection dir);

/**
 * Appends the specified node to the end of this list.
 *
 * @param list The list which should expanded by the specified node.
 * @param data
 */
void List_addLast(List *list, void *data);

/**
 * Inserts the specified node at the beginning of this list.
 *
 * @param list The list which should expanded by the specified node.
 * @param data
 */
void List_addFirst(List *list, void *data);

/**
 * Retrieve the  node from a specified list node at a specified index.
 *
 * @param list the specified list.
 * @param index the specified index.
 * @return the address to the requested node if the node exists otherwise <code>null</code>
 */
Node *List_getNode(List *list, int index);

/**
 * Iterate through the specified list of nodes and call for each node the NodeHandler function.
 *
 * @param list the specified list.
 * @param nodeHandler the NodeHandler which should called for every node.
 */
void List_ForEach(List *list, NodeHandler nodeHandler, void *data);

/**
 *
 * @param list
 * @param node
 * @return
 */
Node *List_detachNode(List *list, Node *node);

/**
 *
 * @param list
 * @param index
 * @return
 */
Node *List_detachNodeAtIndex(List *list, int index);


/**
 *
 * @param list
 * @param node
 * @return
 */
int List_deleteNode(List *list, Node *node);

/**
 *
 * @param list
 * @param index
 * @return
 */
int List_deleteNodeAtIndex(List *list, int index);

/**
 *
 * @param list
 * @param filter
 * @return
 */
void List_deleteAllNodes(List *list);

/**
 *
 * @param list
 * @return
 */
int List_size(List *list);

/**
 *
 * @param list
 * @param filter
 * @return
 */
Node *List_findNode(List *list, NodeHandler filter, void *data);

/**
 *
 * @param list
 * @param filter
 * @return
 */
List *List_findAllNodes(List *list, NodeHandler filter, void *data);

void List_swapNodes(Node *firstNode, Node *lastNode);

void List_sort(List *list, NodeComperator nodeComperator);

void List_mergeSort(List *list, NodeComperator nodeComperator); 

#endif /* LIST_H_ */
