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

//^ 10 Zig Zag traversal
/*
&- The function zigzagLevelOrder takes a TreeNode pointer root as input and returns a 2D vector.
&- If the root is nullptr, indicating an empty tree, an empty vector ans is returned.
&- Otherwise, a queue q is created to perform the level order traversal. The root node is added to the queue.
&- A vector of vectors ans is initialized to store the final result.
&- A boolean variable toggle is set to true to keep track of the traversal direction. If toggle is true, the traversal is from left to right. If toggle is false, the traversal is from right to left.
&- The main loop continues until the queue q is empty, meaning all nodes have been processed.
&- Inside the loop, the current level's size is stored in a variable size.
&- A vector row of size size is created to store the values of the current level.
&- If toggle is true, indicating a left-to-right traversal, the values are added to row in the order they are dequeued from the queue. Each node is dequeued, and its value is added to the row vector. If the dequeued node has left and right children, they are enqueued in the queue.
&- If toggle is false, indicating a right-to-left traversal, the values are added to row in reverse order. Each node is dequeued, and its value is added to the row vector at the corresponding index. If the dequeued node has left and right children, they are enqueued in the queue.
&- After processing the current level, the toggle variable is flipped to change the traversal direction for the next level.
&- The row vector, containing the values of the current level, is added to the ans vector.
&- Once the loop finishes, the function returns the ans vector, which contains the zigzag level order traversal of the binary tree.

* The time complexity of this code is O(N), where N is the number of nodes in the binary tree. This is because each node is visited once during the level order traversal.

* The space complexity is O(M), where M is the maximum number of nodes at any level in the binary tree. This is because at any given time, the queue q holds at most the nodes at the current level. The maximum number of nodes at any level can be the leaf level, which has N/2 nodes in a balanced binary tree, resulting in a space complexity of O(N/2) = O(N).
 */
vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    if (!root)
        return {};
    queue<TreeNode *> q;
    q.emplace(root);
    vector<vector<int>> ans;
    bool toggle = true;
    while (!q.empty())
    {
        int size = q.size();
        vector<int> row(size);
        if (toggle)
        {
            for (int i = 0; i < size; i++)
            {
                auto x = q.front();
                q.pop();
                row[i] = x->val;
                if (x->left)
                    q.emplace(x->left);
                if (x->right)
                    q.emplace(x->right);
            }
        }
        else
        {
            for (int i = size - 1; i >= 0; i--)
            {
                auto x = q.front();
                q.pop();
                row[i] = x->val;
                if (x->left)
                    q.emplace(x->left);
                if (x->right)
                    q.emplace(x->right);
            }
        }
        toggle = !toggle;
        ans.emplace_back(row);
    }
    return ans;
}

