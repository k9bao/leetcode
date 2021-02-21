#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode ret;
        ListNode *p = &ret;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                p->next = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                l2 = l2->next;
            }
            p = p->next;
        }
        p->next = (l1 != nullptr) ? l1 : l2;
        return ret.next;
    }
    ListNode *mergeTwoLists2(ListNode *l1, ListNode *l2) {
        if (l2 == nullptr) {
            return l1;
        } else if (l1 == nullptr) {
            return l2;
        } else if (l1->val < l2->val) {
            l1->next = mergeTwoLists2(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists2(l2->next, l1);
            return l2;
        }
    }
};

int main() {
    Solution test;
    ListNode l13(4);
    ListNode l12(2, &l13);
    ListNode l1(1, &l12);

    ListNode l23(4);
    ListNode l22(3, &l23);
    ListNode l2(1, &l22);
    auto ret = test.mergeTwoLists2(&l1, &l2);
    cout << ret << endl;
    //[1, 1, 2, 3, 4, 4];
    while (ret) {
        cout << ret->val << endl;
        ret = ret->next;
    }

    return 0;
}
