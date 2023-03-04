#include <bits/stdc++.h>

using namespace std;

/*
todo                                                    General Binary tree

    &  Root: The root of a tree is the first node of the tree. In the above image, the root node is the node 30.
    &  Edge: An edge is a link connecting any two nodes in the tree. For example, in the above image there is an edge between node 11 and 6.
    &  Siblings: The children nodes of same parent are called siblings. That is, the nodes with same parent are called siblings. In the above tree, nodes 5, 11, and 63 are siblings.
    &  Leaf Node: A node is said to be the leaf node if it has no children. In the above tree, node 15 is one of the leaf nodes.
    &  Height of a Tree: Height of a tree is defined as the total number of levels in the tree or the length of the path from the root node to the node present at the last level. The above tree is of height 2.

~   A Tree is said to be a Binary Tree if all of its nodes have atmost 2 children. That is, all of its node can have either no child, 1 child, or 2 child nodes.

  ?  Properties of a Binary Tree:

&    The maximum number of nodes at level 'l' of a binary tree is (2l - 1). Level of root is 1. This can be proved by induction. For root, l = 1, number of nodes = 21-1 = 1 Assume that the maximum number of nodes on level l is 2l-1. Since in Binary tree every node has at most 2 children, next level would have twice nodes, i.e. 2 * 2l-1.
&    Maximum number of nodes in a binary tree of height 'h' is (2h – 1). Here height of a tree is the maximum number of nodes on the root to leaf path. The height of a tree with a single node is considered as 1. This result can be derived from point 2 above. A tree has maximum nodes if all levels have maximum nodes. So maximum number of nodes in a binary tree of height h is 1 + 2 + 4 + .. + 2h-1.
&    This is a simple geometric series with h terms and sum of this series is 2h – 1. In some books, the height of the root is considered as 0. In that convention, the above formula becomes 2h+1 – 1.
&    In a Binary Tree with N nodes, the minimum possible height or the minimum number of levels is Log2(N+1). This can be directly derived from point 2 above. If we consider the convention where the height of a leaf node is considered 0, then above formula for minimum possible height becomes Log2(N+1) – 1.
&    A Binary Tree with L leaves has at least (Log2L + 1) levels. A Binary tree has maximum number of leaves (and minimum number of levels) when all levels are fully filled. Let all leaves be at level l, then below is true for number of leaves L.
&    In a Binary tree in which every node has 0 or 2 children, the number of leaf nodes is always one more than the nodes with two children.

?   Types of Binary Trees: Based on the structure and number of parents and children nodes, a Binary Tree is classified into the following common types:


~    Full Binary Tree: A Binary Tree is full if every node has either 0 or 2 children. The following are examples of a full binary tree. We can also say that a full binary tree is a binary tree in which all nodes except leave nodes have two children.
~    In a Full Binary, the number of leaf nodes is number of internal nodes plus 1.

~    Complete Binary Tree: A Binary Tree is a complete Binary Tree if all levels are completely filled except possibly the last level and the last level has all keys as left as possible Following are the examples of Complete Binary Trees:

~    Perfect Binary Tree: A Binary tree is a Perfect Binary Tree when all internal nodes have two children and all the leave nodes are at the same level. Following are the examples of Perfect Binary Trees:
~   A Perfect Binary Tree of height h (where height is the number of nodes on the path from the root to leaf) has 2h – 1 node.

?               Applications of binary trees
~       Store hierarchical data, like folder structure, organization structure, XML/HTML data.
~       Binary Search Tree is a tree that allows fast search, insert, delete on a sorted data. It also allows finding closest item
~       Heap is a tree data structure which is implemented using arrays and used to implement priority queues.
~       B-Tree and B+ Tree : They are used to implement indexing in databases.
~       Syntax Tree:  Scanning, parsing , generation of code and evaluation of arithmetic expressions in Compiler design.
~       K-D Tree: A space partitioning tree used to organize points in K dimensional space.
~       Trie : Used to implement dictionaries with prefix lookup.
~       Suffix Tree : For quick pattern searching in a fixed text.
~       Spanning Trees and shortest path trees are used in routers and bridges respectively in computer networks
~       As a workflow for compositing digital images for visual effects.
~       Decision trees.
~       Organization chart of a large organization.
 */

