#include "stackTransition.h"

struct _transition {
    int startNode;
    char character;
    int targetNode;
    Transition next;
    Transition prev;
};

struct _list {
    Transition firstElement;
    Transition lastElement;
};

Transition createTransition( int startNode, char character, int targetNode);

Stack createStack() {
    Stack stack = malloc(sizeof(struct _stack));
    if (stack == NULL) {
        fprintf(stderr, "Can't allocate stack\n");
        exit(EXIT_FAILURE);
    }
    stack->firstElement = NULL;
    stack->lastElement = NULL;
    return stack;
}

void push(Stack stack, int startNode, char character, int targetNode) {
    Transition newTransition = createTransition(startNode, character, targetNode);
    Transition firstElement = stack->firstElement;
    if (firstElement == NULL) {
        stack->lastElement = newTransition;
        stack->firstElement = newTransition;
    } else {
        newTransition->prev = firstElement;
        firstElement->next = newTransition;
        stack->firstElement = newTransition;
    }
}

Transition pop(Stack stack) {
    Transition firstElement = stack->firstElement;
    Transition prevElement = firstElement->prev;
    firstElement->prev = NULL;
    stack->firstElement = prevElement;
    return firstElement;
}

void freeStack(Stack stack) {
    Transition firstElement = stack->firstElement;
    while(firstElement != NULL) {
        Transition acc = firstElement->prev;
        freeTransition(firstElement);
        firstElement = acc;
    }
    free(stack);
}

int getStartNodeFromTransition(Transition transition) {
    return transition->startNode;
}

char getCharacterFromTransition(Transition transition) {
    return transition->character;
}

int getTargetNodeFromTransition(Transition transition) {
    return transition->targetNode;
}

void freeTransition(Transition transition) {
    free(transition);
}

Transition createTransition( int startNode, char character, int targetNode) {
    Transition result = malloc(sizeof(struct _transition));
    if (result == NULL) {
        fprintf(stderr, "Can't allocate transition\n");
        exit(EXIT_FAILURE);
    }
    result->startNode = startNode;
    result->targetNode = targetNode;
    result->character = character;
    result->prev = NULL;
    result->next = NULL;
    return result;
}