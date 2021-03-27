// 给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。
// 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点。

// 官网给出的方法
//1. 深度优先，递归合并,待实现
//2. 广度优先，递归合并,待实现

#include "tree_node.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        // return mergeTrees1(root1,root2);
        // return mergeTrees2(root1, root2);
        // return mergeTrees3(root1, root2);
        return mergeTrees4(root1, root2);
        // return mergeTrees5(root1, root2);
    }

    void Traversal(TreeNode *root, TreeNode *&newRoot) {
        if (root == nullptr) {
            return;
        }
        newRoot = new TreeNode(root->val);
        if (root->left != nullptr) {
            Traversal(root->left, newRoot->left);
        }
        if (root->right != nullptr) {
            Traversal(root->right, newRoot->right);
        }
    }

    TreeNode *copyTree(TreeNode *root) {
        TreeNode *newRoot = nullptr;
        Traversal(root, newRoot);
        return newRoot;
    }

    //深度先序遍历，递归实现
    TreeNode *mergeTrees5(TreeNode *root0, TreeNode *root2) {
        if (root0 == nullptr || root2 == nullptr) { //某一个为空
            return root0 == nullptr ? copyTree(root2) : copyTree(root0);
        }
        auto merged = new TreeNode(root0->val + root2->val);
        merged->left = mergeTrees5(root0->left, root2->left);
        merged->right = mergeTrees5(root0->right, root2->right);
        return merged;
    }

    //在mergeTrees3的基础上，不破坏root1和root2，返回合并后的root3,原理同mergeTrees3
    TreeNode *mergeTrees4(TreeNode *root0, TreeNode *root2) {
        if (root0 == nullptr || root2 == nullptr) { //某一个为空
            return root0 == nullptr ? copyTree(root2) : copyTree(root0);
        }

        auto root1 = copyTree(root0); //将root2合并到root1
        root1->val += root2->val;
        vector<TreeNode *> v11{root1}; //root1的上一层
        vector<TreeNode *> v21{root2}; //root2的上一层
        vector<TreeNode *> v12;        //root1的当前层,个数肯定是上一层的2倍
        vector<TreeNode *> v22;        //root2的当前层,v12.size()==v22.size()
        int level = 1;
        auto procNode = [this](vector<TreeNode *> &v22, TreeNode *&v1, TreeNode *&v2) {
            if (v2 != nullptr) { //将v2叠加到v1上，并且填充v22
                if (v1 != nullptr) {
                    v1->val += v2->val;
                    v22.push_back(v2);
                } else {
                    v1 = copyTree(v2);
                    v22.push_back(nullptr);
                }
            } else {
                v22.push_back(nullptr);
            }
        };

        while (true) {
            assert(v11.size() == v21.size());
            v12.clear();
            v22.clear();
            for (size_t i = 0; i < v11.size(); i++) { //单层数不错过2^64大小，可以使用迭代器规避
                if (v21[i] == nullptr) {
                    v22.push_back(nullptr);
                    v22.push_back(nullptr);
                    /* code */
                } else {
                    procNode(v22, v11[i]->left, v21[i]->left);   //process left
                    procNode(v22, v11[i]->right, v21[i]->right); //process left
                }
                v12.push_back(v11[i] == nullptr ? nullptr : v11[i]->left);
                v12.push_back(v11[i] == nullptr ? nullptr : v11[i]->right);
            }
            assert(v12.size() == v22.size());

            //如果v22都为nullptr，退出整个循环
            if (count(v22.begin(), v22.end(), nullptr) == v22.size()) {
                break;
            }

            //准备遍历下一层，去掉头尾为nullptr的值,以v12为基准
            size_t beg = 0;
            while (v12[beg] == nullptr && beg < v12.size()) {
                beg++;
            }

            int end = v12.size() - 1;
            while (v12[end] == nullptr && end > 0) {
                end--;
            }

            v11.assign(v12.begin() + beg, v12.begin() + end + 1);
            v21.assign(v22.begin() + beg, v22.begin() + end + 1);
        }
        return root1;
    }

    //在mergeTrees2的基础上，继续优化，取消map，保证上下层2倍关系实现
    //有点类似广度遍历(逐层遍历)，复用了原始节点，题目要求生成心得树，通过了leetcode测试
    TreeNode *mergeTrees3(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr || root2 == nullptr) { //某一个为空
            return root1 == nullptr ? root2 : root1;
        }

        root1->val += root2->val;
        vector<TreeNode *> v11{root1}; //root1的上一层
        vector<TreeNode *> v21{root2}; //root2的上一层
        vector<TreeNode *> v12;        //root1的当前层,个数肯定是上一层的2倍，
        vector<TreeNode *> v22;        //root2的当前层,v12.size()==v22.size()
        int level = 1;
        auto procNode = [](vector<TreeNode *> &v22, TreeNode *&v1, TreeNode *&v2) {
            if (v2 != nullptr) { //将v2叠加到v1上，并且填充v22
                if (v1 != nullptr) {
                    v1->val += v2->val;
                    v22.push_back(v2);
                } else {
                    v1 = v2;
                    v2 = nullptr;
                    v22.push_back(nullptr);
                }
            } else {
                v22.push_back(nullptr);
            }
        };

        while (true) {
            assert(v11.size() == v21.size());
            v12.clear();
            v22.clear();
            for (size_t i = 0; i < v11.size(); i++) { //单层数不错过2^64大小，可以使用迭代器规避
                if (v21[i] == nullptr) {
                    v22.push_back(nullptr);
                    v22.push_back(nullptr);
                    /* code */
                } else {
                    procNode(v22, v11[i]->left, v21[i]->left);   //process left
                    procNode(v22, v11[i]->right, v21[i]->right); //process left
                }
                v12.push_back(v11[i] == nullptr ? nullptr : v11[i]->left);
                v12.push_back(v11[i] == nullptr ? nullptr : v11[i]->right);
            }
            assert(v12.size() == v22.size());

            //如果v22都为nullptr，退出整个循环
            if (count(v22.begin(), v22.end(), nullptr) == v22.size()) {
                break;
            }

            //准备遍历下一层，去掉头尾为nullptr的值,以v12为基准
            size_t beg = 0;
            for (; beg < v12.size(); beg++) {
                if (v12[beg] != nullptr) {
                    break;
                }
            }
            int end = v12.size() - 1;
            for (; end >= 0; end--) {
                if (v12[end] != nullptr) {
                    break;
                }
            }
            v11.assign(v12.begin() + beg, v12.begin() + end + 1);
            v21.assign(v22.begin() + beg, v22.begin() + end + 1);
        }
        return root1;
    }

    //在mergeTrees1的基础上优化，使用map代替vector，减少数量
    //此算法存在越界问题，超过100层以后会超过int64界限，无法通过检测
    //将root2追加到root1上
    //             0
    //           /    \
    //        1         2
    //      /   \      /  \
    //    3       4  5     6
    //   /  \
    //  7    8
    //  规律
    //        k
    //   2k+1   2K+2
    TreeNode *mergeTrees2(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr || root2 == nullptr) { //某一个为空
            return root1 == nullptr ? root2 : root1;
        }

        root1->val += root2->val;
        unordered_map<int64_t, TreeNode *> v11{{0, root1}}; //root1的上一层
        unordered_map<int64_t, TreeNode *> v21{{0, root2}}; //root2的上一层
        unordered_map<int64_t, TreeNode *> v12;             //root1的当前层
        unordered_map<int64_t, TreeNode *> v22;             //root2的当前层
        int level = 1;
        while (true) {
            v12.clear();
            for (auto iter = v11.begin(); iter != v11.end(); iter++) { //根据v11，填充v12
                if (iter->second->left != nullptr) {
                    v12.insert(pair<int64_t, TreeNode *>(iter->first * 2 + 1, iter->second->left));
                }
                if (iter->second->right != nullptr) {
                    v12.insert(pair<int64_t, TreeNode *>(iter->first * 2 + 2, iter->second->right));
                }
            }
            v22.clear();
            for (auto iter = v21.begin(); iter != v21.end(); iter++) { //根据v21，填充v22
                if (iter->second->left != nullptr) {
                    v22.insert(pair<int64_t, TreeNode *>(iter->first * 2 + 1, iter->second->left));
                }
                if (iter->second->right != nullptr) {
                    v22.insert(pair<int64_t, TreeNode *>(iter->first * 2 + 2, iter->second->right));
                }
            }

            level++;
            cout << endl
                 << "level:" << level;
            // printMap("v11", v11);
            // printMap("v21", v21);
            // printMap("v12", v12);
            // printMap("v22", v22);

            if (v22.empty()) { //如果root2为空了，则所有的都添加到root1了，可以直接返回root1
                break;
            }

            for (auto iter = v22.begin(); iter != v22.end();) { //遍历root2当前层
                auto iter1 = v12.find(iter->first);             //判断root1中，是否存在对应节点
                if (iter1 != v12.end()) {                       //存在，将root2对应val加到root1的节点上
                    iter1->second->val += iter->second->val;
                    iter++;
                } else { //不存在的话，直接将root2对应的节点，嫁接到root1对应的节点上
                    if ((iter->first % 2) == 1) {
                        v11[(iter->first - 1) / 2]->left = iter->second;
                    } else {
                        v11[(iter->first - 2) / 2]->right = iter->second;
                    }
                    v22.erase(iter++); //删除对应root2中的节点
                }
            }

            //准备遍历下一层
            v11 = v12;
            v21 = v22;
        }
        return root1;
    }
    //还原完全二叉树，比较对应.太费空间，无法通过检测
    //逐层遍历合并，遍历时保留上层信息，用于指向新节点
    TreeNode *mergeTrees1(TreeNode *root1, TreeNode *root2) {
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

#ifdef CHECK_RESULT

void check(vector<int> s1, vector<int> s2, vector<int> exp) {
    cout << endl
         << "--------------------------------------------";
    printVec("s1", s1);
    printVec("s2", s2);
    printVec("exp", exp);

    Solution test;
    auto ret = test.mergeTrees(CreateTree(s1), CreateTree(s2));
    auto out = printSrc(ret);

    printVec("out", out);

    assert(out == exp);
}

int main() {
    {
        auto s1 = vector<int>{1};
        auto s2 = vector<int>{1, 2};
        auto exp = vector<int>{2, 2};
        check(s1, s2, exp);
    }
    {
        auto s1 = vector<int>{1};
        auto s2 = vector<int>{};
        auto exp = vector<int>{1};
        check(s1, s2, exp);
    }

    {
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
        auto s1 = vector<int>{1, 3, 2, 5};
        auto s2 = vector<int>{2, 1, 3, null, 4, null, 7};
        auto exp = vector<int>{3, 4, 5, 5, 4, null, 7};
        check(s1, s2, exp);
    }

    {
        //     输入:
        // 	Tree 1                     Tree 2
        //           3                         4
        //          / \                       / \
        //         4   5                     1   2
        //        / \                       /
        //       1   2                     1
        // 输出:
        // 合并后的树:
        // 	     7
        // 	    / \
        // 	   5   7
        // 	  / \
        // 	 2   2
        auto s1 = vector<int>{3, 4, 5, 1, 2};
        auto s2 = vector<int>{4, 1, 2, 1};
        auto exp = vector<int>{7, 5, 7, 2, 2};
        check(s1, s2, exp);
    }
    {
        //     输入:
        // 	Tree 1                     Tree 2
        //            -6                      -6           //
        //          /    \                  /    \         //
        //         -9    -3                -9    -3        //
        //          \    /  \               \    /  \      //
        //          -8  -4   1              -8  -4   1     //
        //           \      /  \             \             //
        //           -7     0   5            -7            //
        //                     /                           //
        //                    2                            //
        // 输出:
        // 合并后的树:
        //            -12
        //          /    \
        //         -18    -6
        //          \    /  \
        //          -16  -8   2
        //           \      /  \
        //           -14    0   5
        //                     /
        //                    2
        auto s1 = vector<int>{-6, -9, -3, null, -8, -4, 1, null, -7, null, null, 0, 5, null, null, null, null, 2};
        auto s2 = vector<int>{-6, -9, -3, null, -8, -4, 1, null, -7};
        auto exp = vector<int>{-12, -18, -6, null, -16, -8, 2, null, -14, null, null, 0, 5, null, null, null, null, 2};
        check(s1, s2, exp);
    }
    {
        vector<int> s1 = {1};
        int total = 1000;
        for (size_t i = 0; i < total; i++) {
            s1.push_back(null);
            s1.push_back(1);
        }
        s1.push_back(2);

        vector<int> s2 = {1};
        for (size_t i = 0; i < total / 2; i++) {
            s2.push_back(null);
            s2.push_back(1);
        }
        s2.push_back(2);

        vector<int> exp = {2};
        for (size_t i = 0; i < total / 2; i++) {
            exp.push_back(null);
            exp.push_back(2);
        }
        exp.push_back(2);
        exp.push_back(1);
        exp.push_back(null);
        exp.push_back(null);
        for (size_t i = 0; i < total / 2 - 1; i++) {
            exp.push_back(null);
            exp.push_back(1);
        }
        exp.push_back(2);

        check(s1, s2, exp);
    }

    return 0;
}

#endif //CHECK_RESULT