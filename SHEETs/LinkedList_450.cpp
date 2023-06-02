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
int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
