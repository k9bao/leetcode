// 给定一棵二叉树，你需要计算它的直径长度。
//一棵二叉树的直径长度是任意两个结点路径长度中的最大值。
//这条路径可能穿过也可能不穿过根结点。

#include <iostream>

using namespace std;

//Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

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

int main() {
    Solution test;
    //           1
    //            \
    //             2
    //            /
    //           3
    {
        TreeNode t3(3);
        TreeNode t2(2, &t3, nullptr);
        TreeNode t1(1, nullptr, &t2);
        auto ret = test.diameterOfBinaryTree(&t1);
        cout << "ret = " << ret << endl;
        assert(ret == 2); //1,2,3
    }

    //           1
    //          / \
    //         2   3
    //       /  \
    //      4    5
    {
        TreeNode t4(4);
        TreeNode t5(5);
        TreeNode t2(2, &t4, &t5);
        TreeNode t3(3);
        TreeNode root(1, &t2, &t3);
        auto ret = test.diameterOfBinaryTree(&root);
        cout << "ret = " << ret << endl;
        assert(ret == 3); //4,2,1,3或5，2，1，3
    }

    //          1
    //         / \
    //        2   3
    //       / \
    //      4   5
    //     /     \
    //    6       8
    //     \       \
    //      7       9
    {
        TreeNode t7(7);
        TreeNode t6(6, nullptr, &t7);
        TreeNode t9(9);
        TreeNode t8(8, nullptr, &t9);
        TreeNode t4(4, &t6, nullptr);
        TreeNode t5(5, nullptr, &t8);
        TreeNode t2(2, &t4, &t5);
        TreeNode t3(3);
        TreeNode root(1, &t2, &t3);
        auto ret = test.diameterOfBinaryTree(&root);
        cout << "ret = " << ret << endl;
        assert(ret == 6); //7,6,5,4,3,8,9
    }
    {
        auto ret = test.diameterOfBinaryTree(nullptr);
        cout << "ret = " << ret << endl;
        assert(ret == 0);
    }

    return 0;
}