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
//^ 7 First SingleNode in a loop
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
    SingleNode *findIntersection(SingleNode *head1, SingleNode *head2)
    {
        SingleNode *p1 = head1, *p2 = head2;
        SingleNode *head = NULL, *tail = NULL;

        while (p1 && p2)
            if (p1->val > p2->val)
                // nodes dont match
                // moving to next node in list with smaller node
                p2 = p2->next;

            else if (p2->val > p1->val)
                // nodes dont match
                // moving to next node in list with smaller node
                p1 = p1->next;

            else
            {
                // nodes match

                if (head == NULL)
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

//^ 12 Clone a linked list with random pointer
class CloneList
{
public:
    /*
&     The intuition behind the code is to maintain a mapping between each original node and its corresponding cloned node. This mapping is stored in an unordered map, where the original node is the key and the cloned node is the value.

Here's how the code works:

 &    First, it checks if the given linked list is empty (i.e., head is NULL). If it is, it returns NULL since there's no list to copy.

 &    It initializes an unordered map called mp to store the mapping between original nodes and cloned nodes.

 &    The code then iterates through the original linked list using a pointer curr. In each iteration, it creates a new node with the same data as the current original node and adds it to the map mp with the current original node as the key.

 &    After creating the cloned nodes for all original nodes, the code performs a second iteration through the original linked list. In each iteration, it sets the next pointer of the cloned node to the corresponding cloned node of the next original node using the map mp. Similarly, it sets the arb pointer of the cloned node to the corresponding cloned node of the arb pointer of the original node.

&     Finally, the code returns the cloned node corresponding to the original head node, which can be obtained from the map mp.

& By using the map mp to maintain the mapping between original and cloned nodes, the code ensures that the cloned list is a deep copy with separate memory allocations for each node, while also correctly setting the next and arb pointers.

& Overall, the code effectively creates a deep copy of the given linked list with the additional "arb" pointers by utilizing an unordered map to maintain the mapping between original and cloned nodes.

% O(N) T.C | O(N) S.C
     */
    struct SingleNode
    {
        int data;
        SingleNode *next;
        SingleNode *arb;
        SingleNode(int x)
        {
            data = x;
            next = NULL;
            arb = NULL;
        }
    };
    SingleNode *copyList(SingleNode *head)
    {
        // Write your code here
        if (!head)
            return head;
        unordered_map<SingleNode *, SingleNode *> mp;
        for (SingleNode *curr = head; curr != NULL; curr = curr->next)
        {
            mp[curr] = new SingleNode(curr->data);
        }
        for (SingleNode *curr = head; curr != NULL; curr = curr->next)
        {
            SingleNode *cloned = mp[curr];
            cloned->next = mp[curr->next];
            cloned->arb = mp[curr->arb];
        }
        return mp[head];
    }
    /*
        First, it checks if the given linked list is empty (i.e., head is NULL). If it is, it returns NULL since there's no list to copy.

    The code then iterates through the original linked list using a pointer current. In each iteration, it creates a new node with the same data as the current original node and inserts it after the current original node. This is done by assigning the next pointer of the current original node to the newly created node, and assigning the next pointer of the newly created node to the next node in the original list. This effectively creates a duplicate copy of each node in the original list.

    After creating the duplicate nodes, the code performs another iteration through the list to set the arb pointers of the newly created nodes. For each original node, it sets the arb pointer of its corresponding duplicate node to the next node of the original node's arb pointer. This is done by checking if the original node's arb pointer is not NULL. If it is not NULL, the arb pointer of the duplicate node is set to the next node of the original node's arb pointer. This step ensures that the arb pointers of the duplicate nodes correctly point to the corresponding duplicate nodes.

    The code then separates the original and duplicate linked lists by updating the next pointers of the original nodes and the duplicate nodes. It starts by setting two pointers original and copy to the respective heads of the original and duplicate lists. It also keeps a temporary pointer temp to track the head of the duplicate list.
        In each iteration, it updates the next pointer of the original node to skip the next node (which is the duplicate node), effectively removing the duplicate node from the original list.
        Similarly, it updates the next pointer of the duplicate node to either skip the next duplicate node (if it exists) or NULL (if it doesn't exist), effectively removing the original node from the duplicate list.
        It continues this process until either the original list or the duplicate list reaches the end.

    Finally, it returns the head of the duplicate list, which is stored in the temp pointer.

By following these steps, the code effectively creates a deep copy of the given linked list with the additional "arb" pointers. It achieves this by iteratively duplicating each node in the original list, setting the "arb" pointers of the duplicate nodes to the appropriate nodes, and then separating the original and duplicate lists while updating the "next" pointers.
    * O(N) T.C | O(1) S.C
     */
    SingleNode *copyList(SingleNode *head)
    {
        // Write your code here
        if (!head)
            return head;
        SingleNode *current = head;
        while (current != NULL)
        {
            SingleNode *temp = current->next;
            current->next = new SingleNode(current->data);
            current->next->next = temp;
            current = temp;
        }
        current = head;

        // Setting random pointers to new nodes

        while (current != NULL)
        {

            current->next->arb = (current->arb) ? current->arb->next : current->arb;
            current = current->next->next;
        }
        SingleNode *original = head;
        SingleNode *copy = head->next;
        SingleNode *temp = copy;

        while (original != NULL && copy != NULL)
        {
            original->next = original->next->next;
            copy->next = (copy->next != NULL) ? copy->next->next : copy->next;
            original = original->next;
            copy = copy->next;
        }
        return temp;
    }
};

//^ 13 Check if a linked list is palindrome
class CheckPalindrome
{
public:
    /*
    @ Extra space solution
    & Use any auxillary array (vector) to store the items of the list and check if the array is palindrome or not.
    ~ Stack can also be used to store the items of the list and then keep popping elements from the stack until the stack is empty
    ! O(N) T.C | O(N) S.C
     */

    /*
    @ Constant space approach by finding middle element and reversing the remaining elements
    &     The function isPalindrome takes the head of the linked list as input and returns a boolean value indicating whether it is a palindrome or not.

  &   Initially, it handles the edge case where the linked list is empty (head is NULL). In such a case, it returns NULL (which should ideally be false) since an empty list is not considered a palindrome.

 &    The code then finds the middle element of the linked list using the slow and fast pointer technique. It initializes two pointers slow and fast to the head of the list. The slow pointer moves one step at a time, while the fast pointer moves two steps at a time. By the time the fast pointer reaches the end of the list, the slow pointer will be pointing to the middle element (or the first element of the second half if the list has an odd number of nodes).

 &    The code then reverses the second half of the linked list using the reverseLL function. It passes the slow->next node as the head to reverse the second half starting from that node. The reverseLL function iteratively reverses the linked list by updating the next pointers of each node.

 &    After reversing the second half, the code compares the first half and the reversed second half of the linked list. It does this by using two pointers slow (now pointing to the reversed second half) and fast (pointing to the head of the original list). It iterates while the slow pointer is not NULL (indicating it has reached the end of the reversed second half). In each iteration, it checks whether the data of the corresponding nodes in the first half (fast->data) and the reversed second half (slow->data) are equal. If they are not equal, it returns false since the linked list is not a palindrome. Otherwise, it moves both pointers to the next nodes and continues the comparison.

  &   If the code completes the iteration without finding any mismatched nodes, it means the linked list is a palindrome, and it returns true.

& The time complexity of this code is O(n), where n is the number of nodes in the linked list. This is because the code iterates through the linked list twice: once to find the middle element (which takes O(n/2) time) and once to compare the first half with the reversed second half (which also takes O(n/2) time). The space complexity is O(1) since it uses a constant amount of additional space for the pointers.

Example:
~Consider the linked list: 1 -> 2 -> 3 -> 2 -> 1

 ~   Initially, slow and fast are both set to the head of the list.
 ~   The while loop moves slow and fast as follows: slow = 3, fast = 1 -> 2 -> 3 -> 2 -> 1
 ~   After reversing the second half, the list becomes: 1 -> 2 -> 3 -> 1 -> 2
 ~   The while loop compares the first half (1 -> 2 -> 3) with the reversed second half (1 -> 2). Since all corresponding nodes are equal, it returns true, indicating that the linked list is a palindrome.
     */
    SingleNode *reverseLL(SingleNode *head)
    {
        SingleNode *curr = head;
        SingleNode *prev = NULL;
        while (curr)
        {
            SingleNode *temp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = temp;
        }
        return prev;
    }
    bool isPalindrome(SingleNode *head)
    {
        //? Find the middle element
        if (!head)
        {
            return NULL;
        }
        SingleNode *slow = head;
        SingleNode *fast = head;
        while (fast->next && fast->next->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        slow = reverseLL(slow->next);
        fast = head;
        while (slow)
        {
            if (fast->val != slow->val)
                return false;
            slow = slow->next;
            fast = fast->next;
        }
        return true;
    }
};

//^ 14 Add 1 to number represented by a linked list
class Add1toLL
{
private:
    struct SingleNode
    {
        int data;
        struct SingleNode *next;

        SingleNode(int x)
        {
            data = x;
            next = NULL;
        }
    };

public:
    /*
    @ Recursive approach
&  The solve function is a recursive helper function that performs the addition operation. It takes a current node as input and returns the carry value (either 0 or 1) after adding 1 to the number represented by the subsequent nodes.

&  The base case of the recursion is when the current node's next pointer is NULL, indicating the last digit of the number. In this case, it checks if the current digit is 9. If it is 9, it changes the digit to 0 and returns 1 as the carry. If it is not 9, it increments the digit by 1 and returns 0 as the carry.

&  For non-base cases, it recursively calls the solve function for the next node and stores the returned carry value. If the carry is 1, it performs the same logic as the base case, changing the digit to 0 if it is 9 and returning 1 as the carry. Otherwise, it increments the digit by 1 and returns 0 as the carry.

&  The addOne function is the main function that calls the solve function on the head node of the linked list. It also handles the case where the final carry is 1. If the carry is 1, it creates a new node with a value of 1 and sets its next pointer to the original head. It then returns this new node as the new head of the linked list.

&  The overall process is similar to adding 1 to a number manually, starting from the least significant digit and propagating the carry to the more significant digits if necessary.

&  Note: The code assumes that the input linked list is not empty.

&  The time complexity of the code is O(n), where n is the number of nodes in the linked list, as it needs to traverse the entire linked list.

    ! O(Nodes) T.C | O(Nodes) S.C
     */
    int solve(SingleNode *curr)
    {
        if (curr->next == NULL)
        {
            if (curr->data == 9)
            {
                curr->data = 0;
                return 1;
            }
            else
            {
                curr->data++;
                return 0;
            }
        }
        int carry = solve(curr->next);
        if (carry == 1)
        {
            if (curr->data == 9)
            {
                curr->data = 0;
                return 1;
            }
            else
            {
                curr->data++;
                return 0;
            }
        }
        return carry;
    }
    // SingleNode *addOne(SingleNode *head)
    // {
    //     int getCarry = solve(head);
    //     if (getCarry == 1)
    //     {
    //         SingleNode *temp = new SingleNode(1);
    //         temp->next = head;
    //         return temp;
    //     }
    //     return head;
    // }

    /*
    @ Storing the value of rightmost 9
    &1. The function addOne takes a linked list head as input and returns the modified linked list after adding 1 to the number represented by the linked list.
&2. Two pointers, notNine and end, are initialized to the head of the linked list.
&3. A while loop is used to traverse the linked list until the end node is reached (i.e., end->next is NULL).
&4. Inside the loop, if the current node's data is not equal to 9, the notNine pointer is updated to point to the current node. This helps keep track of the rightmost non-nine digit in the linked list.
&5. Finally, end is updated to point to the last node of the linked list.
&6. At this point, we have identified the rightmost non-nine digit or the last node in the linked list.
&7. If the data of the last node (end->data) is equal to 9, it means all the digits in the linked list are nines.
&8. In such a case, the value of the rightmost non-nine digit is incremented by 1 (notNine->data = notNine->data + 1), and the notNine pointer is moved to the next node.
&9. Then, a while loop is used to traverse the remaining nodes starting from notNine and set their data to 0, effectively changing all the nines to zeros.
&10. If the data of the last node is not 9, it means we can simply increment its value by 1 (end->data = end->data + 1).
&11. Finally, the modified linked list is returned.

The intuition behind this code is to find the rightmost non-nine digit (or the last node) in the linked list and increment its value by 1. If all the digits in the linked list are nines, we need to propagate the carry by incrementing the value of the rightmost non-nine digit and setting all the subsequent digits to zero.

Using this approach, the code efficiently handles cases where the linked list contains consecutive nines or has a mix of non-nine and nine digits.

Please note that the code assumes the input linked list represents a non-negative integer, and it does not consider cases where the resulting number exceeds the range of integer representation.

     */
    SingleNode *addOne(SingleNode *head)
    {
        SingleNode *notNine = head, *end = head;
        while (end->next)
        {
            if (end->data != 9)
                notNine = end;
            end = end->next;
        }
        if (end->data == 9)
        {
            notNine->data = notNine->data + 1;
            notNine = notNine->next;
            while (notNine)
            {
                notNine->data = 0;
                notNine = notNine->next;
            }
        }
        else
        {
            end->data = end->data + 1;
        }
        return head;
    }
};

//^ 15 Merge sort in Linked List
class MergeSortLinkedList
{
    SingleNode *merge(SingleNode *left, SingleNode *right)
    {
        if (!left)
            return right;
        if (!right)
            return left;
        SingleNode *ans = new SingleNode(0);
        SingleNode *dummy = ans;
        while (left && right)
        {
            if (left->val < right->val)
            {
                dummy->next = left;
                dummy = left;
                left = left->next;
            }
            else
            {
                dummy->next = right;
                dummy = right;
                right = right->next;
            }
        }
        while (left)
        {
            dummy->next = left;
            dummy = left;
            left = left->next;
        }
        while (right)
        {
            dummy->next = right;
            dummy = right;
            right = right->next;
        }
        ans = ans->next;
        return ans;
    }
    SingleNode *getMid(SingleNode *head)
    {
        SingleNode *slow = head;
        SingleNode *fast = head->next;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    SingleNode *mergeSort(SingleNode *head)
    {
        if (!head || !head->next)
            return head;
        SingleNode *mid = getMid(head);
        SingleNode *left = head;
        SingleNode *right = mid->next;
        mid->next = NULL;
        //? Sorting both halfs
        left = mergeSort(left);
        right = mergeSort(right);

        //? merge both left and right halves
        SingleNode *res = merge(left, right);
    }
};

//^ 16 Add two numbers represented by linked list
class AddTwoNums
{
private:
    /*
        Reverse both input linked lists:
            & Reverse the first linked list.
            & Reverse the second linked list.

        Create an empty result linked list:
            & Initialize pointers ans and ansHead to NULL.

        Perform digit-wise addition:
            & Traverse both reversed linked lists simultaneously.
            & While there are nodes in both linked lists:
                & Calculate the sum of the current digits from the first and second linked lists along with the carry.
                & Calculate the carry for the next iteration.
                & Create a new node with the digit obtained from the sum modulo 10.
                & Update the result linked list by appending the new node.
                & Move to the next digits in both linked lists.

        Handle remaining digits and carry:
            & While there are remaining digits in either linked list or a carry value:
                & Calculate the sum of the remaining digit and the carry.
                & Calculate the carry for the next iteration.
                & Create a new node with the digit obtained from the sum modulo 10.
                & Update the result linked list by appending the new node.
                & Move to the next remaining digit.

        Reverse the result linked list:
            & Reverse the result linked list.

        Return the result:
            & Return the head of the reversed result linked list.

           * O(N) T.C || O(1) S.C
     */
    struct SingleNode
    {
        int data;
        struct SingleNode *next;
        SingleNode(int x)
        {
            data = x;
            next = NULL;
        }
    };

public:
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

    void addNode(SingleNode *t, int data)
    {
        SingleNode *temp = new SingleNode(data);
        t->next = temp;
    }

    struct SingleNode *addTwoLists(struct SingleNode *first, struct SingleNode *second)
    {
        // code here
        first = reverseList(first);
        second = reverseList(second);
        struct SingleNode *ans = NULL;
        struct SingleNode *ansHead = NULL;
        int carry = 0;
        while (first != NULL && second != NULL)
        {
            int value = first->data + second->data + carry;
            int num = value % 10;
            carry = value / 10;
            struct SingleNode *temp = new SingleNode(num);
            if (ans == NULL)
                ansHead = temp;
            else
            {
                ans->next = temp;
            }
            ans = temp;
            first = first->next;
            second = second->next;
        }
        while (first != NULL)
        {
            int value = first->data + carry;
            int num = value % 10;
            carry = value / 10;
            struct SingleNode *temp = new SingleNode(num);
            if (ans == NULL)
                ansHead = temp;
            else
            {
                ans->next = temp;
            }
            ans = temp;
            first = first->next;
        }
        while (second != NULL)
        {
            int value = second->data + carry;
            int num = value % 10;
            carry = value / 10;
            struct SingleNode *temp = new SingleNode(num);
            if (ans == NULL)
                ansHead = temp;
            else
            {
                ans->next = temp;
            }
            ans = temp;
            second = second->next;
        }
        while (carry != 0)
        {
            int value = carry;
            int num = value % 10;
            carry = value / 10;
            struct SingleNode *temp = new SingleNode(num);
            if (ans == NULL)
                ansHead = temp;
            else
            {
                ans->next = temp;
            }
            ans = temp;
        }

        ansHead = reverseList(ansHead);
        return ansHead;
    }
};

//^ 17 split the circular linked list into two circular lists
class SplitCircularList
{
private:
    /*
        Check if the head of the list is null:
            & If the head is null, it means the list is empty. In this case, there is nothing to split, so return.

        Find the middle node:
            & Initialize two pointers, slow and fast, both pointing to the head node.
            & Move slow one step at a time and fast two steps at a time until fast reaches the end of the list or the node just before the head node.
            & The slow pointer will be at the middle node of the circular linked list.

        Split the list:
            & Set fast to slow->next to get the head of the second half of the list.
            & Set *head2_ref to fast to store the head of the second list.
            & Set slow->next to the original head node to make the first half circular.
            & Set *head1_ref to the original head node to store the head of the first list.

        Adjust the circular links:
            & Traverse the second half of the list using fast until it reaches the last node before the head node.
            & Set fast->next to *head2_ref to make the second half circular.

    ~ The algorithm uses the concept of slow and fast pointers to find the middle of the circular linked list. It then manipulates the pointers to split the list into two halves by adjusting the next pointers accordingly. The resulting lists are still circular linked lists, but they represent the first and second halves of the original circular linked list.
    * O(N) T.C | O(1) S.C
     */
    struct SingleNode
    {
        int data;
        struct SingleNode *next;

        SingleNode(int x)
        {
            data = x;
            next = NULL;
        }
    };

public:
    void splitList(SingleNode *head, SingleNode **head1_ref, SingleNode **head2_ref)
    {
        if (!head)
        {
            return;
        }
        SingleNode *slow = head;
        SingleNode *fast = head->next;
        while (fast != head && fast->next != head)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        fast = slow->next;
        *head2_ref = fast;
        slow->next = head;
        *head1_ref = head;
        while (fast->next != head)
        {
            fast = fast->next;
        }
        fast->next = *head2_ref;
    }
};

//^ 18 Deletion in a circular LL
class deletionInCircularLL
{
    struct SingleNode
    {
        int data;
        struct SingleNode *next;
    };

public:
    void deleteNode(struct SingleNode **head, int key)
    {

        // Your code goes here
        SingleNode *prev = NULL;
        SingleNode *curr = *head;
        while (curr->data != key)
        {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        curr->next = NULL;
        delete curr;
    }

    /* Function to reverse the linked list */
    void reverse(struct SingleNode **head_ref)
    {
        SingleNode *prev = NULL, *curr = *head_ref;
        while (curr->next)
        {
            SingleNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        curr->next = prev;
        *head_ref = prev;
    }
};

//^ 19 Reverse a doubly linked list
class ReverseDLL
{
private:
    struct SingleNode
    {
        int data;
        SingleNode *next;
        SingleNode *prev;
        SingleNode(int x)
        {
            data = x;
            next = NULL;
            prev = NULL;
        }
    };

public:
    /*
    & Check if the head of the list is null or if it has only one node:

  ~   If the head is null or if it has only one node, it means the list is empty or already reversed, so return the head as it is.

& Initialize variables:

 ~    Create two pointers, temp and curr, and set them both to the head of the list.
 ~    temp will be used to traverse the list, and curr will be used to keep track of the current node.

& Reverse the list:

  ~   Enter a loop that continues until temp becomes null.
  ~   Inside the loop:
    & Update the curr pointer to temp.
    & Move temp to the next node in the original list.
    & Swap the prev and next pointers of the curr node to reverse the links of the current node.
    & Repeat these steps until temp reaches the end of the original list.

& Update the head:

 ~    After the loop ends, the curr pointer will be pointing to the last node of the original list, which will be the new head of the reversed list.
    Update the head pointer to point to the new head node.

& Return the head of the reversed list.

~ The algorithm iterates through the doubly linked list and reverses the links of each node by swapping the prev and next pointers. It starts with the initial head and moves forward until the end of the list, updating the pointers along the way. Finally, it returns the new head of the reversed list.
     */

    SingleNode *reverseDLL(SingleNode *head)
    {
        // Your code here
        if (!head || !head->next)
        {
            return head;
        }
        SingleNode *temp = head;
        SingleNode *curr = head;
        while (temp)
        {
            curr = temp;
            temp = temp->next;
            swap(curr->prev, curr->next);
        }
        head = curr;
        return head;
    }
};

//^ 20 find pairs whose sum is equal to x in a sorted doubly linked list
class FindPair
{
private:
    /*
    ~    Initialize two pointer variables to find the candidate elements in the sorted doubly linked list. Initialize first with the start of the doubly linked list i.e; first=head and initialize second with the last node of the doubly linked list i.e; second=last_node.
 ~   We initialize first and second pointers as first and last nodes. Here we don’t have random access, so to find the second pointer, we traverse the list to initialize the second.
 ~   If current sum of first and second is less than x, then we move first in forward direction. If current sum of first and second element is greater than x, then we move second in backward direction.
  ~  Loop termination conditions are also different from arrays. The loop terminates when two pointers cross each other (second->next = first), or they become the same (first == second).
 ~   The case when no pairs are present will be handled by the condition “first==second”

 * O(N) T.C || O(1) S.C

 ! O(N^2) Solution can be achieved by traversing the list in a nested loop

 & Hashmaps can also be used to find pairs in O(N) Time but they will require extra O(N) Space to store all the data
     */
public:
    // structure of node of doubly linked list
    struct SingleNode
    {
        int data;
        struct SingleNode *next, *prev;
    };

    // Function to find pair whose sum equal to given value x.
    void pairSum(struct SingleNode *head, int x)
    {
        // Set two pointers, first to the beginning of DLL
        // and second to the end of DLL.
        struct SingleNode *first = head;
        struct SingleNode *second = head;
        while (second->next != NULL)
            second = second->next;

        // To track if we find a pair or not
        bool found = false;

        // The loop terminates when two pointers
        // cross each other (second->next
        // == first), or they become same (first == second)
        while (first != second && second->next != first)
        {
            // pair found
            if ((first->data + second->data) == x)
            {
                found = true;
                cout << "(" << first->data << ", "
                     << second->data << ")" << endl;

                // move first in forward direction
                first = first->next;

                // move second in backward direction
                second = second->prev;
            }
            else
            {
                if ((first->data + second->data) < x)
                    first = first->next;
                else
                    second = second->prev;
            }
        }

        // if pair is not present
        if (found == false)
            cout << "No pair found";
    }
};

//^ 21 Find triplets in a sorted doubly linked list whose sum is x
class FindTriplets
{
private:
    /*
    @ Method - 1 Naive
    ~ Run 3 loops and check all possibilities
    ! O(N^3) T.C | O(1) S.C

    @ Method - 2 Using hashing to optimize the naive approach
    & For the innermost loop instead of checking every possible element maintain a hash table to get the 3rd element in constant time

    & This algorithm will work for singly linked list too
    * O(N^2) T.C | O(N) S.C

    @ Method-3 Three pointers
    ~ Note this will only work for DLL not singly linked lists
   & Traverse the doubly linked list from left to right. For each current node during the traversal, initialize two pointers first = pointer to the node next to the current node and last = pointer to the last node of the list. Now, count pairs in the list from first to last pointer that sum up to value (x – current node’s data) (algorithm described in this post). Add this count to the total_count of triplets. Pointer to the last node can be found only once in the beginning.
     */
public:
    struct SingleNode
    {
        int data;
        struct SingleNode *next, *prev;
    };

    int countTripletsDLL(SingleNode *head, int x)
    {
        if (!head)
            return 0;
        SingleNode *curr, *first, *last;
        int count = 0;
        last = head;
        while (last->next)
            last = last->next;
        for (curr = head; curr != NULL; curr = curr->next)
        {
            first = curr->next;
            count += getPairs(first, last, x - curr->data);
        }
        return count;
    }

    int getPairs(SingleNode *first, SingleNode *second, int value)
    {
        int count = 0;

        //? The loop terminates when either of two pointers
        //? become NULL, or they cross each other (second->next
        //? == first), or they become same (first == second)
        while (first != NULL && second != NULL &&
               first != second && second->next != first)
        {

            // pair found
            if ((first->data + second->data) == value)
            {

                // increment count
                count++;

                // move first in forward direction
                first = first->next;

                // move second in backward direction
                second = second->prev;
            }

            //? if sum is greater than 'value'
            //? move second in backward direction
            else if ((first->data + second->data) > value)
                second = second->prev;

            // else move first in forward direction
            else
                first = first->next;
        }

        // required count of pairs
        return count;
    }
};

//^ 22 Multiply two linked lists

class MultiplyList
{
private:
    /*
    @ Building number from the linked list
 &    The code starts by initializing two variables num1 and num2 to store the numerical values represented by the linked lists l1 and l2, respectively. These variables are initially set to 0.

& The first while loop iterates through the linked list l1 and updates num1 by multiplying it by 10 and adding the current node's data value. This operation effectively appends the digit represented by the current node to num1. To avoid overflow, the value of num1 is taken modulo mod after each iteration.

& The second while loop performs the same operation for the linked list l2 and updates the variable num2 accordingly.

& Finally, the code returns the product of num1 and num2, taken modulo mod. This ensures that the result is within the range of the given modular arithmetic system.

& The intuition behind this approach is to convert the linked lists into their respective numerical values by iteratively building them digit by digit. By multiplying these numerical values together and applying the modulus operation, the code efficiently calculates the product while keeping the result within the specified range.

* O(N) T.C | O(1) S.C
     */
public:
    long long mod = 1e9 + 7;
    long long multiplyTwoLists(SingleNode *l1, SingleNode *l2)
    {
        // Your code here
        long long num1 = 0;
        while (l1)
        {
            num1 = num1 * 10 + l1->val;
            num1 = num1 % mod;
            l1 = l1->next;
        }
        long long num2 = 0;
        while (l2)
        {
            num2 = num2 * 10 + l2->val;
            num2 = num2 % mod;
            l2 = l2->next;
        }
        return (num1 * num2) % mod;
    }
};

//^ 23 Flatten a linked list
class FlattenList
{
private:
    struct SingleNode
    {
        int data;
        struct SingleNode *next;
        struct SingleNode *bottom;

        SingleNode(int x)
        {
            data = x;
            next = NULL;
            bottom = NULL;
        }
    };

public:
    /*
    @ Naive approach
    & Store all the elements of the linked list into an array and sort them
    & then return the new list made from this sorted array

    @ Using merging two sorted linked lists
     &   The merge function is used to merge two sorted linked lists (left and right) into a single sorted linked list.
     &   Create a dummy node temp and a pointer res to keep track of the head of the merged list.
     &   Iterate through both left and right lists simultaneously until either one of them reaches the end.
    &    Compare the data of the current nodes in left and right. If the data in left is smaller, add the left node to the merged list, update temp, and move left to the next node in its list.
    &    If the data in right is smaller or equal, add the right node to the merged list, update temp, and move right to the next node in its list.
     &   Continue this process until one of the lists reaches the end.
    &    If there are any remaining nodes in either left or right, append them to the merged list.
    &    Return the bottom pointer of the res node, which points to the head of the merged list.

    &The flatten function recursively flattens the given hierarchical linked list by following these steps:

    &    If the given root node is either NULL or it has no next node, return the root itself (base case for recursion).
    &    Recursively flatten the rest of the linked list starting from root->next by calling flatten(root->next).
    &    Update the root node to point to the merged list of root and root->next by calling the merge function.
        Return the updated root.

~    The intuition behind this approach is to divide the problem into subproblems by recursively flattening the linked list and merging them in a sorted manner using the merge function. This approach leverages the merging property of the sorted linked lists to efficiently flatten the entire hierarchical linked list.

~    The time complexity of this code is O(N * M), where N is the total number of nodes in the linked list and M is the number of levels in the hierarchy. The space complexity is O(1) since the operations are performed in-place without using any additional data structures.
     */
    SingleNode *merge(SingleNode *left, SingleNode *right)
    {
        SingleNode *temp = new SingleNode(0);
        SingleNode *res = temp;
        while (left && right)
        {
            if (left->data < right->data)
            {
                temp->bottom = left;
                temp = temp->bottom;
                left = left->bottom;
            }
            else
            {
                temp->bottom = right;
                temp = temp->bottom;
                right = right->bottom;
            }
        }
        if (left)
            temp->bottom = left;
        else
            temp->bottom = right;
        return res->bottom;
    }
    SingleNode *flatten(SingleNode *root)
    {
        if (!root || !root->next)
            return root;
        root->next = flatten(root->next);
        root = merge(root, root->next);

        return root;
    }
};

//^ 24 Segregate even and odd numbers in a linked list
/*
& This code is a function that takes in an integer `N` and a pointer to the head of a linked list `head` as arguments. The function segregates the even and odd numbers in the linked list by rearranging the nodes such that all even nodes come before all odd nodes. The original relative order of the nodes within each of the even and odd segments is maintained.

& The function first checks if the linked list is empty or has only one node, in which case it returns the head of the list. Then, it initializes two pointers `oddList` and `evenList` to `NULL`. These pointers will be used to keep track of the first odd and even nodes in the list, respectively.

& Next, the function checks if the data in the head node is even or odd. If it is even, it sets `evenList` to point to the head node and then iterates through the list using a while loop to find the first odd node. If it finds an odd node, it sets `oddList` to point to that node and breaks out of the loop. If the data in the head node is odd, it sets `oddList` to point to the head node and then iterates through the list using a while loop to find the first even node. If it finds an even node, it sets `evenList` to point to that node and breaks out of the loop.

& After finding the first odd and even nodes, the function checks if either of them is `NULL`. If `evenList` is `NULL`, it returns `oddList`. If `oddList` is `NULL`, it returns `evenList`.

& If both `oddList` and `evenList` are not `NULL`, the function initializes two more pointers `prevO` and `prevE` to point to `oddList` and `evenList`, respectively. It then iterates through the list again using a while loop. For each node, if its data is even and it is not equal to `evenList`, it sets the next pointer of `prevE` to point to that node and updates `prevE` to point to that node. If its data is odd and it is not equal to `oddList`, it sets the next pointer of `prevO` to point to that node and updates `prevO` to point to that node.

& After iterating through all nodes, the function sets the next pointer of `prevO` to `NULL`, effectively terminating the odd list. It then sets the next pointer of `prevE` to point to `oddList`, effectively concatenating the even and odd lists. Finally, it returns `evenList`.

& The time complexity of this function is O(N) since it iterates through all N nodes in the linked list twice. The space complexity is O(1) since it uses a constant number of pointers.

 */
SingleNode *divide(int N, SingleNode *head)
{
    // code here
    if (!head || !head->next)
        return head;
    SingleNode *oddList = NULL, *evenList = NULL;
    if (head->val % 2 == 0)
    {
        evenList = head;
        SingleNode *curr = head;
        while (curr)
        {
            if (curr->val % 2 != 0)
            {
                oddList = curr;
                break;
            }
            curr = curr->next;
        }
    }
    else
    {
        oddList = head;
        SingleNode *curr = head;
        while (curr)
        {
            if (curr->val % 2 == 0)
            {
                evenList = curr;
                break;
            }
            curr = curr->next;
        }
    }

    if (evenList == NULL)
        return oddList;
    else if (oddList == NULL)
        return evenList;

    SingleNode *prevO = oddList, *prevE = evenList;
    SingleNode *curr = head;
    while (curr)
    {
        if (curr->val % 2 == 0 && curr != evenList)
        {
            prevE->next = curr;
            prevE = curr;
        }
        else if (curr->val % 2 != 0 && curr != oddList)
        {
            prevO->next = curr;
            prevO = curr;
        }
        curr = curr->next;
    }
    prevO->next = NULL;
    prevE->next = oddList;
    return evenList;
}

//^ 25 Nth SingleNode from the linked list
/*

& The function first initializes a pointer x to point to the head of the linked list.

& Then, it enters a while loop that iterates through the list until x becomes NULL. Inside the loop, it checks if n is non-zero. If it is, it decrements n by 1. If n is zero, it updates h to point to its next node. Then, it updates x to point to its next node.

& After the while loop, the function checks if n is non-zero. If it is, it means that the value of n was greater than the length of the linked list, so the function returns -1. Otherwise, it returns the data of the node pointed to by h.

~ The intuition behind this code is that it uses two pointers, x and h, to traverse the linked list. Pointer x starts at the head of the list and moves forward one node at a time. Pointer h also starts at the head of the list but only starts moving forward after pointer x has moved forward n nodes. This way, when pointer x reaches the end of the list, pointer h will be pointing to the nth node from the end of the list.

* The time complexity of this function is O(N) since it iterates through all N nodes in the linked list once. The space complexity is O(1) since it uses a constant number of pointers.
 */

//^ 26 First non-repeating character in a stream
/*
* T.C O(26 * n)
* S.C O(26)

&   The solve function takes a string str as input and returns the modified string as the result.
&   It initializes a queue named q, an empty string named ans, and an array freq of size 26, which represents the frequencies of characters from 'a' to 'z'.
&   It iterates through each character in the input string str.
&   For each character, it increments its frequency in the freq array and adds the    character to the queue.
&   It then enters a while loop that processes the characters in the queue to find the first non-repeating character.
&   Inside the while loop, it checks if the frequency of the character at the front of the queue is greater than 1.
&   If the frequency is greater than 1, it means the character is repeating, so it is removed from the queue using q.pop().
&   If the frequency is 1, it means it is the first non-repeating character encountered so far. In this case, the character is appended to the ans string using ans.push_back(q.front()), and the loop is terminated using break.
&   If the queue becomes empty after processing all the characters, it means that there are no non-repeating characters encountered so far. In this case, a '#' character is appended to the ans string using ans.push_back('#').
Finally, the modified string ans is returned as the result of the solve function. */

class FirstCharacter
{
public:
    string solve(string str)
    {
        queue<char> q;
        string ans = "";
        int freq[26] = {0};
        for (int i = 0; i < str.size(); i++)
        {
            char ch = str[i];
            freq[ch - 'a']++;
            q.push(ch);
            while (!q.empty())
            {
                if (freq[q.front() - 'a'] > 1)
                {
                    q.pop();
                }
                else
                {
                    ans.push_back(q.front());
                    break;
                }
            }
            if (q.empty())
            {
                ans.push_back('#');
            }
        }
        return ans;
    }
    string FirstNonRepeating(string A)
    {
        // Code here
        return solve(A);
    }
};

//^ 27 Delete greater nodes at the right
class DeleteGreaterNodes
{
public:
    /*
    @ Stack based solution
    & The function first creates a new node tmp with a large data value (1e8) and initializes an empty stack s of pointers to nodes. It then pushes pointer tmp onto stack s.

& Next, it enters a for loop that iterates through all nodes in the linked list starting from the head. Inside this loop, it enters another while loop that continues until the data of the top element of stack s is greater than or equal to the data of node temp. Inside this inner loop, it pops the top element from stack s. It then sets the next pointer of the top element of stack s to point to node temp and pushes pointer temp onto stack s.

& After both loops, the function returns the next pointer of node tmp, which represents the head of the new linked list.

~ The key idea behind this code is that it uses a stack to keep track of nodes whose value is greater than or equal to the value of any node to their right. In each iteration of the for loop, it visits a node and checks if its value is greater than the value of any node on stack s. If it is, it pops these nodes from stack s until it finds a node whose value is greater than or equal to its own value. It then sets the next pointer of this node to point to itself and pushes itself onto stack s. This way, all nodes whose value is smaller than the value of any node to their right are removed from the linked list.

! The time complexity of this function is O(N) since it visits all N nodes in the linked list once. The space complexity is O(N) since it uses a stack that can store up to N nodes.
     */
    SingleNode *compute(SingleNode *head)
    {
        SingleNode *tmp = new SingleNode(1e8);
        stack<SingleNode *> s;
        s.push(tmp);
        for (SingleNode *temp = head; temp; temp = temp->next)
        {
            while (s.top()->val < temp->val)
                s.pop();
            s.top()->next = temp;
            s.push(temp);
        }
        return tmp->next;
    }

    /*
    @ Reversing the list
&    The compute function takes in a pointer to the head of a singly linked list head as an argument and returns a pointer to the head of a new linked list where all nodes whose value is smaller than the value of any node to their right have been deleted.

& The function first calls the reverse function with argument head to reverse the order of nodes in the linked list. It then enters a for loop that iterates through all nodes in the reversed linked list starting from the head. Inside this loop, it checks if the data of node temp is greater than the data of its next node. If it is, it sets its next pointer to point to its next next node. Otherwise, it updates pointer temp to point to its next node.

& After the for loop, the function calls the reverse function again with argument head to reverse the order of nodes in the linked list back to their original order. It then returns this result.

~ The key idea behind this function is that it first reverses the order of nodes in the linked list, then iterates through all nodes in this reversed linked list and removes any node whose value is smaller than the value of its next node. Finally, it reverses the order of nodes in the linked list again to obtain a new linked list where all nodes whose value is smaller than the value of any node to their right have been deleted.

* The time complexity of this function is O(N) since it calls the reverse function twice (which has time complexity O(N)) and iterates through all N nodes in the linked list once. The space complexity is O(1) since it uses a constant number of pointers.
     */
    SingleNode *reverse(SingleNode *h)
    {
        SingleNode *prev = NULL, *n = h;
        while (n)
        {
            SingleNode *tmp = n;
            n = n->next;
            tmp->next = prev;
            prev = tmp;
        }
        return prev;
    }
    SingleNode *compute_v2(SingleNode *head)
    {
        head = reverse(head);
        for (SingleNode *temp = head; temp && temp->next;)
        {
            if (temp->val > temp->next->val)
                temp->next = temp->next->next;
            else
                temp = temp->next;
        }
        return reverse(head);
    }
    /*
    @ Recursive

     */
    SingleNode *compute(SingleNode *head)
    {
        if (!head->next)
            return head;
        head->next = compute(head->next);
        return (head->val < head->next->val) ? head->next : head;
    }
};
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
