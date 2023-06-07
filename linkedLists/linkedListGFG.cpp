#include <bits/stdc++.h>
using namespace std;

/*struct implementation for singly linked list */
struct node
{
    int data;
    node *next;
    node(int x = 0)
    {
        data = x;
        next = NULL;
    }
};

// traversing a singly linked list in c++
void printLList(node *head)
{ // head is a copied ptr!!!!
    node *curr = curr;
    while (curr != NULL)
    {
        cout << curr->data << " ";
        curr = curr->next;
    }
    printf("\n");
}

// recursive traversal of singly linked list O(1)
//  void printLList(node *head){
//      if(head == NULL){return;}
//      cout<<head->data<<" ";
//      printLList(head->next);
//  }

// insertion at beginning of single linked list
node *insertAtBegin(node *head, int x)
{
    node *newHead = new node(x);
    newHead->next = head;
    return newHead;
}

// insertion at the end of the singly linked list
node *insertAtEnd(node *head, int x)
{
    node *temp = new node(0);
    temp->data = x;
    if (head == NULL)
    {
        return temp;
    }
    node *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    return head;
}

node *deleteAtBegin(node *head)
{
    if (head == NULL)
        return NULL;
    else
    {
        node *temp = head->next;
        delete head;
        return temp;
    }
}
/*deletion at the end Ø(N)*/
node *deleteAtEnd(node *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
    {
        delete head;
        return NULL;
    }
    node *curr = head;

    while (curr->next->next != NULL)
    {
        curr = curr->next;
    }
    delete (curr->next);
    curr->next = NULL;
    return head;
}

node *insertAt(node *head, int x, int pos)
{
    node *temp = new node(x);
    if (pos == 1)
    {
        temp->next = head;
        return temp;
    }
    node *curr = head;
    for (int i = 1; i <= pos - 2 && curr != NULL; i++)
    {
        curr = curr->next;
    }
    if (curr == NULL)
    {
        return head;
    }
    temp->next = curr->next;
    curr->next = temp;
    return head;
}

/*search in a linked list iterative version*/
int findIn(node *head, int x)
{
    int pos = 1;
    node *curr = head;
    while (curr != NULL)
    {
        if (curr->data == x)
        {
            return pos;
        }
        else
        {
            pos++;
            curr = curr->next;
        }
    }
    return -1;
}

/*recursive search in a singly linked list */
int rfindIn(node *head, int x)
{
    if (head == NULL)
        return -1;
    if (head->data == x)
    {
        return 1;
    }
    else
    {
        int res = rfindIn(head->next, x);
        if (res == -1)
        {
            return -1;
        }
        else
        {
            return res + 1;
        }
    }
}

/*Doubly linked list
  ✳ can be traversed in both directions
  ✳delete a node in O(1) time with given ptr to it
  ✳insert/delete before a given node
  ✳extra space for prev
  ✳code becomes more complex*/
struct DLnode
{
    int data;
    DLnode *prev;
    DLnode *next;
    DLnode(int data)
    {
        this->data = data;
        prev = NULL;
        next = NULL;
    }
};

/*insert at beginning of the doubly linked list*/
DLnode *insertAtBegin(DLnode *head, int x)
{
    DLnode *temp = new DLnode(x);
    temp->next = head;
    if (head != NULL)
    {
        head->prev = temp;
    }
    return temp;
}

/*Insert at end of the doubly linked list*/
DLnode *insertAtEnd(DLnode *head, int x)
{
    DLnode *temp = new DLnode(x);
    if (head == NULL)
        return temp;
    DLnode *curr = head;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = temp;
    temp->prev = curr;
    return head;
}

/* reverse a doubly linked list */
DLnode *reverseDlist(DLnode *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head; // single node
    }
    DLnode *prev = NULL;
    DLnode *curr = head;
    while (curr != NULL)
    {
        prev = curr->prev; // swapping pointers
        curr->prev = curr->next;
        curr->next = prev;
    }
    return prev->prev;
}

/* delete at beginning of the doubly linked list */
DLnode *deleteAtBegin(DLnode *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
    {
        delete head;
        return NULL;
    }
    else
    {
        DLnode *temp = head;
        head = head->next;
        head->prev = NULL;
        delete temp;
        return head;
    }
}

/* delete at the end of doubly linked list */
DLnode *deleteAtBegin(DLnode *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else if (head->next == NULL)
    {
        delete head;
        return NULL;
    }
    else
    {
        DLnode *curr = head;
        while (curr->next != NULL)
        {
            curr = curr->next;
        }
        curr->prev->next = NULL;
        delete curr;
        return head;
    }
}

