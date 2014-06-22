/**
 * The default implementation of single and double linked node.
 * This node implemenations is generic which means the
 * implementation for single and douple node list is the same.
 * Hence the ::Node_create function creates the corresponding struct
 * which fit the needs for a single or double linked node.
 *
 * NOTE: the functions ::Node_setPrev and ::Node_getPrev are only
 * callable if the specified node is a double linked list.
 *
 * @file node.c
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#include "node.h"
/**
 * This global value is provided by <errno.h> and contains
 * the error number of the last occurred error. This
 * value is used for determining the error message of a occured error.
 */
extern errno;

/**
 * Struct for single linked list.
 */
struct NodeSingleLinked {

	/**
	 * A boolean value which lets you know that this node is a single linked node
	 * if the value is false.
	 *
	 * This have to be the default value of a single linked
	 * node in order to determine the type of a specified node.
	 */
	bool isDoupleLinkedNode;

	/**
	 * The data pointer which points to the the data of this node.
	 * This is implemented as void pointer in order to support differnt
	 * types.
	 */
	void *data;

	/**
	 * The node handle of the next node of this node.
	 *
	 * A next with the value NULL lets you know
	 * that this node doesn't have a successor.
	 */
	Node next;
}; 

/**
 * Struct for double linked list.
 */
struct NodeDoupleLinked {

	/**
	 * A boolean value which lets you know that this node is a double linked node
	 * if the value is true.
	 *
	 * This have to be the default value of a double linked
	 * node in order to determine the type of a specified node.
	 */
	bool isDoupleLinkedNode;

	/**
	 * The data pointer which points to the the data of this node.
	 * This is implemented as void pointer in order to support differnt
	 * types.
	 */
	void *data;

	/**
	 * The node handle of the next node of this node.
	 *
	 * A next with the value NULL lets you know
	 * that this node doesn't have a successor.
	 */
	Node next;

	/**
	 * The node handle of the previouse node of this node.
	 *
	 * A prev with the value NULL lets you know
	 * that this node doesn't have a predecessor.
	 */
	Node prev;
};

Node Node_create(void *data, bool isDoupleLinkedNode) {
	Node node = NULL;
	if(isDoupleLinkedNode) {
		// let's allocate the singly linked node
		node = malloc(sizeof(struct NodeDoupleLinked));
		if(node == NULL) {
			fprintf(stderr, "DoupleLinkedNode creation failed: \"%s\"", strerror(errno));
			return NULL;
		}
		node->isDoupleLinkedNode = true;
		Node_setPrev(node, NULL);
	} else {
		// let's allocate the singly linked node
		node = malloc(sizeof(struct NodeSingleLinked));
		if(node == NULL) {
			fprintf(stderr, "SingleLinkedNode creation failed: \"%s\"", strerror(errno));
			return NULL;
		}
		node->isDoupleLinkedNode = false;
	}
	Node_setNext(node, NULL);
	Node_setData(node, data);
	return node;
}

bool Node_destroy(Node node, NodeHandler dataDestroyHandler) {
	if(!node) return false;

	if(dataDestroyHandler != NULL) {
		dataDestroyHandler(node, 0, Node_getData(node));
	}

	free(node);
	return true;
}

void* Node_getData(Node node) {
	return node->data;
}
void Node_setData(Node node, void *data) {
	node->data = data;
}

Node Node_getNext(Node node) {
	return node->next;
}
void Node_setNext(Node node, Node next) {
	node->next = next;
}

Node Node_getPrev(Node node) {
	assert(Node_isDoupleLinkedNode(node));
	return node->prev;
}

void Node_setPrev(Node node, Node prev) {
	assert(Node_isDoupleLinkedNode(node));
	node->prev = prev;
}

bool Node_isDoupleLinkedNode(Node node) {
	return node->isDoupleLinkedNode;
}

void Node_swapNodes(Node firstNode, Node secondNode) {

	if(!firstNode || !secondNode || firstNode == secondNode) {
		return;
	}

	void *data = firstNode->data;
	firstNode->data = secondNode->data;
	secondNode->data = data;
}