//^ General Binary Tree
struct Node
{
    int key;
    Node *leftChild;
    Node *rightChild;
    Node(int x)
    {
        key = x;
        leftChild = rightChild = NULL;
    }
};

//^ Inorder Traversal left->root->right
void inorderTraversal(Node *root)
{
    // todo RECURSIVE

    if (root != NULL)
    {
        inorderTraversal(root->leftChild);
        cout << root->key << " ";
        inorderTraversal(root->rightChild);
    }

    //~ Iterative O(N) time and O(H) space
    // if(root==NULL)return;
    // stack<Node*> stk;
    // Node* curr = root;
    // while (curr!=NULL || !stk.empty())
    // {
    //     while (curr!=NULL)
    //     {
    //         stk.push(curr);
    //         curr=curr->leftChild;
    //     }
    //     curr=stk.top();
    //     stk.pop();
    //     cout<<curr->key<<" ";
    //     curr=curr->rightChild;

    // }
}

//^ Preorder traversal root->left->right
void preorderTraversal(Node *root)
{
    // todo Recursive
    //  if (root != NULL)
    //  {
    //      cout << root->key << " ";
    //      preorderTraversal(root->leftChild);
    //      preorderTraversal(root->rightChild);
    //  }

    //~iterative O(N) time and space
    // if(root==NULL)return;
    // stack<Node*> stk;
    // stk.push(root);
    // while (stk.empty()==false)
    // {
    //     Node* curr = stk.top();
    //     cout<<curr->key<<" ";
    //     stk.pop();
    //     if(curr->rightChild!=NULL) stk.push(curr->rightChild);
    //     if(curr->leftChild!=NULL) stk.push(curr->leftChild);
    // }

    //~iterative O(N) time and O(H) space
    if (root == NULL)
        return;
    stack<Node *> s;
    s.push(root);
    Node *curr = root;
    while (!s.empty() || curr != NULL)
    {
        while (curr != NULL)
        {
            cout << curr->key << " ";
            if (curr->rightChild != NULL)
                s.push(curr->rightChild);
            curr = curr->leftChild;
        }
        if (!s.empty())
        {
            curr = s.top();
            s.pop();
        }
    }
}
//^ Postorder traversal left->right->root
/* void postorderTraversal(Node *root)
{
    if (root != NULL)
    {
        postorderTraversal(root->leftChild);
        postorderTraversal(root->rightChild);
        cout << root->key << " ";
    }
} */

//^  height of binary tree | O(Nodes) time and O(H+1) space
int height(Node *root)
{
    if (root == NULL)
        return 0;
    return max(height(root->leftChild), height(root->rightChild)) + 1;
}

//^ print nodes at kth distance | O(N) time O(H) space
void KthNode(Node *root,int k){
    if(root==NULL)return;
    if(k==0){
        cout<<root->key<<" ";
        return;
    }
    else
    {
        KthNode(root->leftChild,k-1);
        KthNode(root->rightChild,k-1);
    }
}

//^ BFS(Level order Traversal)
void levelOrder(Node *root)
{

    //! O((N+H)*H) time;
    // int maxHeight=height(root);
    // for (int i = 0; i < maxHeight; i++)
    // {
    //     KthNode(root,i);
    // }

    //*Efficient approach |  O(N) time O(width) space
    if (root == NULL)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *curr = q.front();
        q.pop();
        cout << curr->key << " ";
        if (curr->leftChild != NULL)
            q.push(curr->leftChild);
        if (curr->rightChild)
            q.push(curr->rightChild);
    }
}

//^Size of a binary tree
/* int getSize(Node* root){
    if(root==NULL)return 0;
    else
    {
        return 1+getSize(root->leftChild)+getSize(root->rightChild);
    }
} */

//^Maximum in a binary tree
int getMax(Node *root)
{
    if (root == NULL)
        return INT_MIN;
    else
    {
        return max(root->key, max(getMax(root->leftChild), getMax(root->rightChild)));
    }
}

//^ level order traversal line by line

