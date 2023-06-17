#include <bits/stdc++.h>
using namespace std;

struct SingleNode
{
    int val;
    SingleNode *next;
    SingleNode(int x = 0)
    {
        val = x;
        next = NULL;
    }
};
//^ 1 Reverse a linked list both iterative and recursive
class reverse_list
{
public:
    /*
    & This code reverses the linked list by first storing the values of the nodes in a vector, then reversing the vector, and finally updating the node values in the linked list with the reversed values.
    ! O(N) T.C | O(N) S.C [Iterative]
     */
    // SingleNode *reverseList(SingleNode *head)
    // {
    //     vector<int> temp;
    //     SingleNode *curr = head;
    //     while (curr != NULL)
    //     {
    //         temp.push_back(curr->val);
    //         curr = curr->next;
    //     }
    //     reverse(temp.begin(), temp.end());
    //     curr = head;
    //     int i = 0;
    //     while (curr != NULL)
    //     {
    //         curr->val = temp[i++];
    //         curr = curr->next;
    //     }
    //     return head;
    // }
    /*
    & Rather than using an auxiliary array just swap the links then the list will be reversed
    * O(N) T.C | O(1) S.C [Iterative];
     */
    SingleNode *reverseList(SingleNode *head)
    {
        if (!head || head->next == NULL)
            return head;
        SingleNode *temp = NULL;
        while (head != NULL)
        {
            SingleNode *next = head->next;
            head->next = temp;
            temp = head;
            head = next;
        }
        return temp;
    }
    /*
    &    The function reverseList_recursive takes a pointer to the head of the linked list as input and returns a pointer to the new head of the reversed list.
    &    The base case of the recursion is when the linked list is empty (head == NULL) or has only one node (head->next == NULL). In such cases, the function simply returns the current head as it is already the head of the reversed list.
    &    If the linked list has more than one node, the function proceeds with the recursive reversal process.
    &    Create a pointer n and assign it the address of the second node in the original list (head->next). This will be the new head of the reversed list.
    &    Call the reverseList_recursive function recursively, passing n as the argument. This will reverse the remaining portion of the linked list starting from n and return the new head of the reversed list.
    &    Once the recursive call returns, we need to perform the pointer manipulation to reverse the connections.
    &    Set head->next->next to head to make the next node in the reversed list point back to the current node (head).
    &    Set head->next to NULL to break the connection between the current node and the next node in the original list.
    &    Finally, return newHead, which is the new head of the reversed list obtained from the recursive call.
    &    The recursive calls and pointer manipulations continue until the initial call returns, giving us the final reversed linked list.
    ! O(N) T.C | O(N) S.C [Recursive]
     */
    SingleNode *reverseList_recursive(SingleNode *head)
    {
        if (head == NULL || head->next == NULL)
            return head;
        SingleNode *n = head->next;
        SingleNode *newHead = reverseList_recursive(n);
        head->next->next = head;
        head->next = NULL;
        return newHead;
    }
};

