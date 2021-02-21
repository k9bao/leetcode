'''
给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。
'''
class Solution:
    # def longestPalindrome(self, s: str) -> str:
    def longestPalindrome(self, s):
        retStr = ""
        for i in range(len(s)):
            start = s[i]
            for j in range(i,len(s)):
                if start == s[j]:
                    if s[i:j+1] == s[i:j+1][::-1]:
                        if len(s[i:j+1]) > len(retStr):
                            retStr = s[i:j+1]
        return retStr


    def longestPalindrome2(self, s):
        ls = list(s)
        retStr = []
        strTemp = []
        for i in range(len(ls)):
            for j in range(i,len(ls)):
                strTemp = ls[i:j+1]
                if strTemp == strTemp[::-1]:
                    if len(strTemp) > len(retStr):
                         retStr = strTemp
        return ''.join(retStr)

    def longestPalindrome1(self, s):
        retStr = ""
        for i in range(len(s)):
            for j in range(i,len(s)):
                if s[i:j+1] == s[i:j+1][::-1]:
                    if len(s[i:j+1]) > len(retStr):
                        retStr = s[i:j+1]
        return retStr

        
print(Solution().longestPalindrome("a")) # a
print(Solution().longestPalindrome("aa")) # aa
print(Solution().longestPalindrome("babad")) # bab 或aba
print(Solution().longestPalindrome("cbbd")) # bb