/**
	
	Project: List
	File: node.h
	Purpose: 

	@author fxdapokalypse
	@version 1.0 06.06.2014
*/

#ifndef NODE_H_
#define NODE_H_

#include <assert.h>
#include <errno.h>


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct NodeDoupleLinked* Node;
typedef bool (*NodeHandler) (Node node, size_t index, void *data);
typedef int (*NodeComperator) (Node prevNode, Node nextNode);

Node Node_create(void *data, bool isDoupleLinkedNode);
bool Node_destroy(Node node, NodeHandler dataDestroyHandler);

void* Node_getData(Node node);
void Node_setData(Node node, void *data);

Node Node_getNext(Node node);
void Node_setNext(Node node, Node next);

Node Node_getPrev(Node node);
void Node_setPrev(Node node, Node prev);

bool Node_isDoupleLinkedNode(Node node);

void Node_swapNodes(Node firstNode, Node secondNode);

#endif /* NODE_H_ */
