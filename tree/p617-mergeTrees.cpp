// 给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。
// 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点。

#include "tree_node.h"
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        return mergeTrees2(root1, root2);
    }
    //思路和mergeTreesTimeout一致，只是使用map代替vector，不需要保存空节点
    TreeNode *mergeTrees2(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr || root2 == nullptr) { //某一个为空
            return root1 == nullptr ? root2 : root1;
        }

        root1->val += root2->val;
        unordered_map<int, TreeNode *> v11{{0, root1}}; //root1的上一层
        unordered_map<int, TreeNode *> v21{{0, root2}}; //root2的上一层
        while (true) {
            unordered_map<int, TreeNode *> v12; //root1的当前层
            unordered_map<int, TreeNode *> v22; //root2的当前层
            for (auto iter = v11.begin(); iter != v11.end(); iter++) {
                if (iter->second->left != nullptr) {
                    v12.insert(pair<int, TreeNode *>(iter->first * 2, iter->second->left));
                }
                if (iter->second->right != nullptr) {
                    v12.insert(pair<int, TreeNode *>(iter->first * 2 + 1, iter->second->right));
                }
            }
            for (auto iter = v21.begin(); iter != v21.end(); iter++) {
                if (iter->second->left != nullptr) {
                    v22.insert(pair<int, TreeNode *>(iter->first * 2, iter->second->left));
                }
                if (iter->second->right != nullptr) {
                    v22.insert(pair<int, TreeNode *>(iter->first * 2 + 1, iter->second->right));
                }
            }

            if (v22.empty()) {
                break;
            }

            for (auto iter = v22.begin(); iter != v22.end();) {
                auto iter1 = v12.find(iter->first);
                if (iter1 != v12.end()) {
                    iter1->second->val += iter->second->val;
                    iter++;
                } else {
                    if (iter->first % 2 == 0) {
                        v11[iter->first / 2]->left = iter->second;
                    } else {
                        v11[iter->first / 2]->right = iter->second;
                    }
                    v22.erase(iter++);
                }
            }

            //准备遍历下一层
            v11.swap(v12);
            v21.swap(v22);
        }
        return root1;
    }
    //还原完整二叉树，比较对应
    //逐层遍历合并，遍历时保留上层信息，用于指向新节点
    TreeNode *mergeTreesTimeout(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr || root2 == nullptr) { //某一个为空
            return root1 == nullptr ? root2 : root1;
        }

        root1->val += root2->val;
        vector<TreeNode *> v11; //root1的上一层
        v11.push_back(root1);

        vector<TreeNode *> v21; //root2的上一层
        v21.push_back(root2);
        while (true) {
            auto over = true;
            vector<TreeNode *> v12;                   //root1的当前层
            vector<TreeNode *> v22;                   //root2的当前层
            for (size_t i = 0; i < v11.size(); i++) { //将当前层完整数据加入v12和v22
                v12.push_back(v11[i] != nullptr ? v11[i]->left : nullptr);
                v12.push_back(v11[i] != nullptr ? v11[i]->right : nullptr);

                v22.push_back(v21[i] != nullptr ? v21[i]->left : nullptr);
                v22.push_back(v21[i] != nullptr ? v21[i]->right : nullptr);

                if (over == true) { //存在非空，将over设置为false
                    over = !(v11[i] != nullptr || v22[i] != nullptr);
                }
            }
            if (over) {
                break;
            }

            for (size_t i = 0; i < v12.size(); i++) {
                if (v12[i] == nullptr) { //root1的当前元素为空，移动root2的原始过来
                    if (v22[i] != nullptr) {
                        if (i % 2 == 0) {
                            v11[i / 2]->left = v22[i];
                        } else {
                            v11[i / 2]->right = v22[i];
                        }
                        v22[i] = nullptr;
                    }
                } else { //将root2的对应元素值，加到root1上
                    v12[i]->val += v22[i] == nullptr ? 0 : v22[i]->val;
                }
            }
            //准备遍历下一层
            v11.swap(v12);
            v21.swap(v22);
        }
        return root1;
    }
};

int main() {
    Solution test;
    {
        auto t1 = initTree(vector<int>{1});
        auto t2 = initTree(vector<int>{1, 2});
        auto ret = test.mergeTrees(t1, t2);
        assert((printTree(ret) == vector<int>{2, 2}));
        // clearTree(t1);
        // clearTree(t2);
    }
    {
        auto t1 = initTree(vector<int>{1});
        auto t2 = initTree(vector<int>{});
        auto ret = test.mergeTrees(t1, t2);
        assert((printTree(ret) == vector<int>{1}));
        // clearTree(t1);
        // clearTree(t2);
    }
    {
#define null INT_MIN
        auto t1 = initTree(vector<int>{1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, 2});
        auto t2 = initTree(vector<int>{1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, 2});
        auto ret = test.mergeTrees(t1, t2);
        printTree(ret);
        // assert((printTree(ret) == vector<int>{2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, null, 2, 2, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, null, 1, 2}));
    }
    //     输入:
    // 	Tree 1                     Tree 2
    //           1                         2
    //          / \                       / \
    //         3   2                     1   3
    //        /                           \   \
    //       5                             4   7
    // 输出:
    // 合并后的树:
    // 	     3
    // 	    / \
    // 	   4   5
    // 	  / \   \
    // 	 5   4   7
    {
        auto t1 = initTree(6);
        t1[1].SetLR(&t1[3], &t1[2]);
        t1[3].SetLR(&t1[5]);
        assert((printTree(&t1[1]) == vector<int>{1, 3, 2, 5}));

        auto t2 = initTree(8);
        t2[2].SetLR(&t2[1], &t2[3]);
        t2[1].SetLR(nullptr, &t2[4]);
        t2[3].SetLR(nullptr, &t2[7]);
        assert((printTree(&t2[2]) == vector<int>{2, 1, 3, INT_MIN, 4, INT_MIN, 7}));

        auto ret = test.mergeTrees(&t1[1], &t2[2]);
        assert((printTree(ret) == vector<int>{3, 4, 5, 5, 4, INT_MIN, 7}));
    }
    return 0;
}