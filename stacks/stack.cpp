#include <bits/stdc++.h>
using namespace std;

/* stack implementation using arrays */
// struct MyStack{
//     int *arr;
//     int cap;
//     int top;
//     MyStack(int c){
//         cap = c;
//         arr = new int[cap];
//         top = -1;
//     }
//     void push(int x){
//         if (top == (cap-1))
//         {
//             cout << "stack overflow !!!"<<endl;
//             return;
//         }

//         top++;
//         arr[top] = x;
//     }
//     int pop(void){
//         int res = arr[top];
//         top--;
//         return res;
//     }
//     int peek(void){
//         return arr[top];
//     }
//     int size(){
//         return (top+1);
//     }
//     bool isEmpty(void){
//         return (top==-1);
//     }
// };

/* implementation of stack using linked list */
struct Node
{
    int data;
    Node *next;
    Node(int d)
    {
        data = d;
        next = NULL;
    }
};

class MyStack
{
public:
    Node *head;
    int sz;
    int currentMinimum;
    stack<int> minimum;
    MyStack()
    {
        head = NULL;
        sz = 0;
        currentMinimum = INT_MAX;
        minimum.push(currentMinimum);
    }
    void push(int x)
    {
        Node *temp = new Node(x);
        temp->next = head;
        head = temp;
        sz++;
        currentMinimum = min(currentMinimum, x);
        if (currentMinimum != minimum.top() || minimum.empty())
            minimum.push(currentMinimum);
    }
    int pop()
    {
        if (head == NULL)
            return UINT16_MAX;
        if (head->data == currentMinimum)
        {
            minimum.pop();
            currentMinimum = minimum.top();
        }
        int res = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        sz--;
        return res;
    }
    inline int size() { return sz; }
    inline bool isEmpty() { return sz == 0 || head == NULL; }
    inline int peek()
    {
        if (head == NULL)
            return UINT16_MAX;
        return head->data;
    }
    inline int getMin(void);
};

/* ------------Applications of stacks-------------
    ⇀function calls
    ⇀checking for balanced parenthesis
    ⇀reversing items
    ⇀infix to prefix/postfix
    ⇀evaluation of postfix/prefix
    ⇀ stock span problem and its variations
    ⇀ undo/redo OR forward/backward
                                    */

/* balanced parenthesis  */
// bool isMatching(char a,char b){
//     return ((a=='('&&b==')'))||((a=='{'&&b=='}'))||((a=='['&&b==']'));
// }
// bool isBalanced(string str){
//     stack<char> s;
//     for (int i = 0; i < str.length(); i++)
//     {
//         if(str[i]=='c'||str[i]=='{'||str[i]=='[')
//             s.push(str[i]);
//         else{
//             if(s.empty())
//                 return false;
//             else if (isMatching(s.top(),str[i]) == false)
//             {
//                 return false;
//             }
//             else
//                 s.pop();

//         }
//     }
//     return (s.empty()==true);

// }

/* implement two stacks in an array*/
// class TwoStacks{
//     public:
//     int arr[]
//     void push1();
//     void push2();
//     // ... for every stack operation
// };

/* optimized space sol */
// struct TwoStacks{
//     int* arr , cap , top1,top2;
//     TwoStacks(int n){
//         cap = n;
//         top1 = -1;
//         top2 = cap;
//         arr = new int[n];
//     }
//     void push(int x){
//         if (top1<top2-1)
//         {
//             top1++; arr[top1]=x;
//         }

//     }
//     void push2(int x){
//         if(top1<top2-1){
//             top2--;
//             arr[top2] = x;
//         }
//     }
//     int pop1(){
//         if(top1>=0){
//             int x = arr[top1];
//             top1--;
//             return x;
//         }
//         else{
//             return; //exit(1);
//         }
//     }
//     int pop2(){
//         if(top2<cap){
//             int x = arr[top1];
//             top2++;
//             return x;
//         }
//         else{
//             return; //exit(1);
//         }
//     }
// };

