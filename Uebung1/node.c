/**
	
	Project: List
	File: node.c
	Purpose: 

	@author fxdapokalypse
	@version 1.0 06.06.2014
*/

#include "node.h"

extern errno;

struct NodeSingleLinked {
	bool isDoupleLinkedNode;
	void *data;
	NodePtr next;
}; 

struct NodeDoupleLinked {
	bool isDoupleLinkedNode;
	void *data;
	NodePtr next;
	NodePtr prev;
};

NodePtr Node_create(void *data, bool isDoupleLinkedNode) {
	NodePtr node = NULL;
	if(isDoupleLinkedNode) {
		node = malloc(sizeof(struct NodeDoupleLinked));
		if(node == NULL) {
			fprintf(stderr, "DoupleLinkedNode creation failed: \"%s\"", strerror(errno));
			return NULL;
		}
		node->isDoupleLinkedNode = true;
		Node_setPrev(node, NULL);
	} else {
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

bool Node_destroy(NodePtr node, NodeHandler dataDestroyHandler) {
	if(!node) return false;

	if(dataDestroyHandler != NULL) {
		dataDestroyHandler(node, 0, Node_getData(node));
	}

	free(node);
	return true;
}

void* Node_getData(NodePtr node) {
	return node->data;
}
void Node_setData(NodePtr node, void *data) {
	node->data = data;
}

NodePtr Node_getNext(NodePtr node) {
	return node->next;
}
void Node_setNext(NodePtr node, NodePtr next) {
	node->next = next;
}

NodePtr Node_getPrev(NodePtr node) {
	assert(Node_isDoupleLinkedNode(node));
	return node->prev;
}

void Node_setPrev(NodePtr node, NodePtr prev) {
	assert(Node_isDoupleLinkedNode(node));
	node->prev = prev;
}

bool Node_isDoupleLinkedNode(NodePtr node) {
	return node->isDoupleLinkedNode;
}

void Node_swapNodes(NodePtr firstNode, NodePtr secondNode) {

	if(!firstNode || !secondNode || firstNode == secondNode) {
		return;
	}

	void *data = firstNode->data;
	firstNode->data = secondNode->data;
	secondNode->data = data;
}








