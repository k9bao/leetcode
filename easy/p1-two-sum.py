import hashlib
'''
给定一个整数数组 nums 和一个目标值 target，
请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
'''
class Solution:
    def twoSum(self, nums, target):
        mapVK = {}#value:index
        for i,v1 in enumerate(nums):
            if target-v1 in mapVK:
                index = mapVK[target-v1]
                return [index,i]
            if v1 not in mapVK:
                mapVK[v1] = i
        return []

    def twoSum2(self, nums, target):
        listIndex = []
        for i,v1 in enumerate(nums):
            for j,v2 in enumerate(nums[i+1:]):
                if v1+v2 == target and (i != j+i+1):
                    return [i,j+i+1]
        return listIndex

test = Solution()
print(test.twoSum([3,3],6))