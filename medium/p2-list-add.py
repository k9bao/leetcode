'''
给出两个 非空 的链表用来表示两个非负的整数。其中，它们各自的位数是按照 逆序 的方式存储的，并且它们的每个节点只能存储 一位 数字。
如果，我们将这两个数相加起来，则会返回一个新的链表来表示它们的和。
您可以假设除了数字 0 之外，这两个数都不会以 0 开头。
'''

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Solution:
    def calcNum(self,l1):
        val = l1.val
        bit = 1
        while l1.next != None:
            l1 = l1.next
            bit *= 10
            val += l1.val*bit
        return val

    def calcList(self,val):
        ret = l1 = ListNode(val%10)
        val //= 10 
        while val > 0:
            l1.next = ListNode(val%10)
            l1 = l1.next
            val //= 10
        return ret

    def addTwoNumbers(self, l1, l2):
        return self.calcList(self.calcNum(l1)+self.calcNum(l2))


c1 = ListNode(2)
c1.next = ListNode(4)
c1.next.next = ListNode(3)
#print(Solution().calcNum(c1))

c2 = ListNode(5)
c2.next = ListNode(6)
c2.next.next = ListNode(4)
#print(Solution().calcNum(c2))
#print(Solution().calcNum(c1)+Solution().calcNum(c2))

#c3 = Solution().calcList(1234567)
#print(c3)
#print(Solution().calcNum(c3))
#print(Solution().calcNum(Solution().calcList(10)))

c3 = Solution().addTwoNumbers(c1,c2)
print(Solution().calcNum(c3))