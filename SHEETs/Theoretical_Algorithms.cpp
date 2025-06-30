#include<bits/stdc++.h>
using namespace std;

class SortingAlgorithms
{
public:
    // Bubble Sort
    // Time Complexity: O(n^2)
    // Repeatedly swaps adjacent elements if they are in the wrong order
    static void bubbleSort(std::vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break; // If no elements were swapped, the array is already sorted
        }
    }

    // Selection Sort
    // Time Complexity: O(n^2)
    // Repeatedly selects the minimum element and places it at the correct position
    static void selectionSort(std::vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[minIndex])
                {
                    minIndex = j;
                }
            }
            std::swap(arr[i], arr[minIndex]);
        }
    }

    // Insertion Sort
    // Time Complexity: O(n^2)
    // Builds a sorted section of the array element by element
    static void insertionSort(std::vector<int> &arr)
    {
        int n = arr.size();
        for (int i = 1; i < n; i++)
        {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Merge Sort
    // Time Complexity: O(n log n)
    // Divide and conquer approach, recursively splits the array and merges sorted halves
    static void mergeSort(std::vector<int> &arr)
    {
        if (arr.size() <= 1)
            return;
        mergeSortRecursive(arr, 0, arr.size() - 1);
    }

private:
    // Helper function for Merge Sort
    static void mergeSortRecursive(std::vector<int> &arr, int left, int right)
    {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        mergeSortRecursive(arr, left, mid);
        mergeSortRecursive(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    // Merges two sorted halves of the array
    static void merge(std::vector<int> &arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<int> leftArr(n1), rightArr(n2);
        for (int i = 0; i < n1; i++)
            leftArr[i] = arr[left + i];
        for (int i = 0; i < n2; i++)
            rightArr[i] = arr[mid + 1 + i];
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (leftArr[i] <= rightArr[j])
                arr[k++] = leftArr[i++];
            else
                arr[k++] = rightArr[j++];
        }
        while (i < n1)
            arr[k++] = leftArr[i++];
        while (j < n2)
            arr[k++] = rightArr[j++];
    }

public:
    // Quick Sort
    // Time Complexity: O(n log n) on average, O(n^2) worst case
    // Divide and conquer approach, picks a pivot and partitions the array
    static void quickSort(std::vector<int> &arr)
    {
        quickSortRecursive(arr, 0, arr.size() - 1);
    }

private:
    // Helper function for Quick Sort
    static void quickSortRecursive(std::vector<int> &arr, int low, int high)
    {
        if (low < high)
        {
            int pi = partition(arr, low, high);
            quickSortRecursive(arr, low, pi - 1);
            quickSortRecursive(arr, pi + 1, high);
        }
    }

    // Partitions the array and returns the pivot index
    static int partition(std::vector<int> &arr, int low, int high)
    {
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        return i + 1;
    }

public:
    // Heap Sort
    // Time Complexity: O(n log n)
    // Sorts an array by first building a max heap and then performing heap sort
    static void heapSort(std::vector<int> &arr)
    {
        int n = arr.size();
        // Build a max heap
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, n, i);
        }
        // Extract elements from the heap one by one
        for (int i = n - 1; i > 0; i--)
        {
            std::swap(arr[0], arr[i]); // Move current root to end
            heapify(arr, i, 0);        // Call heapify on reduced heap
        }
    }

private:
    // To heapify a subtree rooted at index i, n is the size of the heap
    static void heapify(std::vector<int> &arr, int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;
        if (largest != i)
        {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }
};

// int main()
// {
//     std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

//     std::cout << "Original array:\n";
//     for (int i : arr)
//         std::cout << i << " ";
//     std::cout << "\n";

//     // Example usage: Call any sorting function
//     SortingAlgorithms::quickSort(arr);

//     std::cout << "Sorted array:\n";
//     for (int i : arr)
//         std::cout << i << " ";
//     std::cout << "\n";

//     return 0;
// }


class Stack
{
private:
    std::vector<int> elements; // Container to store the stack elements

public:
    // Push an element to the top of the stack
    void push(int value)
    {
        elements.push_back(value);
    }

    // Pop the top element from the stack
    void pop()
    {
        if (elements.empty())
        {
            std::cout << "Stack Underflow\n";
            return;
        }
        elements.pop_back();
    }

    // Return the top element without removing it
    int peek()
    {
        if (elements.empty())
        {
            std::cout << "Stack is empty\n";
            return -1; // Return a sentinel value
        }
        return elements.back();
    }

    // Check if the stack is empty
    bool isEmpty()
    {
        return elements.empty();
    }

    // Get the size of the stack
    int size()
    {
        return elements.size();
    }
};

// int main() {
//     Stack stack;
//     stack.push(10);
//     stack.push(20);
//     std::cout << "Top element is: " << stack.peek() << "\n";
//     stack.pop();
//     std::cout << "Top element after pop: " << stack.peek() << "\n";
//     return 0;
// }

class Queue {
private:
    std::list<int> elements; // Container to store the queue elements

public:
    // Enqueue (insert) an element at the back of the queue
    void enqueue(int value) {
        elements.push_back(value);
    }

    // Dequeue (remove) an element from the front of the queue
    void dequeue() {
        if (elements.empty()) {
            std::cout << "Queue Underflow\n";
            return;
        }
        elements.pop_front();
    }

    // Return the front element without removing it
    int front() {
        if (elements.empty()) {
            std::cout << "Queue is empty\n";
            return -1; // Return a sentinel value
        }
        return elements.front();
    }

    // Check if the queue is empty
    bool isEmpty() {
        return elements.empty();
    }

    // Get the size of the queue
    int size() {
        return elements.size();
    }
};

// int main() {
//     Queue queue;
//     queue.enqueue(10);
//     queue.enqueue(20);
//     std::cout << "Front element is: " << queue.front() << "\n";
//     queue.dequeue();
//     std::cout << "Front element after dequeue: " << queue.front() << "\n";
//     return 0;
// }

#include <iostream>
#include <vector>

class Heap {
private:
    std::vector<int> heap; // Container to store the heap elements

    // Helper function to heapify the tree after insertion
    void heapifyUp(int index) {
        if (index == 0) return; // Reached the root
        int parentIndex = (index - 1) / 2;
        if (heap[index] > heap[parentIndex]) {
            std::swap(heap[index], heap[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    // Helper function to heapify the tree after removal
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;

        if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        }

        if (largest != index) {
            std::swap(heap[index], heap[largest]);
            heapifyDown(largest);
        }
    }

public:
    // Insert an element into the heap
    void insert(int value) {
        heap.push_back(value); // Add the element to the end
        heapifyUp(heap.size() - 1); // Rebalance the heap
    }

    // Remove the max element from the heap
    void removeMax() {
        if (heap.empty()) {
            std::cout << "Heap Underflow\n";
            return;
        }
        heap[0] = heap.back(); // Replace the root with the last element
        heap.pop_back(); // Remove the last element
        heapifyDown(0); // Rebalance the heap
    }

    // Get the max element from the heap
    int getMax() {
        if (heap.empty()) {
            std::cout << "Heap is empty\n";
            return -1; // Return a sentinel value
        }
        return heap[0];
    }

    // Check if the heap is empty
    bool isEmpty() {
        return heap.empty();
    }

    // Get the size of the heap
    int size() {
        return heap.size();
    }
};

// int main() {
//     Heap maxHeap;
//     maxHeap.insert(30);
//     maxHeap.insert(20);
//     maxHeap.insert(50);
//     std::cout << "Max element is: " << maxHeap.getMax() << "\n";
//     maxHeap.removeMax();
//     std::cout << "Max element after removal: " << maxHeap.getMax() << "\n";
//     return 0;
// }


#include <iostream>
#include <stack>
#include <algorithm> // for reverse
#include <cctype>    // for isalnum (to check if it's a digit or letter)
/* 
Definitions:

    Infix Expression: The operator is written between operands. Example: A + B.
    Prefix Expression: The operator is written before the operands. Example: + A B.
    Postfix Expression: The operator is written after the operands. Example: A B +.

Conversion Steps:

    Infix to Prefix:
        Reverse the infix expression.
        Replace '(' with ')' and vice-versa.
        Convert the reversed expression to postfix.
        Reverse the postfix expression to get the prefix.

    Infix to Postfix:
        Use a stack to keep track of operators.
        Output operands directly.
        Apply operator precedence and associativity to output the operators in the correct order.

Helper Functions

We need a few helper functions to assist in the conversion process:

    Precedence: Determines the precedence of operators.
    Associativity: Determines if the operator is left-to-right or right-to-left associative.
    isOperator: Checks if a character is an operator.
    isOperand: Checks if a character is an operand.



    Infix to Postfix Conversion:

    Use a stack to hold operators and manage precedence. Pop operators from the stack when their precedence is greater or equal to the current operator.

    Infix to Prefix Conversion:

        Reverse the infix expression, convert it to postfix, and reverse the result to obtain the prefix expression.

    Postfix to Infix Conversion:

        Use a stack to store operands. When encountering an operator, pop two operands, and create an infix expression by placing the operator between them.

    Prefix to Infix Conversion:

        Similar to postfix-to-infix but starts from the rightmost character.

    Postfix to Prefix Conversion:

        Using a stack, combine two operands with an operator and push the result back onto the stack.

    Prefix to Postfix Conversion:

        Iterate through the prefix expression from right to left and apply operators to operands when necessary, storing the result back on the stack.

 */
// Helper function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3; // Exponent has the highest precedence
    return 0;
}

// Helper function to check associativity
bool isRightAssociative(char op) {
    return (op == '^'); // Exponentiation is right associative
}

// Helper function to check if the character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Helper function to check if the character is an operand
bool isOperand(char c) {
    return isalnum(c); // True if alphanumeric
}

// Convert infix expression to postfix expression
std::string infixToPostfix(const std::string& infix) {
    std::stack<char> st; // stack to hold operators
    std::string postfix; // result string

    for (char c : infix) {
        if (isOperand(c)) {
            // If it's an operand, add it directly to the output
            postfix += c;
        }
        else if (c == '(') {
            // Push opening bracket to the stack
            st.push(c);
        }
        else if (c == ')') {
            // Pop until we encounter a '('
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // Pop the '(' as well
        }
        else if (isOperator(c)) {
            // Pop higher or equal precedence operators and push the current one
            while (!st.empty() && (precedence(st.top()) > precedence(c) || 
                   (precedence(st.top()) == precedence(c) && !isRightAssociative(c)))) {
                if (st.top() == '(') break;
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    // Pop all remaining operators in the stack
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }

    return postfix;
}

// Convert infix to prefix expression
std::string infixToPrefix(const std::string& infix) {
    std::string revInfix = infix; // Create a copy of infix expression
    std::reverse(revInfix.begin(), revInfix.end());

    // Replace '(' with ')' and vice versa in the reversed expression
    for (char& c : revInfix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }

    // Convert the reversed infix expression to postfix
    std::string revPostfix = infixToPostfix(revInfix);

    // Reverse the postfix expression to get the prefix expression
    std::reverse(revPostfix.begin(), revPostfix.end());

    return revPostfix;
}

// Convert postfix to infix expression
std::string postfixToInfix(const std::string& postfix) {
    std::stack<std::string> st;

    for (char c : postfix) {
        if (isOperand(c)) {
            st.push(std::string(1, c)); // Push the operand as a string
        } else if (isOperator(c)) {
            std::string op2 = st.top(); st.pop();
            std::string op1 = st.top(); st.pop();
            std::string expr = "(" + op1 + c + op2 + ")";
            st.push(expr);
        }
    }

    return st.top(); // The final expression will be in the stack
}

// Convert prefix to infix expression
std::string prefixToInfix(const std::string& prefix) {
    std::stack<std::string> st;

    for (int i = prefix.size() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isOperand(c)) {
            st.push(std::string(1, c));
        } else if (isOperator(c)) {
            std::string op1 = st.top(); st.pop();
            std::string op2 = st.top(); st.pop();
            std::string expr = "(" + op1 + c + op2 + ")";
            st.push(expr);
        }
    }

    return st.top();
}

// Convert postfix to prefix expression
std::string postfixToPrefix(const std::string& postfix) {
    std::stack<std::string> st;

    for (char c : postfix) {
        if (isOperand(c)) {
            st.push(std::string(1, c));
        } else if (isOperator(c)) {
            std::string op2 = st.top(); st.pop();
            std::string op1 = st.top(); st.pop();
            std::string expr = c + op1 + op2;
            st.push(expr);
        }
    }

    return st.top();
}

// Convert prefix to postfix expression
std::string prefixToPostfix(const std::string& prefix) {
    std::stack<std::string> st;

    for (int i = prefix.size() - 1; i >= 0; i--) {
        char c = prefix[i];
        if (isOperand(c)) {
            st.push(std::string(1, c));
        } else if (isOperator(c)) {
            std::string op1 = st.top(); st.pop();
            std::string op2 = st.top(); st.pop();
            std::string expr = op1 + op2 + c;
            st.push(expr);
        }
    }

    return st.top();
}

// int main() {
//     std::string infix = "(A-B/C)*(A/K-L)";

//     std::cout << "Infix: " << infix << "\n";
//     std::string postfix = infixToPostfix(infix);
//     std::cout << "Postfix: " << postfix << "\n";
//     std::string prefix = infixToPrefix(infix);
//     std::cout << "Prefix: " << prefix << "\n";

//     // Convert back to infix
//     std::cout << "Postfix to Infix: " << postfixToInfix(postfix) << "\n";
//     std::cout << "Prefix to Infix: " << prefixToInfix(prefix) << "\n";

//     // Convert between postfix and prefix
//     std::cout << "Postfix to Prefix: " << postfixToPrefix(postfix) << "\n";
//     std::cout << "Prefix to Postfix: " << prefixToPostfix(prefix) << "\n";

//     return 0;
// }
