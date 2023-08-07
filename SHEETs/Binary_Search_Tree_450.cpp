#include <bits/stdc++.h>
using namespace std;
/*
Binary Search Tree is a node-based binary tree data structure which has the following properties:

    The left subtree of a node contains only nodes with keys lesser than the node’s key.
    The right subtree of a node contains only nodes with keys greater than the node’s key.
    The left and right subtree each must also be a binary search tree.
 */

// % leetcode
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
//% GFG
struct Node
{
    int data;
    Node *left, *right;
    Node(int x)
    {
        data = x;
        left = NULL;
        right = NULL;
    }
    Node() : data(0), left(NULL), right(NULL) {}
};

//^ 1 Search in a binary search tree
TreeNode *searchBST(TreeNode *root, int val)
{
    return ((!root || root->val == val) ? root : (root->val > val) ? searchBST(root->left, val)
                                                                   : searchBST(root->right, val));
}

//^ 2 Ceil of a binary search tree
int findCeil(Node *root, int input)
{
    if (!root)
        return -1;
    int ans = -1;
    while (root)
    {
        if (root->data == input)
        {
            return root->data;
        }
        else if (root->data < input)
        {
            root = root->right;
        }
        else
        {
            ans = root->data;
            root = root->left;
        }
    }
    return ans;
}

//^ 3 Insert a node in the bst
TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);
    TreeNode *curr = root;
    TreeNode *prev = curr;
    while (curr)
    {
        prev = curr;
        if (val > curr->val)
        {
            curr = curr->right;
        }
        else
        {
            curr = curr->left;
        }
    }
    if (val > prev->val)
    {
        prev->right = new TreeNode(val);
    }
    else
    {
        prev->left = new TreeNode(val);
    }
    return root;
}

//^ 4 Delete node in a bst
class DeleteNodesBST
{
public:
    TreeNode *helper(TreeNode *root)
    {
        if (!root->left)
        {
            return root->right;
        }
        else if (!root->right)
            return root->left;
        TreeNode *rightChild = root->right;
        TreeNode *leftLastRight = findLastRight(root->left);
        leftLastRight->right = rightChild;
        return root->left;
    }
    TreeNode *findLastRight(TreeNode *root)
    {
        if (!root->right)
        {
            return root;
        }
        while (root->right)
        {
            root = root->right;
        }
        return root;
    }
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (!root)
            return root;
        if (root->val == key)
            return helper(root);
        TreeNode *curr = root;
        while (root)
        {
            if (root->val > key)
            {
                if (root->left && root->left->val == key)
                {
                    root->left = helper(root->left);
                    break;
                }
                else
                {
                    root = root->left;
                }
            }
            else
            {
                if (root->right && root->right->val == key)
                {
                    root->right = helper(root->right);
                    break;
                }
                else
                {
                    root = root->right;
                }
            }
        }
        return curr;
    }
};

//^ 5  Kth Smallest element in a BST
class KthSmallest
{
public:
    /*
    @ Using extra space O(K)
     */
    void inorder(TreeNode *root, int k, vector<int> &in)
    {
        if (!root)
        {
            return;
        }
        inorder(root->left, k, in);
        if (in.size() == k)
            return;
        in.emplace_back(root->val);
        inorder(root->right, k, in);
    }
    int kthSmallest(TreeNode *root, int k)
    {
        vector<int> in;
        inorder(root, k, in);
        return in.back();
    }

    /*
    @ Optimized version of above code
    ? Can also use Morris traversal to avoid extra stack space
     */
    void inorder(TreeNode *root, int &k, int &res)
    {
        if (!root)
        {
            return;
        }
        inorder(root->left, k, res);
        if (k == 1)
        {
            res = root->val;
            k--;
            return;
        }
        k--;
        inorder(root->right, k, res);
    }
    int kthSmallest_v2(TreeNode *root, int k)
    {
        int res = root->val;
        inorder(root, k, res);
        return res;
    }

    /*
    @ Morris approach
     */
    int KthSmallestElement(Node *root, int k)
    {
        if (!root)
        {
            return -1;
        }
        Node *curr = root;
        int count = 0;
        while (curr)
        {
            if (!curr->left)
            {
                if (++count == k)
                    return curr->data;
                curr = curr->right;
            }
            else
            {
                Node *prev = curr->left;
                while (prev->right && prev->right != curr)
                {
                    prev = prev->right;
                }
                if (!prev->right)
                {
                    prev->right = curr;
                    curr = curr->left;
                }
                else
                {
                    prev->right = NULL;
                    if (++count == k)
                        return curr->data;
                    curr = curr->right;
                }
            }
        }
        return -1;
    }
};

