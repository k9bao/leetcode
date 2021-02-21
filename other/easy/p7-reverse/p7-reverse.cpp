
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int reverseGW(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && pop > 7)) //0x7F FF FF FF
                return 0;
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && pop < -8)) //0x8F FF FF FF
                return 0;
            rev = rev * 10 + pop;
        }
        return rev;
    }

    int reverse(int ix) {
        int sign = 1;
        long x = ix;
        if (x < 0) {
            sign = -1;
            x *= -1;
        }
        std::vector<int> nums;
        while (true) {
            if (x > 0) {
                nums.push_back(x % 10);
                x /= 10;
            }
            if (x == 0) {
                break;
            }
        }
        unsigned long result = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            result += nums[i] * pow(10, nums.size() - i - 1);
        }

        if (result > 2147483648) {
            result = 0;
        }
        return int(result * sign);
    }
};

int main() {
    Solution test;
    cout << test.reverse(123) << endl;
    cout << test.reverse(-123) << endl;
    cout << test.reverse(2147483647) << endl;  //2^31-1
    cout << test.reverse(-2147483648) << endl; //2^31-1
}
