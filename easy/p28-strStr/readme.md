28. 实现 strStr()
实现 strStr() 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

示例 1:

输入: haystack = "hello", needle = "ll"
输出: 2
示例 2:

输入: haystack = "aaaaa", needle = "bba"
输出: -1
说明:

当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。

对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

其中 N 为 haystack 字符串的长度，L 为 needle 字符串的长度。

## 方案一

子串逐一比较 - 线性时间复杂度
最直接的方法 - 沿着字符换逐步移动滑动窗口，将窗口内的子串与 needle 字符串比较。
c++中，会用到substr()获取needle长度的字符串，比较长度。其实没必要获取全部needle做判断，这样就有了方案二

时间复杂度：O((N - L)L).空间复杂度：O(1)

## 方案二

同方案一，只是计较的时候，不调用系统的substr，而是逐个比较，最少比较一个字符就可以判断不相同
时间复杂度：O((N - L)L).空间复杂度：O(1)

## 方案三Sunday 解法

在方案二的基础上，继续优化。方案二中，haystack是一个一个字符的后移
其实没必要一个一个的跳。如果如果haystack[i+needle.len()]在needle中，则i+=偏移量,否则i+=needle.len()
需要提前记录出来偏移量表，用于循环时，跳过去
最坏时间复杂度：O((N - L)L).空间复杂度：O(len(needle))，平均时间复杂度o(N)

## 方案四 KMP算法

具体