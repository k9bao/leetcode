'''
给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
'''
class Solution:
    #def removeDuplicates(self, nums: List[int]) -> int:
    def removeDuplicates(self, nums):
        if len(nums) == 0:
            return 0
        if len(nums) == 1:
            return 1
        newSize = 0
        for i,num in enumerate(nums):
            if i == 0:
                newSize += 1
            elif num != nums[i-1]:
                if newSize != i:
                    nums[newSize] = nums[i]
                newSize += 1
        return newSize

nums = [1,2,3,3,4,4,5,6,6,7]
print(nums[0:Solution().removeDuplicates(nums)])