/* Circular linked list (similar struct as singly linked list)
    ✳traverse the whole list from any node
    ✳implementation of algorithm like round robin
    ✳we can insert at the beginning and end by just maintaining one tail ptr/ref
    ✳implementation of operations are complex*/

struct cNode
{
    int data;
    cNode *next;
    cNode(int x)
    {
        data = x;
        next = NULL;
    }
};

/* traversing circular linked list O(nodes) */
void printCList(cNode *head)
{
    if (head == NULL)
        return;
    cout << head->data << " "; // can use do-while loop also
    for (cNode *p = head->next; p != head; p = p->next)
    {
        cout << p->data << " ";
    }
    printf("\n");
}

/* insert at the beginning of the circular linked list O(n)
    ✳ can be changed to O(1) by maintaining a tail pointer too.*/
// cNode* insertAtBegin(cNode* head,int x){
//     cNode* temp = new cNode(x);
//     if(head == NULL){ temp->next = temp;}
//     else{
//         cNode*curr = head;
//         while (curr->next!=head)
//         {
//             curr= curr->next;
//         }
//         curr->next = temp;
//         temp->next = head;
//     }
//     return temp;
// }

// swapping technique O(1)
cNode *insertAtBegin(cNode *head, int x)
{
    cNode *temp = new cNode(x);
    if (head == NULL)
    {
        temp->next = temp;
        return temp;
    }
    else
    {
        temp->next = head->next;
        head->next = temp;
        swap(head->data, temp->data);
        return head;
    }
}

/* insert at the end of the circular linked list O(n)
   ✳ insertAtBegin and insertATEnd are almost similar except different return value*/
// cNode *insertAtEnd(cNode *head, int x)
// {
//     cNode *temp = new cNode(x);
//     if (head == NULL)
//     {
//         temp->next = temp;
//         return temp;
//     }
//     else
//     {
//         cNode *curr = head;
//         while (curr->next != head)
//         {
//             curr = curr->next;
//         }
//         curr->next = temp;
//         temp->next = head;
//         return head;
//     }
// }

// swapping technique for insertion at end O(1)
cNode *insertAtBegin(cNode *head, int x)
{
    cNode *temp = new cNode(x);
    if (head == NULL)
    {
        temp->next = temp;
        return temp;
    }
    else
    {
        temp->next = head->next;
        head->next = temp;
        swap(head->data, temp->data);
        return temp;
    }
}

/* delete at beginning of the circular linked list */
// cNode* deleteAtBegin(cNode* head){
//     if(head == NULL)
//     return NULL;
//     if(head->next == head){delete head; return NULL;}
//     cNode* curr = head;
//     while (curr->next != head)
//     {
//         curr = curr->next;
//     }
//     curr->next = head->next;
//     delete head;
//     return curr->next;
// }

// O(1) deletion
cNode *deleteAtBegin(cNode *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == head)
    {
        delete head;
        return NULL;
    }
    head->data = head->next->data;
    cNode *temp = head->next;
    head->next = head->next->next;
    delete temp;
    return head;
}

/* delete kth node from a circular linked list */
cNode *deleteKthNode(cNode *head, int k)
{
    if (head == NULL)
    {
        return NULL;
    }
    if (k == 1)
    {
        return deleteAtBegin(head);
    }
    cNode *curr = head;
    for (int i = 0; i < k - 2; i++)
    {
        curr = curr->next;
    }
    cNode *temp = curr->next;
    curr->next = curr->next->next;
    delete temp;
    return head;
}

/* Circular doubly linked list
  ❇ we get all the advantages of circular and doubly linked lists
  ❇ we can access last node in constant time without maintaining extra tail pointer/reference */

struct CDLnode
{
    int data;
    CDLnode *next;
    CDLnode *prev;
    CDLnode(int x)
    {
        data = x;
        next = NULL;
        prev = NULL;
    }
};

CDLnode *insertAtBegin(CDLnode *head, int x)
{
    CDLnode *temp = new CDLnode(x);
    if (head == NULL)
    {
        temp->next = temp;
        temp->prev = temp;
        return temp;
    }
    temp->prev = head->prev;
    temp->next = head;
    head->prev->next = temp;
    head->prev = temp;
    return temp;
}
CDLnode *insertAtEnd(CDLnode *head, int x)
{
    CDLnode *temp = new CDLnode(x);
    if (head == NULL)
    {
        temp->next = temp;
        temp->prev = temp;
        return head;
    }
    temp->prev = head->prev;
    temp->next = head;
    head->prev->next = temp;
    head->prev = temp;
    return head;
}

