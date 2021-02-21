'''
给定一个 haystack 字符串和一个 needle 字符串，
在 haystack 字符串中找出 needle 字符串出现的
第一个位置 (从0开始)。如果不存在，则返回-1。
'''
class Solution:
    # def strStr(self, haystack: str, needle: str) -> int:
    def strStr(self, haystack, needle):
        if needle == "":
            return 0
        if len(haystack) < len(needle):
            return -1
        for i in range(len(haystack)-len(needle)+1):
            if haystack[i:i+len(needle)] == needle:
                return i
        return -1

print(Solution().strStr("hello","ll")) #2
print(Solution().strStr("aaaaa","bba")) #-1
