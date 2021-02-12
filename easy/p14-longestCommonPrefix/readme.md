# 最长公共前缀

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1：

输入：strs = ["flower","flow","flight"]
输出："fl"
示例 2：

输入：strs = ["dog","racecar","car"]
输出：""
解释：输入不存在公共前缀。

提示：

0 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] 仅由小写英文字母组成

## 方案一

1. 如果strs长度为0，直接返回空
2. 取长度最小值minLen,str=strs[0][0:minLen]
3. 使用 str 与所有字符串的前[0:minLen]内容比较，如果都相等，返回strs[0][0:minLen]. else 取minLen-=1,重复第2步，直到minLen==0
字符串长度不超过200的话，时间复杂度：o(mn)，空间复杂度：o(1)，其中 m 是字符串数组中的字符串的最小长度，n 是字符串的数量

## 方案二(最优)

1. 如果strs长度为0，直接返回空
2. 取长度最小值minLen,利用二分法，从中间取内容。初始化beg=0,len=minLen-begin
3. str = strs[0][beg:(len+1)/2],判断str与所有其他字符串对应内容strs[i][beg:len(str)]
4. if 都相等，beg+=(len+1)/2,len/=2,if len != 0,重复第2步 else return strs[0][0:beg]
5. if 有不相等的,len=len/2,if len != 0,重复第2步 else return strs[0][0:beg]
字符串长度不超过200的话，时间复杂度：o(nm*logm)，空间复杂度：o(1)，其中 m 是字符串数组中的字符串的最小长度，n 是字符串的数量

## 其他方案详见官网

包括横向查找，纵向查找(方案一)，分治思想，二分思想(方案二)
