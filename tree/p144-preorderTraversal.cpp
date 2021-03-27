//给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

#include "tree_node.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void recursion_preorder(TreeNode *p, vector<int> &ret) {
        ret.push_back(p->val);
        if (p->left != nullptr) {
            recursion_preorder(p->left, ret);
        }
        if (p->right != nullptr) {
            recursion_preorder(p->right, ret);
        }
    }
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> ret;
        if (root != nullptr) {
            recursion_preorder(root, ret);
        }
        return ret;
    }
};

int main() {
    Solution test;
    auto f = [&test](TreeNode *root) -> vector<int> { return test.preorderTraversal(root); };

    for (size_t i = 0; i < 4; i++) {
        checkVector(GetTree(i), GetExpect(i, 0), f);
    }
    return 0;
}