//给定一个二叉树，返回它的 后序 遍历。

#include "tree_node.h"
#include <iostream>
#include <vector>

using namespace std;

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
    auto f = [&test](TreeNode *root) -> vector<int> { return test.postorderTraversal(root); };

    for (size_t i = 0; i < 4; i++) {
        checkVector(GetTree(i), GetExpect(i, 2), f);
    }
    return 0;
}