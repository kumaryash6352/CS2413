#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void removeElementsP(struct ListNode* hd, struct ListNode* tl, int v) {
    if(!hd) return;
    if(hd->val != v) {
        tl->next = malloc(sizeof(struct ListNode));
        tl->next->val = hd->val;
        tl->next->next = NULL;
        tl = tl->next;
    }
    removeElementsP(hd->next, tl, v);
}

struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* throwawayHd = malloc(sizeof(struct ListNode));
    throwawayHd->val = 0;
    throwawayHd->next = NULL;
    removeElementsP(head, throwawayHd, val);
    struct ListNode* res = throwawayHd->next;
    free(throwawayHd);
    return res;
}