void printLevelOrderLine(Node *root)
{

    //~ 1st method
    // if (root == NULL)
    //     return;
    // queue<Node *> q;
    // q.push(root);
    // q.push(NULL); //? adding null to specify the end of a level
    // while (q.size() > 1)
    // {
    //     Node *curr = q.front();
    //     q.pop();
    //     if (curr == NULL)
    //     {
    //         cout << "\n";
    //         q.push(NULL); //?adding null again in the queue to specify the end of the next level
    //         continue;
    //     }
    //     cout << curr->key << " ";
    //     if (curr->leftChild != NULL)
    //     {
    //         curr = curr->leftChild;
    //     }
    //     if (curr->rightChild != NULL)
    //     {
    //         curr = curr->rightChild;
    //     }
    // }

    //~ 2nd method
    if (root == NULL)
        return;
    queue<Node *> q;
    q.push(root);
    while (q.empty() == false)
    {
        /* code */
        int count = q.size();
        for (int i = 0; i < count; i++)
        {
            Node *curr = q.front();
            q.pop();
            cout << curr->key << " ";
            if (curr->leftChild != NULL)
            {
                q.emplace(curr->leftChild);
            }
            if (curr->rightChild != NULL)
            {
                q.emplace(curr->rightChild);
            }
        }
        cout << "\n";
    }
}

//^ print left-view of a binary tree
void printLeft(Node *root, int level = 1)
{

    // todo Recursive method O(N) time and O(H) space
    //  static int maxLevel=0;
    //  if(root==NULL)return ; //? preorder traversal approach
    //  if (maxLevel<level)
    //  {
    //      cout<<root->key<<" ";
    //      maxLevel=level;
    //  }
    //  printLeft(root->leftChild,level+1);
    //  printLeft(root->rightChild,level+1);

    //~ iterative method  O(N) time and O(width) space;
    if (root == NULL)
        return;
    queue<Node *> q;
    q.push(root);
    //?using level order line by line traversal but for leftChilds(i==0) only..
    while (!q.empty())
    {
        int count = q.size();
        for (int i = 0; i < count; i++)
        {
            Node *curr = root;
            q.pop();
            if (i == 0)
                cout << curr->key << " ";
            if (curr->leftChild != NULL)
            {
                q.emplace(curr->leftChild);
                // curr=curr->leftChild;
            }
            if (curr->rightChild)
            {
                q.emplace(curr->rightChild);
                // curr=curr->rightChild;
            }
        }
    }
}

//^Children sum property of a binary tree | O(N) time O(H) space
/* bool childrenSum(Node *root)
{
    if (root == NULL)
        return true;
    if (root->leftChild == NULL && root->rightChild == NULL)
        return true;
    int sum = 0;
    if (root->leftChild != NULL)
    {
        sum += root->leftChild->key;
    }
    if (root->rightChild)
    {
        sum += root->rightChild->key;
    }
    return (root->key == sum && childrenSum(root->leftChild) && childrenSum(root->rightChild));
}
 */
/*
^height balanced tree 
^In a Balanced Binary Tree for every node, the difference between heights of left subtree and right subtree should not be more than one.
 */

// ! O(N^2) time
/* bool isHeightBalanced(Node *root)
{
    if (root == NULL)
    {
        return true;
    }
    int leftHeight = height(root->leftChild);
    int rightHeight = height(root->rightChild);
    return (abs(leftHeight - rightHeight) <= 1 && isHeightBalanced(root->leftChild) && isHeightBalanced(root->rightChild));
} */

//* Efficient solution: O(N)
/* int isBalanced(Node* root){
    if(root==NULL)return 0;
    int leftHeight=isBalanced(root->leftChild); //?check for left subtree also get the left height
    if(leftHeight==-1)return -1;
    int rightHeight=isBalanced(root->rightChild);//?check for right subtree also get the right height
    if(rightHeight==-1)return -1;
    if (abs(leftHeight-rightHeight)>1)return -1;
    else return max(leftHeight,rightHeight)+1;
    
} */


//^ Maximum width of a binary tree | O(N) time O(width) space
/* int maxWidth(Node* root){
    if(root==NULL)return 0;
    queue<Node*> q;
    q.push(root); //? using BFS to find the size of queue(current level) and return the max size
    int res=0;
    while (q.empty()==false)
    {
        int count=q.size();
        res=max(res,count);
        for (int i = 0; i < count; i++)
        {
            Node* curr = q.front();
            q.pop();
            if (curr->leftChild!=NULL)
            {
                q.emplace(curr->leftChild);
            }
            if (curr->rightChild!=NULL)
            {
                q.emplace(curr->rightChild);
            }
            
        }
        
    }
    return res;
    
}
 */
