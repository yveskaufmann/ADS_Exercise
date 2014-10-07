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
 * type 'List' only as handle of aspecific list.
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
 * Creates a empty single or double linked list and specifies
 * a optional destroyHandler which should deallocate the memory
 * of the data attribute of a node.
 *
 * The caller of constructor function responsible to deallocate the new list by
 * using ::List_destroy.
 *
 * @param[in] isDoubleLinkedList	A flag which determines if a double linked list should be created or a single linked list.
 * @param[in] destroyHandler 		A opional NodeHandler which is reponsible for deallocating
 * 						 			the allocated memory of the data attribute of a node.
 *
 * @return 	The list handle to the successfully created list otherwise NULL.
 */
List List_create(bool isDoupleLinkedList, NodeHandler destroyHandler);

/**
 * Deallocate a specified list and destroies each node of this list.
 *
 * This operation uses the destroyHandler which was assigned in the List_create operation,
 * to deallocate the data attribute of each node if a destroyHandler was assigned.
 *
 * @param[in] list The specified list which should be destroyed.
 */
void List_destroy(List list);


/**
 * Inserts a node into a list before or after a specified node.
 *
 * @param[in] list 		The list which should obtain the 'newNode'.
 * @param[in] newNode   The node which should inserted into the specified list.
 * @param[in] position	The node after or before the new node should inserted.
 * @param[in] dir		The direction in which
 *
 * @return 	The handle of the successfully inserted node otherwise null.
 */
Node List_insertNodeAt(List list, Node newNode, Node position, NodeInsertDirection dir);

/**
 * Appends the a new node to the end of the specified list.
 *
 * @param[in] list 	The list which should obtain the new node.
 * @param[in] data	The content of the new node.
 *
 * @return 	True, if the insert of the new node was successful.
 */
bool List_addLast(List list, void *data);

/**
 * Inserts a new node at the beginning of the specified list.
 *
 * @param[in] list 	The list which should obtain the new node.
 * @param[in] data 	The content of the new node.
 *
 * @return 	True, if the insert of the new node was successful.
 */
bool List_addFirst(List list, void *data);

/**
 * Returns the node from a specified list by his index.
 * Index means a integer which indicates the sequence number/position of the desired node.
 *
 * @param[in] list 	The specified list which contains the desired node.
 * @param[in] index The sequence number/position of the desired node.
 *
 * @return 	The handle of the desired node which is located at the specified index.
 * 			If the index is invalid NULL will be returned.
 */
Node List_getNode(List list, int index);

/**
 * A for each loop which iterates over each node in a specified list and calls
 * the specified NodeHandler for each node in the list. If one call of nodeHandler
 * call returns false then the the iteration of the remaining nodes will be break off
 * by this function.
 *
 * @param[in] list 			The specified list which should iterated by the nodeHandler.
 * @param[in] nodeHandler 	The NodeHandler which will be called for every node.
 * @param[in] data 			A optional pointer which is passed to the nodeHandler in order
 * 							to parameterize the node handler.
 */
void List_ForEach(List list, NodeHandler nodeHandler, void *data);

/**
 * Removes a node from a specified list but doesn't deallocates the Node itself.
 *
 * @param[in] list	The specified list which contains the node which should be removed from the list.
 * @param[in] node	The node which should detached from the specified list.
 * @return	The handle of the successfully detached node or
 * 			NULL if the node doesn't exists in the specified list.
 */
Node List_detachNode(List list, Node node);

/**
 * Removes the node at position 'index' from a specified list but doesn't deallocates the Node itself.
 * Index means a integer which indicates the sequence number/position of the desired node.
 *
 * @param[in] list	The specified list which contains the node which should be removed from the list.
 * @param[in] index	The sequence number/position of the desired node which should be removed from the list.
 * @return	The handle of the successfully detached node or
 * 			NULL if the node doesn't exists in the specified list.
 */
Node List_detachNodeAtIndex(List list, int index);


