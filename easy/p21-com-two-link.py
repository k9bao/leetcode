'''
将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例：

输入：1->2->4, 1->3->4
输出：1->1->2->3->4->4
'''
# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    # def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
    def mergeTwoLists(self, l1, l2):
        l0 = lCur = ListNode(0)
        while True:
            if l1 == None:
                lCur.next = l2
                break
            elif l2 == None:
                lCur.next = l1
                break
            elif l1.val < l2.val:
                lCur.next = l1
                l1 = l1.next
                lCur = lCur.next
            else:
                lCur.next = l2
                l2 = l2.next
                lCur = lCur.next
        return l0.next

list1 = ListNode(1)
list1.next = ListNode(2)
list1.next.next = ListNode(4)

list2 = ListNode(1)
list2.next = ListNode(3)
list2.next.next = ListNode(4)

list3 = Solution().mergeTwoLists(list1,list2)
while True:
    print(list3.val)
    if list3.next != None:
        list3 = list3.next
    else:
        break