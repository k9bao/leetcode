//给定一个二叉树，找出其最大深度。
//二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

#include "tree_node.h"
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int depth(TreeNode *root, int &maxDep) {
        if (root == nullptr) {
            return 0;
        }
        auto l = depth(root->left, maxDep);
        auto r = depth(root->right, maxDep);
        maxDep = max(maxDep, max(l, r) + 1);
        return max(l, r) + 1;
    }
    int maxDepth(TreeNode *root) {
        int maxDep = 0;
        depth(root, maxDep);
        return maxDep;
    }
};

void check(TreeNode *root, int exp) {
    Solution test;
    auto ret = test.maxDepth(root);
    cout << "ret = " << ret << ",exp = " << exp;
    assert(ret == exp);
    delTree(root);
    cout << endl
         << "------------------------------------" << endl;
}

int main() {
    check(GetTree(0), 0);
    check(GetTree(1), 3);
    check(GetTree(2), 3);
    check(GetTree(3), 5);

    return 0;
}