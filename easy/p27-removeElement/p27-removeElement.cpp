// 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
// 不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。
// 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int removeElement(vector<int> &nums, int val) {
        return removeElement2(nums, val);
        int len = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                if (len != i) {
                    nums[len] = nums[i];
                }
                len++;
            }
        }
    }
    int removeElement2(vector<int> &nums, int val) {
        int total = nums.size();
        int i = 0;
        for (; i < total; i++) {
            if (nums[i] == val) {
                nums[i] = nums[total - 1];
                total--;
                i--;
            }
        }
        return i;
    }
};

int main() {
    Solution test;
    vector<int> v1 = {3, 2, 2, 3};
    auto ret = test.removeElement(v1, 3);
    for (size_t i = 0; i < ret; i++) {
        cout << v1[i];
    }
    cout << ":" << ret << endl;
    assert(ret == 2); //[2,2]

    vector<int> v2 = {0, 1, 2, 2, 3, 0, 4, 2};
    ret = test.removeElement(v2, 2);
    for (size_t i = 0; i < ret; i++) {
        cout << v2[i];
    }
    cout << ":" << ret << endl;
    assert(ret == 5); //[01304]
    return 0;
}
