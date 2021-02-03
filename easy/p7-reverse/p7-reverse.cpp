
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
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
