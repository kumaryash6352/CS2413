#include <stdio.h>
#include <stdlib.h>

// stack
typedef struct LListNode {
    int data;
    struct LListNode* next;
} LListNode;

typedef struct Stack {
    LListNode* hd;
} Stack;

void push(Stack* s, int x) {
    LListNode* new_hd = malloc(sizeof(LListNode));
    new_hd->data = x;
    new_hd->next = s->hd;
    s->hd = new_hd;
}

int pop(Stack* s, int* out) {
    if(s->hd) {
        LListNode* to_free = s->hd;
        *out = s->hd->data;
        s->hd = s->hd->next;
        free(to_free);
        return 1;
    }
    return 0;
}

int peek(Stack* s, int* out) {
    if(s->hd) {
        *out = s->hd->data;
        return 1;
    }
    return 0;
}

void stack_free(LListNode* hd) {
    if(hd) {
        LListNode* nxt = hd->next;
        free(hd);
        stack_free(nxt);
    }
}
// end stack

typedef struct MyQueue {
    Stack ins;
    Stack outs;
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* q = malloc(sizeof(MyQueue));
    q->ins.hd = NULL;
    q->outs.hd = NULL;
    return q;
}

void myQueuePush(MyQueue* q, int x) {
    push(&q->ins, x);
}

int myQueuePop(MyQueue* q) {
    // if outs is empty, transfer ins to outs
    if(q->outs.hd == NULL) {
        for(int x; pop(&q->ins, &x); )
            push(&q->outs, x);
    }
    int x;
    pop(&q->outs, &x);
    return x;
}

int myQueuePeek(MyQueue* q) {
    if(q->outs.hd == NULL) {
        for(int x; pop(&q->ins, &x); )
            push(&q->outs, x);
    }
    int x;
    peek(&q->outs, &x);
    return x;
}

int myQueueEmpty(MyQueue* q) {
    return q->ins.hd == NULL && q->outs.hd == NULL;
}

void myQueueFree(MyQueue* q) {
    stack_free(q->ins.hd);
    stack_free(q->outs.hd);
    free(q);
}

int main(void) {
    MyQueue* q = myQueueCreate();
    myQueuePush(q, 1);
    myQueuePush(q, 2);
    myQueuePush(q, 3);
    myQueuePush(q, 4);
    myQueuePush(q, 5);
    for(; !myQueueEmpty(q); printf("pop: %d\n", myQueuePop(q))) ;
}
