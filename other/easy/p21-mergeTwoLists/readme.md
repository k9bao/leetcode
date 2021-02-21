21. 合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例 1：

输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：

输入：l1 = [], l2 = []
输出：[]
示例 3：

输入：l1 = [], l2 = [0]
输出：[0]
 
提示：

两个链表的节点数目范围是 [0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按 非递减顺序 排列

## 方案一：迭代

空间复杂度 o(1) 时间复杂度o(m+n)

```C++
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
```

## 方案二：递归

空间复杂度 o(m+n) 时间复杂度o(m+n)

```C++
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
```
