/**
 * This file contains the interface to the single linked list
 * and double linked list data structure.
 *
 * The interface contains only the public access function to
 * the data structure hence the user of this list could
 * not access the intern list data structure directly.
 * The data structure have to be provided by the
 * implementation of the list data structure.
 * This prevents that the internal state data structure can
 * corrupted by the outside. Furthermore this allows
 * to change the intern data structure without changing the
 * code which uses the list.
 *
 *
 * @file list.h
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#ifndef _LIST_H_
#define _LIST_H_

#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "node.h"

/**
 * The handle to a specific list which have to be assigned to
 * to a list function in order to work with the specific list.
 *
 * The handle is implemented as incomplete type which means
 * the user of this interface could not use the type List
 * as pointer. Hence a user of the list have to use
 * type 'List' only as handle to specific list.
 *
 */
typedef struct List* List;

/**
 * A enumeration of directions in which a node could be inserted to a list.
 */
typedef enum {
	/**
	 * A node should be inserted after a specific node.
	 */
	AFTER,
	/**
	 * A node should be inserted before a specific node.
	 */
	BEFORE
} NodeInsertDirection;

/**
 * A enumeration of sort orders.
 */
typedef enum {
	/**
	 * A list should be sorted in ascending order.
	 */
	ASC = 1,
	/**
	 * A list should be sorted in descending order.
	 */
	DESC = -1 
} NodeSortOrder;

/**
 * Just creates a empty list and specifies if a single or double linked list should be created.
 *
 * @param isDoubleLinkedList
 * @param destroyHandler
 * @return the list handle to the successfully created list otherwise NULL.
 */
List List_create(bool isDoupleLinkedList, NodeHandler destroyHandler);

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
bool List_addLast(List list, void *data);

/**
 * Inserts the specified node at the beginning of this list.
 *
 * @param list The list which should expanded by the specified node.
 * @param data
 */
bool List_addFirst(List list, void *data);

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
int List_getSize(List list);

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

void List_sort(List list, NodeComperator nodeComperator, NodeSortOrder sortOrder);

void List_mergeSort(List list, NodeComperator nodeComperator, NodeSortOrder sortOrder);

#endif /* LIST_H_ */