//^ 2 Reverse the linked list in groups of K nodes
class ReverseListK
{
public:
    /*
    @ RECURSIVE APPROACH
    &       Initialize three pointers: curr to the head of the current group, prev as NULL to store the previous node, and next as NULL to store the next node.
    &   Initialize a variable count to keep track of the number of nodes processed in the current group.
    &   Enter a while loop that iterates until curr is not NULL and the count is less than k. This loop is responsible for reversing the nodes in the current group.
    &       Store the next node after curr in the next pointer.
    &       Update the next pointer of curr to point to the previous node prev.
    &       Move the prev pointer to the current node curr.
    &       Move the curr pointer to the next node next.
    &       Increment the count variable.
    &   After the loop finishes, the current group of nodes is reversed, and the prev pointer points to the last node of the reversed group.
    &   Check if there are more nodes remaining in the linked list (i.e., next is not NULL). If there are, recursively call the reverseKnodes function with next as the new head and k as the group size. This step will reverse the next group of nodes and return the new head of that group.
    &   Connect the reversed group (represented by prev) with the head of the next group (returned by the recursive call) by updating the next pointer of the current group's head (head->next) to the new head of the next group.
    & Return the prev pointer, which is now the head of the reversed linked list.
    ! O(N) T.C || O(N/K) S.C
     */
    SingleNode *reverseKnodes(SingleNode *head, int k)
    {
        SingleNode *curr = head;
        SingleNode *prev = NULL, *next = NULL;
        int count = 0;
        while (curr != NULL && count < k)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
            count++;
        }
        if (next != NULL)
        {
            SingleNode *restHead = reverseKnodes(next, k);
            head->next = restHead;
        }
        return prev;
    }

    /*
    @ ITERATIVE APPROACH
    &       Initialize the current node curr to the head of the linked list and create a pointer prevFirst to keep track of the previous group's first node.
    &   Set a boolean variable isFirstPass to true. This flag helps identify the first group of nodes to update the head of the linked list.
    &   Enter a while loop that iterates until the current node curr reaches the end of the linked list.
   &     Inside the loop, create a pointer first to store the current group's first node and initialize a pointer prev as NULL to track the previous node while reversing the group.
    &   Initialize a variable count to keep track of the number of nodes reversed in the current group.
   &     Enter a nested while loop that iterates until the current node curr is not NULL and the count is less than k. This loop is responsible for reversing the nodes in the current group.
    &       Create a pointer next and store the next node after curr.
    &    Update the next pointer of curr to point to the previous node prev.
    &    Move the prev pointer to the current node curr.
    &    Move the curr pointer to the next node next.
    &    Increment the count variable.
    &   After the inner loop finishes, the current group of nodes is reversed, and the prev pointer points to the last node of the reversed group.
    &   Check if it is the first pass (i.e., isFirstPass is true). If it is, update the head of the linked list to the current group's last node (prev).
    &   If it is not the first pass, update the next pointer of the previous group's first node (prevFirst->next) to the current group's last node (prev).
   & Update the prevFirst pointer to the first node of the current group.
    Repeat steps 3-10 until all nodes in the linked list are processed.
    Return the modified head of the linked list.

    * O(N) T.C | O(1) S.C
     */
    SingleNode *reverseKnodesIterative(SingleNode *head, int k)
    {
        SingleNode *curr = head, *prevFirst = NULL;
        bool isFirstPass = true;
        while (curr != NULL)
        {
            SingleNode *first = curr, *prev = NULL;
            int count = 0;
            while (curr != NULL && count < k)
            {
                SingleNode *next = curr->next;
                curr->next = prev;
                prev = curr;
                curr = next;
                count++;
            }
            if (isFirstPass)
            {
                head = prev;
                isFirstPass = false;
            }
            else
            {
                prevFirst->next = prev;
            }
            prevFirst = first;
        }
        return head;
    }
};

//^ 3 detect loops
class detectLoopLinkedList
{
private:
public:
    /*
    ! DESTROYS the linked list
    * O(N) T.C | O(1) S.C
     */
    bool detectLoop(SingleNode *head)
    {
        if (!head)
            return false;
        SingleNode *curr = head;
        while (curr != NULL)
        {
            if (curr->val == INT_MAX)
            {
                return true;
            }
            else
            {
                curr->val = INT_MAX;
                curr = curr->next;
            }
        }
        return false;
    }
    /*
        & Using Hash set (unordered_sets)
        * O(N) T.C & S.C
     */
    bool detectLoop_v2(SingleNode *head)
    {
        unordered_set<SingleNode *> hs;
        for (SingleNode *curr = 0; curr != NULL; curr = curr->next)
        {
            if (hs.find(curr) != hs.end())
                return true;
            hs.insert(curr);
        }
        return false;
    }
    /*
    @ Floyd's Cycle Algorithm
    &1. Begin by initializing two pointers, fast and slow, both pointing to the head of the linked list.

&2. Enter a while loop that continues until fast and slow meet or until the end of the linked list is reached.

&3. Inside the loop, check if fast or fast->next is NULL. If either of them is NULL, it means that the fast pointer has reached the end of the linked list, indicating that no cycle exists. In such a case, return false.

&4. Move the fast pointer two steps ahead by setting it to fast->next->next.

&5. Move the slow pointer one step ahead by setting it to slow->next.

&6. Repeat steps 3-5 until fast and slow meet (i.e., fast == slow). This condition indicates the presence of a cycle in the linked list.

&7. If the while loop terminates without finding a cycle (i.e., fast and slow do not meet), return false.

&8. If a cycle is detected (i.e., fast and slow meet), return true to indicate the presence of a cycle in the linked list.

&The algorithm uses the approach of a slow pointer moving one step at a time and a fast pointer moving two steps at a time. If a cycle exists in the linked list, the fast pointer will eventually catch up to the slow pointer, resulting in the two pointers meeting. If there is no cycle, the fast pointer will reach the end of the linked list before the slow pointer.
     */
    bool detectLoop_v3(SingleNode *head)
    {
        if (!head)
            return false;

        // using two pointers and moving one pointer(slow) by one node and
        // another pointer(fast) by two nodes in each iteration.
        SingleNode *fast = head->next;
        SingleNode *slow = head;

        while (fast != slow)
        {
            // if the node pointed by first pointer(fast) or the node
            // next to it is null, we return false.
            if (!fast || !fast->next)
                return false;

            fast = fast->next->next;
            slow = slow->next;
        }
        // if we reach here it means both the pointers fast and slow point to
        // same node which shows the presence of loop so we return true.
        return true;
    }
};

