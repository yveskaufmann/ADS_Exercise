/**
 * The default implementation of single and double linked list.
 * This list implemenations is generic which means the
 * implementation for single and douple linked list is the same
 * hence exists some section in the code which only handle a single linked list.
 *
 * @file list.c
 * @author Yves Kaufmann
 * @date 12 Jun 2014
 */

#include "list.h"

/**
 * Struct of the list data structure.
 */
struct List {

	/**
	 * The handle of the first node of this list.
	 * The value NULL signals the list is empty.
	 */
	Node root;

	/**
	 * The handle of the last node of this list.
	 * The value NULL signals the list is empty.
	 */
	Node head;

	/**
	 * The optional assigned destroyHandler which should
	 * be used for node deallocation inside this list.
	 */
	NodeHandler destroyDataHandler;

	/**
	 * The count of nodes in the list.
	 */
	size_t elementCount;

	/**
	 * A flag which indicates that this list is a douple linked list (in the case of true)
	 * or a single linked list in the case of false.
	 */
	bool isDoupleLinkedList;
};


/**
 * Determines the predecessor (previous node) of a specified node.
 *
 * This function is used as fall back implementation for a single linked list
 * which doesn't provide a connection between a node and his predecessor.
 *
 * NOTE: this function is only used internaly inside the list implementation.
 *
 * @param[in] rootNode	The handle of the root node of this list.
 * @param[in] node		The handle of the specified node for which the predecessor should be determined.
 *
 * @return 	The node handle of the predecessor or
 * 		 	NULL if the current node doesn't have a predecessor.
 */
static
Node getPrevNode(Node rootNode, Node node) {
	Node currentNode = rootNode;

	if(rootNode == node) return NULL;

	while(currentNode != NULL && (Node_getNext(currentNode) != node)) {
		currentNode = Node_getNext(currentNode);
	}

	return currentNode;
}

List_t List_create(bool isDoupleLinkedList, NodeHandler destroyHandler) {
	List_t list = (List_t) malloc(sizeof(struct List));
	if(list == NULL) {
		perror("List creation failed");
		return NULL;
	}

	list->elementCount = 0;
	list->root = NULL;
	list->head = NULL;
	list->destroyDataHandler = destroyHandler;
	list->isDoupleLinkedList = isDoupleLinkedList;

	return list;
}

bool List_addFirst(List_t list, void *data) {
	Node newNode = Node_create(data, list->isDoupleLinkedList);
	if(newNode == NULL) {
		return false;
	}
	return List_insertNodeAt(list,newNode, list->root, BEFORE) == newNode;
}

bool List_addLast(List_t list, void *data) {
	Node newNode = Node_create(data, list->isDoupleLinkedList);
	if(newNode == NULL) {
		return false;
	}
	return List_insertNodeAt(list,newNode, list->head, AFTER) == newNode;
}