/* 
^Inorder conversion of Binary Tree to Doubly Linked List. | O(N time O(H) space
^ we need to do the inorder traversal of the Tree and while doing inorder traversal we can simply maintain a previous pointer or reference of the previously traversed node.
^ And change right child of the previous node to current node and left child of current node as previous.*/

Node* BTtoDLL(Node* root){
    if(root==NULL)return root;
    static Node* prev=NULL;
    Node* head=BTtoDLL(root->leftChild);
    if(prev==NULL)head=root;
    else
    {
        root->leftChild=prev;
        prev->rightChild=root;
    }
    prev=root;
    BTtoDLL(root->rightChild);
    return head;
    
}


//^ Construction of a binary tree from inorder and preorder traversal | O(N^2) time
Node* constructTree(vector<int> &inorder,vector<int> &preorder, int is, int ie){
    static int preIndex=0; 
    if(is>ie)return NULL;
    Node* root = new Node (preorder[preIndex++]);
    int inIndex;
    for (int i = is; i <= ie; i++)
    {
        if(inorder[i]==root->key){
            inIndex=i;
            break;
        }
    }
    root->leftChild=constructTree(inorder,preorder,is,inIndex-1);
    root->rightChild=constructTree(inorder,preorder,inIndex+1,ie);
    return root;   
}

//^spiral traversal of a BT
/* void spiralTraversal(Node* root){
    if(root==NULL)return;
    queue<Node*> q;
    stack<Node*> s;
    bool reverse=false;
    q.emplace(root);
    while (!q.empty())
    {
        int count=q.size();
        for (int i = 0; i < count; i++)
        {
            Node* curr = q.top();
            q.pop();
            if(reverse)
                s.emplace(curr->key);
            else
                cout<<curr->key<<" ";
                if(curr->leftChild!=NULL)q.emplace(curr->leftChild);
                if(curr->rightChild!=NULL)q.emplace(curr->rightChild);
        }
        if(reverse){
            while (s.empty()==false)
            {
                cout<<s.top()<<" ";
                s.pop();
            }
            
        }
        reverse=!reverse;
        cout<<"\n";
    }   
} */

//*optimized solution
void printSpiral(Node *root){
    if (root == NULL) 
        return;  

    stack<Node*> s1;  
    stack<Node*> s2;  
  
    s1.emplace(root); 
  
    while (!s1.empty() || !s2.empty()) { 
        while (!s1.empty()) { 
            Node* temp = s1.top(); 
            s1.pop(); 
            cout << temp->key << " "; 
  
            if (temp->rightChild) 
                s2.emplace(temp->rightChild); 
            if (temp->leftChild) 
                s2.emplace(temp->leftChild); 
        } 
        
        while (!s2.empty()) { 
            Node* temp = s2.top(); 
            s2.pop(); 
            cout << temp->key << " "; 
  
            if (temp->leftChild) 
                s1.emplace(temp->leftChild); 
            if (temp->rightChild) 
                s1.emplace(temp->rightChild); 
        } 
    } 
}  

//^ diameter of a binary tree
int diameter(Node* root){

    //! O(N^2) time and O(H) space ...
    // if(root!=NULL){
    //     int d1 = 1+height(root->leftChild)+height(root->rightChild);
    //     int d2=diameter(root->leftChild);
    //     int d3=diameter(root->rightChild);

    //     return max(d1,max(d2,d3));
    // }
    // return 0;

    //*efficient approach (modify height function "diameter->height") | O(N) time and O(H) space
    static int res=0;
    if(root==NULL)return 0;
    int lh=diameter(root->leftChild);
    int rh=diameter(root->rightChild);
    res = max(res,1+lh+rh); //? stores diameter whenever the height(diameter) func is called.
    return 1+max(lh,rh);
}