//^ 11 Boundary Traversal of a binary tree
class BoundaryTraversal
{
public:
    bool isLeaf(Node *root)
    {
        return !root->left && !root->right;
    }
    void addLeftBoundary(Node *root, vector<int> &res)
    {
        Node *curr = root->left;
        while (curr)
        {
            if (!isLeaf(curr))
                res.push_back(curr->data);
            if (curr->left)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }
    void addRightBoundary(Node *root, vector<int> &res)
    {
        Node *curr = root->right;
        vector<int> tmp;
        while (curr)
        {
            if (!isLeaf(curr))
                tmp.push_back(curr->data);
            if (curr->right)
                curr = curr->right;
            else
                curr = curr->left;
        }
        for (int i = tmp.size() - 1; i >= 0; i--)
        {
            res.push_back(tmp.at(i));
        }
    }
    void addLeaves(Node *root, vector<int> &res)
    {
        if (isLeaf(root))
        {
            res.push_back(root->data);
            return;
        }
        if (root->left)
            addLeaves(root->left, res);
        if (root->right)
            addLeaves(root->right, res);
    }

    vector<int> printBoundary(Node *root)
    {
        vector<int> res;
        if (!root)
            return res;
        if (!isLeaf(root))
            res.push_back(root->data);
        addLeftBoundary(root, res);
        addLeaves(root, res);
        addRightBoundary(root, res);
        return res;
    }
};

//^ 12 vertical order traversal
class VerticalOrder
{
private:
    /*
&        Check if the root node is null. If it is, return an empty vector since there are no nodes to traverse.

&    Create a map called nodes to store the nodes of the binary tree based on their horizontal and vertical positions. The map is defined as map<int, map<int, multiset<int>>>, where the first integer represents the horizontal position (x-coordinate), the second map represents the vertical position (y-coordinate), and the multiset stores the nodes' values. Using a multiset allows nodes with the same vertical position to be sorted in ascending order.

&    Create a queue called q to perform a breadth-first search. Each element in the queue is a pair consisting of a tree node and its corresponding position (x, y). Initialize the queue with the root node at position (0, 0).

&    Start a while loop that continues until the queue becomes empty:
    ~    Retrieve the front element from the queue.
    ~    Extract the node, x-coordinate, and y-coordinate from the element.
    ~    Insert the node's value into the nodes map at the corresponding position (x, y).
    ~    If the node has a left child, push it into the queue with the position (x-1, y+1) to move left and down.
    ~    If the node has a right child, push it into the queue with the position (x+1, y+1) to move right and down.

&    After traversing all nodes, create a vector called ans to store the final result.

&    Iterate over the nodes map using a range-based loop:
    ~    For each horizontal position (x), create a vector called col to store the nodes' values.
    ~    Iterate over the multiset of nodes at each vertical position (y) using another range-based loop.
    ~    Insert the node values from the multiset into the col vector using the insert function.
    ~    Append the col vector to the ans vector.

&    Return the ans vector, which contains the vertical order traversal of the binary tree.

*   The time complexity of this code is O(n log n), where n is the number of nodes in the binary tree. This is because the code performs a breadth-first traversal, which takes O(n) time, and inserting values into the multiset within the map takes O(log n) time. The space complexity is O(n) since the nodes map can potentially store all nodes of the binary tree.

     */
public:
    vector<vector<int>> verticalTraversal(TreeNode *root)
    {
        if (!root)
            return {};
        map<int, map<int, multiset<int>>> nodes;
        queue<pair<TreeNode *, pair<int, int>>> q;
        q.push({root, {0, 0}});
        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            TreeNode *node = it.first;
            int x = it.second.first;
            int y = it.second.second;
            nodes[x][y].insert(node->val);
            if (node->left)
                q.push({node->left, {x - 1, y + 1}});
            if (node->right)
                q.push({node->right, {x + 1, y + 1}});
        }

        vector<vector<int>> ans;
        for (auto &it : nodes)
        {
            vector<int> col;
            for (auto &k : it.second)
                col.insert(col.end(), k.second.begin(), k.second.end());
            ans.push_back(col);
        }
        return ans;
    }

    /*
    @ Slightly more optimized version of the above function
        Create a map called m to store the nodes of the binary tree based on their horizontal positions (x-axis). The map is defined as map<int, vector<int>>, where the key represents the horizontal position (x-axis), and the value is a vector that stores the node values.

    Create a queue called q to perform a level order traversal. Each element in the queue is a pair consisting of an integer representing the horizontal position (x-axis) and a tree node. Initialize the queue with a pair (0, root), where 0 represents the horizontal position of the root node.

    Start a while loop that continues until the queue becomes empty:
        Create a set called tmp to store the nodes with the same horizontal position (x-axis). The set is defined as set<pair<int, int>>, where each pair consists of the horizontal position (x-axis) and the node value.
        Get the current size of the queue to iterate only over the nodes at the current level.
        Iterate over the elements in the queue:
            Retrieve the front element from the queue.
            Insert the pair (horizontal position, node value) into the tmp set.
            If the node has a left child, push it into the queue with the horizontal position decreased by 1 to move left.
            If the node has a right child, push it into the queue with the horizontal position increased by 1 to move right.
        After processing all nodes at the current level, iterate over the tmp set and insert the node values into the corresponding vector in the m map.

    After traversing all nodes, create a vector called res to store the final result.

    Iterate over the elements in the m map using a range-based loop:
        For each horizontal position (x-axis), append the corresponding vector of node values to the res vector.

    Return the res vector, which contains the vertical order traversal of the binary tree.

The time complexity of this code is O(n log n), where n is the number of nodes in the binary tree. This is because the code performs a breadth-first traversal, which takes O(n) time, and inserting values into the set within the loop takes O(log n) time. The space complexity is O(n) since the m map can potentially store all nodes of the binary tree.
     */
    vector<vector<int>>
    verticalTraversal_optimized(TreeNode *root)
    {
        map<int, vector<int>> m;        // when iterate map, key is already the order of x-axis
        queue<pair<int, TreeNode *>> q; // for level traversal
        q.push(make_pair(0, root));     // root default x-axis is 0
        while (!q.empty())
        {
            set<pair<int, int>> tmp; // k: x-axis, v:val Already solved the case when the position is ths same
            int len = q.size();
            for (int i = 0; i < len; ++i)
            {
                auto p = q.front();
                q.pop();
                tmp.insert(make_pair(p.first, p.second->val));
                if (p.second->left)
                    q.push(make_pair(p.first - 1, p.second->left));
                if (p.second->right)
                    q.push(make_pair(p.first + 1, p.second->right));
            }

            for (auto p : tmp)
                m[p.first].push_back(p.second);
        }

        vector<vector<int>> res;
        for (auto kv : m)
            res.push_back(kv.second);
        return res;
    }
};