/* implement K stacks in an array */
// class Kstacks
// {
// private:
// public:
//     int *arr, *top, *next;
//     unsigned int k, capacity;
//     int freeTop;
//     Kstacks(unsigned k1, unsigned n)
//     {
//         k = k1;
//         capacity = n;
//         arr = new int[capacity];
//         top = new int[k];
//         next = new int[capacity];
//         for (int i = 0; i < k; i++)
//         {
//             top[i] = -1;
//         }
//         freeTop = 0;
//         for (int i = 0; i < capacity - 1; i++)
//         {
//             next[i] = i + 1;
//         }
//         next[capacity - 1] = -1;
//     }
//     void push(int x, int stackNum)
//     {
//         int i = freeTop;
//         freeTop = next[i];
//         next[i] = top[stackNum];
//         top[stackNum] = i;
//         arr[i] = x;
//     }
//     int pop(int stackNum){
//         int i = top[stackNum];
//         top[stackNum] = next[i];
//         next[i] = freeTop;
//         freeTop = i;
//         return arr[i];
//     }
// };

/* stock span problem */
// O(n^2)
//  void printSpan(vector<int> &arr){
//      for (int i = 0; i < arr.size(); i++)
//      {
//          int span = 1;
//          for (int j = i-1 - 1; j >= 0 && (arr[j]<=arr[i]); j--)
//          {
//              span++;
//          }
//          cout<<span<< " ";
//      }
//  }

// O(n) space and time
//  void printSpan_v2(vector<int> &arr){
//      //span = index of current element - index of closest greater element than current
//      if(arr.empty())return;
//      stack<int> s;
//      s.push(0); //storing index in the stack
//      cout<<1<<" ";
//      for (int i = 1; i < arr.size(); i++)
//      {
//          while (s.empty()==false && arr[s.top()]<=arr[i])
//          {
//              /* code */
//              s.pop();
//          }
//         int span = s.empty()?i+1:i-s.top();
//          cout<<span<<" ";
//          s.push(i);
//      }

// }

/* previous greater element */
// void printPrevGreater(vector<int> &arr)
// {
//     stack<int> s;
//     s.push(arr[0]);
//     cout << 1 << " ";
//     for (int i = 0; i < arr.size(); i++)
//     {
//         while (!s.empty() && s.top() <= arr[i])
//         {
//             s.pop();
//         }
//         (s.empty()) ? cout << -1 << " " : cout << s.top() << " ";
//         s.push(arr[i]);
//     }
// }

/* Next greater element */
// O(n^2) time and O(1) space
//  void printNextGreater(vector<int> &arr)
//  {
//      for (int i = 0; i < arr.size(); i++)
//      {
//          int j;
//          for (j = i + 1; j < arr.size(); j++)
//          {
//              if (arr[j] > arr[i])
//              {
//                  cout << arr[j] << " ";
//                  break;
//              }
//          }
//          if (j == arr.size() - 1)
//          {
//              cout << -1 << " ";
//              return;
//          }
//      }
//      return;
//  }

// O(n) time

// void printNextGreater_v2(vector<int> &arr){
// vector<int> output;
//     stack<int> s;
//     s.push(arr.back());
//     for (int i = arr.size() - 2; i >= 0; i--)  //reverse traversal such that the next greater element becomes previous greater element
//     {
//         while (!s.empty() && s.top()<=arr[i]) //same code as previous greater element
//         {
//             s.pop();
//         }
//         int nextGreater = (s.empty())?-1:s.top();
//         cout<<nextGreater<<" ";
// output.push_back(nextGreater);
//         s.push(arr[i]);
//     }
// reverse(output.begin(),output.end());
// prints the output in reverse order...
// }

/* Largest rectangular area in a histogram
method-1: O(n^2) time and O(1) space*/
// method-1 : assume every element of the array as the smallest and find the corresponding rect area on both L-R side.
// int largestRecArea(vector<int> &arr)
// {
//     int res = 0;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         int curr = arr[i];
//         for (int j = i - 1; j >= 0; j--) // finding elements that are greater or equal to arr[i]
//         {
//             if (arr[j] >= arr[i]) // adding area (smallest element area is added till  we find an element smaller than the current smallest)
//                 curr += arr[i];
//             else
//                 break;
//         }
//         for (int j = i + 1; j < arr.size(); j++)
//         {
//             if (arr[j] >= arr[i])
//             {
//                 curr += arr[i];
//             }
//             else
//             {
//                 break;
//             }
//         }
//         res = max(res, curr);
//     }
//     return res;
// }

