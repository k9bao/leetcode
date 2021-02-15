#include <iostream>
#include <vector>

using namespace std;

class SolutionHeap {
    void maxHeapify(vector<int> &nums, int i, int len) {
        for (; (i << 1) + 1 <= len;) {
            int lson = (i << 1) + 1;
            int rson = (i << 1) + 2;
            int large;
            if (lson <= len && nums[lson] > nums[i]) {
                large = lson;
            } else {
                large = i;
            }
            if (rson <= len && nums[rson] > nums[large]) {
                large = rson;
            }
            if (large != i) {
                swap(nums[i], nums[large]);
                i = large;
            } else {
                break;
            }
        }
    }
    void buildMaxHeap(vector<int> &nums, int len) {
        for (int i = len / 2; i >= 0; --i) {
            maxHeapify(nums, i, len);
        }
    }
    void heapSort(vector<int> &nums) {
        int len = (int)nums.size() - 1;
        buildMaxHeap(nums, len);
        for (int i = len; i >= 1; --i) {
            swap(nums[i], nums[0]);
            len -= 1;
            maxHeapify(nums, 0, len);
        }
    }

public:
    vector<int> sortArray(vector<int> &nums) {
        heapSort(nums);
        return nums;
    }
};

class Solution {
public:
    //升序排序
    vector<int> sortArray(vector<int> &arr) {
        // return sortArray1(arr);
        // return sortArray2(arr);
        // return sortArray3(arr);
        return sortArray4(arr);
    }
    //冒泡,时间o(n^2),空间o(1)
    vector<int> sortArray1(vector<int> &arr) {
        for (size_t i = 0; i < arr.size(); i++) {
            for (size_t j = i + 1; j < arr.size(); j++) {
                if (arr[i] > arr[j]) {
                    swap(arr[i], arr[j]);
                }
            }
        }
        return arr;
    }
    //快排,时间o(nlogn),空间o(h)，h为递归层数，最小logn,最大n
    vector<int> sortArray2(vector<int> &arr) {
        quikSort(arr, 0, arr.size() - 1);
        return arr;
    }
    //归并排序,时间o(nlogn),空间o(n)
    vector<int> sortArray3(vector<int> &arr) {
        vector<int> tmp;
        tmp.resize((int)arr.size(), 0);
        mergeSort(arr, 0, (int)arr.size() - 1, tmp);
        return arr;
    }
    //堆排序,时间o(nlogn),空间o(1)
    vector<int> sortArray4(vector<int> &arr) {
        heapSort(arr);
        return arr;
    }

private:
    void swap(int &x, int &y) {
        auto temp = x;
        x = y;
        y = temp;
    }
    //重构大顶堆
    void maxHeapify(vector<int> &arr, int i, int len) {
        for (; i * 2 + 1 <= len;) {
            int lson = i * 2 + 1;
            int rson = i * 2 + 2;
            int large;
            if (lson <= len && arr[lson] > arr[i]) {
                large = lson;
            } else {
                large = i;
            }
            if (rson <= len && arr[rson] > arr[large]) {
                large = rson;
            }
            if (large != i) {
                swap(arr[i], arr[large]);
                i = large;
            } else {
                break;
            }
        }
    }
    //构建大顶推
    void buildMaxHeap(vector<int> &arr, int len) {
        for (int i = len / 2; i >= 0; i--) { //这里必须是int，因为len可能小于0
            maxHeapify(arr, i, len);
        }
    }
    void heapSort(vector<int> &arr) {
        int len = (int)arr.size() - 1; //这里必须是int，因为arr.size可能为0
        buildMaxHeap(arr, len);
        for (int i = len; i >= 1; i--) { //这里必须是int，因为len可能小于0
            swap(arr[i], arr[0]);        //最大值交换到后边已排序位置
            len -= 1;
            maxHeapify(arr, 0, len);
        }
    }
    void mergeSort(vector<int> &arr, int left, int right, vector<int> &tmp) {
        if (left >= right) {
            return;
        }
        auto mid = (left + right) >> 1;
        mergeSort(arr, left, mid, tmp);
        mergeSort(arr, mid + 1, right, tmp);
        int i = left;
        int j = mid + 1;
        int k = 0;
        while (i <= mid && j <= right) {
            if (arr[i] < arr[j]) {
                tmp[k++] = arr[i++];
            } else {
                tmp[k++] = arr[j++];
            }
        }
        while (i <= mid) {
            tmp[k++] = arr[i++];
        }
        while (j <= right) {
            tmp[k++] = arr[j++];
        }
        for (size_t i = 0; i <= right - left; i++) {
            arr[i + left] = tmp[i];
        }
    }
    void quikSort(vector<int> &arr, int left, int right) {
        if (left < right) {
            auto pivot = patition(arr, left, right);
            quikSort(arr, left, pivot - 1);
            quikSort(arr, pivot + 1, right);
        }
    }
    int patition(vector<int> &arr, int left, int right) {
        //随机去一个值，交换到最后arr[r]，这里省去随机选取和交换
        //所有小于arr[r]的移到前边，大于arr[r]的移到后边
        //使用j来记录>arr[r]和<=arr[r]的分界线下标
        //j初始指向一个无效分割点l-1,l可能为0，j可能取-1(所以必须是有符号)
        int j = left - 1;
        for (size_t i = left; i <= right - 1; i++) { //访问[l,r-1],包含l和r-1
            if (arr[i] <= arr[right]) {
                swap(arr[i], arr[++j]); //先移动分割点，然后再交换
            }
        }
        swap(arr[j + 1], arr[right]); //把最后基准元素和j+1位置交互
        return j + 1;
    }
};

void checkRet(vector<int> &val, vector<int> &exp) {
    auto print = [](int x) { cout << x << " "; };
    Solution test;
    auto ret = test.sortArray(val);
    for_each(ret.begin(), ret.end(), print);
    assert(ret == exp);
    cout << endl;
}

int main() {
    auto val = vector<int>{5, 2, 3, 1};
    auto exp = vector<int>{1, 2, 3, 5};
    checkRet(val, exp);

    val = vector<int>{};
    exp = vector<int>{};
    checkRet(val, exp);

    return 0;
}