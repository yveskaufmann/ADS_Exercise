/**
	
	Project: List
	File: list.c
	Purpose: 
	@author fxdapokalypse
	@version 1.0 09.04.2014
*/

#include "list.h"


/**
 * Type definition for a list segment type
 */
struct List {
	NodePtr root;
	NodePtr head;
	NodeHandler destroyDataHandler;
	size_t elementCount;
	bool isDoupleLinkedList;
};


static
NodePtr getPrevNode(NodePtr rootNode, NodePtr node) {
	NodePtr currentNode = rootNode;

	if(rootNode == node) return NULL;

	while(currentNode != NULL && (Node_getNext(currentNode) != node)) {
		currentNode = Node_getNext(currentNode);
	}

	return currentNode;
}

List List_create(bool isDoupleLinkedList, NodeHandler destroyHandler) {
	List list = (List) malloc(sizeof(struct List));
	if(list == NULL) {
		fprintf(stderr, "List creation failed: \"%s\"", strerror(errno));
		return NULL;
	}

	list->elementCount = 0;
	list->root = NULL;
	list->head = NULL;
	list->destroyDataHandler = destroyHandler;
	list->isDoupleLinkedList = isDoupleLinkedList;

	return list;
}

bool List_addFirst(List list, void *data) {
	NodePtr newNode = Node_create(data, list->isDoupleLinkedList);
	if(newNode == NULL) {
		return false;
	}
	List_insertNodeAt(list,newNode, list->root, BEFORE);
	return true;
}

bool List_addLast(List list, void *data) {
	NodePtr newNode = Node_create(data, list->isDoupleLinkedList);
	if(newNode == NULL) {
		return false;
	}
	List_insertNodeAt(list,newNode, list->head, AFTER);
	return true;
}


NodePtr List_insertNodeAt(List list, NodePtr newNode, NodePtr position, NodeInsertDirection dir) {

	if(list == NULL || newNode == NULL  ) {
		return NULL;
	}

	// is the list empty ?
	if(list->root == NULL) {
		list->head = newNode;
		list->root = newNode;
		list->elementCount++;
		return newNode;
	}

	if(position == NULL) return NULL;

	if(dir == AFTER) {

		NodePtr oldNextNode = Node_getNext(position);
		Node_setNext(position, newNode);

		if(list->isDoupleLinkedList) {
			Node_setPrev(newNode, position);
		}
		Node_setNext(newNode, oldNextNode);

		if(oldNextNode && list->isDoupleLinkedList) {
			Node_setPrev(oldNextNode, newNode);
		} else {
			list->head = newNode;
		}
	}

	if(dir == BEFORE) {

		NodePtr oldPrevNode = list->isDoupleLinkedList ? Node_getPrev(position) : getPrevNode(list->root, position);
		if(list->isDoupleLinkedList) {
			Node_setPrev(position, newNode);
			Node_setPrev(newNode, oldPrevNode);
		}
		Node_setNext(newNode, position);

		if(oldPrevNode) {
			Node_setNext(oldPrevNode, newNode);
		} else {
			list->root = newNode;
		}
	}
	list->elementCount++;

	return newNode;
}

NodePtr List_getNode(List list, int index) {

	if(!list || !list->root || index < 0 || index >= list->elementCount) {
		return NULL;
	}

	if(index == 0) {
		return list->root;
	}

	if(index == list->elementCount - 1) {
		return list->head;
	}

	/**
	 * This idea is descriped like this:
	 * This linear search has a simple improvement if the requested
	 * index lies in the left half of the list then the search
	 * start from the start of the list otherwise the search start
	 * from the end of the list.
	 */
	NodePtr currentNode = NULL;
	NodePtr (*nodeRetriever) (NodePtr) = NULL;
	size_t piviot = (size_t) (list->elementCount / 2);

	if(!list->isDoupleLinkedList || index < piviot) {
		currentNode = list->root;
		nodeRetriever = Node_getNext;
	} else {
		currentNode = list->head;
		index = (list->elementCount - 1) - index;
		nodeRetriever = Node_getPrev;
	}

	while(currentNode != NULL && --index >= 0) {
		 // retrieve dynamicaly the pPrev or pNext field.
		currentNode = nodeRetriever(currentNode);
	}
	return index < 0 ? currentNode : NULL;

}

void List_destroy(List list) {

	if(!list) {
		return;
	}
	
	if(list->root) {
		List_deleteAllNodes(list);
	}
	
	free(list);
}


void List_ForEach(List list, NodeHandler nodeHandler, void *data) {
	if(!list || !list->root || list->elementCount == 0 || !nodeHandler) {
		return;
	}

	NodePtr currentNode = list->root;
	NodePtr nextNode = NULL;
	size_t index = 0;
	while(NULL != currentNode) {
		nextNode = Node_getNext(currentNode);
		if(!nodeHandler(currentNode, index, data)) {
			break;
		}
		currentNode = nextNode;
		index++;
	}
}

NodePtr List_detachNode(List list, NodePtr node) {
	if(!node || list->elementCount <= 0 ) {
		return node;
	}

	NodePtr next = Node_getNext(node);
	NodePtr prev = list->isDoupleLinkedList ? Node_getPrev(node) : getPrevNode(list->root, node);

	Node_setNext(node, NULL);
	if(list->isDoupleLinkedList) Node_setPrev(node, NULL);
	list->elementCount--;

	if(!next && !prev) { // is last node ?
		list->head = NULL;
		list->root = NULL;
	}
	else if(!prev) { // is start node ?
		list->root = next;
		if(list->isDoupleLinkedList) Node_setPrev(next, NULL);
	}
	else if(!next) { // is end node ?
		list->head = prev;
		Node_setNext(prev, NULL);
	}
	else { // is inside node ?
		Node_setNext(prev, next);
		if(list->isDoupleLinkedList) Node_setPrev(next, prev);
	}
	return node;
}