//^ 4 Detect and remove loop
/*
~ The intuition behind this code is to use two pointers, one slow and one fast, to detect the loop in the linked list. The slow pointer moves one step at a time, while the fast pointer moves two steps at a time. If there is a loop, the fast pointer will eventually catch up with the slow pointer. Once a loop is detected, the starting node of the loop is found by resetting the slow pointer to the head and moving both pointers one step at a time until they meet again. Finally, the last node of the loop is found by moving the fast pointer until its next node is the same as the slow pointer. By breaking the link of the last node, the loop is removed from the linked list.

* O(N) T.C | O(1) S.C
 */
void detectAndRemoveLoop(SingleNode *head)
{
    if (!head)
        return;
    SingleNode *s = head;
    SingleNode *f = head;
    while (f and f->next)
    {
        s = s->next;
        f = f->next->next;
        if (f == s)
        {
            s = head;
            while (s != f)
            {
                s = s->next;
                f = f->next;
            }
            while (f->next != s)
            {
                f = f->next;
            }
            f->next = NULL;
        }
    }
    return;
}

//^ 5 Merge two sorted linked lists
/*

! O(N) Space solution : use a temporary array to store the elements of list1 and list2 then sort it or use merge function of merge sort!

& 1. Create two pointers, head and tail, and initialize them to NULL. These pointers will be used to build the merged linked list.
& 2. Check if either list1 or list2 is NULL. If one of them is NULL, it means one of the lists is empty. In that case, return the non-empty list as the merged list.
& 3. Compare the values of the first nodes of list1 and list2 to determine which one should be the head of the merged list. Set head and tail accordingly.
& 4. Move the appropriate pointer (list1 or list2) to the next node, as it has been used to set the head of the merged list.
& 5. Start a while loop that continues until either list1 or list2 becomes NULL. This loop is used to merge the remaining nodes of list1 and list2 in ascending order.
& 5.1. Compare the values of the current nodes of list1 and list2.
& 5.2. If the value of the node in list1 is less than or equal to the value in list2, append the node from list1 to the merged list (tail->next = list1), update tail to the appended node, and move list1 to the next node (list1 = list1->next).
& 5.3. If the value of the node in list2 is greater than the value in list1, append the node from list2 to the merged list (tail->next = list2), update tail to the appended node, and move list2 to the next node (list2 = list2->next).
& 6. Check if either list1 or list2 is NULL. If list1 is NULL, it means all nodes from list1 have been merged. Append the remaining nodes from list2 to the merged list (tail->next = list2).
& 7. If list2 is NULL, it means all nodes from list2 have been merged. Append the remaining nodes from list1 to the merged list (tail->next = list1).
& 8. Return head, which is the head of the merged list.

* O(N) T.C
 */
SingleNode *mergeList(SingleNode *list1, SingleNode *list2)
{

    SingleNode *head, *tail;
    if (!list1)
        return list2;
    if (!list2)
        return list1;

    if (list1->val <= list2->val)
    {
        head = list1;
        tail = list1;
        list1 = list1->next;
    }
    else
    {
        head = list2;
        tail = list2;
        list2 = list2->next;
    }

    while (list1 != NULL && list2 != NULL)
    {
        if (list1->val <= list2->val)
        {
            tail->next = list1;
            tail = list1;
            list1 = list1->next;
        }
        else
        {
            tail->next = list2;
            tail = list2;
            list2 = list2->next;
        }
    }
    if (list1 == NULL)
        tail->next = list2;
    else
        tail->next = list1;
    return head;
}
//^ 6 Rotate Singly Linked list by K
/*


&1. Check if the rotation count k is 0 or if the head of the linked list is NULL. If either condition is true, there is no need to rotate the list, so return the head as it is.

&2. Initialize a pointer curr to the head of the linked list and a pointer tail to NULL. These pointers will be used to traverse the list and keep track of the new tail after rotation.

&3. Start a loop that runs k times to traverse k nodes in the linked list. In each iteration, update tail to curr and move curr to the next node.

&4. After the loop, check if curr is NULL or if it is pointing to the head of the list. If either condition is true, it means the rotation count is greater than or equal to the length of the list, resulting in no effective rotation. In this case, return the head as it is.

&5. Set the next pointer of tail to NULL, effectively disconnecting the rotated portion from the rest of the list.

&6. Update tail to the current value of curr. Now, tail points to the last node of the original list, which will be the new tail after rotation.

&7. Traverse the remaining portion of the list by moving curr to the next node until curr->next becomes NULL. This will bring curr to the last node of the original list.

&8. Connect the original head (which is now at the end) to the next pointer of curr, effectively making it the new head of the rotated list.

&9. Return tail, which is the new head of the rotated list.

~The algorithm rotates the linked list by k positions by adjusting the pointers in the list. It first traverses k nodes to find the new tail and disconnects the rotated portion from the rest of the list. Then, it moves to the end of the original list and connects it with the original head to form the rotated list.
* O(N) T.C | O(1) S.C
 */
