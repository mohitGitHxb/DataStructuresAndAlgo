#include <bits/stdc++.h>
using namespace std;
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
};
//% LC
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//^ 1 DFS traversals for binary tree [basic]
class BasicDFSTraversals
{
public:
    void preorder(Node *root)
    {
        if (!root)
            return;
        cout << root->data << "\n";
        preorder(root->left);
        preorder(root->right);
    }
    void inorder(Node *root)
    {
        if (!root)
            return;
        inorder(root->left);
        cout << root->data << "\n";
        inorder(root->right);
    }
    void postorder(Node *root)
    {
        if (!root)
            return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << "\n";
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (!root)
            return {};
        stack<TreeNode *> st;
        st.emplace(root);
        vector<int> ans;
        while (!st.empty())
        {
            TreeNode *top = st.top();
            st.pop();
            ans.push_back(top->val);
            if (top->right)
                st.emplace(top->right);
            if (top->left)
                st.emplace(top->left);
        }
        return ans;
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        if (!root)
            return {};
        stack<TreeNode *> st;
        TreeNode *temp = root;
        while (!st.empty() or temp)
        {
            while (temp)
            {
                st.push(temp);
                temp = temp->left;
            }
            temp = st.top();
            ans.push_back(st.top()->val);
            st.pop();
            temp = temp->right;
        }
        return ans;
    }
};

//^2 Level order traversal of a binary tree
/*
&1. If the root of the binary tree is NULL, return an empty vector (representing an empty tree).
&2. Create an empty queue q to store the nodes to be processed.
&3. Create an empty vector of vectors ans to store the level order traversal result.
&4. Enqueue the root node into the queue.
&5. Start a loop that continues until the queue becomes empty.
&6. Inside the loop, create an empty vector temp to store the values of the nodes at the current level.
&7. Get the current size of the queue qsize (representing the number of nodes at the current level).
&8. Run a loop i from 0 to qsize - 1 to process each node at the current level.
&9. Dequeue the front node top from the queue.
&10. Add the value of top to the temp vector.
&11. If top has a left child, enqueue the left child into the queue.
&12. If top has a right child, enqueue the right child into the queue.
&13. After processing all the nodes at the current level, push the temp vector into the ans vector.
&14. Repeat steps 5 to 13 until the queue becomes empty.
&15. Return the ans vector containing the level order traversal of the binary tree.

~ The algorithm utilizes the queue data structure to perform a breadth-first traversal of the binary tree. It ensures that the nodes at each level are processed before moving on to the next level. By using the queue, we can keep track of the nodes at each level and process them in the required order.

* The time complexity of this algorithm is O(N), where N is the total number of nodes in the binary tree. This is because we visit each node once. The space complexity is O(M), where M is the maximum number of nodes at any level in the binary tree. This is because at most M nodes will be stored in the queue at any given time, representing the nodes at the current level.
 */
vector<vector<int>> levelOrder(TreeNode *root)
{
    if (!root)
        return {};
    queue<TreeNode *> q;
    vector<vector<int>> ans;
    q.emplace(root);
    while (!q.empty())
    {
        vector<int> temp;
        int qsize = q.size();
        for (int i = 0; i < qsize; i++)
        {
            TreeNode *top = q.front();
            q.pop();
            temp.push_back(top->val);
            if (top->left)
                q.emplace(top->left);
            if (top->right)
                q.emplace(top->right);
        }
        ans.push_back(temp);
    }
    return ans;
}
int main()
{
    return 0;
}