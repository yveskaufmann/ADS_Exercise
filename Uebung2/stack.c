#include "stack.h"

void Stack_Create(Stack *stack, int maxSize) {
	stack->content = (StackElement*) malloc( maxSize *  sizeof(StackElement));
	
	if (stack->content != NULL)   
		return;
	stack->maxSize = maxSize;
	stack->top = -1;
}

void Stack_Clear(Stack *stack) {
	free(stack->content);
}


int Stack_push(Stack *stack, StackElement data) {
	if((stack->top) >= stack->maxSize) {
		return -1;
	}
	
	stack->content[++stack->top] = data;
	return 0;
}

StackElement * Stack_pop(Stack *stack) {
	if(stack->top <= 0) {
		return 0;
	}
	return &stack->content[stack->top--];
}