//^ Lowest common ancestor LCA
//~ constructing two path arrays and finding the lowest(last common in array) ancestor in the tree
//! O(N) time and 3 traversals + O(N) space (worst case: skewed tree)
// bool findPath(Node* root,vector<Node*> &p,int n){
//     if(root==NULL)return false;
//     p.emplace_back(root);
//     if(root->key==n)return true;
//     if (findPath(root->leftChild,p,n) || findPath(root->rightChild,p,n))
//     {
//         return true;
//     }
//     p.pop_back();
//     return false;
    
// }

// Node* LCA(Node* root,int n1,int n2){
//     vector<Node*> path1,path2;
//     if(findPath(root,path1,n1)==false||findPath(root,path2,n2)==false)
//         return NULL;
//     for (int i = 0; i < path1.size()-1 && i< path2.size()-1; i++)
//     {
//         if(path1[i+1]!=path2[i+1]){
//             return path1[i];
//         }
//     }
//     return NULL;
    
// }

//* efficient solution
Node *lca(Node *root, int n1, int n2){
    if(root==NULL)return NULL;
    if(root->key==n1||root->key==n2)
        return root;
    
    Node *lca1=lca(root->leftChild,n1,n2);
    Node *lca2=lca(root->rightChild,n1,n2);
    
    if(lca1!=NULL && lca2!=NULL)
        return root;
    if(lca1!=NULL)
        return lca1;
    else
        return lca2;
}

//^ We are given a binary tree and a leaf node, we need to find time to burn the Binary Tree if we burn the given leaf at 0-th second | O(N) time.

int burnTree(Node* root,int leaf,int &dist){
    //? find farthest distance from the leaf node this distance
    //? is equal to the time required to burn the tree
    static int res=0;
    if(root==NULL)return 0;
    if(root->key==leaf && root->leftChild==NULL && root->rightChild==NULL){dist=0; return 1;}
    else{return -1;}
    int ldist=-1,rdist=-1; //? check if this node is an ancestor
    int lh = burnTree(root->leftChild,leaf,dist);
    int rh = burnTree(root->rightChild,leaf,dist);
    if(ldist!=-1){
        dist = ldist+1;
        res=max(res,dist+rh);
    }
    else if (rdist!=-1)
    {
        dist = rdist+1;
        res = max(res,dist+lh);
    }
    return max(lh,rh)+1;
    

}

// ^ Count Nodes in a given complete binary tree. | O(N) time (for any binary-tree)
int countNode(Node* root){
    // if(root!=NULL){
    //     return 1+countNode(root->leftChild)+countNode(root->rightChild);
    // }
    // return 0;

    //* efficient sol | O(logn x logn) time
    int lh=0,rh=0;
    Node* curr = root;
    //? check if a subtree is a perfect binary tree
    //? no of nodes = 2^Height - 1;
    while (curr!=NULL)
    {
        lh++;
        curr=curr->leftChild;
    }
    curr=root;
    while (curr!=NULL)
    {
        rh++;
        curr=curr->rightChild;
    }
    if(lh==rh){
        return pow(2,lh)-1;
    }
    return 1+countNode(root->leftChild)+countNode(root->rightChild);
    
}

void serialize(Node* root,vector<int> &v){
    if(root==NULL){v.push_back(INT_MIN); return;}
    v.push_back(root->key);
    serialize(root->leftChild,v);
    serialize(root->rightChild,v);
}

Node* deSerialize(vector<int> &arr){
    static int index = 0;
    if(index==arr.size())return NULL;

    int val = arr[index++];
    if(val==INT_MIN)return NULL;
    Node* root = new Node(val);
    root->leftChild=deSerialize(arr);
    root->rightChild=deSerialize(arr);
    return root;
}
int main(int argc, char const *argv[])
{
    // Node *root = new Node(10);
    // root->leftChild = new Node(20);
    // root->rightChild = new Node(30);
    // root->rightChild->leftChild = new Node(40);
    // root->rightChild->rightChild = new Node(50);
    // vector<int> in{40,10,20,40,50,60};
    // vector<int> pre{20,10,40,40,50,60};
    // Node* root=constructTree(in,pre,0,5);
    // KthNode(root,2);
    // levelOrder(root);
    // printLeft(root);
    // childrenSum(root);
    // inorderTraversal(root);
    //     cout << "\n";
    // preorderTraversal(root);
    //     cout << "\n";
    // postorderTraversal(root);
    //     cout << "\n";
    return 0;
}
