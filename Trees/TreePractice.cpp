#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
};

//^  check if two trees are equal or not
bool isIdentical(Node *r1, Node *r2)
{
    if (r1 == NULL && r2 == NULL)
        return true;
    if (r1 == NULL || r2 == NULL)
        return false;
    if (r1->data != r2->data)
        return false;
    return isIdentical(r1->left, r2->left) && isIdentical(r1->right, r2->right);
}

//^ spiral traversal using deque
vector<int> findSpiral(Node *root)
{

    vector<int> res;
    int level = 0;
    deque<Node *> q;
    q.push_back(root);

    if (root == NULL)
    {
        return res;
    }

    while (q.empty() == false)
    {
        int size = q.size();

        if (level % 2 == 0)
        {

            for (int i = 0; i < size; i++)
            {
                Node *curr = q.back();
                q.pop_back();

                if (curr->right != NULL)
                    q.push_front(curr->right);
                if (curr->left != NULL)
                    q.push_front(curr->left);

                res.push_back(curr->data);
            }
        }
        else
        {

            for (int i = 0; i < size; i++)
            {
                Node *curr = q.front();
                q.pop_front();

                if (curr->left != NULL)
                    q.push_back(curr->left);
                if (curr->right != NULL)
                    q.push_back(curr->right);

                res.push_back(curr->data);
            }
        }

        level++;
    }
    return res;
}

//^ right-view of a binary tree
vector<int> rightView(Node *root)
{
    vector<int> ans;
    if (root != NULL)
    {
        queue<Node *> q;
        q.emplace(root);
        while (!q.empty())
        {
            int count = q.size();
            for (int i = 0; i < count; i++)
            {
                Node *curr = q.front();
                q.pop();
                if (i == 0)
                    ans.push_back(curr->data);
                if (curr->right != NULL)
                    q.emplace(curr->right);
                if (curr->left != NULL)
                    q.emplace(curr->left);
            }
        }
        return ans;
    }
    return ans;
}

//^ vertical width of a tree
unordered_set<int> st;
void inorder(Node *root, int hd)
{
    if (root != NULL)
    {
        inorder(root->left, hd - 1);
        st.insert(hd);
        inorder(root->right, hd + 1);
    }
}
int verticalWidth(Node *root)
{
    st.clear();
    inorder(root, 0);
    return st.size();
}

//^ Function to convert a binary tree into its mirror tree.
void mirror(Node *node)
{
    // code here
    if (node == NULL)
        return;
    mirror(node->left);
    mirror(node->right);
    swap(node->left, node->right);
}




//^Node from leaf at K distance
/* bool check(Node *root,int k){
   if(root==NULL) return false;
   if(root->right==NULL && root->left==NULL){
       if(k==0) return true;
       else return false;
   }
   
   bool left = check(root->left,k-1);
   bool right = check(root->right,k-1);
   
   return left||right;
}

 

void inorder(Node *root,int k,unordered_set<Node*> &s){
   if(root==NULL) return;
   inorder(root->left,k,s);
   if(check(root,k)){
       s.insert(root);
   }
   inorder(root->right,k,s);
}

int printKDistantfromLeaf(Node* root, int k)
{
unordered_set<Node*> s;
inorder(root,k,s);
return s.size();
} */

//*efficient solution:


void kDistantFromLeafUtil(Node* node,int &counter,bool visited[],int pathLen,int k)
{
	//base case
	if (node==NULL) return;

	visited[pathLen] = false;
	pathLen++;

	//if it's a leaf node, we increment the count but only if the 
	//same ancestor at distance k is not already counted.
	if (node->left == NULL && node->right == NULL &&
		pathLen-k-1 >= 0 && visited[pathLen-k-1] == false)
	{
		counter++;
		//setting the ancestor as visited so that we won't count it again.
		visited[pathLen-k-1] = true;
		return;
	}

	//if the current node is not a leaf node then we call the function 
	//recursively for left and right subtrees.
	kDistantFromLeafUtil(node->left, counter, visited, pathLen, k);
	kDistantFromLeafUtil(node->right, counter, visited, pathLen, k);
	
}

//Function to return count of nodes at a given distance from leaf nodes.
int printKDistantfromLeaf(Node* node, int k)
{
	int counter = 0;
	bool visited[100000] = {false};
	kDistantFromLeafUtil(node, counter, visited, 0, k);
	
	//returning the count.
	return counter;
}


//^ binary tree to circular doubly linked list
//?method-1 : convert binary tree to doubly linked list then, convert doubly linked list to circular doubly linked list.
//?method-2 : 
Node *concatenate(Node *leftList, Node *rightList)
    {    
        //if either of the lists is empty, we return the other list. 
        if (leftList == NULL)
            return rightList;
        if (rightList == NULL)
            return leftList;
            
        //storing the last node of left list. 
        Node *leftLast = leftList->left;
        //storing the last node of right list. 
        Node *rightLast = rightList->left;
        
        
        //connecting the last node of Left list with the first 
        //node of the right list.
        leftLast->right = rightList;
        rightList->left = leftLast;
        
        //left of first node points to the last node in the list.
        leftList->left = rightLast;
        
        //right of last node refers to the first node of the list.
        rightLast->right = leftList;
        return leftList;
    }
    
    //Function to convert binary tree into circular doubly linked list.
    Node *bTreeToCList(Node *root)
    {
        if (root == NULL)
            return NULL;
        
        //calling the function for left and right subtrees recursively.    
        Node *left = bTreeToCList(root->left);
        Node *right = bTreeToCList(root->right);
        
        
        //making a circular linked list of single node. To do so, we make the  
        //right and left pointers of this node point to itself.
        root->left = root->right = root;
        
        
        //firstly, concatenating the left list with the list with 
        //single node i.e. current node. 
        //then concatenating the returned list with the right list. 
        return concatenate(concatenate(left, root), right);
    }
int main(int argc, char const *argv[])
{
    Node *root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->right = new Node(60);
    // cout<<printKDistantfromLeaf(root,2);
    // cout << verticalWidth(root);
    return 0;
}