/* Questions practice now... */
node *insertSorted(node *head, int x)
{
    node *temp = new node(x);
    if (head == NULL)
    {
        return temp;
    }
    if (x < head->data)
    {
        temp->next = head;
        return temp;
    }
    node *curr = head;
    while (curr->next != NULL && curr->next->data < x)
    {
        curr = curr->next;
    }
    temp->next = curr->next;
    curr->next = temp;
    return head;
}

// print middle element of the linked list O(n)
// void middleOf(node* head){
//     if(head == NULL){
//         return;
//     }
//     unsigned int count = 0;
//     node* curr = head;
//     for (curr = head; curr!=NULL;curr->next)
//         count++;
//     curr=head;
//     for (int i = 0; i < count/2; i++)
//     {
//         curr = curr->next;
//     }
//     cout<<curr->data;
// }

/* middle element of the linked list single traversal
   ❇ Slow and fast pointers  */
void middleOf_v2(node * head){
    node* slow = head;
    node* fast = head;
    if(head==NULL)return;
    while (fast!=NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast= fast->next->next;
    }
    cout << (slow->data);
}

/* nth node from the end of the list */
// void nthNodeFromEnd(node* head , int Nd){
//     if(head==NULL)return;
//     uint_fast32_t count = 0;
//     for (node* curr = head; curr!=NULL; curr->next)
//     {
//         count++;
//     }
//     if(count<Nd)
//     return;
//     node * curr = head;
//     for (int i = 1; i < count - Nd + 1; i++)
//     {
//         curr = curr->next;
//     }
//     cout<<curr->data<<" ";
// }

/* using two pointers nth node from the end of the list */
void nthNodeFromEnd_v2(node *head, int Nd)
{
    if (head == NULL)
        return;
    node *first = head;
    for (int i = 0; i < Nd; i++)
    {
        if (first == NULL)
            return;
        first = first->next;
    }
    node *second = head;
    while (first != NULL)
    {
        second = second->next;
        first = first->next;
    }
    cout << second->data;
}

/* reverse a linked list O(n) time and space
 */
// node* reverseList(node* head){
//     if(head==NULL)return NULL;
//     stack<int> s;
//     for (node* i = head; i != NULL; i = i->next)
//     {
//         s.push(i->data);
//     }
//     for (node* i = head; i != NULL; i = i->next)
//     {
//         i->data = s.top();
//         s.pop();
//     }
//     return head;
// }

// efficient solution w/ single traversal and O(1) space...
 node* reverseList(node* head){
     if(head==NULL)return NULL;
     if(head->next == NULL)return head;
     node * curr = head;
     node* prev = NULL;
     while (curr != NULL)
     {
         node* next = curr->next; /* creating 'next' so that we don't lose the remaining linked list
                                     pointers (curr,prev) are changed in way so that the links b/w nodes are reversed */
         curr->next = prev;
         prev = curr;
         curr = next;
     }
     return prev;
 }

// recursive function for reversing a linked list...
 node* rReverseList(node* head){
     if(head==NULL)return NULL;
     if(head->next == NULL)return head;
     else{
         node* rest_head = rReverseList(head->next);
         node* rest_tail = head->next;
         rest_tail->next = head;
         head->next = NULL;
         return rest_head;
     }
 }

/* remove duplicates from sorted linked lists */
node *removeDup(node *head)
{
    if (head == NULL)
        return NULL;
    else if (head->next == NULL)
        return head;
    node *curr = head;
    while (curr != NULL && curr->next != NULL)
    {
        if (curr->data == curr->next->data)
        {
            node *temp = curr->next;
            curr->next = curr->next->next;
            delete temp;
        }
        else
        {
            curr = curr->next;
        }
    }
    return head;
};

/* reverse a linked list in groups O(n) O(n/k)*/
// Recursive solution:
 node* reverseListInGroups(node* head , int k){
     if(head==NULL)return NULL;
     if(head->next == NULL)return head;
     node* curr = head;
     node* prev = NULL ,*next = NULL;
     unsigned int count  = 0;
     while (curr!=NULL && count<k)
     {
         /* code */
         next = curr->next;
         curr->next = prev;
         prev = curr;
         curr = next;
         count++;
     }
     if((next!=NULL)){
         node* restHead = reverseListInGroups(next,k);
         head->next = restHead;
     }
     return prev;
 }

// iterative solution
//