//^ 13,14,15,16
class DifferentViewsOfTree
{
public:
    /*
    @ TOP G View
    &- The code implements the top view of a binary tree.
&- The algorithm utilizes a breadth-first search (BFS) approach to traverse the tree level by level.
&- It uses a queue to store pairs of nodes and their corresponding horizontal distances from the root.
&- A map is used to keep track of the nodes for each horizontal distance.
&- The root node is pushed into the queue with a horizontal distance of 0.
&- While the queue is not empty, the algorithm performs the following steps:
&- Dequeue a pair from the front of the queue, consisting of a node and its horizontal distance.
&- If the current horizontal distance does not exist in the map, insert the node's data into the map with the horizontal distance as the key.
&- If the node has a left child, enqueue a pair with a horizontal distance decremented by 1 and the left child.
&- If the node has a right child, enqueue a pair with a horizontal distance incremented by 1 and the right child.
&- After the BFS traversal, the map contains the top view nodes for each horizontal distance.
&- Extract the nodes from the map in ascending order of their horizontal distances and store them in a vector.
&- Return the vector containing the top view nodes.

~ The intuition behind this algorithm is to traverse the binary tree in a level-wise manner, keeping track of the horizontal distances of the nodes. By storing only the first encountered node for each horizontal distance in the map, the algorithm captures the nodes visible from the top view of the tree. Finally, the nodes are extracted from the map and returned as the top view vector.

* O(NlogN) T.C | O(N) S.C

     */

