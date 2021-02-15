'''
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
'''

class Solution:
    # def removeElement(self, nums: List[int], val: int) -> int:
    def removeElement(self, nums, val):
        preIndex = 0
        lastIndex = len(nums)-1
        while True:
            if preIndex < lastIndex:
                if nums[preIndex] == val:
                    nums[preIndex],nums[lastIndex] = nums[lastIndex],nums[preIndex]
                    lastIndex -= 1
                else:
                    preIndex += 1
            elif preIndex == lastIndex:
                if nums[preIndex] != val:
                    preIndex +=1
                return preIndex
            else:
                return preIndex

            
nums = [3,2,2,3,5,8,9,4,2,5,6,3,2,7,3]
# Solution().swap(nums,1,3)
print(nums)
print(nums[0:Solution().removeElement(nums,3)])