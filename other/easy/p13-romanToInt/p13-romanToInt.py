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