    vector<int> topView(Node *root)
    {
        // Your code here
        if (!root)
            return {};
        queue<pair<int, Node *>> q;
        vector<int> ans;
        map<int, int> mp;
        q.push({0, root});
        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            Node *node = it.second;
            int x = it.first;
            if (mp.find(x) == mp.end())
                mp[x] = node->data;
            if (node->left)
                q.push({x - 1, node->left});
            if (node->right)
                q.push({x + 1, node->right});
        }
        for (auto &it : mp)
        {
            ans.push_back(it.second);
        }
        return ans;
    }
    /*
    @ Bottom G view

     */
    vector<int> bottomView(Node *root)
    {
        // Your Code Here
        if (!root)
            return {};
        queue<pair<int, Node *>> q;
        vector<int> ans;
        q.emplace(0, root);
        map<int, int> mp;
        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            int x = it.first;
            Node *p = it.second;
            mp[x] = p->data;
            if (p->left)
                q.emplace(x - 1, p->left);
            if (p->right)
                q.emplace(x + 1, p->right);
        }
        for (auto &i : mp)
            ans.emplace_back(i.second);
        return ans;
    }
    /*
    @ Right View
     */
    vector<int> rightSideView(TreeNode *root)
    {
        if (!root)
            return {};
        vector<int> ans;
        queue<pair<TreeNode *, int>> q;
        map<int, TreeNode *> mp;
        q.emplace(root, 0);
        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            int y = it.second;
            mp[y] = it.first;
            if (it.first->left)
                q.emplace(it.first->left, y + 1);
            if (it.first->right)
                q.emplace(it.first->right, y + 1);
        }
        for (auto &k : mp)
            ans.emplace_back(k.second->val);
        return ans;
    }
    /*
    @ Left view of the tree
     */
    void leftViewTree(Node *root, vector<int> &ans, int level)
    {
        if (!root)
            return;
        if (level == ans.size())
            ans.emplace_back(root->data);
        leftViewTree(root->left, ans, level + 1);
        leftViewTree(root->right, ans, level + 1);
    }
};
/*
&- The code implements the diagonal traversal of a binary tree.
&- The algorithm utilizes a modified form of the breadth-first search (BFS) approach.
&- It uses a queue to store the nodes to be processed.
&- A vector is used to store the values of the nodes in the diagonal order.
&- The root node is pushed into the queue.
&- While the queue is not empty, the algorithm performs the following steps:
&- Dequeue a node from the front of the queue.
&- While the current node is not null, perform the following steps:
&- If the node has a left child, enqueue the left child into the queue.
&- Add the data of the current node to the result vector.
&- Move to the right child of the current node.
&- After the traversal, the result vector contains the values of the nodes in the diagonal order.
&- Return the result vector.

~ The intuition behind this algorithm is to traverse the binary tree in a modified BFS manner, where each diagonal is traversed from top-left to bottom-right. By enqueueing the left child of each node (if it exists) before processing the current node and moving to the right child, the algorithm ensures that the diagonal elements are visited in the correct order.

* Since the algorithm visits each node once and performs constant-time operations, the time complexity is O(n), where n is the number of nodes in the binary tree. The space complexity is also O(n) in the worst case, as the queue may store all the nodes in the binary tree in the case of a skewed tree
 */

//^ 17
vector<int> diagonal(Node *root)
{
    if (!root)
        return {};
    queue<Node *> q;
    q.emplace(root);
    vector<int> res;
    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        while (node)
        {
            if (node->left)
                q.emplace(node->left);
            res.emplace_back(node->data);
            node = node->right;
        }
    }
    return res;
}

//^ 18 Root to a given node path
/*
& Traverse using Inorder traversal technique (DFS algorithm)
& getPath functions checks whether the node is present in the tree or not
& at the same time it keeps track of the path by using a ds like array or vector
& after the functions returns the ds will hold the path from root to that target node

* O(N) T.C | O(H) S.C
 */
bool getPath(Node *root, vector<int> &ds, int x)
{
    if (!root)
        return false;
    ds.emplace_back(root->data);

    if (root->data == x)
    {
        return true;
    }
    if (getPath(root->left, ds, x) || getPath(root->right, ds, x))
    {
        return true;
    }
    ds.pop_back();
    return false;
}

//^ 19 Lowest Common Ancestor of a binary tree
class LCS
{
public:
    /*
    @ Method - 1 brute force
    & use the root to a given node path solution to get the path of two elements whose lcs needs to be found

    & then just look for the rightmost common element and that will be our LCS
     */

    /*
    @ Method - 2
    &- If the root is NULL, it means we have reached the end of the tree, so we return NULL.

&- If the current node root is equal to either p or q, it means we have found one of the nodes we are looking for. Therefore, we return the current node as the lowest common ancestor.

&- We recursively call the lowestCommonAncestor function on the left and right subtrees of the current node to find the lowest common ancestor in those subtrees.

&- If both the left and right subtrees return non-null values, it means that p and q are found in different subtrees, and the current node root is their lowest common ancestor. Hence, we return root.

&- If either the left or right subtree returns a non-null value, it means that both p and q are found in the same subtree, and the non-null value represents their lowest common ancestor. We return that value.

* The time complexity of this algorithm is O(N), where N is the number of nodes in the binary tree. This is because we need to visit each node exactly once.

* The space complexity is O(H), where H is the height of the binary tree. In the worst case, when the binary tree is skewed, the height can be equal to the number of nodes in the tree, resulting in O(N) space complexity. However, in a balanced binary tree, the height is logarithmic, resulting in O(log N) space complexity.
     */
    TreeNode *lcs(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (!root)
            return nullptr;
        if (root == p || root == q)
            return root;
        TreeNode *left = lcs(root->left, p, q);
        TreeNode *right = lcs(root->right, p, q);
        if (left && right)
        {
            return root;
        }

        return (left) ? left : right;
    }
};

