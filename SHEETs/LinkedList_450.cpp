#include <bits/stdc++.h>
using namespace std;

struct SingleNode
{
    int val;
    SingleNode *next;
    SingleNode(int x = 0)
    {
        val = x;
        next = nullptr;
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
    //     while (curr != nullptr)
    //     {
    //         temp.push_back(curr->val);
    //         curr = curr->next;
    //     }
    //     reverse(temp.begin(), temp.end());
    //     curr = head;
    //     int i = 0;
    //     while (curr != nullptr)
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
        if (!head || head->next == nullptr)
            return head;
        SingleNode *temp = nullptr;
        while (head != nullptr)
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
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
