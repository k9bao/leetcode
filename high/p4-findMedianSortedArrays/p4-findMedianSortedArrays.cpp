// 给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。
// 中位数（Median）又称中值，统计学中的专有名词，是按顺序排列的一组数据中居于中间位置的数
// 进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        // return findMedianSortedArrays1(nums1, nums2);
        return findMedianSortedArrays2(nums1, nums2);
    }
    double findMedianSortedArrays1(vector<int> &nums1, vector<int> &nums2) {
        if (nums1.size() + nums2.size() == 0) {
            return 0;
        }

        auto needTwo = (nums1.size() + nums2.size()) % 2 == 0 ? true : false; //中位数是一个数还是二个数
        auto find = (nums1.size() + nums2.size() - 1) / 2;                    //需要查找的元素索引,如果needTwo为true，需要找出find和find+1
        auto i = 0;
        auto j = 0;
        while (true) {
            if (i == nums1.size()) { //nums1遍历结束
                j = find - nums1.size();
                if (needTwo) {
                    return double(nums2[j] + nums2[j + 1]) / 2;
                }
                return nums2[j];

            } else if (j == nums2.size()) { //nums2遍历结束
                i = find - nums2.size();
                if (needTwo) {
                    return double(nums1[i] + nums1[i + 1]) / 2;
                }
                return nums1[i];
            }
            if (i + j == find) { //找到索引
                if (needTwo) {
                    if (nums1[i] < nums2[j]) {      //1 2,-1,3
                        if (i + 1 < nums1.size()) { //可能nums1[i+1]<nums2[j]
                            auto second = nums1[i + 1] < nums2[j] ? nums1[i + 1] : nums2[j];
                            return double(nums1[i] + second) / 2;
                        }
                    } else {                        //1 3 ,2 7
                        if (j + 1 < nums2.size()) { //可能nums2[j+1]<nums1[i]
                            auto second = nums1[i] < nums2[j + 1] ? nums1[i] : nums2[j + 1];
                            return double(nums2[j] + second) / 2;
                        }
                    }
                    return double(nums1[i] + nums2[j]) / 2;
                } else { //1 2, 1 2 3
                    return nums1[i] < nums2[j] ? nums1[i] : nums2[j];
                }
            }
            if (nums1[i] < nums2[j]) { //此处理需要放在while的最后判断，保证i,j有效且不满足find条件
                i++;
            } else {
                j++;
            }
        }
    }
    double findMedianSortedArrays2(vector<int> &nums1, vector<int> &nums2) {
        if (nums1.size() + nums2.size() == 0) {
            return 0;
        }

        auto needTwo = (nums1.size() + nums2.size()) % 2 == 0 ? true : false; //中位数是一个数还是二个数
        auto find = (nums1.size() + nums2.size() - 1) / 2;                    //需要查找的元素索引,如果needTwo为true，需要找出find和find+1
        auto i = 0;
        auto j = 0;
        auto left1 = 0;
        auto right1 = nums1.size() - 1;
        auto left2 = 0;
        auto right2 = nums2.size() - 1;
        while (true) {
            if (i == nums1.size()) { //nums1遍历结束
                j = find - nums1.size();
                if (needTwo) {
                    return double(nums2[j] + nums2[j + 1]) / 2;
                }
                return nums2[j];

            } else if (j == nums2.size()) { //nums2遍历结束
                i = find - nums2.size();
                if (needTwo) {
                    return double(nums1[i] + nums1[i + 1]) / 2;
                }
                return nums1[i];
            }
            if (i + j == find) { //找到索引
                if (needTwo) {
                    if (nums1[i] < nums2[j]) {      //1 2,-1,3
                        if (i + 1 < nums1.size()) { //可能nums1[i+1]<nums2[j]
                            auto second = nums1[i + 1] < nums2[j] ? nums1[i + 1] : nums2[j];
                            return double(nums1[i] + second) / 2;
                        }
                    } else {                        //1 3 ,2 7
                        if (j + 1 < nums2.size()) { //可能nums2[j+1]<nums1[i]
                            auto second = nums1[i] < nums2[j + 1] ? nums1[i] : nums2[j + 1];
                            return double(nums2[j] + second) / 2;
                        }
                    }
                    return double(nums1[i] + nums2[j]) / 2;
                } else { //1 2, 1 2 3
                    return nums1[i] < nums2[j] ? nums1[i] : nums2[j];
                }
            }
            i = (right1 - left1) / 2 + left1;
            j = (right2 - left2) / 2 + left2;
            if (nums1[i] < nums2[j]) { //此处理需要放在while的最后判断，保证i,j有效且不满足find条件
                left1 = i;
                right2 = j;
            } else {
                right1 = i;
                left2 = j;
            }
        }
        return 0.0;
    }
};
int main() {
    Solution test;
    auto v1 = vector<int>{1, 3};
    auto v2 = vector<int>{2};
    auto ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 2);

    v1 = vector<int>{1, 2};
    v2 = vector<int>{3, 4};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 2.5);

    v1 = vector<int>{0, 0};
    v2 = vector<int>{0, 0};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 0);

    v1 = vector<int>{};
    v2 = vector<int>{};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 0);

    v1 = vector<int>{2};
    v2 = vector<int>{};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 2);

    v1 = vector<int>{1};
    v2 = vector<int>{1};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 1);

    v1 = vector<int>{1, 2};
    v2 = vector<int>{-1, 3};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 1.5);

    v1 = vector<int>{1, 3};
    v2 = vector<int>{2, 7};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 2.5);

    v1 = vector<int>{1, 2};
    v2 = vector<int>{1, 2, 3};
    ret = test.findMedianSortedArrays(v1, v2);
    cout << ret << endl;
    assert(ret == 2);
    return 0;
}
