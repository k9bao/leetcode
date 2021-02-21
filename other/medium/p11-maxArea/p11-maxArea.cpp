#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
public:
    int maxArea(vector<int> &height) {
        return maxArea0(height);
        // return maxArea1(height);
        // return maxArea2(height);
    }
    //双指针法
    int maxArea0(vector<int> &height) {
        int left = 0, right = height.size() - 1;
        int maxArea = 0;
        while (left < right) {
            if (height[left] < height[right]) {
                maxArea = max(maxArea, (right - left) * height[left]);
                left++;
            } else {
                maxArea = max(maxArea, (right - left) * height[right]);
                right--;
            }
        }

        return maxArea;
    }
    //暴力计算
    int maxArea1(vector<int> &height) {
        int maxArea = 0;
        for (size_t i = 0; i < height.size(); i++) {
            for (size_t j = i + 1; j < height.size(); j++) {
                int area = (j - i) * min(height[i], height[j]);
                maxArea = max(maxArea, area);
            }
        }

        return maxArea;
    }
    //1. 获取二个最大值，中间的数据都无效
    //2. 暴力计算剩下的容积
    //待实现
    int maxArea2(vector<int> &height) {
        if (height.size() <= 1) {
            return 0;
        }

        int maxArea = 0;
        int top1Index = height[0] > height[1] ? 0 : 1;
        int top2Index = height[0] > height[1] ? 1 : 0;
        int top1Val = height[top1Index];
        int top2Val = height[top2Index];
        for (size_t i = 2; i < height.size(); i++) {
            if (height[i] > top1Val) {
                top2Index = top1Index;
                top2Val = height[top1Index];
                top1Index = i;
                top1Val = height[top1Index];
            }
        }

        return maxArea;
    }
};

int main() {
    Solution test;
    std::vector<std::tuple<std::vector<int>, int>> examples{
        make_tuple(vector<int>{1, 8, 6, 2, 5, 4, 8, 3, 7}, 49),
        make_tuple(vector<int>{1, 1}, 1),
        make_tuple(vector<int>{4, 3, 2, 1, 4}, 16),
        make_tuple(vector<int>{1, 2, 1}, 2),
    };

    for (auto iter = examples.begin(); iter != examples.end(); iter++) {
        auto ret = test.maxArea(get<0>(*iter));
        cout << get<0>(*iter).size() << " --- result:" << ret << ",exp:" << get<1>(*iter) << endl;
        assert(ret == get<1>(*iter));
    }
    return 0;
}
