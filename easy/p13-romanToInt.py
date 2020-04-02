'''
罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。
12 写做 XII ，即为 X + II 。
27 写做  XXVII, 即为 XX + V + II 。
通常情况下，罗马数字中小的数字在大的数字的右边。
但也存在特例，例如 4 不写做 IIII，而是 IV。
数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。
同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。

给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。
'''
class Solution:
    def __init__(self):
        self.m = {}
        self.m["IV"] = 4
        self.m["IX"] = 9
        self.m["XL"] = 40
        self.m["XC"] = 90
        self.m["CD"] = 400
        self.m["CM"] = 900
        self.m["I"] = 1
        self.m["V"] = 5
        self.m["X"] = 10
        self.m["L"] = 50
        self.m["C"] = 100
        self.m["D"] = 500
        self.m["M"] = 1000
    # def romanToInt(self, s: str) -> int:
    def romanToInt(self, s):
        num = 0
        while True:
            if len(s) == 0:
                break
            if len(s) >= 2:
                if s[0:2] in self.m.keys():
                    num += self.m[s[0:2]]
                    s = s[2:]
                else:
                    num += self.m[s[0]]
                    s = s[1:]
            else:
                num += self.m[s[0]]
                s = s[1:]
        return num

#IVXLCDM -1 5 10 50 100 500 1000
print(Solution().romanToInt("IV"))
print(Solution().romanToInt("MDCLXVI"))
print(Solution().romanToInt("DC"))
print(Solution().romanToInt("CD"))

