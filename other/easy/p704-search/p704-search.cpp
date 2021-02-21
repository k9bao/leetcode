// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
// 你可以假设数组中无重复元素。

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int search(vector<int> &nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        int ret = nums.size();
        while (left <= right) {
            auto mid = ((right - left) >> 1) + left;
            if (target == nums[mid]) {
                return mid;
            } else if (target > nums[mid]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};

int main() {
    Solution test;
    auto v = vector<int>{-1, 0, 3, 5, 9, 12};

    auto ret = test.search(v, 9);
    cout << ret << endl;
    assert(ret == 4);

    ret = test.search(v, 2);
    cout << ret << endl;
    assert(ret == -1);

    return 0;
}
