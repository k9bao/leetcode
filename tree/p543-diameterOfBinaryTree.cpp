// 给定一棵二叉树，你需要计算它的直径长度。
//一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
//这条路径可能穿过也可能不穿过根结点。

#include "tree_node.h"
#include <iostream>

using namespace std;

class Solution {
public:
    //树的高度
    int depth(TreeNode *root, int &maxDep) {
        if (root == nullptr) {
            return 0;
        }
        auto l = depth(root->left, maxDep);
        auto r = depth(root->right, maxDep);
        maxDep = max(maxDep, l + r);
        return max(l, r) + 1;
    }
    int diameterOfBinaryTree(TreeNode *root) {
        int maxDepth = 0;
        depth(root, maxDepth);
        return maxDepth;
    }
};

void check(TreeNode *root, int exp) {
    Solution test;
    auto ret = test.diameterOfBinaryTree(root);
    cout << "ret = " << ret << ",exp = " << exp;
    assert(ret == exp);
    delTree(root);
    cout << endl
         << "------------------------------------" << endl;
}

int main() {
    check(GetTree(0), 0);
    check(GetTree(1), 2);
    check(GetTree(2), 3);
    check(GetTree(3), 6);
    return 0;
}