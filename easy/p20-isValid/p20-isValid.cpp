/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    //
    bool isValid(string s) {
        return isValid1(s);
    }
    bool isValid1(string s) {
        std::map<char, char> bracket = {{'}', '{'}, {']', '['}, {')', '('}};
        stack<char> st;
        for (char c : s) {
            if (c == '{' || c == '[' || c == '(') {
                st.push(c);
            } else if (bracket.count(c) > 0) {
                if (st.size() > 0 && bracket[c] == st.top()) {
                    st.pop();
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        if (st.size() == 0) {
            return true;
        }
        return false;
    }
};

int main() {
    Solution test;
    auto ret = test.isValid("()");
    cout << ret << endl;
    assert(ret == true);

    ret = test.isValid("()[]{}");
    cout << ret << endl;
    assert(ret == true);

    ret = test.isValid("(]");
    cout << ret << endl;
    assert(ret == false);

    ret = test.isValid("([)]");
    cout << ret << endl;
    assert(ret == false);

    ret = test.isValid("{[]}");
    cout << ret << endl;
    assert(ret == true);

    return 0;
}