// method - 2 : O(n) time and space
// initialize res = 0;
// find previous smaller element for every element.
// find next smaller element for every element
// // Do following for every element arr[i]
//         curr = arr[i];
//         curr+=(i-pos[i]-1)*arr[i]
//         res = max(res,curr);
//     return res;

// method-3: O(n) time with single traversal
// int largestRecArea_v2(vector<int> &arr)
// {
//     stack<int> s;
//     int res = INT16_MIN;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         while (!s.empty() && s.top() >= arr[i])
//         {
//         int tp = s.top();
//         s.pop();
//         int curr = arr[tp]*(s.empty())?i:(i-s.top()-1);
//         res = max(res,curr);
//         }
//         s.push(i);
//     }
//     while (s.empty()==false)
//     {
//         int tp = s.top();
//         s.pop();
//         int curr = arr[tp]*(s.empty())?arr.size():(arr.size()-s.top()-1);
//         res = max(res,curr);
//     }
//     return res;

// }

// /* largest rectangle with 1s O(RxC) */
// int largestRectWith1s(vector<vector<int>> &binMat){
//     unsigned int R = binMat.size();
//     unsigned int C = binMat[0].size();
//     int res = largestRecArea_v2(binMat[0]);
//     for (int i = 1; i < R; i++)
//     {
//         // vector<int> temp(R);
//         for (int j = 0; j < C; j++)
//         {
//             if(binMat[i][j] == 1)
//                 binMat[i][j]+=binMat[i-1][j];
//         }
//         res = max(res,largestRecArea_v2(binMat[i]));

//     }
//     cout<<res;
//     return res;
// }

/* stack with getMin function */
// inline int MyStack::getMin(void){
//     return currentMinimum;
// }

/* Infix postfix and prefix notations
    infix : x+y
    postfix: xy+
    prefix: +xy

    Advantages of Prefix and Postfix
    ✳Do not require parenthesis,precedence rules and associativity rules
    ✳Can be evaluated by writing a program that traverses the given expression exactly once

    ^   --> right to left
    *,/ --> left to right
    +,- --> left to right */

// ^provides precdence for operators
int prec(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

//? The main function to convert infix
// ?expression to postfix expression
/* void infixToPostfix(string s)
{
    stack<char> st;
    st.push('N');

    int l = s.length();

    string ns;

    for (int i = 0; i < l; i++)
    {
        // If the scanned character is an operand,
        // add it to output string.
        if ((s[i] >= 'a' && s[i] <= 'z') ||
            (s[i] >= 'A' && s[i] <= 'Z'))
            ns += s[i];
        // If the scanned character is an ‘(‘,
        // push it to the stack.
        else if (s[i] == '(')

            st.push('(');

        // If the scanned character is an ‘)’,
        // pop and to output string from the stack
        // until an ‘(‘ is encountered.
        else if (s[i] == ')')
        {
            while (st.top() != 'N' && st.top() != '(')
            {
                char c = st.top();
                st.pop();

                ns += c;
            }
            if (st.top() == '(')
            {
                char c = st.top();
                st.pop();
            }
        }

        // If an operator is scanned
        else
        {
            while (st.top() != 'N' && prec(s[i]) <= prec(st.top()))
            {
                char c = st.top();
                st.pop();
                ns += c;
            }

            st.push(s[i]);
        }
    }

    // Pop all the remaining elements from the stack
    while (st.top() != 'N')
    {
        char c = st.top();
        st.pop();
        ns += c;
    }

    cout << ns << endl;
}
 */
/*


    ~Create a stack to store operands (or values).
    ~Scan the given expression and do following for every scanned element.
    ~If the element is a number, push it into the stack.
    ~If the element is an operator, pop operands for the operator from the stack. Evaluate the operator and push the result back to the stack.
    ~When the expression is ended, the number in the stack is the final answer.
 */

   int evaluatePostfix(string &S)
    {
        // Your code here    
         stack<int> s;
       for (int i=0; i<S.size(); i++){
           if (S[i]>='0' && S[i]<='9'){
               s.push(S[i]-'0');
           }
           else{
               int a=s.top();
               s.pop();
               int b=s.top();
               s.pop();
               if (S[i]=='*'){
                   s.push(b*a);
               }
               else if (S[i]=='/'){
                   s.push(b/a);
               }
               else if (S[i]=='+'){
                   s.push(a+b);
               }
               else if (S[i]=='-'){
                   s.push(b-a);
               }
           }
       }
       return s.top();
    }


/* INFIX TO PREFIX 
*/
bool isOperator(char c)
{
    return (!isalpha(c) && !isdigit(c));
}

int getPriority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    return 0;
}

