// 给定一个整数数组 nums 和一个目标值 target，
// 请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        vector<int> ret;
        unordered_map<int, int> mapVK;
        for (size_t i = 0; i < nums.size(); i++) {
            if (mapVK.count(target - nums[i])) {
                ret.push_back(mapVK[target - nums[i]]);
                ret.push_back(i);
                return ret;
            } else {
                mapVK[nums[i]] = i;
            }
        }
        return ret;
    }
};

int main() {
    Solution test;
    vector<int> nums(3, 3);
    auto ret = test.twoSum(nums, 6);
    for (size_t i = 0; i < ret.size(); i++) {
        cout << ret[i] << endl;
    }
}
