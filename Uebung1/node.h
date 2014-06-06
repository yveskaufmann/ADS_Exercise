/**
	
	Project: List
	File: node.h
	Purpose: 

	@author fxdapokalypse
	@version 1.0 06.06.2014
*/

#ifndef NODE_H_
#define NODE_H_

#include <stdbool.h>

typedef struct NodeDoupleLinked* NodePtr;
typedef bool (*NodeHandler) (NodePtr node, size_t index, void *data);
typedef int (*NodeComperator) (NodePtr prevNode, NodePtr nextNode);

NodePtr Node_create(void *data, bool isDoupleLinkedNode);

bool Node_destroy(NodePtr node, NodeHandler dataDestroyHandler);

void* Node_getData(NodePtr node);
void Node_setData(NodePtr node, void *data);

NodePtr Node_getNext(NodePtr node);
void Node_setNext(NodePtr node, NodePtr next);

NodePtr Node_getPrev(NodePtr node);
void Node_setPrev(NodePtr node, NodePtr prev);

bool Node_isDoupleLinkedNode(NodePtr node);

void Node_swapNodes(NodePtr firstNode, NodePtr secondNode);

#endif /* NODE_H_ */
