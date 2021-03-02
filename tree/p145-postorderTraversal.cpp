//给定一个二叉树，返回它的 后序 遍历。

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    void recursion_postorder(TreeNode *p, vector<int> &ret) {
        if (p->left != nullptr) {
            recursion_postorder(p->left, ret);
        }
        if (p->right != nullptr) {
            recursion_postorder(p->right, ret);
        }
        ret.push_back(p->val);
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> ret;
        if (root != nullptr) {
            recursion_postorder(root, ret);
        }
        return ret;
    }
};

int main() {
    Solution test;
    TreeNode t4(4);
    TreeNode t5(5);
    TreeNode t2(2, &t4, &t5);
    TreeNode t3(3);
    TreeNode root(1, &t2, &t3);
    //          1
    //        2   3
    //      4   5
    auto ret = test.postorderTraversal(&root);
    cout << "ret = " << ret.size() << endl;
    for_each(ret.begin(), ret.end(), [](int &v) { cout << v << ","; });
    assert((ret == vector<int>{4, 5, 2, 3, 1}));
    cout << endl;
    TreeNode t7(7);
    TreeNode t6(6, nullptr, &t7);
    t4.left = &t6;
    TreeNode t9(9);
    TreeNode t8(8, nullptr, &t9);
    t5.right = &t8;
    //          1
    //        2   3
    //      4   5
    //    6       8
    //      7       9
    ret = test.postorderTraversal(&root);
    cout << "ret = " << ret.size() << endl;
    for_each(ret.begin(), ret.end(), [](int v) { cout << v << ","; });
    cout << endl;
    assert((ret == vector<int>{7, 6, 4, 9, 8, 5, 2, 3, 1}));

    return 0;
}