/* detect a loop in a linked list
  ☢ method-1 O(n^2)
  ☢ method-2 changing structure of linked list
  ☢ method-3 dummy node (changes the links of a linked list)
  ☢ method-4 using hashing(unordered_Set)
  ☢ method-5 FLOYD cycle detection.. (IMP) */

// new structure (method-2)
//  struct node{
//      int data;
//      node* next;
//      bool visited = false;  //tells whether we have already visited the node or not
//      node(int x){data = x; next=NULL; visited=false;}

// };

// method-3 not recommended as it destroys the list
// bool isLoop(node *head)
// {
//     node *temp = new node;
//     node *curr = head;
//     while (curr != NULL)
//     {
//         if (curr->next == NULL)
//             return false;
//         if (curr->next == temp)
//             return true;
//         node *curr_next = curr->next; // pointing all next nodes to dummy temp and checking if a pointer is already pointing to it
//         curr->next = temp;
//         curr = curr_next;
//     }
//     return false;
// }

// method-4 using unordered-set O(n) space
//  bool isLoop(node* head){
//      unordered_set<node*> s;
//      for(node* curr=head;curr!=NULL;curr=curr->next){
//          if(s.find(curr)!=s.end()){
//              return true;
//          }
//          s.insert(curr);
//      }
//      return false;
//  }

// method-5 floyd-cycle detection O(n) time and O(1) space
//  guide: 1->initialize slow_p = head and fast_p = head,
//  2-> slow moves by 1 and fast moves by 2 , if they both meet then there must be a loop

// bool isLoop(node* head){
//     if(head==NULL)return false;
//     node* slow_p = head;
//     node* fast_p = head;
//     while (fast_p!=NULL && fast_p->next != NULL)
//     {
//         slow_p = slow_p->next;
//         fast_p = fast_p->next->next;
//         if(slow_p == fast_p)
//             return true;
//     }
//     return false;
// }

/* detect and remove loop in a linked list */
// ===>detect loop using floyd-detection ALGORITHM
// ===>move "slow_p" to the beginning and keep the "fast_p" at the meeting point
// ===>one by one move both "slow_p" and "fast_p"(at same speed),
//     the point where they meet now is the first node of the loop

// void detectRemoveLoop(node* head){
//     if(head==NULL)return;
//     node* slow = head,*fast = head;
//     while (fast!=NULL && fast->next!=NULL)
//     {
//         slow=slow->next;
//         fast=fast->next->next;
//         if(slow==fast)
//             break;
//     }
//     if(slow!=fast)return;
//     slow = head;
//     while (slow->next != fast->next)
//     {
//         slow = slow->next;
//         fast = fast->next;
//     }
//     fast->next = NULL;

// }

/* delete node with only one pointer to it...*/
// works only if ptr!= last node...
//  void deleteNode(node* ptr){
//      node* temp = ptr->next;
//      ptr->data = temp->data;
//      ptr->next = temp->next;
//      delete temp;
//  }

/* segregate even odd nodes of linked list */
// node *segregateEvenOdd(node *head)
// {
//     if (head == NULL)
//         return NULL;
//     if (head->next == NULL)
//         return head;
//     node *evenStart = NULL, *evenEnd = NULL, *oddStart = NULL, *oddEnd = NULL;
//     for (node *curr = head; curr != NULL; curr = curr->next)
//     {
//         /* setting nodes while traversing at the same time*/
//         int x = curr->data;
//         if (x % 2 == 0)
//         {
//             if (evenStart == NULL)
//             {
//                 evenStart = curr;
//                 evenEnd = evenStart;
//             }
//             else
//             {
//                 evenEnd->next = curr;
//                 evenEnd = evenEnd->next;
//             }
//         }
//         else
//         {
//             if (oddStart == NULL)
//             {
//                 oddStart = curr;
//                 oddEnd = oddStart;
//             }
//             else
//             {
//                 oddEnd->next = curr;
//                 oddEnd = oddEnd->next;
//             }
//         }
//     }
//     if(oddStart==NULL||evenStart==NULL)
//         return head;
//     evenEnd->next = oddStart;
//     oddEnd->next = NULL;
//     return evenStart;
// }