/**
 * Removes a node from a specified list and deallocates the Node itself.
 *
 * @param[in] list	The specified list which contains the node which should be removed from the list.
 * @param[in] node	The node which should detached from the specified list and should be deallocated.
 * @return	True if the node was successfully detached and deallocated.
 */
bool List_deleteNode(List list, Node node);

/**
 * Removes the node at position 'index' from a specified list and deallocates the Node itself.
 * Index means a integer which indicates the sequence number/position of the desired node.
 *
 * @param[in] list	The specified list which contains the node which should be removed from the list.
 * @param[in] index	The sequence number/position of the desired node which should be removed from the list.
 * @return  True if the node was successfully detached and deallocated.
 */
bool List_deleteNodeAtIndex(List list, int index);

/**
 * Deletes all nodes from a specified list and deallocates each detached node.
 *
 * @param[in] list	The specified list which nodes should be removed and deleted.
 *
 * @return	True if the deletion of each node was successful.
 */
bool List_deleteAllNodes(List list);

/**
 * Returns the count of nodes in the specified list.
 *
 * @param[in] list 	The specified list for which the size should be determined.
 * @return	The size, the count of nodes in the specified list.
 */
int List_getSize(List list);

/**
 * Searches for a single node in a specified list by using a NodeHandler
 * as filter function.
 *
 * The search algorithm is just a simple linear search because a binary
 * search doesn't perform very well on a pure linked list, the structure of
 * a single or double linked list caused the iteration to the mid node.
 *
 * The NodeHandler have to return a boolean value which
 * indicates that the current handled node is the desired node.
 *
 *
 * @param[in] list		The specified list in which  a node should be searched.
 * @param[in] filter	The filter functions which is used to determine if a node is the searched node.
 * @param[in] data 	A optional pointer which is passed to the filter in order
 * 					to parameterize the filter.
 * @return The handle to the desired node if the desired node was otherwise NULL.
 */
Node List_findNode(List list, NodeHandler filter, void *data);

/**
 * Searches for a set of nodes in a specified list by using a NodeHandler
 * as filter function.
 *
 * The search algorithm is just a simple linear search because a binary
 * search doesn't perform very well on a pure linked list, the structure of
 * a single or double linked list caused the iteration to the mid node.
 *
 * The NodeHandler have to return a boolean value which
 * indicates that the current handled node is the desired node.
 * The caller of this function is reponsible to deallocate the returned
 * list whicht contains the filtered nodes by using List_destroy.
 *
 *
 * @param[in] list		The specified list in which a set of nodes should be searched.
 * @param[in] filter	The filter functions which is used to determine if a node is a searched node.
 * @param[in] data 	A optional pointer which is passed to the filter in order
 * 					to parameterize the filter.
 * @return 	The handle to the list which containe the filtered/ founded nodes.
 * 		   	If theire was an error NULL will be returned.
 */
List List_findAllNodes(List list, NodeHandler filter, void *data);

/**
 * Sorts a specified list with the bubble sort algorithm by using
 * the nodeComperator as compare function which determines the order of two nodes.
 *
 * The compare function have to return a negative integer,
 * zero, or a positive integer as the first node is less
 * than, equal to, or greater than the second node.
 *
 *
 * @param[in] list				The list which should be sorted.
 * @param[in] nodeComperator	The comparator function which should be used for order determination of the nodes.
 * @param[in] sortOrder			The sort order in which the list should be sorted.
 */
void List_sort(List list, NodeComperator nodeComperator, NodeSortOrder sortOrder);

/**
 * Sorts a specified list with the merge sort algorithm by using
 * the nodeComperator as compare function which determines the order of two nodes.
 *
 * The compare function have to return a negative integer,
 * zero, or a positive integer as the first node is less
 * than, equal to, or greater than the second node.
 *
 * @param[in] list				The list which should be sorted.
 * @param[in] nodeComperator	The comparator function which should be used for order determination of the nodes.
 * @param[in] sortOrder			The sort order in which the list should be sorted. (ascending|descending)
 */
void List_mergeSort(List list, NodeComperator nodeComperator, NodeSortOrder sortOrder);

#endif /* LIST_H_ */
