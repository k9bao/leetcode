import copy

'''
输入一个正整数 target ，输出所有和为 target 的连续正整数序列（至少含有两个数）。
序列内的数字由小到大排列，不同序列按照首个数字从小到大排列。
'''
class Solution:
    def findContinuousSequence(self, target):
        if target == 1 or target == 2:
            return [[]]
        listOut = []
        listIn=[]
        for i in range(int(target/2)+1):
            listIn.append(i+1)
            if sum(listIn) == target:
                listOk = copy.copy(listIn)
                del(listIn[0])
                listOut.append(listOk)
            elif sum(listIn) > target:
                del(listIn[0])
                while sum(listIn) >target:
                    del(listIn[0])
                if sum(listIn) == target:
                    listOk = copy.copy(listIn)
                    del(listIn[0])
                    listOut.append(listOk)
            else:
                pass
        return listOut

a = Solution()
print(a.findContinuousSequence(21))
