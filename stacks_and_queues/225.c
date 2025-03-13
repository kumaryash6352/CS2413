#include <stdio.h>
#include <stdlib.h>

typedef int bool;

// q
typedef struct LListNode {
    int data;
    struct LListNode* next;
} LinkedList;

typedef struct Queue {
    struct LListNode* hd;
    struct LListNode* tl;
} Queue;

Queue q_init() {
    return (Queue) { .hd = NULL, .tl = NULL };
}

void q_push(Queue* q, int x) {
    if(q->hd == NULL) {
        q->hd = malloc(sizeof(struct LListNode));
        q->hd->data = x;
        q->hd->next = NULL;
        q->tl = q->hd;
    } else {
        struct LListNode* old_tl = q->tl;
        q->tl = malloc(sizeof(struct LListNode));
        old_tl->next = q->tl;
        q->tl->next = NULL;
        q->tl->data = x;
    }
}

int q_pop(Queue* q, int* out) {
    int has_more = q->hd != NULL;
    if(has_more) {
        struct LListNode* old_hd = q->hd;
        q->hd = q->hd->next;
        *out = old_hd->data;
        free(old_hd);
    }
    return has_more;
}

int q_free(Queue* q) {
    for(int out; q_pop(q, &out););
    return 0;
}

int q_peek(Queue* q, int* out) {
    if(q->hd)
        *out = q->hd->data;
    return q->hd != NULL;
}
// end q


typedef struct {
    Queue q1;
    Queue q2;
} MyStack;


MyStack* myStackCreate() {
    MyStack* s = malloc(sizeof(MyStack));
    s->q1 = q_init();
    s->q2 = q_init();
    return s;
}

void myStackPush(MyStack* s, int x) {
    Queue* pop;
    Queue* push;
    int out;
    if(q_peek(&s->q1, &out)) {
        pop = &s->q1;
        push = &s->q2;
    } else {
        pop = &s->q2;
        push = &s->q1;
    }

    q_push(push, x);
    for(int out; q_pop(pop, &out);)
        q_push(push, out);
}

int myStackPop(MyStack* s) {
    int out;
    Queue* q = q_peek(&s->q1, &out) ? &s->q1 : &s->q2;
    q_pop(q, &out);
    return out;
}

int myStackTop(MyStack* s) {
    int out;
    Queue* q = q_peek(&s->q1, &out) ? &s->q1 : &s->q2;
    q_peek(q, &out);
    return out;
}

bool myStackEmpty(MyStack* s) {
    return !s->q1.hd && !s->q2.hd;
}

void myStackFree(MyStack* s) {
    q_free(&s->q1);
    q_free(&s->q2);
    free(s);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);

 * int param_2 = myStackPop(obj);

 * int param_3 = myStackTop(obj);

 * bool param_4 = myStackEmpty(obj);

 * myStackFree(obj);
*/

int main(void) {
    MyStack* s = myStackCreate();
    myStackPush(s, 1);
    myStackPush(s, 2);
    myStackPush(s, 3);
    myStackPush(s, 4);
    myStackPush(s, 5);
    for(; !myStackEmpty(s); printf("pop: %d\n", myStackPop(s))) ;
}