SingleNode *rotate(SingleNode *head, int k)
{
    // Your code here
    if (k == 0 || !head)
        return head;
    SingleNode *curr = head;
    SingleNode *tail = NULL;
    while (k--)
    {
        tail = curr;
        curr = curr->next;
    }
    if (!curr || curr == head)
        return head;
    tail->next = NULL;
    tail = curr;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = head;
    return tail;
}
//^ 7 First Node in a loop
/*
& 1)Temp,slowPointer and fastPointer, both set to the head of the linked list.

& 2)Move slowPointer one node at a time and fastPointer two nodes at a time.

& 3)If fastPointer becomes null, then there is no loop in the linked list and return -1.

& 4)If fastPointer and slowPointer meet, then there is a loop in the linked list.

& 5) Move slowPointer and temp one node at a time. The point where they meet is the first node of the loop. Return the data of the first node of the loop.

~ This approach will have a time complexity of O(n) and space complexity of O(1).
 */
int findFirstNode(SingleNode *head)
{
    // your code here
    if (!head)
        return -1;
    SingleNode *fast = head;
    SingleNode *slow = head;
    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            break;
        }
    }
    if (slow != fast)
        return -1;
    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return fast->val;
}

//^ 8 Intersection Point in Y shaped linked list
class FindIntersectionPoint
{
public:
    /*
    @ Hashing Solution

    ! O(N+M) T.C | O(max(N,M)) S.C
     */
    int intersectPoint(SingleNode *head1, SingleNode *head2)
    {
        // Your Code Here
        if (!head1 || !head2)
            return -1;
        unordered_set<SingleNode *> hs;
        while (head1 != NULL)
        {
            hs.insert(head1);
            head1 = head1->next;
        }
        while (head2 != NULL)
        {
            if (hs.find(head2) != hs.end())
            {
                return head2->val;
            }
            head2 = head2->next;
        }
        return -1;
    }
    /*
    @ Optimized version
    * O(M+N) T.C | O(1) S.C
     */
    int intersectPoint_v2(SingleNode *head1, SingleNode *head2)
    {
        // Your Code Here
        int cnt1 = 0;
        int cnt2 = 0;
        SingleNode *temp1 = head1;
        SingleNode *temp2 = head2;
        while (temp1 != NULL)
        {
            cnt1++;
            temp1 = temp1->next;
        }
        while (temp2 != NULL)
        {
            cnt2++;
            temp2 = temp2->next;
        }
        temp1 = head1;
        temp2 = head2;
        while (temp1 != NULL && cnt1 > cnt2)
        {
            cnt1--;
            temp1 = temp1->next;
        }
        while (temp2 != NULL && cnt2 > cnt1)
        {
            cnt2--;
            temp2 = temp2->next;
        }
        while (temp1 != temp2)
        {
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        return temp1->val;
    }
};

//^ 9 Find duplicates in a sorted linked list

/*
&1. Check if the linked list is empty (!head) or has only one node (!head->next). If either condition is true, there are no duplicates to remove, so return the head as it is.

&2. Initialize a pointer x to the head of the linked list. This pointer will be used to iterate through the list.

&3. Start a while loop that continues until the next node of x is NULL.

&4. Inside the loop, check if the value (data) of the current node (x) is equal to the value of its next node (x->next). If they are equal, it means there is a duplicate.

&5. To remove the duplicate, update the next pointer of the current node (x->next) to skip the duplicate node and point to the next node in the list (x->next->next).

&6. If the values are not equal, move x to the next node (x = x->next), as there is no duplicate to remove at this point.

&7. Repeat steps 3-6 until the end of the linked list is reached.

&8. Return the modified linked list head after removing duplicates.

~ The intuition behind this code is to traverse the linked list while comparing consecutive nodes. If duplicate values are found, the duplicate node is skipped by adjusting the next pointer of the current node to point to the next non-duplicate node. This way, only unique values remain in the linked list.
 */
SingleNode *removeDuplicates(SingleNode *head)
{
    // your code goes here
    if (!head || !head->next)
    {
        return head;
    }
    SingleNode *x = head;
    while (x->next)
    {
        if (x->val == x->next->val)
            x->next = x->next->next;
        else
            x = x->next;
    }
    return head;
}

//^ 11 Common elements in a sorted linked list
class CommonElements
{
public:
    /*
    @ Naive Approach
 & - Map m is initialized to store the count of each value in both linked lists.
 & - Traverse head1 and increment the count of each value in m.
 & - Traverse head2 and increment the count of each value in m.
 & - Initialize a new node ans with a value of 0.
 & - Initialize a pointer cur to ans.
 & - Traverse m and for each element with a count greater than or equal to 2:

     ~    Calculate t as i.second/2.
     ~    Repeat the following steps t times:
     ~        Create a new node temp with the value i.first.
     ~        Append temp to cur->next.
     ~        Move cur to the newly added node.
             & - Delete the first node (initialized with 0) by freeing the memory allocated to it.
             & - Return the merged linked list starting from ans->next.

 ~ The intuition behind this code is to use a map to store the count of each value in the linked lists. By traversing the map, we can identify the duplicate elements and create a new merged linked list by adding them the required number of times. The use of division by 2 ensures that the duplicates are added an equal number of times from both lists. The final merged linked list is returned by excluding the initial placeholder node.
    ! O((N+M)log(N+M)) T.C | O(N+M) S.C
     */