//^ 6 Validate a BST
class ValidateBST
{
private:
public:
    /*
    @ Using fact that inorder of a bst is a sorted array

    *O(N) T.C | O(N) S.C
     */
    bool isValidBST(TreeNode *root)
    {
        vector<int> inorder;
        if (!root)
            return true;
        TreeNode *curr = root;
        while (curr)
        {
            if (!curr->left)
            {
                inorder.emplace_back(curr->val);
                curr = curr->right;
            }
            else
            {
                TreeNode *prev = curr->left;
                while (prev->right && prev->right != curr)
                {
                    prev = prev->right;
                }
                if (!prev->right)
                {
                    prev->right = curr;
                    curr = curr->left;
                }

                else
                {
                    prev->right = nullptr;
                    inorder.emplace_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        // for(auto &it : inorder) cout << it << " ";
        for (int i = 0; i < inorder.size() - 1; i++)
        {
            if (inorder[i + 1] <= inorder[i])
                return false;
        }
        return true;
    }

    /*
    @ Simple recursion
    &- All the nodes will get some valid range according to their parent.
     */
    bool isBST(Node *root, int lowerRange = -1e9, int upperRange = 1e9)
    {
        if (!root)
            return true;
        if (root->data <= lowerRange || root->data >= upperRange)
            return false;
        return isBST(root->left, lowerRange, root->data) && isBST(root->right, root->data, upperRange);
    }
};

//^ 7  LCA of a bst
class LCA
{
private:
public:
    /*
    @ This LCA code works for both BT and BST
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root || root == p || root == q)
            return root;
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left && right)
            return root;
        return left ? left : right;
    }
};

//^ 8 Construct a binary SEARCH tree from preorder traversal
class PreorderTree
{
private:
    typedef vector<int> vi;
    typedef unordered_map<int, int> hmp;

public:
    /*
    @ Brute force NlogN Time
    ? This method works for binary trees as well as BST!
    */
    TreeNode *helper(vi &pre, vi &in, hmp &mp, int preStart, int preEnd, int inStart, int inEnd)
    {
        if (preStart > preEnd || inStart > inEnd)
            return nullptr;
        TreeNode *node = new TreeNode(pre[preStart]);
        int inRoot = mp[node->val];
        int numsLeft = inRoot - inStart;
        node->left = helper(pre, in, mp, preStart + 1, preStart + numsLeft, inStart, inStart + numsLeft);
        node->right = helper(pre, in, mp, preStart + numsLeft + 1, preEnd, inRoot + 1, inEnd);
        return node;
    }
    TreeNode *bstFromPreorder(vi &preorder)
    {
        vi inorder = preorder;
        sort(inorder.begin(), inorder.end());
        hmp mp;
        for (int i = 0; i < inorder.size(); i++)
        {
            mp[inorder[i]] = i;
        }
        TreeNode *root = helper(preorder, inorder, mp, 0, preorder.size() - 1, 0, inorder.size() - 1);
        return root;
    }

    /*
    @ Best approach using range method
    &- For each node in preorder we can decide the possible range of that node.
    &- This will help to decide where that node would be placed in the tree.
    &- For every node in left side the lower range will be 0 and upper range will be decided by the parent node [0,parent value)
    &- For every node in right side the lower range will be 0 and upper range will not be changed at all i.e [0,previous value);

    *O(N) T.c | O(1) S.C
     */
    int idx = 0;
    TreeNode *bstFromPreorder(vi &preorder, int upperLim = 1e9)
    {
        if (idx >= preorder.size() || preorder.at(idx) >= upperLim)
            return nullptr;
        TreeNode *node = new TreeNode(preorder.at(idx++));
        node->left = bstFromPreorder(preorder, node->val);
        node->right = bstFromPreorder(preorder, upperLim);
        return node;
    }
};

//^ 9 Find inorder successor and predecessor
void findPreSuc(Node *root, Node *&pre, Node *&suc, int val)
{
    pre = NULL, suc = NULL;
    Node *curr = root;
    while (root != NULL)
    {
        if (root->data >= val)
        {
            root = root->left;
        }
        else
        {
            pre = root;
            root = root->right;
        }
    }

    root = curr;
    while (root)
    {
        if (root->data <= val)
        {
            root = root->right;
        }
        else
        {
            suc = root;
            root = root->left;
        }
    }
}
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
