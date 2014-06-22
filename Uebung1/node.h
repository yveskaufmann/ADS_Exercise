/**
 * This file contains the interface to the single linked node
 * and double linked node data structure.
 *
 * The interface contains only the public access function to
 * the data structure hence the user of this node could
 * not access the intern node data structure directly.
 * The data structure have to be provided by the
 * implementation of the node data structure.
 * This prevents that the internal state data structure can
 * corrupted by the outside. Furthermore this allows
 * to change the intern data structure without changing the
 * code which uses the node.
 *
 *
 * @file node.h
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#ifndef NODE_H_
#define NODE_H_

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/**
 * The handle to a specific node which have to be assigned to
 * to a node accessor function in order to work with the specific node.
 *
 * The handle is implemented as incomplete type which means
 * the user of this interface could not use the type node
 * as pointer. Hence a user of the node have to use
 * type 'Node' only as handle to specific node.
 *
 */
typedef struct NodeDoupleLinked* Node;

/**
 * A NodeHandler is a interface(function pointer) for a function which
 * is responsible to handle a node in various contexts.
 *
 * For example a NodeHandler implementation could used as iterator
 * function by the function ::List_ForEach. A Implementer of such
 * a function could abort the iteration by returning false.
 *
 * Furthermore the interface is used by the node ::Node_destroy function
 * as handle to a NodeDestroyer function. A user of ::List_create could provide
 * a function of this signature which is responsible to deallocate the memory
 * of the node attribute called data which stores the data of a node.
 * A Implementer of such a function have to return true in order to deallocate all nodes data.
 * Of course a NodeDestroyer is only required for memory which was allocated on
 * the heap.
 *
 * @param[out] 	node	The node should be handled (iterated, deallocated, ...)
 * @param[in] 	index	The sequence number/position of the node called 'node' which have to be handled.
 * @param[in]	data	A optional pointer which is passed by the caller of a nodeHandler in order
 * 						to parameterize the node handler.
 * @return	The implemented function should return true if the iteration should be continued
 * 			otherwise they should return false in order to break off the iteration.
 */
typedef bool (*NodeHandler) (Node node, size_t index, void *data);

/**
 * A NodeComperator is a interface(function pointer) for a function which
 * is responsible to compare two nodes for order.
 *
 * The compare function have to return a negative integer,
 * zero, or a positive integer as the first node is less
 * than, equal to, or greater than the second node.
 *
 * This interface is used by the functions ::List_sort and ::List_mergeSort.
 *
 * @param[in] prevNode 	The first node to be compared.
 * @param[in] nextNode	The second node to be compared.
 *
 * @return a negative integer, zero, or a positive integer as the first node is less than, equal to, or greater than the node.
 */
typedef int (*NodeComperator) (Node prevNode, Node nextNode);

/**
 * Creates a single linked or double linked node.
 * This constructor function assigns the data and determines if
 * a singe or linked list should be created.
 *
 * The node stores only the pointer to the data itself,
 * if a node should returned from a function the data have to be on
 * the heap or be in a higher scope in order to access the data
 * in the outside function.
 *
 * @param[in] data 					A pointer to the data which should stored inside the node.
 * @param[in] isDoupleLinkedNode	A flag which determines if a double or single linked node should be creeated.
 * @return The successfully new created node or NULL if the creation failed.
 */
Node Node_create(void *data, bool isDoupleLinkedNode);

/**
 * Deallocates the memory of the specified node.
 * The allocated node data will not be dellocaten by default,
 * if the deallocation of the node data is desired a dataDestoryHandler
 * have to be provided by the caller of this function. A dataDestoryHandler
 * is only required if ::Node_getData points to memory on the Heap.
 *
 * @param[in] node					The node which should be dallocated.
 * @param[in] dataDestroyHandler	The dataDestroyHandler which is responsible to deallocate
 * 									the memory of the allocated data attribute.
 *
 * @return True if the node was successfully dallocated.
 */
bool Node_destroy(Node node, NodeHandler dataDestroyHandler);

/**
 * Accessor function which returns the data pointer
 * of a specified node.
 *
 * @param[in] 	node The data pointer of a specified node.
 * @return 	The data pointer of the specified node.
 */
void* Node_getData(Node node);

/**
 * Setter function which sets the data pointer a
 * specified node.
 *
 * @param[in] node	The specified node which should obtain the data pointer.
 * @param[in] data	The data pointer which should stored inside the specified node.
 */
void Node_setData(Node node, void *data);

/**
 * Accessor function which returns the handle of the next node
 * of a specified node.

 * @param[in] node	The specified node.
 * @return	The handle of the next node of the specified node.
 */
Node Node_getNext(Node node);

/**
 * Setter function which sets the handle of the next node
 * of a specified node.
 *
 * @param[in] node	The specified node which should obtain the next node handle.
 * @param[in] next	A hande to a node which should be the next node of the specified node.
 */
void Node_setNext(Node node, Node next);

/**
 * Accessor function which returns the handle of the previous node
 * of a specified node.
 *
 * This function is only callable if the specified node is a double linked node,
 * if a single linked list will be provided then a assertion error will be thrown.
 *
 *
 * @param[in] node	The specified node.
 * @return	The handle of the previous node of the specified node.
 */
Node Node_getPrev(Node node);

/**
 * Setter function which sets the handle of the previous node
 * of a specified node.
 *
 * This function is only callable if the specified node is a double linked node,
 * if a single linked list will be provided then a assertion error will be thrown.
 *
 * @param[in] node	The specified node which should obtain the previous node handle.
 * @param[in] next	A hande to a node which should be the previous node of the specified node.
 */
void Node_setPrev(Node node, Node prev);

/**
 * Checks if a specified node is a double or single linked list.
 *
 * @param[in] node	The specified node which should be checked for his type (single or double linked).
 * @return	True if the specified node is a double linked list or false if the node is a single linked list.
 */
bool Node_isDoupleLinkedNode(Node node);

/**
 * Swaps the content of two nodes which exchanges the data attributes of bote node handles.
 *
 * @param firstNode		The first node to be exchanged.
 * @param secondNode	The first node to be exchanged.
 */
void Node_swapNodes(Node firstNode, Node secondNode);

#endif /* NODE_H_ */