NodePtr List_detachNodeAtIndex(List list, int index) {
	NodePtr node = List_getNode(list, index);
	return List_detachNode(list, node);
}

bool List_deleteNodeAtIndex(List list, int index) {
	NodePtr node = List_getNode(list, index);
	return List_deleteNode(list, node);
}


bool List_deleteNode(List list, NodePtr node) {
	node = List_detachNode(list, node);

	if(NULL == node) {
		return false;
	}

	Node_destroy(node, list->destroyDataHandler);

	return true;
}


bool List_deleteAllNodes(List list) {

	bool removeNode(NodePtr node, size_t index, void *data) {
		return List_deleteNode(list, node);
	}

	List_ForEach(list, removeNode, NULL);

	return true;

}

int List_getSize(List list) {
	if(!list) return 0;
	return list->elementCount;
}

NodePtr List_findNode(List list, NodeHandler filter, void *filterCriteria) {
	NodePtr desiredNode = NULL;
	
	bool filterNode(NodePtr node, size_t index, void *filterCriteria) {
		if(filter(node, index, filterCriteria)) {
			desiredNode = node;
			return false;
		}
		return true;
	}
	
	List_ForEach(list, filterNode, filterCriteria);
		
	return desiredNode;
}

List List_findAllNodes(List list, NodeHandler filter, void *filterCriteria) {
	List filteredNodes = List_create(false, NULL);
	if(filteredNodes == NULL) {
		return NULL;
	}

	bool filterNodes(NodePtr node, size_t index, void *data) {
		if(filter(node, index, data)) {
			List_addLast(filteredNodes, Node_getData(node));
		}
		return true;
	}
	
	List_ForEach(list, filterNodes, filterCriteria);

	return filteredNodes;
}

void List_sort(List list, NodeComperator nodeComperator) {
	if(!list || !list->root || list->elementCount <= 1 ) {
		return;
	}

	int countOfSwaps;
	NodePtr currNode = NULL;
	NodePtr lastNode = NULL;
	
	do {
		countOfSwaps = 0;
		for(currNode = list->root; Node_getNext(currNode) != lastNode; currNode = Node_getNext(currNode)) {
			NodePtr nextNode = Node_getNext(currNode);
			if( nodeComperator(currNode, nextNode) > 0) {
				Node_swapNodes(currNode, nextNode);
				countOfSwaps++;
			}
		}
		// notice the last node to be able to ignore the already sorted nodes
		lastNode = currNode; 
	} while(countOfSwaps > 0);
}

void List_mergeSort(List list, NodeComperator nodeComperator) {
	if(!list || !list->root || list->elementCount <= 1 ) {
		return;
	}

	List merge(struct List *left, struct List *right) {
		NodePtr node = NULL;

		List newList = List_create(list->isDoupleLinkedList, list->destroyDataHandler);
		if(newList == NULL) {
			fprintf(stderr, "List mergSort: list creation failed: \"%s\"", strerror(errno));
			return NULL;
		}
		
		while(left->root != NULL && right->root != NULL) {
			
			if(nodeComperator(left->root, right->root) <= 0) {
				node = List_detachNode(left, left->root);	
			} else {
				node = List_detachNode(right, right->root);
			}

			List_insertNodeAt(newList, node, newList->head, AFTER);     
		}

		while(left->root != NULL) {
			node = List_detachNode(left, left->root);	
			List_insertNodeAt(newList, node, newList->head, AFTER);     
		}
				
		while(right->root != NULL) {
			node = List_detachNode(right, right->root);	
			List_insertNodeAt(newList, node, newList->head, AFTER);     
		}

		return newList;
	} 
		
	List sort(List _list) {
		if(_list->elementCount <= 1 || _list == NULL) {
			return _list;
		}
		
		int mid = (_list->elementCount / 2);
		NodePtr midNode = List_getNode(_list, mid);
		
		struct List left = {
			.root =  _list->root,
			.head = (_list->isDoupleLinkedList ? Node_getPrev(midNode) : getPrevNode(_list->root, midNode)),
			.elementCount = mid,
			.isDoupleLinkedList = _list->isDoupleLinkedList
		};

		struct List right = {
			.root =  midNode,
			.head = _list->head,
			.elementCount = _list->elementCount - left.elementCount,
			.isDoupleLinkedList = _list->isDoupleLinkedList
		};
		
		Node_setNext(left.head, NULL);
		if(_list->isDoupleLinkedList) {
			Node_setPrev(right.root, NULL);
		}

		
		List lSorted = sort(&left);
		List rSorted = sort(&right);
		List result = merge(lSorted, rSorted);
		
		if(lSorted != NULL && lSorted != &left) {
			free(lSorted);
		}
			
		if(rSorted != NULL && rSorted != &right) {
			free(rSorted);
		}

		if(lSorted == NULL || rSorted == NULL) {
			return NULL;
		}

		return result;
	}

	List newList = sort(list);
	if(newList != NULL) {
		list->root = newList->root;
		list->head = newList->head;
		list->elementCount = newList->elementCount;
		free(newList);
	}
}
