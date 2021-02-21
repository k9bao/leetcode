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

    def twoSum3(self,nums,target):
        # 遍历nums下标i及值v，如果i后边的值与当前值v的和是target，说明满足条件，将i添加到lst里
        lst = [i for i,v in enumerate(nums) if target-v in nums[i+1:]]
        if len(lst) == 1:#
            lst.append(lst[0]+1+nums[lst[0]+1:].index(target-nums[lst[0]]))
        return lst
test = Solution()
print(test.twoSum3([2,7,11,5],9))
print(test.twoSum3([3,3],6))
print(test.twoSum3([3,2,4],6))