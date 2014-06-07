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
#include <stdbool.h>
#include "node.h"


typedef struct List* List;
typedef enum {
	AFTER,
	BEFORE
} NodeInsertDirection;


/**
 * Just create and initialize root element of the list.
 *
 *
 * @return Pointer to the allocated root List.
 */
List List_create(NodeHandler destroyHandler);

/**
 * Deallocate each element of the list.
 *
 * @param *list the pointer to the list which should be cleared.
 */
void List_destroy(List list);


/**
 *
 * @param list
 * @param newNode
 * @param position
 * @param dir
 * @return
 */
NodePtr List_insertNodeAt(List list, NodePtr newNode, NodePtr position, NodeInsertDirection dir);

/**
 * Appends the specified node to the end of this list.
 *
 * @param list The list which should expanded by the specified node.
 * @param data
 */
void List_addLast(List list, void *data);

/**
 * Inserts the specified node at the beginning of this list.
 *
 * @param list The list which should expanded by the specified node.
 * @param data
 */
void List_addFirst(List list, void *data);

/**
 * Retrieve the  node from a specified list node at a specified index.
 *
 * @param list the specified list.
 * @param index the specified index.
 * @return the address to the requested node if the node exists otherwise <code>null</code>
 */
NodePtr List_getNode(List list, int index);

/**
 * Iterate through the specified list of nodes and call for each node the NodeHandler function.
 *
 * @param list the specified list.
 * @param nodeHandler the NodeHandler which should called for every node.
 */
void List_ForEach(List list, NodeHandler nodeHandler, void *data);

/**
 *
 * @param list
 * @param node
 * @return
 */
NodePtr List_detachNode(List list, NodePtr node);

/**
 *
 * @param list
 * @param index
 * @return
 */
NodePtr List_detachNodeAtIndex(List list, int index);


/**
 *
 * @param list
 * @param node
 * @return
 */
bool List_deleteNode(List list, NodePtr node);

/**
 *
 * @param list
 * @param index
 * @return
 */
bool List_deleteNodeAtIndex(List list, int index);

/**
 *
 * @param list
 * @param filter
 * @return
 */
bool List_deleteAllNodes(List list);

/**
 *
 * @param list
 * @return
 */
int List_size(List list);

/**
 *
 * @param list
 * @param filter
 * @return
 */
NodePtr List_findNode(List list, NodeHandler filter, void *data);

/**
 *
 * @param list
 * @param filter
 * @return
 */
List List_findAllNodes(List list, NodeHandler filter, void *data);


void List_sort(List list, NodeComperator nodeComperator);

void List_mergeSort(List list, NodeComperator nodeComperator);

#endif /* LIST_H_ */
