/*
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。
说明:

所有输入只包含小写字母 a-z 。
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    //
    string longestCommonPrefix(vector<string> &strs) {
        return longestCommonPrefix2(strs);
    }
    string longestCommonPrefix1(vector<string> &strs) {
        if (strs.size() == 0) {
            return "";
        }

        string str = *max_element(strs.begin(), strs.end(), [](string a, string b) -> bool { return a.size() < b.size(); });
        while (true) {
            size_t i = 0;
            for (; i < strs.size(); i++) {
                if (str != strs[i].substr(0, str.size())) {
                    str = str.substr(0, str.size() - 1);
                    break;
                }
            }
            if (i == strs.size()) {
                break;
            }
        }

        return str;
    }
    string longestCommonPrefix2(vector<string> &strs) {
        if (strs.size() == 0) {
            return "";
        }

        int len = max_element(strs.begin(), strs.end(), [](string &a, string &b) -> bool { return a.size() < b.size(); })->size();
        int beg = 0;
        while (len > 0) {
            auto midLen = (len + 1) / 2;
            auto str = strs[0].substr(beg, midLen);
            size_t i = 0;
            for (; i < strs.size(); i++) {
                if (str != strs[i].substr(beg, str.size())) {
                    break;
                }
            }
            if (i == strs.size()) {
                beg += midLen;
            }
            len /= 2;
        }

        return strs[0].substr(0, beg);
    }
};

int main() {
    Solution test;
    vector<string> strs{"flower", "flow", "flight"};
    auto ret = test.longestCommonPrefix(strs);
    cout << ret << endl;
    assert(ret == "fl");

    vector<string> strs2 = {"dog", "racecar", "car"};
    ret = test.longestCommonPrefix(strs2);
    cout << ret << endl;
    assert(ret == "");

    vector<string> strs3;
    ret = test.longestCommonPrefix(strs3);
    cout << ret << endl;
    assert(ret == "");
    return 0;
}
