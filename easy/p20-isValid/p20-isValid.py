'''
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。
'''
class Solution:
    # def isValid(self, s: str) -> bool:
    def isValid(self, s):
        if s == "":
            return True
        list1 = []
        for v in s:
            if v == '(' or v == "[" or v == "{":
                list1.append(v)
            elif len(list1) > 0:
                if (v == ')' and list1[-1] == '(') or \
                    (v == ']' and list1[-1] == '[') or \
                    (v == '}' and list1[-1] == '{'):
                    list1 = list1[0:-1]
                else:
                    return False
            else:
                return False
        if len(list1) == 0:
            return True
        else:
            return False


if __name__ == '__main__':
    print(Solution().isValid("()"))
    print(Solution().isValid("()[]{}"))
    print(Solution().isValid("(]"))
    print(Solution().isValid("([)]"))
    print(Solution().isValid("{[]}"))
    print(Solution().isValid("(])"))