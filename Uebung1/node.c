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
	Node next;
}; 

struct NodeDoupleLinked {
	bool isDoupleLinkedNode;
	void *data;
	Node next;
	Node prev;
};

Node Node_create(void *data, bool isDoupleLinkedNode) {
	Node node = NULL;
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








