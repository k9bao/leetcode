'''
给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
'''
'''
给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。
'''

class Solution:
    def reverse(self, x):
        sign = 1
        if x < 0:
            x = -x
            sign = -1
        l1 = []
        
        while x > 0:
            l1.append(x%10)
            x //=10
        result = sum([x*(10**(len(l1)-i-1)) for i, x in enumerate(l1)])
        if result >= 2**31:
            result = 0
        return int(result)*sign
    def reverse1(self, x):
        sign = 1
        if x < 0:
            x = -x
            sign = -1
        l1 = []
        while x > 0:
            l1.append(x%10)
            x //=10
        result = 0
        maxBit = 10**(len(l1)-1)
        for i in l1:
            result += i*maxBit
            maxBit /= 10
        if result >= 2**31:
            result = 0
        return int(result)*sign

print(Solution().reverse(123))
# print(Solution().reverse(1534236469))
# print(Solution().reverse(123456789))
# print(Solution().reverse(-12345))