#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *left, *right;
    Node(int x)
    {
        this->data = x;
        left = right = NULL;
    }
};

//^ searching O(H) time
bool searchBst(Node *root, int x)
{

    //~ Recursive approach
    /*  if (root!=NULL)
     {
         if (root->data == x)
         {
             return true;
         }
         else if (root->data > x)
         {
             return searchBst(root->left , x);

         }
         else
         {
             return searchBst(root->right,x);
         }
     }
     return false; */

    //* Iterative approach

    while (root != NULL)
    {
        if (root->data == x)
        {
            return true;
        }
        else if (root->data < x)
        {
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
}


//^insert in a BST O(H)
Node* insert(Node* root,int x){
    //~ recursive solution
 /*    if(root==NULL)return new Node(x);
    else if (root->data<x)
    {
        root->right=insert(root->right,x);
    }

    else if (root->data>x)
    {
        root->left = insert(root->left,x);
    }
    return root; */

    //*iterative sol
    Node* temp = new Node(x);
    Node* parent = NULL,* curr = root;
    while (curr!=NULL)
    {
        parent=curr;
        if (curr->data>x)
        {
            curr=curr->left;
        }
        else if (curr->data<x)
        {
            curr=curr->right;
        }
        else
        {
            return root;
        }
        
    }
    if (parent==NULL)
    {
        return temp;
    }
    if (parent->data>x)
    {
        parent->left = temp;
    }
    
    else
    {
        parent->right = temp;
    }
    return root;
}

//^ Deletion in BST O(H) time and space

Node* getSuccessor(Node* curr){
    curr = curr->right;
    while (curr!=NULL && curr->left!=NULL)
    {
        curr=curr->left;
    }
    return curr;
    
}

Node* deleteNode(Node* root,int x){
    if (root==NULL)
    {
        return root;
    }
    
    if (root->data>x)
    {
        root->left = deleteNode(root,x);
    }
    else if (root->data<x)
    {
        root->right=deleteNode(root,x);
    }
    else
    {
        if (root->left==NULL)
        {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else
        {
            Node* successor = getSuccessor(root);
            root->data = successor->data;
            root->right = deleteNode(root->right,successor->data);
        }
        return root;
    }
    
}


//^ Floor in a BST
int floor(Node* root, int x) {
    // Your code goes here
    int floorVal=(root->data>x)?-1:root->data;
    int diff=INT16_MAX;
        while (root != NULL)
        {
        if (root->data == x)
        {
            // return true;
            return root->data;
        }
        else if (root->data < x)
        {
            if (diff > (root->data-x))
            {
                floorVal = max(floorVal,root->data);
                diff = min(diff,x-root->data);
            }
            
            root = root->right;
        }
        else
        {
            root = root->left;
        }
    }
    return floorVal;
}

//^ Ceil in a BST
Node *ceil(Node *root, int x){
    Node *res=NULL;
    while(root!=NULL){
        if(root->data==x)
            return root;
        else if(root->data<x)
            root=root->right;
        else{
            res=root;
            root=root->left;
        }
    }
    return res;
} 


//^ceiling on left side
void printCeiling(vector<int> &arr){
    cout << -1 << " ";
    set<int> s;
    s.emplace(arr[0]);
    for (auto &c : arr)
    {
        if(c==arr[0])continue;
        if (s.lower_bound(c)!=s.end())
        {
            cout << *s.lower_bound(c)<<" ";
        }
        else    cout<<-1<<" ";
        s.emplace(c);
        
    }
    
}

//^ check for BST
// bool isBST(Node* root,int min=INT_MIN, int max=INT_MAX)  
// {  
//   if (root == NULL)  
//     return true;  
//       
//       ? for left subtrees we are limiting our upper limit of range to root's data(less than).
//       ? for right subtree we are limiting our lower limit of range to root's data(more than).
      
//        
//   return ( root->data>min && root->data<max && 
//             isBST(root->left,min,root->data) && isBST(root->right,root->data,max));  
// }

bool isBST(Node* root,int &prev)  //?prev=INT_MIN
{  
    //?simple inorder traversal and checking if the inorder is sorted or not..
    if (root == NULL)  
        return true;  
    
    if(isBST(root->left,prev)==false)return false;
    
    if(root->data<=prev)return false;
    prev=root->data;
    
    return isBST(root->right,prev);
}


//^ fix bst with two nodes swapped
/* 
? find inorder traversal and check the violation(find two nodes which need to be swapped)
? swap the two node's data
 */

    Node* first = NULL;
    Node* second = NULL;
  void fixBst(Node* root,Node* prev=NULL){
    // static Node* prev =NULL;
    if(root!=NULL){
        fixBst(root->left,prev);
        if (prev!=NULL && root->data<prev->data)
        {
            /* code */
            if (first==NULL)
            {
                first=prev;
            }
            second=root;
        }
        prev = root;
        fixBst(root->right,prev);
        // swap(first->data,second->data);
    }
}

void correctBST( struct Node* root )
    {
        // add code here.
        if(root==NULL)return;
        fixBst(root);
        swap(first->data,second->data);
    }



//^ pair sum in a BST
/* 
!Method-1: perform inorder traversal and store it in an vector
!         use two-pointer approach to find if such sum is present or not
! time complexity: theta(N) space: theta(N)

*Method-2: using hash-tables to check while traversing at the same time
*           can be used for normal binary trees also as it doesn't use the fact that inorder of BST is sorted...
 */


bool isPairSum(Node* root,int sum,unordered_set<int> &s){
    if(root==NULL)return false;
    if (isPairSum(root->left,sum,s))return true;
    if(s.find(sum-root->data)!=s.end())return true;
    else
    {
        s.insert(root->data);
        return isPairSum(root->right,sum,s);
    }
}


//^vertical sum in a binary tree.
void verticalSumUtil(Node* root,int horizontalDistance,map<int,int> &mp){
    if (root==NULL)
    {
        return;
    }
    verticalSumUtil(root->left,horizontalDistance-1,mp);
    mp[horizontalDistance]+=root->data;
    verticalSumUtil(root->right,horizontalDistance+1,mp);
}

void verticalSum(Node* root){
    map<int,int> mp;
    verticalSumUtil(root,0,mp);
    for (auto &x : mp)
    {
        cout << x.second << " ";
    }
    
}


//^ vertical order traversal in a Binary tree.
 vector<int> verticalOrder(Node *root)
    {
        //Your code here
        queue<pair<Node*,int>> q;
        map<int,vector<int>> mp;
        vector<int> v;
        if(root){
            q.emplace(root,0);
            while(!q.empty()){
                auto it = q.front();
                q.pop();
                Node* curr = it.first;
                int horizontalDist = it.second;
                mp[horizontalDist].push_back(curr->data);
                if(curr->left!=NULL)q.emplace(curr->left,horizontalDist-1);
                if(curr->right!=NULL)q.emplace(curr->right,horizontalDist+1);
            }
            for(auto &x : mp){
                v.insert(v.end(),x.second.begin(),x.second.end());
            }
        }
        return v;
    }


//^ Top-view of binary tree.

void topView(Node* root){
    queue<pair<Node*,int>> q;
    map<int,int> mp;
    if(root){
        q.emplace(root,0);
        while (!q.empty()){
            auto it = q.front();
            Node* curr = it.first;
            int horizontalDist = it.second;
            q.pop();
            if (mp.find(horizontalDist)==mp.end())
            {
                mp[horizontalDist] = curr->data;
            }
            if (curr->left)
            {
                q.emplace(curr->left,horizontalDist-1);
            }
            if (curr->right)
            {
                q.emplace(curr->right,horizontalDist+1);
            }
            
        }

        for (auto &&i : mp)
        {
            cout << i.second << " ";
        }
        
        
    }
}

//^ bottom view of a binary tree
void bottomView(Node* root){
    if(!root)return;
    queue<pair<Node*,int>> q;
    q.emplace(root,0);
    map<int,int> mp;
    while (!q.empty())
    {
        auto it = q.front();
        q.pop();
        Node* curr = it.first;
        int horizontalDistance=it.second;
        mp[horizontalDistance] = curr->data;
        if(curr->left)q.emplace(curr->left,horizontalDistance-1);
        if(curr->left)q.emplace(curr->right,horizontalDistance+1);
    }

    for (auto &&i : mp)
    {
        cout << i.second <<" ";
    }
}


//^ merge two BSTs
/* 
?Method-1 : find inorder of both BSTs and construct a combined inorder traversal
?           for a new BST then construct the BST from the combined inorder traversal 
 !O(m+n) time and O(m+n) space
 */
/* 
void inorder(Node* root,vector<int> &res){
    if(!root)return;
    inorder(root->left,res);
    res.push_back(root->data);
    inorder(root->right,res);
}

vector<int> combinedInorder(vector<int> &bst1,vector<int> &bst2){
    vector<int> ans;
    int i=0,j=0;
    while (i<bst1.size() && j<bst2.size())
    {
        if(bst1[i]<bst2[j]){
            ans.push_back(bst1[i]);
            i++;
        }
        else if(bst1[i]>bst2[j]){
            ans.push_back(bst2[j]);
            j++;
        }
    }
    while (i<bst1.size())
    {
        ans.push_back(bst1[i]);
        i++;
    }
    while (j<bst2.size())
    {
        ans.push_back(bst2[j]);
        j++;
    }
    return ans;
}

Node* inorderToBST(int start , int end,vector<int> &v){
    if (start>end)
    {
        return NULL;
    }
    int mid=(start+end)/2;
    Node* root = new Node(v[mid]);
    root->left = inorderToBST(start,mid-1,v);
    root->right = inorderToBST(mid+1,end,v);
    return root;
}

Node* mergeBsts(Node* root1,Node* root2){
    vector<int> a,b;
    inorder(root1,a);
    inorder(root2,b);
    vector<int> combined = combinedInorder(a,b);
    return inorderToBST(0,combined.size()-1,combined);
}
 */
/* 
*Method-2: convert bsts into sorted DLLs respectively and merge both DLLs
*           convert DLL to balanced BST
 */

void BstToDLL(Node* root , Node* head){
    if( root == NULL)return;
    BstToDLL(root->right,head);
    root->right = head;
    if(head!=NULL)head->left = root;
    head=root;

    BstToDLL(root->left,head);

}

Node* mergeDLL(Node* head1,Node* head2){
    Node* head = NULL;
    Node* tail = NULL;
    while (head1!=NULL && head2!=NULL)
    {
        if(head1->data<head2->data){
            if(head==NULL){
                head=head1;
                tail=head1;
                head1=head1->right;
            }
            else
            {
                tail->right = head1;
                head->left = tail;
                tail=head1;
                head1=head1->right;
            }
            

        }
        else
        {
            if (head==NULL)
            {
                head = tail = head2;
                head2=head2->right;
            }
            else
            {
                tail->right = head2;
                head2->left = tail;
                tail = head2;
                head2=head2->right; 
            }
            
            
        }

        while (head1!=NULL)
        {
                tail->right = head1;
                head->left = tail;
                tail=head1;
                head1=head1->right;
            
        }
        while (head2=NULL)
        {
                tail->right = head2;
                head->left = tail;
                tail=head2;
                head2=head2->right;
            
        }
        return head;
    }
}

int countNodes(Node* head){
    int c=0;
    Node* curr = head;
    while (curr!=NULL)
    {
        c++; curr=curr->right;
    }
    return c;
}
Node* constructBSTfromDLL(Node* head,int n){
    if (n<=0 || head==NULL)
    {
        return NULL;
    }
    
    Node* left = constructBSTfromDLL(head,n/2);
    Node* root = head;
    root->left = left;
    head=head->right;
    root->right = constructBSTfromDLL(head,n-n/2-1);
    return root;

}

int main(int argc, char const *argv[])
{

    return 0;
}
