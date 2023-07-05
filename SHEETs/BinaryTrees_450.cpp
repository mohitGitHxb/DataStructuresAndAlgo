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
    vector<int> postOrderTraversal(Node *root)
    {
        vector<int> postOrder;
        if (!root)
            return {};
        // stack<Node *> s1, s2;
        // s1.emplace(root);
        // while (!s1.empty())
        // {
        //     root = s1.top();
        //     s1.pop();
        //     s2.emplace(root);
        //     if (root->left != NULL)
        //     {
        //         s1.emplace(root->left);
        //     }
        //     if (root->right != NULL)
        //     {
        //         s1.emplace(root->right);
        //     }
        // }
        // while (!s2.empty())
        // {
        //     postOrder.push_back(s2.top()->data);
        //     s2.pop();
        // }

        return postOrder;
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

//^ 3 Reverse level order traversal of a tree
/*
& Store all the levels in a vector and reverse it
* O(Nodes) T.C | O(N) S.C
 */
vector<int> reverseLevelOrder(Node *root)
{
    if (!root)
        return {};
    vector<vector<int>> order;
    queue<Node *> q;
    q.emplace(root);
    while (!q.empty())
    {
        int qsize = q.size();
        vector<int> temp;
        for (int i = 0; i < qsize; i++)
        {
            Node *fr = q.front();
            q.pop();
            temp.push_back(fr->data);
            if (fr->left)
                q.emplace(fr->left);
            if (fr->right)
                q.emplace(fr->right);
        }
        order.push_back(temp);
    }
    vector<int> ans;
    for (int i = order.size() - 1; i >= 0; i--)
    {
        for (auto &x : order[i])
            ans.push_back(x);
    }
    return ans;
}

//^ 4 Height of a binary tree
/*
~ Height of binary tree rooted at 'i' is equal to (max(height of left subtree, height of right subtree) + 1) as height of the tree is the maximum depth it goes either through left subtree or right subtree.

~ Create a recursive function, recursively calling left subtree and right subtree and evaluating the height of every subtree from leaf to root using the equation above defined and the height of the leaf node is 1 and this is used as base condition of the recursive function.

* O(N) T.C | O(N) S.C
 */
int height(struct Node *root)
{
    // code here
    if (!root)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

//^ 5 preorder inorder and postorder traversal in one traversal
/*
& The function first checks if the root of the tree is NULL. If it is, the function returns an empty 2D vector.

& Next, the function initializes an empty stack s of pairs, where each pair consists of a pointer to a tree node and an integer. It also initializes three empty vectors preorder, inorder, and postorder to store the preorder, inorder, and postorder traversals of the tree, respectively. It then pushes a pair onto stack s consisting of the root of the tree and the integer 1.

& Then, it enters a while loop that continues until stack s is empty. Inside the loop, it sets variable p to the top element of stack s and pops it from the stack. It then checks if the second element of pair p is equal to 1. If it is, it means that this is the first time that node p.first is being visited, so it adds its value to vector preorder. It then pushes a pair onto stack s consisting of node p.first and the integer 2. If node p.first has a left child, it also pushes a pair onto stack s consisting of its left child and the integer 1.

& If the second element of pair p is equal to 2, it means that this is the second time that node p.first is being visited, so it adds its value to vector inorder. It then pushes a pair onto stack s consisting of node p.first and the integer 3. If node p.first has a right child, it also pushes a pair onto stack s consisting of its right child and the integer 1.

& If the second element of pair p is equal to 3, it means that this is the third time that node p.first is being visited, so it adds its value to vector postorder.

& After the while loop, the function returns a 2D vector consisting of vectors preorder, inorder, and postorder.

~ The key idea behind this code is that it uses a stack to simulate the recursive traversal of a binary tree. In each iteration of the while loop, it visits a node and checks if this is the first, second, or third time that this node is being visited. If it is the first time, it adds its value to vector preorder. If it is the second time, it adds its value to vector inorder. If it is the third time, it adds its value to vector postorder. This way, all three traversals are performed in one single traversal.

* The time complexity of this function is O(N) since it visits all N nodes in the binary tree once. The space complexity is O(N) since it uses a stack that can store up to N nodes.
 */
vector<vector<int>> preInPostTraversal(TreeNode *root)
{
    if (!root)
        return {};
    stack<pair<TreeNode *, int>> s;
    vector<int> preorder, inorder, postorder;
    s.emplace(make_pair(root, 1));
    while (!s.empty())
    {
        auto p = s.top();
        s.pop();
        if (p.second == 1)
        {
            preorder.push_back(p.first->val);
            s.push({p.first, 2});
            if (p.first->left)
                s.push({p.first->left, 1});
        }
        else if (p.second == 2)
        {
            inorder.push_back(p.first->val);
            s.push({p.first, 3});
            if (p.first->right)
                s.push({p.first->right, 1});
        }
        else
        {
            postorder.push_back(p.first->val);
        }
    }
    return {preorder, inorder, postorder};
}

//^ 6 Check if a tree is balanced
class CheckBalance
{
private:
    /*
~    The dfsHeight function calculates the height of the binary tree recursively using a depth-first search (DFS) approach. It takes a Node pointer as input and returns the height of the subtree rooted at that node. If the subtree is not balanced (i.e., the absolute difference in heights between the left and right subtrees is greater than 1), the function returns -1 to indicate imbalance. Otherwise, it returns the actual height of the subtree.

Here's a breakdown of the dfsHeight function:
&- The base case checks if the current node is null. If it is, the height is considered as 0, and the function returns 0.
&- The function recursively calls itself for the left subtree and stores the result in the left variable.
&- If the left variable is -1 (indicating an imbalance in the left subtree), the function immediately returns -1 to propagate the imbalance.
&- The function then recursively calls itself for the right subtree and stores the result in the right variable.
&- If the right variable is -1 (indicating an imbalance in the right subtree), the function immediately returns -1 to propagate the imbalance.
&- Finally, if the absolute difference between left and right is greater than 1, the subtree is considered imbalanced, and the function returns -1.
&- Otherwise, the function returns 1 plus the maximum of left and right, representing the height of the current subtree.

~ The isBalanced function serves as a wrapper function that calls dfsHeight and checks if the returned height is -1 (indicating an imbalance). If the height is -1, it means the binary tree is not balanced, and the function returns false. Otherwise, it returns true, indicating that the binary tree is balanced.

* The time complexity of this code is O(N), where N is the number of nodes in the binary tree. This is because the dfsHeight function visits each node once, performing constant-time operations at each node.

* The space complexity is O(H), where H is the height of the binary tree. This is due to the recursive calls of dfsHeight, which consume stack space proportional to the height of the tree. In the worst case, where the tree is skewed and has a height of N, the space complexity becomes O(N).
     */
public:
    int dfsHeight(Node *root)
    {
        if (!root)
            return 0;
        int left = dfsHeight(root->left);
        if (left == -1)
            return -1;
        int right = dfsHeight(root->right);
        if (right == -1)
            return -1;

        if (abs(left - right) > 1)
            return -1;

        return 1 + max(left, right);
    }
    bool isBalanced(Node *root)
    {
        return dfsHeight(root) == -1 ? false : true;
    }
};

//^ 7 Diameter of a binary tree
class FindDiameter
{
public:
    int findHeight(Node *root, int &dia)
    {
        if (!root)
            return 0;
        int lh = findHeight(root->left, dia);
        int rh = findHeight(root->right, dia);
        dia = max(dia, lh + rh);
        return 1 + max(lh, rh);
    }
    int diameter(Node *root)
    {
        int dia = 0;
        findHeight(root, dia);
        return dia;
    }
};

//^ 8 Mirror of a tree
/*
& swap left and right pointers
* O(N) T.C | O(H) S.C
 */
Node *Mirror(Node *root)
{
    if (!root)
        return root;
    swap(root->left, root->right);
    if (root->left)
        Mirror(root->left);
    if (root->right)
        Mirror(root->right);
    return root;
}

//^ 9 Minimum path sum in a binary tree
class MinPathSum
{
private:
    /*
        The solve function takes a TreeNode pointer root and a reference to an integer maxi (initialized to a very small value) as parameters.

    If root is nullptr, indicating an empty node, the function returns 0.

    The function recursively calls solve on the left and right subtrees of root, storing the returned values in the variables left and right, respectively. The values are calculated by taking the maximum between 0 and the result of the recursive calls. This ensures that negative values are not considered in the path sum.

    The maximum path sum that includes the current root node is calculated as left + right + root->val. This is compared with the current maximum sum maxi, and the greater value is stored in maxi. This step finds the maximum sum path that includes the current node.

    The function returns the maximum path sum starting from the current root node, which is calculated as root->val + max(right, left). This step considers whether to include the current node in the path sum or not, by choosing the maximum between the sums of the left and right subtrees.

    The maxPathSum function initializes the maxi variable to a very small value.

    It calls the solve function with the root node and the maxi variable as parameters. This updates the maxi variable with the maximum path sum in the tree.

    Finally, the maxi variable, which now holds the maximum path sum, is returned as the result of the function.

The time complexity of this code is O(N), where N is the number of nodes in the binary tree. This is because we perform a DFS traversal of the tree, visiting each node once.

The space complexity is O(H), where H is the height of the binary tree. This is because the recursion stack will have at most H frames at any given time, corresponding to the maximum depth of the tree. In the worst case, when the tree is skewed, the height can be equal to N, resulting in a space complexity of O(N). However, in a balanced tree, the height is typically logarithmic in the number of nodes, resulting in a space complexity of O(log N).
    * O(N) T.C | O(N) S.C
     */
public:
    int solve(TreeNode *root, int &maxi)
    {
        if (!root)
            return 0;
        int left = max(0, solve(root->left, maxi));
        int right = max(0, solve(root->right, maxi));
        maxi = max(maxi, left + right + root->val);
        return root->val + max(right, left);
    }
    int maxPathSum(TreeNode *root)
    {
        int maxi = -1e8;
        solve(root, maxi);
        return maxi;
    }
};
int main()
{
    return 0;
}