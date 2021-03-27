#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;
#define null 65535

#define CHECK_RESULT 1

//Definition for a binary tree node.
typedef struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
} TreeNode;

//除非最后一层，其它层节点个数必须是上一层节点个数的2倍
TreeNode *CreateTree(vector<int> Data) {
    TreeNode *root = nullptr;
    if (Data.size() == 0)
        return root;
    vector<TreeNode *> NodesNow;    //用于存储当前层的结点
    vector<TreeNode *> FatherNodes; //用于存储上一层的结点
    root = new TreeNode(Data[0]);
    FatherNodes.push_back(root);
    int index = 1;
    int MaxNum = FatherNodes.size() * 2; //用于存储每一层可以存储的最大结点个数，应该是上一层非空结点的2倍
    int SaveNum = 0;                     //用于记录当前层已经存储了多少结点
    bool LRFlag = false;                 //用于记录下一个上上层结点的左孩子还是右孩子
    while (index < Data.size()) {
        if (Data[index] == null && SaveNum < MaxNum) {
            SaveNum++;
            index++;
            if (index == Data.size())
                break;
            LRFlag = (LRFlag == true) ? false : true;
        } else {
            if (SaveNum < MaxNum) {
                auto tmp = new TreeNode(Data[index]);
                NodesNow.push_back(tmp);
                if (LRFlag) {
                    FatherNodes[SaveNum / 2]->right = tmp;
                    LRFlag = false;
                } else {
                    FatherNodes[SaveNum / 2]->left = tmp;
                    LRFlag = true;
                }
                SaveNum++;
                index++;
            } else {
                FatherNodes.clear();
                for (int i = 0; i < NodesNow.size(); i++) {
                    FatherNodes.push_back(NodesNow[i]);
                }
                MaxNum = FatherNodes.size() * 2;
                SaveNum = 0;
                LRFlag = false;
                NodesNow.clear();
            }
        }
    }
    return root;
}

void prePrint(TreeNode *root) { //先序遍历
    if (root == nullptr)
        return;
    cout << root->val << ',';
    prePrint(root->left);
    prePrint(root->right);
    return;
}

void postPrint(TreeNode *root, bool del = false) { //后序遍历
    if (root == nullptr)
        return;
    postPrint(root->left, del);
    postPrint(root->right, del);
    if (del) {
        delete root;
        root = nullptr;
    } else {
        cout << root->val << ',';
    }

    return;
}

void inPrint(TreeNode *root) { //中序遍历
    if (root == nullptr)
        return;
    inPrint(root->left);
    cout << root->val << ',';
    inPrint(root->right);
    return;
}

void recursion_levelorder(queue<TreeNode *> q, vector<int> &ret) {
    if (q.empty()) {
        return;
    }

    auto p = q.front();
    ret.push_back(p->val);
    q.pop();
    if (p->val != null) {
        if (p->left != nullptr) {
            q.push(p->left);
        } else { //打印 left null
            q.push(new TreeNode(null));
        }
        if (p->right != nullptr) {
            q.push(p->right);
        } else { //打印 right null
            q.push(new TreeNode(null));
        }
    }

    if (q.size() > 0) {
        recursion_levelorder(q, ret);
    }
}

vector<int> printSrc(TreeNode *root) {
    vector<int> ret;
    if (root != nullptr) {
        queue<TreeNode *> q;
        q.push(root);
        recursion_levelorder(q, ret);
    }
    while (ret.size() > 0) {
        if (*ret.rbegin() == null) {
            ret.erase(ret.end() - 1);
        } else {
            break;
        }
    }

    return ret;
}

void delTree(TreeNode *root) {
    postPrint(root, true);
}

void checkVector(TreeNode *root, vector<int> exp, function<vector<int>(TreeNode *root)> f) {
    cout << endl
         << "------------------------------------";

    cout << endl
         << "exp = " << exp.size() << endl;
    for_each(exp.begin(), exp.end(), [](int &v) { cout << v << ","; });

    auto ret = f(root);
    delTree(root);

    cout << endl
         << "ret = " << ret.size() << endl;
    for_each(ret.begin(), ret.end(), [](int &v) { cout << v << ","; });

    assert(ret == exp);
}

/*
|--0--|----1------|--------2---------|----------3--------|
|     |    1      |          1       |          1        |  
|     |     \     |         / \      |         / \       |   
|     |      2    |        2   3     |        2   3      |    
|     |     /     |      /  \        |       / \         | 
|     |    3      |     4    5       |      4   5        | 
|     |           |                  |     /     \       |  
|     |           |                  |    6       8      |   
|     |           |                  |     \       \     |    
|     |           |                  |      7       9    |     
*/
//type:0,pre;1,in;2,post;3,level
vector<int> GetExpect(int index, int type) {
    std::vector<std::vector<int>> src;
    //pre,type=0
    src.push_back(vector<int>{});                          //index=0
    src.push_back(vector<int>{1, 2, 3});                   //index=1
    src.push_back(vector<int>{1, 2, 4, 5, 3});             //index=2
    src.push_back(vector<int>{1, 2, 4, 6, 7, 5, 8, 9, 3}); //index=3
    //in,type=1
    src.push_back(vector<int>{});
    src.push_back(vector<int>{1, 3, 2});
    src.push_back(vector<int>{4, 2, 5, 1, 3});
    src.push_back(vector<int>{6, 7, 4, 2, 5, 8, 9, 1, 3});
    //post,type=2
    src.push_back(vector<int>{});
    src.push_back(vector<int>{3, 2, 1});
    src.push_back(vector<int>{4, 5, 2, 3, 1});
    src.push_back(vector<int>{7, 6, 4, 9, 8, 5, 2, 3, 1});
    //level,type=3
    src.push_back(vector<int>{});
    src.push_back(vector<int>{1, 2, 3});
    src.push_back(vector<int>{1, 2, 3, 4, 5});
    src.push_back(vector<int>{1, 2, 3, 4, 5, 6, 8, 7, 9});

    return src[type * 4 + index];
}
TreeNode *GetTree(int index) {
    std::vector<std::vector<int>> src;
    src.push_back(vector<int>{});
    src.push_back(vector<int>{1, null, 2, 3});
    src.push_back(vector<int>{1, 2, 3, 4, 5});
    src.push_back(vector<int>{1, 2, 3, 4, 5, null, null, 6, null, null, 8, null, 7, null, 9});
    return CreateTree(index < src.size() ? src[index] : src[0]);
}

void printMap(string tag, unordered_map<u_long, TreeNode *> m) {
    cout << endl
         << tag << "-------------------------";
    for (auto iter = m.begin(); iter != m.end(); iter++) {
        cout << endl
             << "first:" << iter->first << ", sencond:" << iter->second->val;
    }
}
void printVec(string tag, vector<int> &val) {
    cout << endl
         << tag << " :";
    for_each(val.begin(), val.end(), [](int v) { cout << v << ","; });
}