// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
// 你可以假设数组中无重复元素。

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int searchInsert(vector<int> &nums, int target) {
        // return searchInsert1(nums, target);
        return searchInsert2(nums, target);
    }
    int searchInsert1(vector<int> &nums, int target) {
        for (size_t i = 0; i < nums.size(); i++) {
            if (target <= nums[i]) {
                return i;
            }
        }
        return nums.size();
    }
    int searchInsert2(vector<int> &nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ret = nums.size();
        while (left <= right) {
            auto mid = ((right - left) >> 1) + left;
            if (target <= nums[mid]) {
                ret = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return ret;
    }
};

int main() {
    Solution test;
    auto v = vector<int>{1, 3, 5, 6};
    auto ret = test.searchInsert(v, 5);
    cout << ret << endl;
    assert(ret == 2);

    ret = test.searchInsert(v, 2);
    cout << ret << endl;
    assert(ret == 1);

    ret = test.searchInsert(v, 7);
    cout << ret << endl;
    assert(ret == 4);

    ret = test.searchInsert(v, 0);
    cout << ret << endl;
    assert(ret == 0);
    return 0;
}
