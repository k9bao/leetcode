// 实现 strStr() 函数。
// 给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

#include <iostream>

using namespace std;
class Solution {
public:
    int strStr(string haystack, string needle) {
        // return strStr1(haystack, needle);
        return strStr2(haystack, needle);
    }

    int strStr1(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        if (haystack.size() < needle.size()) {
            return -1;
        }

        for (size_t i = 0; i < haystack.size() - needle.size() + 1; i++) {
            if (haystack.substr(i, needle.size()) == needle) {
                return i;
            }
        }
        return -1;
    }

    int strStr2(string haystack, string needle) {
        if (needle.empty()) {
            return 0;
        }
        if (haystack.size() < needle.size()) {
            return -1;
        }

        for (size_t i = 0; i < haystack.size() - needle.size() + 1; i++) {
            size_t j = 0;
            for (; j < needle.size(); j++) {
                if (haystack[j + i] != needle[j]) {
                    break;
                }
            }
            if (j == needle.size()) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Solution test;
    auto ret = test.strStr("hello", "ll");
    cout << ret << endl;
    assert(ret == 2);

    ret = test.strStr("aaaaa", "bba");
    cout << ret << endl;
    assert(ret == -1);

    ret = test.strStr("aaaaa", "");
    cout << ret << endl;
    assert(ret == 0);

    ret = test.strStr("a", "a");
    cout << ret << endl;
    assert(ret == 0);
    return 0;
}
