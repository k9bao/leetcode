'''
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

示例:
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。
看官方解释有三种方法：分制，弹性，动态规划(kadane算法)
'''

class Solution:
    # def maxSubArray(self, nums: List[int]) -> int:
    def maxSubArray(self, nums):
        if len(nums) == 1:#一个元素直接返回
            return nums[0]
        elif min(nums) >= 0:#最小值<=0,最小值就是连续最大值
            return sum(nums)
        elif max(nums) <= 0:#最大值>=0,求和即可
            return max(nums)

        maxsum = nums[0]#连续最大值
        sum1 = nums[0]#局部最大值
        for n in nums[1:]:#从第2个元素开始遍历
            if sum1 < 0:#如果局部求和小于0，说明前边的和对后边没有任何帮助，只会拉低分数，直接放弃
                sum1 = 0
            sum1 += n#局部累加
            if sum1 > maxsum:#保证全局大于局部和
                maxsum = sum1
        return maxsum
    def maxSubArray0(self, nums):#暴力检索，耗时没通过
        max1 = nums[0]
        for i in range(1,len(nums)+1):#分割大小
            for j in range(len(nums)-i+1):#计算每个分割和
                s = sum(nums[j:j+i])
                if s > max1:
                    max1 = s
        return max1

# print(Solution().maxSubArray([-2,1,-3,4,-1,2,1,-5,4])) #6
# print(Solution().maxSubArray([-1])) #-1
# print(Solution().maxSubArray([-2,-1])) #-1
# print(Solution().maxSubArray([1,-1,-2])) #1
# print(Solution().maxSubArray([0,-3,1,1])) #2
# print(Solution().maxSubArray([-2,1])) #1