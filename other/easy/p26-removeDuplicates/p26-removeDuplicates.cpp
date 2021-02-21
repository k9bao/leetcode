// 给定一个排序数组，你需要在 原地 删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。
// 不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。

#include <iostream>
#include <vector>

using namespace std;
class Solution {
public:
    int removeDuplicates(vector<int> &nums) {
        int len = 0;
        for (size_t i = 0; i < nums.size(); i++) {
            if (nums[i] != nums[len]) {
                len++;
                nums[len] = nums[i];
            }
        }

        return (nums.size() > 0) ? len + 1 : 0;
    }
};

int main() {
    Solution test;
    vector<int> v1 = {1, 1, 2};
    auto ret = test.removeDuplicates(v1);
    for (size_t i = 0; i < ret; i++) {
        cout << v1[i];
    }
    cout << ":" << ret << endl;
    assert(ret == 2);

    vector<int> v2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    ret = test.removeDuplicates(v2);
    for (size_t i = 0; i < ret; i++) {
        cout << v2[i];
    }
    cout << ":" << ret << endl;
    assert(ret == 5);

    vector<int> v3;
    ret = test.removeDuplicates(v3);
    for (size_t i = 0; i < ret; i++) {
        cout << v3[i];
    }
    cout << ":" << ret << endl;
    assert(ret == 0);

    vector<int> v4 = {1};
    ret = test.removeDuplicates(v4);
    for (size_t i = 0; i < ret; i++) {
        cout << v4[i];
    }
    cout << ":" << ret << endl;
    assert(ret == 1);
    return 0;
}
