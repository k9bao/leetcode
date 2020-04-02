'''
「外观数列」是一个整数序列，从数字 1 开始，序列中的每一项都是对前一项的描述。前五项如下：
1.     1               6. 312211
2.     11              7. 13112221
3.     21              8. 1113213211
4.     1211            9. 31131211131221
5.     111221          10.13211311123113112211
1 被读作  "one 1"  ("一个一") , 即 11。
11 被读作 "two 1s" ("两个一"）, 即 21。
21 被读作 "one 2",  "one 1" （"一个二" ,  "一个一") , 即 1211。
1211 被读作 "one 1" "one 2" "two 1"(一个一，一个二，二个一)，既111221

给定一个正整数 n（1 ≤ n ≤ 30），输出外观数列的第 n 项。

注意：整数序列中的每一项将表示为一个字符串。
'''

class Solution:
    #基本思路就是统计相同元素个数size+value塞到新的list中(lnew),循环执行
    #def countAndSay(self, n: int) -> str:
    def countAndSay(self, n):
        if n == 1:#直接返回
            return "1"
        l = [1]
        for _ in range(n-1):#除去1，遍历n-1次
            lnew = []
            size = 0
            last = -1
            for x in l:
                if last == -1:#第一次赋值
                    last = x
                    size = 1
                elif x == last:#相同+1
                    size += 1
                else:#不同统计
                    lnew.append(size)
                    lnew.append(last)
                    size = 1
                    last = x
            lnew.append(size)#最后一次统计
            lnew.append(last)
            l = lnew #继续遍历

        l = [str(x) for x in l]
        return "".join(l)

for i in range(1,11):
    print(i,":",Solution().countAndSay(i))