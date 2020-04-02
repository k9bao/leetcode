'''
判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
你能不将整数转为字符串来解决这个问题吗？
'''

class Solution:
    #def isPalindrome(self, x: int) -> bool:
    def isPalindrome(self, x):
        if x < 0:
            return False
        if x == self.reverse(x):
            return True
        return False

    def reverse(self,x):
        result = 0
        bitNum = 1
        y = x
        # while True:
        #     x = x//10
        #     if x == 0:
        #         break
        #     bitNum *= 10
        bitNum = 10**(len(str(x))-1)
        print(bitNum)
        while True:
            result += (y%10)*bitNum
            bitNum /= 10
            y = y//10
            if y==0:
                break
        print(result)
        return int(result)

print(Solution().isPalindrome(12321))
# print(Solution().isPalindrome(-12321))