//^ 20 Maximum Width of a binary tree [LeetCode]
int widthOfBinaryTree(TreeNode *root)
{
    if (!root)
        return 0;
    int ans = 0;
    queue<pair<TreeNode *, int>> q;
    q.emplace(root, 0);
    while (!q.empty())
    {
        int size = q.size();
        int parent_id = q.front().second;
        int first = 0, last = 0;
        for (int i = 0; i < size; i++)
        {
            int cur_id = q.front().second - parent_id;
            TreeNode *node = q.front().first;
            q.pop();
            if (i == 0)
            {
                first = cur_id;
            }
            if (i == size - 1)
            {
                last = cur_id;
            }

            if (node->left)
            {
                q.emplace(node->left, cur_id * 2 + 1);
            }
            if (node->right)
            {
                q.emplace(node->right, cur_id * 2 + 2);
            }
        }

        ans = max(ans, last - first + 1);
    }
    return ans;
}

//^ 21 Children sum property [hard]
void changeTree(Node *root)
{
    if (!root)
        return;
    int childSum = 0;
    if (root->left)
    {
        childSum += root->left->data;
    }
    if (root->right)
    {
        childSum += root->right->data;
    }
    if (childSum >= root->data)
    {
        root->data = childSum;
    }
    else
    {
        if (root->left)
        {
            root->left->data = root->data;
        }
        if (root->right)
        {
            root->right->data = root->data;
        }
    }
    changeTree(root->left);
    changeTree(root->right);
    int sum = 0;
    if (root->left)
    {
        sum += root->left->data;
    }
    if (root->right)
    {
        sum += root->right->data;
    }
    root->data = max(root->data, sum);
}

//^ 22 All nodes at a distance k in a binary tree
class DistanceK
{
private:
    /*
 &       The setParents function sets up a parent-child relationship map for the nodes in the binary tree. It performs a level order traversal using a queue and populates the parent map for each node except the root. This map helps in traversing back to the parent nodes during the BFS traversal in the distanceK function.

 &   The distanceK function takes three arguments: the root of the binary tree, the target node, and the distance k. It first performs some basic input validations and initializes data structures.

 &   It uses a BFS (Breadth-First Search) traversal to explore the tree starting from the target node and moving outward in levels.

 &   It maintains a queue q to store the nodes to be visited during the traversal. Initially, the target node is enqueued.

 &   It also maintains a visited map to keep track of the nodes that have been visited during the traversal.

 &   Inside the main BFS loop, it processes each level by iterating over the nodes in the current level. It checks if the current level is equal to the desired distance k. If it is, it breaks out of the loop as we have explored all nodes at distance k from the target.

 &   For each node, it checks its left child, right child, and parent nodes. If they exist and have not been visited, they are enqueued, and their corresponding entries in the visited map are marked as true.

 &   Once the BFS traversal is complete, the queue q contains all the nodes at distance k from the target node.

 &   The nodes in the queue are extracted one by one, and their values are added to the result vector res.

 &   Finally, the function returns the res vector containing the values of all nodes at distance k from the target node.

Intuition:
~   The code uses a BFS traversal starting from the target node to explore the tree. It maintains a visited map to prevent revisiting the same node and a parent map to keep track of parent-child relationships. By breaking the loop when the current level is equal to the desired distance k, we ensure that only nodes at the desired distance are processed.

*   Time Complexity: The code performs a BFS traversal on the binary tree, which takes O(n) time, where n is the number of nodes in the tree. Additionally, adding nodes to the queue and marking them as visited take constant time operations. Therefore, the overall time complexity is O(n).

*   Space Complexity: The space complexity is determined by the space used for the queue, the visited map, and the parent map. In the worst case, the queue may contain all the nodes at the maximum level of the tree, which would be O(n/2) = O(n) nodes. The visited and parent maps also occupy O(n) space. Therefore, the overall space complexity is O(n).

In summary, the code efficiently finds all nodes at a distance k from a target node in a binary tree using a BFS traversal and maintains a visited map and a parent map. It has a time complexity of O(n) and a space complexity of O(n).

     */
public:
    void setParents(TreeNode *root, unordered_map<TreeNode *, TreeNode *> &parent)
    {
        queue<TreeNode *> q;
        q.emplace(root);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *cur = q.front();
                q.pop();
                if (cur->left)
                {
                    q.emplace(cur->left);
                    parent[cur->left] = cur;
                }
                if (cur->right)
                {
                    q.emplace(cur->right);
                    parent[cur->right] = cur;
                }
            }
        }
    }

    vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
    {
        if (!root || k < 0 || !target)
            return {};
        unordered_map<TreeNode *, TreeNode *> parent;
        setParents(root, parent);
        queue<TreeNode *> q;
        q.emplace(target);
        unordered_map<TreeNode *, bool> visited;
        int currentLevel = 0;
        visited[target] = true;
        while (!q.empty())
        {
            int size = q.size();
            if (currentLevel++ == k)
                break;
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = q.front();
                q.pop();
                if (node->left && !visited[node->left])
                {
                    q.emplace(node->left);
                    visited[node->left] = true;
                }
                if (node->right && !visited[node->right])
                {
                    q.emplace(node->right);
                    visited[node->right] = true;
                }
                if (parent[node] && !visited[parent[node]])
                {
                    q.emplace(parent[node]);
                    visited[parent[node]] = true;
                }
            }
        }

        // q has all the elements we need :-)
        vector<int> res;
        while (!q.empty())
        {
            res.push_back(q.front()->val);
            q.pop();
        }
        return res;
    }
};