/* intersection point of two linked list !!! */
//   method-1 O(n+m)time and O(m) space: create an empty hashset(unordered_set) hs
//             traverse the first linked list and put all of its nodes into hs
//             traverse the other list and look for every node in hs as soon as we
//             find a node print in hs,we return value of H
// int getIntersection(node* h1 , node* h2){
//     if(h1==NULL || h2==NULL)return -1;
//     if(h2->next == NULL && h1->next ==NULL){
//         if(h2->data==h1->data)
//             return h1->data;
//         else
//             return -1;
//     }
//     unordered_set<node*> hs;
//     // node* curr = head;
//     for(node* curr = h1; curr!=NULL;curr=curr->next)
//         hs.insert(curr);
//     for(node* curr = h2; curr!=NULL;curr=curr->next){
//         if(hs.find(curr)!=hs.end()){
//             return curr->data;
//         }
//     }
//     return -1;
// }

// method-2 : count nodes in both the list let counts be c1,c2
//             traverse the bigger list abs(c1-c2) times
//             traverse both the lists simultaneously until we see a common node.

// int getIntersection(node* h1,node* h2){
//         if(h1==NULL || h2==NULL)return -1;
//     if(h2->next == NULL && h1->next ==NULL){
//         if(h2->data==h1->data)
//             return h1->data;
//         else
//             return -1;
//     }
//     unsigned c1 = 0 , c2 = 0;
//      for(node* curr = h1; curr!=NULL;curr=curr->next)
//         c1++;
//      for(node* curr = h2; curr!=NULL;curr=curr->next)
//         c2++;
//     int bigger = abs(c1-c2);
//     node* curr1 = h1,*curr2 = h2;
//       for (int i = 0; i < bigger; i++) {
//         if (curr1 == NULL) {
//             return -1;
//         }
//         curr1 = curr1->next;
//     }
//     while (curr1!=NULL && curr2!=NULL)
//     {
//         if(curr1==curr2){return curr1->data;}
//         curr1=curr1->next;
//         curr2=curr2->next;
//     }
//     return -1;
// }

/* pairwise swap nodes of linked list */
// method-1 : swapping data O(n) time (can be costly if using w/ objects)
// void pairwiseSwap(node* head){
//     node* curr = head;
//     while (curr!=NULL&&curr->next!=NULL)
//     {
//         swap(curr->data,curr->next->data);
//         curr=curr->next->next;
//     }
// }

// method-2 : changing links(pointers)
// node* pairwiseSwap(node* head){
//     if (head==NULL || head->next == NULL)
//     {
//         return;
//     }
//     node* curr = head->next->next;
//     node* prev = head;
//     head = head->next;
//     head->next = prev;
//     while (curr!=NULL && curr->next!=NULL)
//     {
//         /**/
//         prev->next = curr->next;
//         prev = curr;
//         node* next = curr->next->next;
//         curr->next->next = curr;
//         curr = next;
//     }
//     prev->next = curr;
//     return head;
// }



/* clone a linked list with random pointer */
// method-1 : =>create a hash map _Hash_imp
//            =>for(curr=h1;curr!=NULL;curr=curr->-next)
//                 hm[curr] = new node(Curr->data)
//            =>for(curr=h1;curr!=NULL;curr=curr->next){
//             cloneCurr = hm.find(curr);
//             cloneCurr->next = hm(curr->next)
//             cloneCurr->random = hm(curr->random);
//            }
//            => h2 = hm[h1]

//see code at gfg official site...

//method-2 : insert new nodes b/w alternate nodes of original linked list 
//then deleting the original linked list nodes from it...😥😥


/* LRU cache design  
implementation 1-using arrays O(n) both hit and miss
implementation 2- hashing and doubly linked list*/


/* merge two sorted linked lists (no extra space only modify pointers/links)*/
node* mergeList(node* h1 , node* h2){
    if(h1==NULL||h2==NULL)return;
    node* head=NULL,*tail=NULL;
    if(h1->data<=h2->data){
        head=tail=h1; h1=h1->next;
    }
    else{
        head=tail=h2; h2=h2->next;
    }
    while (h1!=NULL&&h2!=NULL)
    {
        if(h1->data<=h2->data){
            tail->next = h1; tail = h1; h1 = h1->next;
        }
        else{
            tail->next = h2; tail = h2; h2 = h2->next;
        }
    }
    if(h1==NULL){
        tail->next = h2;
    }
    else{
        tail->next = h1;
    }
    return head;
    
    
}
int main()
{
    node *head = new node(12);
    /*  head = insertAtBegin(head,30);
        head = insertAtBegin(head,69);
        head = insertAtBegin(head,39);
        head = insertAtEnd(head,9);
        head = deleteAtBegin(head);
        head = deleteAtEnd(head);
        head = insertAtBegin(head,90);
        head = insertAt(head,1,92);
        printLList(head); */

    // DLnode *head = new DLnode(10);
    // DLnode *temp1 = new DLnode(20);

    return 0;
}