    SingleNode *FindIntersection(SingleNode *head1, SingleNode *head2)
    {
        map<int, int> m;
        // Store all the value of node in map
        while (head1 != NULL)
        {
            m[head1->val]++;
            head1 = head1->next;
        }

        while (head2 != NULL)
        {
            m[head2->val]++;
            head2 = head2->next;
        }

        // make new node as ans and initially store 0 in it.
        SingleNode *ans = new SingleNode(0);

        SingleNode *cur = ans;

        // traverse the map and extract all the element greater than 1.
        for (auto i : m)
        {
            if (i.second >= 2)
            {

                // if there are same duplicate element in both the lists then we will store the element   i.second/2 number of times

                int t = i.second / 2;

                while (t--)
                {
                    SingleNode *temp = new SingleNode(i.first);
                    cur->next = temp;
                    cur = cur->next;
                }
            }
        }

        // delete the first node as we stored 0 in ans node
        cur = ans;
        ans = ans->next;
        free(cur);
        return ans;
    }
    /* 
    @ Using the same approach as merge 2 sorted LL
    & - Initialize two pointers p1 and p2 to the heads of head1 and head2 respectively.
& - Initialize head and tail pointers to NULL.
& - Iterate while both p1 and p2 are not NULL:

~        If p1->data is greater than p2->data, move p2 to the next node in the list with the smaller node value.
~        If p2->data is greater than p1->data, move p1 to the next node in the list with the smaller node value.
~        If p1->data is equal to p2->data, it means a node match is found:
~                If head is NULL, create a new node with p1->data and assign it to both head and tail. This initializes the intersection list.
~                If head is not NULL, append a new node with p1->data at the end of the intersection list (using the tail pointer).
~                Move p1 and p2 to their respective next nodes.
                & - Return the head of the intersection list.

? The intuition behind this code is to iterate through both linked lists simultaneously using two pointers p1 and p2. By comparing the node values, we can identify the common nodes between the lists and construct a new linked list containing those common nodes. The algorithm ensures that the intersection list is built in ascending order.
* O(M+N) T.C | O(1) S.C
     */
    SingleNode* findIntersection(SingleNode* head1, SingleNode* head2)
{
    SingleNode *p1=head1, *p2=head2;
    SingleNode *head=NULL, *tail=NULL;
    
    while(p1 && p2)
        if(p1->val > p2->val)
            // nodes dont match
            // moving to next node in list with smaller node
            p2 = p2->next;
        
        else if(p2->val > p1->val)
            // nodes dont match
            // moving to next node in list with smaller node
            p1 = p1->next;
        
        else
        {
            // nodes match
            
            if(head==NULL)
                head = tail = new SingleNode(p1->val);
                // creating new head for intersection list
            else
            {
                // appending new node at the end
                tail->next = new SingleNode(p1->val);
                tail = tail->next;
            }
            p1 = p1->next;
            p2 = p2->next;
            // moving to next nodes in both lists
        }
    
    return head;
}
};
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
