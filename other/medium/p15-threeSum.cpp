// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。
// 注意：答案中不可以包含重复的三元组。

#include <algorithm>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        return threeSum1(nums);
    }
    //1. 将正数与负数分开
    //2. 遍历正数x，从负数里边取2个，负数必须大于等于-x
    //3. 遍历负数y，从正数里边取2个，正数必须小于等于-y
    vector<vector<int>> threeSum1(vector<int> &nums) {
        vector<vector<int>> ret;
        if (nums.size() < 3) {
            return ret;
        }
        auto maxVal = *max_element(nums.begin(), nums.end());
        auto minVal = *min_element(nums.begin(), nums.end());
        if (minVal > 0 || maxVal < 0) {
            return ret;
        }
        if (minVal == 0) { //有3个0，则返回000
            int zeroCount = 0;
            for (auto v : nums) {
                if (v == 0) {
                    zeroCount++;
                }
                if (zeroCount == 3) {
                    break;
                }
            }
            if (zeroCount == 3) {
                ret.push_back({0, 0, 0});
            }
        }

        int splitIndex = 0, j = nums.size() - 1;
        while (splitIndex < j) { //小于0的在前边，大于等于0的在后边，就是分界线，splitIndex>=0
            if (nums[splitIndex] >= 0) {
                swap(nums[splitIndex], nums[j]);
                j--;
            } else {
                splitIndex++;
            }
        }
        // for_each(nums.begin(), nums.end(), [](int &v) { cout << v << ","; });
        // cout << endl;
        if (splitIndex == 0) { //最小值是0
        }

        set<int> keys;
        for (int i = 0; i < splitIndex; i++) {
            if (keys.count(nums[i])) {
                continue;
            }
            keys.insert(nums[i]);

            for (j = splitIndex; j < nums.size(); j++) {
                if (nums[j] * -1 >= nums[i]) {
                    for (int k = j + 1; k < nums.size(); k++) {
                        if (nums[j] + nums[k] + nums[i] == 0) {
                            ret.push_back(vector<int>{nums[i], nums[j], nums[k]});
                        }
                    }
                }
            }
        }

        keys.clear();
        for (int i = splitIndex; i < nums.size(); i++) {
            if (keys.count(nums[i])) {
                continue;
            }
            keys.insert(nums[i]);
            for (j = 0; j < splitIndex; j++) {
                if (nums[j] * -1 <= nums[i]) {
                    for (int k = j + 1; k < splitIndex; k++) {
                        if (nums[j] + nums[k] + nums[i] == 0) {
                            ret.push_back(vector<int>{nums[i], nums[j], nums[k]});
                        }
                    }
                }
            }
        }

        return ret;
    }
};

int main() {
    Solution test;
    std::vector<std::tuple<vector<int>, vector<vector<int>>>> examples{
        make_tuple(vector<int>{-1, 0, 1, 2, -1, -4}, vector<vector<int>>{{-1, -1, 2},
                                                                         {-1, 0, 1}}),
        make_tuple(vector<int>{}, vector<vector<int>>{}),
        make_tuple(vector<int>{0}, vector<vector<int>>{}),
        make_tuple(vector<int>{0, 0, 0}, vector<vector<int>>{{0, 0, 0}}),
        make_tuple(vector<int>{0, -1, 1}, vector<vector<int>>{{-1, 0, 1}}),
    };
    for (auto iter = examples.begin(); iter != examples.end(); iter++) {
        cout << endl
             << "---------" << endl;
        cout << "src:";
        for_each(get<0>(*iter).begin(), get<0>(*iter).end(), [](int &v) { cout << v << ","; });
        cout << endl;

        auto ret = test.threeSum(get<0>(*iter));
        cout << "ret:";
        for (auto v : ret) {
            for_each(v.begin(), v.end(), [](int &v) { cout << v << ","; });
            cout << endl;
        }
        cout << "exp:";
        for (auto v : get<1>(*iter)) {
            for_each(v.begin(), v.end(), [](int &v) { cout << v << ","; });
            cout << endl;
        }
    }
    return 0;
}
