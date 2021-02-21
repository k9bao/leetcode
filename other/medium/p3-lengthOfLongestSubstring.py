'''
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。
'''
class Solution:
    # def lengthOfLongestSubstring(self, s: str) -> int:
    def lengthOfLongestSubstring(self, s):
        maxLen = 0
        subString = []
        for v in s:
            if v in subString:
                if maxLen < len(subString):
                    maxLen = len(subString)
                if subString.index(v) == len(subString)-1:
                    subString = []
                else:
                    subString = subString[subString.index(v)+1:]
                subString.append(v)
            else:
                subString.append(v)
        if maxLen < len(subString):
            maxLen = len(subString)
        return maxLen

# 1. print(Solution().lengthOfLongestSubstring("abcabcbb")) #3
# 2. print(Solution().lengthOfLongestSubstring("bbbbb")) #1
# 3. print(Solution().lengthOfLongestSubstring("pwwkew")) #3
# 4. print(Solution().lengthOfLongestSubstring("aab")) #2
print(Solution().lengthOfLongestSubstring("dvdf")) #3