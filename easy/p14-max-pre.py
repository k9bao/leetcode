'''
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。
说明:

所有输入只包含小写字母 a-z 。
'''
class Solution:
    # def longestCommonPrefix(self, strs: List[str]) -> str:
    def longestCommonPrefix(self, strs):
        if len(strs) == 0:
            return ""
        index = min(len(x) for x in strs)
        while True:
            if index == 0:
                return ""
            if len(set(x[0:index] for x in strs)) == 1:
                return strs[0][0:index]
            else:
                index -= 1

l1 = ["flower","flow","flight"]
print(Solution().longestCommonPrefix(l1))
l2 = ["dog","racecar","car"]
print(Solution().longestCommonPrefix(l2))