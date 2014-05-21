#ifndef __STACK_H__
#define __STACK_H_

#include <stdlib.h>

	typedef unsigned int StackElement;
	typedef struct _Stack Stack;
	struct _Stack {
		StackElement *content;
		int maxSize;
		int top;
	};

	void Stack_Create(Stack *stack, int maxSize);

	void Stack_Clear(Stack *stack);

	int Stack_push(Stack *stack, StackElement data);
	StackElement * Stack_pop(Stack *stack);
	

#endif