Node List_insertNodeAt(List_t list, Node newNode, Node position, NodeInsertDirection dir) {

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

	// inserts the newNode in the front of position.
	if(dir == AFTER) {

		Node oldNextNode = Node_getNext(position);
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

	// inserts the newNode in after position.
	if(dir == BEFORE) {

		Node oldPrevNode = list->isDoupleLinkedList ? Node_getPrev(position) : getPrevNode(list->root, position);
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

Node List_getNode(List_t list, int index) {

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
	Node currentNode = NULL;
	Node (*nodeRetriever) (Node) = NULL;
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

void List_destroy(List_t list) {

	if(!list) {
		return;
	}
	
	if(list->root) {
		List_deleteAllNodes(list);
	}
	
	free(list);
}


void List_ForEach(List_t list, NodeHandler nodeHandler, void *data) {
	if(!list || !list->root || list->elementCount == 0 || !nodeHandler) {
		return;
	}

	Node currentNode = list->root;
	Node nextNode = NULL;
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

Node List_detachNode(List_t list, Node node) {
	if(!node || list->elementCount <= 0 ) {
		return node;
	}

	Node next = Node_getNext(node);
	Node prev = list->isDoupleLinkedList ? Node_getPrev(node) : getPrevNode(list->root, node);

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

Node List_detachNodeAtIndex(List_t list, int index) {
	Node node = List_getNode(list, index);
	return List_detachNode(list, node);
}

bool List_deleteNodeAtIndex(List_t list, int index) {
	Node node = List_getNode(list, index);
	return List_deleteNode(list, node);
}


bool List_deleteNode(List_t list, Node node) {
	node = List_detachNode(list, node);

	if(NULL == node) {
		return false;
	}

	Node_destroy(node, list->destroyDataHandler);

	return true;
}


bool List_deleteAllNodes(List_t list) {

	bool removeNode(Node node, size_t index, void *data) {
		return List_deleteNode(list, node);
	}

	List_ForEach(list, removeNode, NULL);

	return true;

}

int List_getSize(List_t list) {
	if(!list) return 0;
	return list->elementCount;
}

Node List_findNode(List_t list, NodeHandler filter, void *filterCriteria) {
	Node desiredNode = NULL;
	
	bool filterNode(Node node, size_t index, void *filterCriteria) {
		if(filter(node, index, filterCriteria)) {
			desiredNode = node;
			return false;
		}
		return true;
	}
	
	List_ForEach(list, filterNode, filterCriteria);
		
	return desiredNode;
}

List_t List_findAllNodes(List_t list, NodeHandler filter, void *filterCriteria) {
	/**
	 * The filteredNodes list contains direct references (handles) to the nodes
	 * of "list" hence a destroyHandler should not provided to the filteredNodes list.
	 * Otherwise this could lead to a invalid state of the list, which means a node
	 * of "list" could be accidentally deleted and this could lead to segmentation fault faulures.
	 */
	List_t filteredNodes = List_create(false, NULL);
	if(filteredNodes == NULL) {
		return NULL;
	}

	bool filterNodes(Node node, size_t index, void *data) {
		if(filter(node, index, data)) {
			List_addLast(filteredNodes, Node_getData(node));
		}
		return true;
	}
	
	List_ForEach(list, filterNodes, filterCriteria);

	return filteredNodes;
}

void List_sort(List_t list, NodeComperator nodeComperator, NodeSortOrder sortOrder) {
	if(!list || !list->root || list->elementCount <= 1 ) {
		return;
	}

	int countOfSwaps;
	Node currNode = NULL;
	Node lastNode = NULL;
	
	do {
		countOfSwaps = 0;
		for(currNode = list->root; Node_getNext(currNode) != lastNode; currNode = Node_getNext(currNode)) {
			Node nextNode = Node_getNext(currNode);
			if( nodeComperator(currNode, nextNode) * sortOrder > 0) {
				Node_swapNodes(currNode, nextNode);
				countOfSwaps++;
			}
		}
		// notice the last node to be able to ignore the already sorted nodes
		lastNode = currNode; 
	} while(countOfSwaps > 0);
}

void List_mergeSort(List_t list, NodeComperator nodeComperator, NodeSortOrder sortOrder) {
	if(!list || !list->root || list->elementCount <= 1 ) {
		return;
	}
	/**
	 * Merged the two splited lists in to one list the
	 * merging works the follwing the most left node of both lists will be
	 * compared and the node with the smallest order number will be removed
	 * from his list and inserted into the new list. This procedure is repeaded until
	 * one list is empty. After this the remaining nodes in the other list will be removed from
	 * his list and added to the new list.
	 *
	 *
	 * @param[in] left 	A pointer to the left list.
	 * @param[in] right A pointer to the right list.
	 * @return A pointer to new allocated list which contains the nodes of left and right.
	 */
	List_t merge(struct List *left, struct List *right) {
		Node node = NULL;

		List_t newList = List_create(list->isDoupleLinkedList, list->destroyDataHandler);
		if(newList == NULL) {
			perror("List mergSort: list creation failed");
			return NULL;
		}
		
		while(left->root != NULL && right->root != NULL) {
			
			if(nodeComperator(left->root, right->root) * sortOrder <= 0) {
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

	/**
	 * Sorts the specified list by splitting the list in to two
	 * sub lists and sorts these sub lists by a recursively calling sort and
	 * then merged into a single list by using the merge algorithm described
	 * in the function merge.
	 *
	 * @param[in] _list 	The list which should sorted.
	 * @return	The sorted sub list.
	 */
	List_t sort(List_t _list) {
		if(_list->elementCount <= 1 || _list == NULL) {
			return _list;
		}
		
		// Starts the splitting of the _list into the two lists left and right.
		int mid = (_list->elementCount / 2);
		Node midNode = List_getNode(_list, mid);
		
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
		// The end of the list splitting
		

		List_t lSorted = sort(&left);
		List_t rSorted = sort(&right);
		List_t result = merge(lSorted, rSorted);
		
		// Ensures that only allocated memory is deallocated
		if(lSorted != NULL && lSorted != &left) {
			free(lSorted);
		}

		// Ensures that only allocated memory is deallocated
		if(rSorted != NULL && rSorted != &right) {
			free(rSorted);
		}

		// The abort condition when a error occurred in the merge function.
		if(lSorted == NULL || rSorted == NULL) {
			return NULL;
		}

		return result;
	}

	List_t newList = sort(list);
	if(newList != NULL) {
		list->root = newList->root;
		list->head = newList->head;
		list->elementCount = newList->elementCount;
		free(newList);
	}
}
