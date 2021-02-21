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
    int diameterOfBinaryTree(TreeNode *root) {
        return 0;
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
    assert(3 == test.diameterOfBinaryTree(&root)); // 4,2,1,3 或 5,2,1,3
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
    assert(6 == test.diameterOfBinaryTree(&root)); // 7,6,4,3,5,8,9
    return 0;
}