//^ 23 Minimum time to burn a binary tree
class BurnTree
{
public:
    /*

&       This code is a solution to the problem of burning a tree from a given target node. The problem is to find the minimum time required to burn the entire tree if we start burning it from the target node. The code uses a breadth-first search (BFS) algorithm to solve this problem.

&   The `convertIntoGraph` function converts the tree into a graph by storing the parent of each node in an unordered_map. This is done using a BFS traversal of the tree.

&   The `getTargetAddress` function returns the address of the target node in the tree.

&   The `minTime` function calculates the minimum time required to burn the entire tree. It first converts the tree into a graph using the `convertIntoGraph` function and then finds the address of the target node using the `getTargetAddress` function. It then performs a BFS traversal starting from the target node and keeps track of the minimum time required to burn all nodes.

* The time complexity of this code is O(n) where n is the number of nodes in the tree. The space complexity is also O(n) as we need to store the parent and visited information for each node.

&- The code uses BFS to solve the problem.
&- The `convertIntoGraph` function converts the tree into a graph.
&- The `getTargetAddress` function returns the address of the target node.
&- The `minTime` function calculates the minimum time required to burn the entire tree.
&- The time complexity is O(n) and space complexity is also O(n).
     */
    void convertIntoGraph(Node *root, unordered_map<Node *, Node *> &mp)
    {
        queue<Node *> q;
        q.emplace(root);
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                Node *curr = q.front();
                q.pop();
                if (curr->left)
                {
                    q.emplace(curr->left);
                    mp[curr->left] = curr;
                }
                if (curr->right)
                {
                    q.emplace(curr->right);
                    mp[curr->right] = curr;
                }
            }
        }
    }
    Node *getTargetAddress(Node *root, int target)
    {
        if (!root || root->data == target)
            return root;
        Node *l = getTargetAddress(root->left, target);
        Node *r = getTargetAddress(root->right, target);
        return (l) ? l : r;
    }
    int minTime(Node *root, int target)
    {
        if (!root)
            return 0;
        unordered_map<Node *, Node *> parent;
        unordered_map<Node *, bool> visited;
        convertIntoGraph(root, parent);
        Node *key = getTargetAddress(root, target);
        queue<Node *> q;
        q.emplace(key);
        visited[key] = true;
        int minTime = -1;
        while (!q.empty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                Node *curr = q.front();
                q.pop();
                visited[curr] = true;
                if (curr->left && !visited[curr->left])
                {
                    q.emplace(curr->left);
                    visited[curr->left] = true;
                }
                if (curr->right && !visited[curr->right])
                {
                    q.emplace(curr->right);
                    visited[curr->right] = true;
                }
                if (parent[curr] && !visited[parent[curr]])
                {
                    q.emplace(parent[curr]);
                    visited[parent[curr]] = true;
                }
            }
            minTime++;
        }
        return minTime;
    }
};

