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
	NodeHandler onBeforeRemove;
	size_t elementCount;
	bool isDoupleLinkedList;
};


List List_create() {
	List list = (List) malloc(sizeof(List));
	if(list == NULL) {
		return NULL;
	}

	list->elementCount = 0;
	list->root = NULL;
	list->head = NULL;
	list->onBeforeRemove = NULL;
	list->isDoupleLinkedList = true;

	return list;
}

void List_addFirst(List list, void *data) {
	NodePtr newNode = Node_create(data, list->isDoupleLinkedList);
	if(newNode == NULL) {
		return;
	}
	List_insertNodeAt(list,newNode, list->root, BEFORE);
}

void List_addLast(List list, void *data) {
	NodePtr newNode = Node_create(data, list->isDoupleLinkedList);
	if(newNode == NULL) {
		return;
	}
	List_insertNodeAt(list,newNode, list->head, AFTER);
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

		Node_setPrev(newNode, position);
		Node_setNext(newNode, oldNextNode);

		if(oldNextNode) {
			Node_setPrev(oldNextNode, newNode);
		} else {
			list->head = newNode;
		}
	}

	if(dir == BEFORE) {
		NodePtr oldPrevNode = Node_getPrev(position);
		Node_setPrev(position, newNode);

		Node_setPrev(newNode, oldPrevNode);
		Node_setNext(newNode, position);

		if(oldPrevNode) {
			Node_setNext(oldPrevNode, newNode);
		} else {
			list->root = newNode;
		}
	}
	list->elementCount++;

	return NULL;
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

	if(index < piviot) {
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

void List_clear(List list) {

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
	NodePtr prev = Node_getPrev(node);

	Node_setNext(node, NULL);
	Node_setPrev(node, NULL);
	list->elementCount--;

	if(!next && !prev) { // is last node ?
		list->head = NULL;
		list->root = NULL;
	}
	else if(!prev) { // is start node ?
		list->root = next;
		Node_setPrev(next, NULL);
	}
	else if(!next) { // is end node ?
		list->head = prev;
		Node_setNext(prev, NULL);
	}
	else { // is inside node ?
		Node_setNext(prev, next);
		Node_setPrev(next, prev);
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

	Node_free(node, list->onBeforeRemove);

	return true;
}


bool List_deleteAllNodes(List list) {

	bool removeNode(NodePtr node, size_t index, void *data) {
		return List_deleteNode(list, node);
	}

	List_ForEach(list, removeNode, NULL);

	return true;

}

int List_size(List list) {
	if(!list) return 0;
	return list->elementCount;
}

NodePtr List_findNode(List list, NodeHandler filter, void *data) {
	NodePtr desiredNode = NULL;
	
	bool filterNode(NodePtr node, size_t index, void *data) {
		if(filter(node, index, data)) {
			desiredNode = node;
			return false;
		}
		return true;
	}
	
	List_ForEach(list, filterNode, data);
		
	return desiredNode;
}

List List_findAllNodes(List list, NodeHandler filter, void *data) {
	List filteredNodes = List_create();
	
	bool filterNodes(NodePtr node, size_t index, void *data) {
		if(filter(node, index, data)) {
			List_addLast(filteredNodes, Node_getData(node));
		}
		return true;
	}
	
	List_ForEach(list, filterNodes, data);

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
		List newList = List_create();
		
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
		if(_list->elementCount <= 1) {  
			return _list;
		}
		
		int mid = (_list->elementCount / 2);
		NodePtr midNode = List_getNode(_list, mid);
		
		struct List left = {
			.root =  _list->root,
			.head = Node_getPrev(midNode),
			.elementCount = mid
		};

		struct List right = {
			.root =  midNode,
			.head = _list->head,
			.elementCount = _list->elementCount - left.elementCount
		};
		
		Node_setNext(left.head, NULL);
		Node_setPrev(right.root, NULL);
		
		List *lSorted = sort(&left);
		List *rSorted = sort(&right);
		List *result = merge(lSorted, rSorted);
		
		if(lSorted != &left) {
			free(lSorted);
		}
			
		if(rSorted != &right) {
			free(rSorted);
		}

		return result;
	}

	List newList = sort(list);
	list->root = newList->root;
	list->head = newList->head;
	list->elementCount = newList->elementCount;
	free(newList);
}
