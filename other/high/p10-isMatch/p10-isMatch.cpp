// 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。
// '.' 匹配任意单个字符
// '*' 匹配零个或多个前面的那一个元素
// 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

#include <iostream>
#include <stack>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
public:
    //p是否可以覆盖整个s,这里假设p有效，不存在非法格式，比如 *x ..
    bool isMatch(string s, string p) {
        return isMatchMy(s, p);
    }
    //此方法有问题，无法解决这种情况"ab", ".*..c*"
    bool isMatchMy(string s, string p) {
        if (p == ".*") {
            return true;
        }

        int indexS = s.size() - 1;
        int indexP = p.size() - 1;
        while (indexS >= 0 && indexP >= 0) { //去除p后边非*结束的字符
            if (p[indexP] != '*') {
                if (p[indexP] != '.' && p[indexP] != s[indexS]) {
                    return false;
                }
                indexS--;
                indexP--;
            } else {
                break;
            }
        }
        s = s.substr(0, indexS + 1);
        p = p.substr(0, indexP + 1);

        indexS = 0;
        indexP = 0;
        while (indexP < p.size() && indexS < s.size()) {
            if (s[indexS] == p[indexP] || p[indexP] == '.') {
                indexP++;
                indexS++;
            } else if (p[indexP] == '*') {
                if (p[indexP - 1] == s[indexS]) {
                    indexS++;
                    continue;
                } else if (p[indexP - 1] == '.') {
                    indexS++;
                } else {
                    indexP++;
                }
            } else if (s[indexS] != p[indexP]) { //跳过x*,其中x!=s[indexS]，因为可能有0个x，下个值可能等于s[indexS]
                if (indexP + 1 < p.size() && p[indexP + 1] == '*') {
                    indexP += 2;
                    continue;
                }
                return false;
            } else {
                assert(0);
            }
        }
        if (indexS != s.size()) {
            return false;
        }
        while (indexP < p.size()) {
            if (p[indexP] == '*') {
                indexP++;
            } else if (p[indexP] != '*') {
                if (indexP + 1 < p.size() && p[indexP + 1] == '*') {
                    indexP += 2;
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    Solution test;
    std::vector<std::tuple<string, string, bool>> examples{
        std::make_tuple("aa", "a", false),
        std::make_tuple("aa", "a*", true),
        std::make_tuple("aa", ".*", true),
        std::make_tuple("aab", "c*a*b", true),
        std::make_tuple("mississippi", "mis*is*p*.", false),
        std::make_tuple("mississippi", "mis*is*ip*.", true),
        std::make_tuple("aaa", "a*a", true),
        std::make_tuple("aaa", "a*aaaa.", false),
        std::make_tuple("aaa", "ab*ac*a", true),
        std::make_tuple("ab", ".*..", true),
        std::make_tuple("ab", ".*..c*", true),
    };

    for (auto iter = examples.begin(); iter != examples.end(); iter++) {
        auto ret = test.isMatch(get<0>(*iter), get<1>(*iter));
        cout << get<0>(*iter) << ", " << get<1>(*iter) << " --- result:" << ret << ",exp:" << get<2>(*iter) << endl;
        assert(ret == get<2>(*iter));
    }
    return 0;
}