//^ 24 Count all nodes in a complete tree
class CountNodes
{
private:
    /*
&     The f function takes two arguments, left and right, which are the left and right children of a node. If the left child is NULL, it returns 0. If the right child is NULL, it returns 1. Otherwise, it returns 2 plus the result of recursively calling the f function on the left and right children of both the left and right children.

& The countNodes function takes the root of the tree as an argument and returns the number of nodes in the tree. If the root is NULL, it returns 0. Otherwise, it returns 1 plus the result of calling the f function on the left and right children of the root.

! The time complexity of this code is O(n) where n is the number of nodes in the tree. The space complexity is O(h) where h is the height of the tree.

    * Important property : total nodes in a complete tree = 2*height - 1;
     */
public:
    int f(TreeNode *left, TreeNode *right)
    {
        if (!left)
            return 0;
        if (!right)
            return 1;
        return 2 + f(left->left, left->right) + f(right->left, right->right);
    }
    int countNodes(TreeNode *root)
    {
        if (!root)
            return 0;
        return 1 + f(root->left, root->right);
    }
    /*
&       The leftHeight function calculates the height of the left subtree of the given root by traversing down the leftmost path of the tree. Similarly, the rightHeight function calculates the height of the right subtree of the given root by traversing down the rightmost path of the tree.

&   The countNodes_v2 function takes the root of the tree as an argument and returns the number of nodes in the tree. If the root is NULL, it returns 0. It then calculates the height of the left and right subtrees using the leftHeight and rightHeight functions. If the heights are equal, it means that the last level of the tree is completely filled, so it returns 2^h - 1, where h is the height of the tree. Otherwise, it returns 1 plus the result of recursively calling countNodes_v2 on the left and right children of the root.

*   The time complexity of this code is O(log^2 n) where n is the number of nodes in the tree. The space complexity is O(h) where h is the height of the tree.

     */
    int leftHeight(TreeNode *root)
    {
        int h = 0;
        while (root)
        {
            root = root->left;
            h++;
        }
        return h;
    }
    int rightHeight(TreeNode *root)
    {
        int h = 0;
        while (root)
        {
            root = root->right;
            h++;
        }
        return h;
    }
    int countNodes_v2(TreeNode *root)
    {
        if (!root)
            return 0;
        int lh = leftHeight(root);
        int rh = rightHeight(root);
        if (lh == rh)
            return pow(2, lh) - 1;
        return 1 + countNodes_v2(root->left) + countNodes_v2(root->right);
    }
};

