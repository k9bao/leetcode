'''
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
你可以假设数组中无重复元素。
'''
class Solution:
    # def searchInsert(self, nums: List[int], target: int) -> int:
    def searchInsert(self, nums, target):
        for i,v in enumerate(nums):
            if v > target or v == target:
                return i
        else:
            return len(nums)

print(Solution().searchInsert([1,3,5,6], 5)) #2
print(Solution().searchInsert([1,3,5,6], 2)) #1
print(Solution().searchInsert([1,3,5,6], 7)) #4
print(Solution().searchInsert([1,3,5,6], 0)) #0
