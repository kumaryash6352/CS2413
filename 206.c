#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};
// [0, a, b, c, d ]
struct ListNode* reverseListP(struct ListNode* prv, struct ListNode* hed) {
    if(!hed) return prv;
    struct ListNode* nxt = hed->next;
    hed->next = prv;
    return reverseListP(hed, nxt);
}

struct ListNode* reverseList(struct ListNode* head) {
    if(!head) return reverseListP(NULL, NULL);
    struct ListNode* hed = head->next;
    head->next = NULL;
    return reverseListP(head, hed);
}