//^ 25 Construct binary tree from inorder and preorder traversal [duplicates allowed]
class BuildTree
{
private:
    /*
&    The helper function takes in seven arguments: two arrays of integers pre and in representing the preorder and inorder traversals of a binary tree, four integers preStart, preEnd, inStart, and inEnd representing the start and end indices of the current subarrays in arrays pre and in, and an integer n representing the number of nodes in the binary tree. The function returns a pointer to the root of the binary tree constructed from these traversals.

& The function first checks if either integer preEnd is less than integer preStart or integer inEnd is less than integer inStart. If either of these conditions is true, the function returns NULL since there are no more nodes left to construct.

& Next, the function creates a new node root with data equal to element preStart of array pre. It then initializes an integer inRoot to 0 and enters a for loop that iterates from 0 to n-1. Inside this loop, it checks if element i of array in is equal to element preStart of array pre. If it is, it sets integer inRoot to integer i, sets element i of array in to -1, and breaks out of the for loop.

& After the for loop, the function initializes an integer numsLeft to the difference between integers inRoot and inStart. It then sets the left pointer of node root to the result of a recursive call to itself with updated arguments, and sets the right pointer of node root to the result of another recursive call to itself with updated arguments. It then returns pointer root.

~ The key idea behind this function is that it uses a recursive approach to construct a binary tree from its preorder and inorder traversals. In each call to the function, it creates a new node with data equal to the first element in the current subarray of array pre. This element represents the root of the current subtree. It then finds the index of this element in array in, which represents the inorder traversal of this subtree. All elements to the left of this index in array “in” represent the left subtree, while all elements to the right represent the right subtree. The function then makes two recursive calls to itself with updated arguments to construct these subtrees.

* The time complexity of this function is O(n^2) where n is the number of nodes in the binary tree. This is because in each call to the function, it needs to search for an element in array “in”, which takes O(n) time. Since there are n calls to the function (one for each node), the total time complexity is O(n^2). The space complexity is O(n) since it uses a recursive call stack that can grow up to n levels deep.

The “buildTree” function takes in three arguments: two arrays of integers “in” and “pre” representing the inorder and preorder traversals of a binary tree, and an integer “n” representing the number of nodes in the binary tree. The function returns a pointer to the root of the binary tree constructed from these traversals.

& The function first calls the “helper” function with arguments “pre”, 0, “n-1”, “in”, 0, “n-1”, and “n” to construct the binary tree. It then returns this result.

* The time complexity of this function is O(n^2) since it calls the “helper” function, which has time complexity O(n^2). The space complexity is also O(n) since it uses a recursive call stack that can grow up to n levels deep.

% If there are no duplicates use hashmap to store inorder traversal to get inRoot in O(1) time this will reduce T.C to O(N)
     */

public:
    Node *helper(int pre[], int preStart, int preEnd, int in[], int inStart, int inEnd, int n)
    {
        if (preEnd < preStart || inEnd < inStart)
        {
            return NULL;
        }
        Node *root = new Node(pre[preStart]);
        int inRoot = 0;
        for (int i = 0; i < n; i++)
        {
            if (in[i] == pre[preStart])
            {
                inRoot = i;
                in[i] = -1;
                break;
            }
        }
        int numsLeft = inRoot - inStart;
        root->left = helper(pre, preStart + 1, preStart + numsLeft, in, inStart, inRoot - 1, n);
        root->right = helper(pre, preStart + numsLeft + 1, preEnd, in, inRoot + 1, inEnd, n);
        return root;
    }
    Node *buildTree(int in[], int pre[], int n)
    {
        // Code here

        Node *root = helper(pre, 0, n - 1, in, 0, n - 1, n);
        return root;
    }
};
//^ 26 Construct Binary tree from inorder and postorder traversal
class BuildTree_2
{
private:
public:
    TreeNode *helper(vector<int> &postorder, vector<int> &inorder, unordered_map<int, int> &mp, int postStart, int postEnd, int inStart, int inEnd)
    {

        if (postStart > postEnd || inStart > inEnd)
        {
            return nullptr;
        }
        TreeNode *root = new TreeNode(postorder[postEnd]);
        int inRoot = mp[root->val];
        int numsLeft = inRoot - inStart;

        root->left = helper(postorder, inorder, mp, postStart, postStart + numsLeft - 1, inStart, inStart + numsLeft - 1);
        root->right = helper(postorder, inorder, mp, postStart + numsLeft, postEnd - 1, inStart + numsLeft + 1, inEnd);
        return root;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        unordered_map<int, int> mp;
        for (int i = 0; i < inorder.size(); i++)
        {
            mp[inorder[i]] = i;
        }
        return helper(postorder, inorder, mp, 0, postorder.size() - 1, 0, inorder.size() - 1);
    }
};

//^ Morris traversals [inorder,postorder,preorder];

class MorrisTraversals
{
private:
public:
    vector<int> morrisInorder(TreeNode *root)
    {
        vector<int> inorder;
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
                if (prev->right == curr)
                {
                    prev->right = nullptr;
                    inorder.emplace_back(curr->val);
                    curr = curr->right;
                }
            }
        }
        return inorder;
    }

    vector<int> morrisPreorder(TreeNode *root)
    {
        vector<int> preorder;
        TreeNode *curr = root;
        while (curr)
        {
            if (!curr->left)
            {
                preorder.emplace_back(curr->val);
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
                    preorder.emplace_back(curr);
                    curr = curr->left;
                }
                else
                {
                    prev->right = nullptr;
                    curr = curr->right;
                }
            }
        }
        return preorder;
    }

    vector<int> morrisPostorder(TreeNode* root){
        
    }
};
int main()
{
    return 0;
}