string infixToPostfix(string infix)
{
    infix = '(' + infix + ')';
    int l = infix.size();
    stack<char>  char_stack;
    string output;

    for (int i = 0; i < l; i++) {

        // If the scanned character is an
        // operand, add it to output.
        if (isalpha(infix[i]) || isdigit(infix[i]))
            output += infix[i];

        // If the scanned character is an
        // ‘(‘, push it to the stack.
        else if (infix[i] == '(')
            char_stack.push('(');

        // If the scanned character is an
        // ‘)’, pop and output from the stack
        // until an ‘(‘ is encountered.
        else if (infix[i] == ')') {
            while (char_stack.top() != '(') {
                output += char_stack.top();
                char_stack.pop();
            }

            // Remove '(' from the stack
            char_stack.pop();
        }

        // Operator found
        else 
        {
            if (isOperator(char_stack.top())) 
            {
                if(infix[i] == '^')
                {
                      while (getPriority(infix[i]) <= getPriority(char_stack.top()))
                       {
                         output += char_stack.top();
                         char_stack.pop();
                       }
                    
                }
                else
                {
                    while (getPriority(infix[i]) < getPriority(char_stack.top()))
                       {
                         output += char_stack.top();
                         char_stack.pop();
                       }
                    
                }

                // Push current Operator on stack
                char_stack.push(infix[i]);
            }
        }
    }
      while(!char_stack.empty()){
          output += char_stack.top();
        char_stack.pop();
    }
    return output;
}

string infixToPrefix(string infix)
{
    /* Reverse String
     * Replace ( with ) and vice versa
     * Get Postfix
     * Reverse Postfix  *  */
    int l = infix.size();

    // Reverse infix
    reverse(infix.begin(), infix.end());

    // Replace ( with ) and vice versa
    for (int i = 0; i < l; i++) {

        if (infix[i] == '(') {
            infix[i] = ')';
        }
        else if (infix[i] == ')') {
            infix[i] = '(';
        }
    }

    string prefix = infixToPostfix(infix);

    // Reverse postfix
    reverse(prefix.begin(), prefix.end());

    return prefix;
}


int main(int argc, char const *argv[])
{
    // vector<int> temp = {6, 2, 5, 4, 1, 5, 6};
    // vector<vector<int>> binMatrix = {{0,1,1,0},{1,1,1,1},{1,1,1,1},{1,1,0,0}};
    // printSpan_v2(temp);
    // printPrevGreater(temp);
    // printNextGreater(temp);
    // cout<<previousSmaller(temp);
    // cout<<largestRecArea_v2(temp);
    // cout<<largestRectWith1s(binMatrix);
    // cout<<evalPostfix("231*+9-");

    /* stack custom */
    // MyStack s;
    // s.push(10);
    // s.push(20);
    // s.push(30);
    // cout<<s.getMin()<<endl;
    // cout<<s.pop()<<endl;
    // s.push(-2);
    // cout<<s.getMin()<<endl;
    // cout<<s.pop()<<endl;
    // cout<<s.getMin()<<endl;
    return 0;
}
