#include <bits/stdc++.h>
using namespace std;

//^ Power function recursive
// int power(int base, int exponent)
// {
//     if (exponent == 0 || base == 1 || exponent == INT8_MAX)
//     {
//         return 1;
//     }
//     int temp = power(base, exponent / 2);
//     temp *= temp;
//     if (exponent % 2 == 0)
//     {
//         return temp;
//     }
//     else
//     {
//         return temp * base;
//     }
// }

// e^x taylor expression😑😑
// double Expansion_e(int x, int terms)
// {
//     static double pow = 1;
//     static double fact = 1;
//     double r;
//     if (terms == 0)
//     {
//         return 1;
//     }
//     else
//     {
//         r = Expansion_e(x, terms - 1);
//         pow = pow * x;
//         fact = fact * terms;
//         return r + pow / fact;
//     }
// }
// Horner's rule taylor expansion
// double expansion(int x, int k)
// {
//     static double sum = 1;
//     if (x == 0)
//     {
//         return 1;
//     }
//     else
//     {
//         if (k > 0)
//         {
//             sum = 1 + x * (sum) / k;
//             k--;
//             return expansion(x, k);
//         }
//     }
// }

// fibonacci series O(2^n)
// int fibonacci(int n)
// {
//     if (n <= 1 && n > -1)
//     {
//         return n;
//     }
//     else
//     {
//         return fibonacci(n - 2) + fibonacci(n - 1);
//     }
// }

// fibonacci but it is optimized O(n)
// int arr[INT16_MAX];
// int optFib(int terms)
// {
//     // static int* arr = new int[terms];
//     if (terms <= 1 && terms > -1)
//     {
//         return terms;
//     }
//     else
//     {
//         if (arr[terms - 2] == -1)
//         {
//             arr[terms - 2] = optFib(terms - 2);
//         }
//         else if (arr[terms - 1] == -1)
//         {
//             arr[terms - 1] = optFib(terms - 1);
//         }
//         else
//         {
//             return arr[terms - 1] + arr[terms - 2];
//         }
//     }
// }

// Combinations(n,r) O(n)

double combination(unsigned short int n, unsigned short int r)
{
    if (r == 0 || n == r)
    {
        return 1;
    }
    else
    {
        return combination(n - 1, r - 1) + combination(n - 1, r);
    }
}

// Tower of hanoi O(2^n)

void TOH(int n, int A, int B, int C)
{
    if (n > 0)
    {
        TOH(n - 1, A, C, B);
        cout << A << " " << C << endl;
        TOH(n - 1, B, A, C);
    }
}

// Sum of digits with recursion
// void sumOfDigits(int &n, int &sum)
// {
//     int k = 0, j = 0;
//     if (n == 0)
//     {
//         return;
//     }
//     k = n % 10;
//     j = n / 10;
//     sum += k;
//     sumOfDigits(j, sum);
//     cout << k << endl;
// }
int func(int n = 5)
{
    int x = 1, k;
    if (n == 1)
    {
        return x;
    }
    else
    {
        for (k = 1; k < 5; k++)
        {
            x += func(k) * func(n - k);
        }
    }
    return x;
}

// * Recurision + backtracking ---------------------------------------------------------------->

//^ sum of digits
int sumOfDigits(int N)
{
    if (N == 0 || N % 10 == N)
        return N;

    return (N % 10) + sumOfDigits(N / 10);
    //@ return (N%10)*productOfDigits(N/10) for products
}

//^ reversing an integer

long long reverseInt(long long N, long long digits)
{
    if (N % 10 == N)
        return N;
    long long rem = N % 10;
    return rem * pow(10, digits - 1) + reverseInt(N / 10, digits - 1);
}

//^ count zeroes

int countZeroes(int N)
{
    static int c = 0;
    if (N == 0)
        return 1;
    if (N % 10 == 0)
    {
        c++;
    }
    countZeroes(N / 10);
    return c;
}

bool isSorted(vector<int> &arr, int idx)
{
    if (arr[idx + 1] > arr[idx] && (idx + 1) != arr.size())
        return isSorted(arr, idx + 1);
    if ((idx + 1) == arr.size())
        return true;
    else
        return false;
}

void triangle(int r, int c)
{
    if (r == 0)
        return;
    if (c < r)
    {
        cout << "* ";
        triangle(r, c + 1);
    }
    else
    {
        cout << "\n";
        triangle(r - 1, 0);
    }
}

void selection(vector<int> &arr, int r, int c, int max)
{
    if (r == 0)
        return;
    if (c < r)
    {
        if (arr[c] > arr[max])
            selection(arr, r, c + 1, c);
        else
            selection(arr, r, c + 1, max);
    }
    else
    {
        swap(arr[max], arr[r - 1]);
        selection(arr, r - 1, 0, 0);
    }
}
// ^ merge sort in place
void merge(vector<int> &arr, int s, int mid, int e)
{
    vector<int> mix(e - s);
    int i = s;
    int j = mid + 1;
    int k = 0;
    while (i < mid && j < e)
    {
        if (arr[i] < arr[j])
        {
            mix[k++] = arr[i++];
        }
        else
        {
            mix[k++] = arr[j++];
        }
    }
    while (i < mid)
    {
        mix[k++] = arr[i++];
    }
    while (j < e)
    {
        mix[k++] = arr[j++];
    }
    int c = 0;
    for (auto &&it : mix)
    {
        arr[c++] = it;
    }
}
void mergeSort(vector<int> &arr, int s, int e)
{
    if (e - s == 1)
        return;
    int mid = (arr.size() - 1) / 2;
    mergeSort(arr, s, mid);
    mergeSort(arr, mid, e);
    merge(arr, s, mid, e);
}

//^ SKip a character (BRUH CODE)
string skipChar(string &s, string &ans)
{
    static int i = 0;
    // string ans = "";
    if (s.length() == 0 || i == s.length() - 1)
        return ans;
    if (s.at(i) == 'a')
    {
        i++;
        return skipChar(s, ans);
    }
    else
    {

        i++;
        ans.push_back(s[i]);
        return skipChar(s, ans);
    }
    return ans;
}

//^ Permutations of a string

void printPermutations(string s, int idx = 0)
{
    if (idx == s.size())
    {
        cout << s << "\n";
        return;
    }
    for (int j = idx; j < s.length(); j++)
    {
        swap(s.at(idx), s.at(j));
        printPermutations(s, idx + 1);
        swap(s[idx], s[j]);
    }
}

//^ Print all subsequence O(2^N * N) time and O(N) space

void printAllSubsequence(vector<int> &arr, vector<int> &subsequence, int index)
{
    if (index == arr.size()) //? base condition
    {
        for (int i = 0; i < subsequence.size(); i++)
            cout << subsequence.at(i) << " ";
        cout << endl;
        return;
    }

    //@ pick the particular index into the sequence
    subsequence.push_back(arr[index]);
    printAllSubsequence(arr, subsequence, index + 1);
    //@ not pick this element (not added to the current subsequence)
    subsequence.pop_back();
    printAllSubsequence(arr, subsequence, index + 1);
}

void printSubsequenceSum(vector<int> &arr, vector<int> &subsequence, int index, int sum, int givenSum)
{
    if (index == arr.size())
    {
        if (sum == givenSum)
        {
            for (auto &&i : subsequence)
            {
                cout << i << " ";
            }
            cout << "\n";
        }
        return;
    }
    subsequence.push_back(arr[index]);
    sum += arr[index];
    printSubsequenceSum(arr, subsequence, index + 1, sum, givenSum);
    sum -= arr[index];
    subsequence.pop_back();
    printSubsequenceSum(arr, subsequence, index + 1, sum, givenSum);
}

bool printAny1Subsequeunce(vector<int> &arr, vector<int> &subsequence, int idx, int sum, int givenSum)
{
    if (idx == arr.size())
    {
        if (sum == givenSum)
        {
            for (auto &&i : subsequence)
            {
                cout << i << " ";
            }
            cout << "\n";

            return true;
        }
        else
        {
            return false;
        }
    }
    subsequence.push_back(arr[idx]);
    sum += arr[idx];
    if (printAny1Subsequeunce(arr, subsequence, idx + 1, sum, givenSum))
        return true;
    sum -= arr[idx];
    subsequence.pop_back();
    if (printAny1Subsequeunce(arr, subsequence, idx + 1, sum, givenSum))
        return true;
}

//^ Count the number of sub sequences of some given sum;
int countSubsequeunce(vector<int> &arr, int idx, int sum, int givenSum)
{
    if (idx == arr.size())
    {
        if (sum == givenSum)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    sum += arr[idx];
    int l = countSubsequeunce(arr, idx + 1, sum, givenSum);
    sum -= arr[idx];
    int r = countSubsequeunce(arr, idx + 1, sum, givenSum);
    return l + r;
}

//^ Combination sum

void findCombinations(vector<int> &arr, int target, int index, vector<int> &ds, vector<vector<int>> &combinations)
{
    if (index == arr.size())
    {
        if (target == 0)
            combinations.push_back(ds);
        return;
    }
    if (arr[index] <= target)
    {
        ds.push_back(arr[index]);
        findCombinations(arr, target - arr[index], index, ds, combinations); //? Pick the same element again(as per the question)
        ds.pop_back();
    }
    findCombinations(arr, target, index + 1, ds, combinations); //? do not pick the element
}

//^ Subset sum 1

void SubsetSum(vector<int> &arr, vector<int> &subset, int index, int currentSum, vector<int> &res)
{
    if (index == arr.size())
    {
        res.push_back(currentSum);
        return;
    }
    subset.push_back(arr[index]);
    SubsetSum(arr, subset, index + 1, currentSum + arr[index], res);
    subset.pop_back();
    SubsetSum(arr, subset, index + 1, currentSum, res);
}

//^ subset sum 2

void SubsetSum2(vector<int> &arr, vector<int> &ds, vector<vector<int>> &subset, int index)
{
    //* Assumption : arr is sorted
    /*  if(index == arr.size()){
         subset.push_back(ds);
         return;
     } */
    //? base case is not required for thsi one
    subset.push_back(ds);
    for (int i = index; i < arr.size(); i++)
    {
        if (i != index && arr[i] == arr[i - 1])
            continue; //~ if the element is not the first and if it is the duplicate let's continue(skip);
        ds.push_back(arr[i]);
        SubsetSum2(arr, ds, subset, i + 1);
        ds.pop_back();
    }
}

//^ print all permutations of string/array O(N!)time
//! Extra space solution (using map);

/* void printAllPermutations(vector<int> &arr,vector<int> &ds,vector<vector<int>> &res,vector<bool> &visited) //? assuming no.s 1 to N-1;
{
    if(ds.size() == arr.size()){
        res.push_back(ds);
        return;
    }
    for(int i=index;i<arr.size();i++){
        if (!visited[i])
        {
            visited[i] = true;
            ds.push_back(arr[i]);
            printAllPermutations(arr, ds, res, visited);

            ds.pop_back();
            visited[i] = false;

        }

    }
} */

void printAllPermutations(vector<int> &arr, int index, vector<vector<int>> &res)
{
    if (index == arr.size())
    {
        res.push_back(arr);
        // for_each(arr.begin(), arr.end(),[](auto  i){cout << i << " "; });
        // cout << "\n";
        return;
    }
    for (int i = index; i < arr.size(); i++)
    {
        swap(arr[i], arr[index]);
        printAllPermutations(arr, index + 1, res);
        swap(arr[i], arr[index]);
    }
}

//^ Maze Problems

int countWays(int r, int c, vector<vector<int>> &matrix)
{
    if (r == 1 || c == 1)
    {
        return 1;
    }
    int left = countWays(r - 1, c, matrix);
    int right = countWays(r, c - 1, matrix);
    return left + right;
}

void printWays(string s = "", int r = 3, int c = 3)
{
    if (r == 1 && c == 1)
    {
        cout << s << "\n";
        return;
    }
    if (r > 1)
    {
        s.push_back('D');
        printWays(s, r - 1, c);
        s.pop_back();
    }
    if (c > 1)
    {
        s.push_back('R');
        printWays(s, r, c - 1);
        s.pop_back();
    }
}

//^ Allowed moving in diagonal directions also..
/*
~ V -> vertical
~ H -> horizontal
~ D -> diagonal
 */
void printWaysUsingDiagonals(string s = "", int r = 3, int c = 3)
{
    if (r == 1 && c == 1)
    {
        cout << s << "\n";
        return;
    }
    if (r > 1 && c > 1)
    {
        s.push_back('D');
        printWays(s, r - 1, c - 1);
        s.pop_back();
    }
    if (r > 1)
    {
        s.push_back('V');
        printWays(s, r - 1, c);
        s.pop_back();
    }
    if (c > 1)
    {
        s.push_back('H');
        printWays(s, r, c - 1);
        s.pop_back();
    }
}

//^ Maze with obstacles
void pathWithObstacles(string s, int r, int c, vector<vector<bool>> &maze)
{
    if (r == maze.size() - 1 && c == maze[0].size() - 1)
    {
        cout << s << "\n";
        return;
    }

    //~ obstacle at this postion (r,c)
    if (maze[r][c] == false)
    {
        return;
    }

    if (r < maze.size() - 1)
    {
        s.push_back('D');
        pathWithObstacles(s, r + 1, c, maze);
        s.pop_back();
    }
    if (c < maze[0].size() - 1)
    {
        s.push_back('R');
        pathWithObstacles(s, r, c + 1, maze);
        s.pop_back();
    }
}

//^ Possible words from phone digits;

//* Recursive approach (4*N) time and O(N) space
// vector<pair<int,string>> keypad = {{0,""},{1,""},{2,"abc"},{3,"def"},{4,"ghi"},{5,"jkl"},{6,"mno"},{7,"pqrs"},{8,"tuv"},{9,"wxyz"}};
//     //Function to find list of all words possible by pressing given numbers.

//     void helper(int a[],int N,set<string> &ds,string &temp,int index,int numb){
//         if(index == N || temp.length() == N){
//                 ds.insert(temp);
//             for(int i=1;i<keypad[numb].second.length();i++){
//                 temp.pop_back();
//                 temp.push_back(keypad[numb].second[i]);
//                 ds.insert(temp);
//             }
//             return;
//         }

//         else{
//             for(int i=0;i<keypad[a[index]].second.length() ;i++){
//                 temp.push_back(keypad[a[index]].second[i]);
//                 if(index+1==N){
//                 helper(a,N,ds,temp,index+1,a[index]);}
//                 else
//                 helper(a,N,ds,temp,index+1,a[index+1]);
//                 temp.pop_back();
//             }
//         }
//     }
//     vector<string> possibleWords(int a[], int N)
//     {
//         //Your code here
//         vector<string> res;
//         set<string> st;
//         string temp="";
//         helper(a,N,st,temp,0,a[0]);
//         for(auto &it : st){
//             res.push_back(it);
//         }
//         return res;
//     }

//* simplified version of above function
const char hashTable[10][5] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
//~ recursive function to return all possible words that can
//~ be obtained by input number[] of size n.
void printWordsUtil(int number[], int curr_digit, string output, int n, vector<string> &res)
{
    int i;
    //?base case, if current output word is prepared.
    if (curr_digit == n)
    {
        //?pushing the word in output list.
        res.push_back(output);
        return;
    }

    //&trying all 3 possible characters for current digit in number[]
    //&and calling recursive function for remaining digits.
    for (i = 0; i < strlen(hashTable[number[curr_digit]]); i++)
    {
        output.push_back(hashTable[number[curr_digit]][i]);
        printWordsUtil(number, curr_digit + 1, output, n, res);
        if (number[curr_digit] == 0 || number[curr_digit] == 1)
            return;
        output.pop_back();
    }
}

// Function to find list of all words possible by pressing given numbers.
vector<string> possibleWords(int a[], int N)
{
    vector<string> res;
    string result;
    printWordsUtil(a, 0, result, N, res);

    // returning the result.
    return res;
}

//^ josephus problem using recursion
//* One line of code
int safePos(int n, int k)
{
    return (n == 1) ? 1 : (safePos(n - 1, k) + k - 1) % n + 1;
}

//^ get stair path you can jump only 1,2,3 steps at a time

vector<string> getStairPath(int n)
{
    if (n < 0)
    {
        vector<string> bres;
        return bres;
    }
    if (n == 0)
    {
        vector<string> bres;
        bres.push_back("");
        return bres;
    }
    vector<string> paths1 = getStairPath(n - 1);
    vector<string> paths2 = getStairPath(n - 2);
    vector<string> paths3 = getStairPath(n - 3);

    vector<string> paths;
    for (auto &s : paths1)
    {
        paths.push_back("1" + s);
    }
    for (auto &s : paths2)
    {
        paths.push_back("2" + s);
    }
    for (auto &s : paths3)
    {
        paths.push_back("3" + s);
    }
}

//^ get maze path when jumps are allowed
void getMazePath(int x, int y, int destinationHorizontal, int destinationVertical, string temp)
{
    if (x == destinationHorizontal && y == destinationVertical)
    {
        cout << temp << "\n";
        return;
    }
    // ? horizontal moves , 'i' denotes move size or jump size
    for (int i = 1; i <= destinationHorizontal - x; i++)
    {
        getMazePath(x + i, y, destinationHorizontal, destinationVertical, temp + "h" + to_string(i));
    }

    // ? vertical moves , 'i' denotes move size or jump size
    for (int i = 1; i <= destinationVertical - y; i++)
    {

        getMazePath(x, y + i, destinationHorizontal, destinationVertical, temp + "v" + to_string(i));
    }
    // ? diagonal moves , 'i' denotes move size or jump size
    for (int i = 1; i <= destinationVertical - y && i <= destinationHorizontal - x; i++)
    {
        getMazePath(x + i, y + i, destinationHorizontal, destinationVertical, temp + "d" + to_string(i));
    }
}

//^ Given three integers n, k, and target, return the number of possible ways (out of the kn total ways) to roll the dice, so the sum of the face-up numbers equals target.

//@ if the dice has m faces then replace '6' --> 'm' and pass m in the argument of the function
void possibleWay(vector<string> &ans, int target, string &s)
{
    if (target == 0)
    {
        ans.push_back(s);
        return;
    }
    else
    {
        for (int i = 1; i <= 6 && i <= target; i++)
        {

            string temp = to_string(i);
            char v = temp.front();
            s.push_back(v);
            possibleWay(ans, target - i, s);
            s.pop_back();
        }
    }
}

//^ Special Keyboard
/*


@ A few important points to note are
@ a) For N < 7, the output is N itself.
@ b) Ctrl V can be used multiple times to print current buffer. The idea is to compute @ the optimal string length for N keystrokes by using a simple insight. The sequence @ of N keystrokes which produces an optimal string length will end with a suffix of @ Ctrl-A, a Ctrl-C, followed by only Ctrl-V’s . (For N > 6)

@ Now the task is to find out the breakpoint after which get the above suffix of @ keystrokes.
@ Definition of a breakpoint is that instance after which one need to only press Ctrl-@ A, Ctrl-C once and the only Ctrl-V’s afterwards to generate the optimal length.
@ If one loop from N-3 to 1 and choose each of these values for the break-point, and @ compute that optimal string they would produce. Once the loop ends, you will have @ the maximum of the optimal lengths for various breakpoints, thereby giving the @ optimal length for N keystrokes.
 */

long long int optimalKeys(int N)
{
    // code here
    int x, y;

    if (N < 6)
    {
        return N;
    }

    else
    {
        x = 4 * optimalKeys(N - 5);

        y = 3 * optimalKeys(N - 4);

        return max(x, y);
    }
}

//^ Unique partitions

//! Brute force (similar problem as dice throw just replace '6' with given number) O(2^N) time complexity
/* void solve(vector<int> &temp , int target , set<vector<int>> &s,int givenNum){
         if(target<0)return;
         if(target == 0){
           //  sort(temp.rbegin(),temp.rend());
           vector<int> v = temp;
           sort(v.begin(),v.end(),greater<int>());
             s.emplace(v);
             return;
         }
         else{
             for(int i=1;i<=givenNum && i<=target;i++){
                 temp.push_back(i);
                 solve(temp,target - i,s,givenNum);
                 temp.pop_back();
             }
         }
     }

    vector<vector<int>> UniquePartitions(int n) {
    vector<vector<int>> result;
    vector<int> temp;
    set<vector<int>> s;
        // Code here
        solve(temp,n,s,n);
    auto it = s.rbegin();
    for(it = s.rbegin(); it!=s.rend();it++){
        result.push_back(*it);
    }
    return result;
} */

//* Optimized version of above problem without using set
void solve(int index, vector<int> &ds, int tar, vector<vector<int>> &ans, vector<int> &arr)
{

    // base case
    if (index == arr.size())
    {
        if (tar == 0)
        {
            ans.push_back(ds);
        }
        return;
    }

    // rec case
    if (arr[index] <= tar)
    {
        ds.push_back(arr[index]);
        solve(index, ds, tar - arr[index], ans, arr);
        ds.pop_back();
    }

    solve(index + 1, ds, tar, ans, arr);
}

vector<vector<int>> UniquePartitions(int n)
{
    // Code here

    vector<vector<int>> res;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i] = n - i;
    }

    vector<int> ds;
    solve(0, ds, n, res, arr);

    return res;
}

//^ gray code generate

//! Recursive approach O(2^N) time and space complexity
// vector<string> graycode(int n)
//     {
//         //code here
//           if(n==1)
//             return {"0","1"};
//         vector<string> res = graycode(n-1);
//         vector<string> ans;
//         for(int i=0;i<res.size();i++)
//             ans.push_back("0"+res[i]);
//         for(int i=res.size()-1;i>=0;i--)
//             ans.push_back("1"+res[i]);
//         return ans;
//     }

//* Optimized version of above function
vector<string> graycode(int n)
{
    vector<string> vec;
    int num = pow(2, n);
    for (int i = 0; i < num; i++)
    {
        string str = "";
        int gray_num = i ^ (i >> 1); //~ XOR the number itself with its 1 right shift to get its gray code (Digital Electronics BRUH)
        str = bitset<16>(gray_num).to_string();
        str = str.substr(16 - n, n);
        vec.push_back(str);
    }
    return vec;
}

//^ Backtracking portion -->

class Nqueens
{
private:
    /*
    Given an NxN chess board
    Rules : Each row and column must contain one queen
            No queens should be attacked
     */
public:
    /*     bool isValidPosition(int row, int col, vector<string> &board, int N)
        {
            int dupRow = row, dupCol = col;
            while (row >= 0 && col >= 0)
            {
                if (board[row][col] == 'Q')
                    return false;
                row--;
                col--;
            }
            col = dupCol;
            row = dupRow;
            while (col >= 0)
            {
                if (board[row][col] == 'Q')
                    return false;
                col--;
            }
            row = dupRow;
            col = dupCol;
            while (row < N && col >= 0)
            {
                if (board[row][col] == 'Q')
                    return false;
                row++;
                col--;
            }
            return true;
        }
        void solve(int col, vector<string> &board, vector<vector<string>> &ans, int N)
        {
            if (col == N)
            {
                ans.push_back(board);
                return;
            }

            for (int row = 0; row < N; row++)
            {
                if (isValidPosition(row, col, board, N))
                {
                    board[row][col] = 'Q';
                    solve(col + 1, board, ans, N);
                    board[row][col] = '.';
                }
            }
        }
        vector<vector<string>> solveQueens(int N)
        {
            vector<vector<string>> ans;
            vector<string> board(N);
            string s(N, '.');
            for (int i = 0; i < N; i++)
            {
                board[i] = s;
            }

            solve(0, board, ans, N);
            return ans;
        } */

    /*

& This code solves the N-Queens problem, which is to find all possible arrangements of N queens on an NxN chessboard such that no two queens threaten each other. Each queen should be placed in a separate row, column, or diagonal.

& The code uses a backtracking algorithm to explore all possible placements of queens on the chessboard. It maintains three arrays `leftRow`, `upperDiagonal`, and `lowerDiagonal` to keep track of the availability of rows, upper diagonals, and lower diagonals respectively. Initially, all elements in these arrays are set to 0, indicating that they are available for queen placement.

& The `solve` function is a recursive function that takes the current column `col`, the chessboard configuration `board`, the resulting solutions `ans`, and the arrays `leftRow`, `upperDiagonal`, and `lowerDiagonal`. It explores all possible row positions for the queen in the current column. If a valid position is found, the queen is placed, and the corresponding elements in the arrays are updated to mark the row, upper diagonal, and lower diagonal as occupied. Then, the function recursively calls itself for the next column. Once all columns are filled (i.e., `col == n`), a valid solution is found, and the chessboard configuration is added to the `ans` vector.

& If a queen cannot be placed in a row due to conflicts, the function backtracks by undoing the previous placement and restoring the array values. This allows the algorithm to explore other possible configurations.

& The `solveNQueens` function initializes the chessboard configuration, creates the arrays, and calls the `solve` function to find all valid solutions. It returns the resulting vector of chessboard configurations.

& The intuition behind the code is to systematically explore all possible placements of queens using backtracking. By maintaining arrays to track the availability of rows and diagonals, the algorithm avoids invalid configurations where queens threaten each other. The recursive nature of the algorithm allows it to efficiently explore all possible configurations and find all valid solutions.

* O(N!) T.C | O(N) Space
     */
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, vector<int> &leftRow, vector<int> &upperDiagonal, vector<int> &lowerDiagonal, int n)
    {

        if (col == n)
        {
            ans.push_back(board);
            return;
        }
        for (int row = 0; row < n; row++)
        {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 && upperDiagonal[(n - 1) + (col - row)] == 0)
            {
                board[row][col] = 'Q';
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;
                solve(col + 1, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
                board[row][col] = '.';
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for (int i = 0; i < n; i++)
        {
            board[i] = s;
        }
        vector<int> leftRow(n, 0), upperDiagonal(2 * n - 1, 0), lowerDiagonal(2 * n - 1, 0);
        solve(0, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
        return ans;
    }
};

//^ Rat in a maze
class RatInAMaze
{
public:
    /*
&     The solve function is the recursive helper function that explores all possible paths from the current position (row, col) to the destination (n-1, n-1). It takes the current position, the matrix, the size of the matrix, the list of valid paths ans, the current path path, and a matrix vis to keep track of visited positions.

& The base case of the recursion is when the current position is at the bottom-right corner of the matrix (row == n-1 and col == n-1). In this case, the current path path is added to the list of valid paths ans, and the function returns.

& The recursive calls are made in four directions: down (D), left (L), right (R), and up (U). For each direction, the code checks if it is within the boundaries of the matrix, if the position is not visited (vis[row][col] == false), and if the position represents a valid path (m[row][col] == 1).

& If the above conditions are satisfied, the code marks the current position as visited (vis[row][col] = 1), appends the corresponding direction to the current path (path.push_back()), and makes a recursive call to explore the next position in that direction. After the recursive call, the code removes the appended direction from the current path (path.pop_back()) and resets the visited status of the current position (vis[row][col] = 0).

& The findPath function initializes the visited matrix vis and the empty list of valid paths ans. It then checks if the top-left corner of the matrix (0, 0) represents a valid path (m[0][0] == 1). If it does, it calls the solve function to find all possible paths from the start position (0, 0) to the destination position (n-1, n-1). Finally, it returns the list of valid paths ans.

& In summary, this code uses backtracking to explore all possible paths in a matrix from the top-left corner to the bottom-right corner, considering only valid paths represented by 1s in the matrix. The time complexity of this code depends on the number of valid paths and can be exponential in the worst case.
     */
    void solve(int row, int col, vector<vector<int>> &m, int n, vector<string> &ans, string &path, vector<vector<int>> &vis)
    {
        if (row == n - 1 && col == n - 1)
        {
            ans.push_back(path);
            return;
        }

        if (row + 1 < n && vis[row + 1][col] == false && m[row + 1][col] == 1)
        {
            vis[row][col] = 1;
            path.push_back('D');
            solve(row + 1, col, m, n, ans, path, vis);
            path.pop_back();
            vis[row][col] = 0;
        }
        if (col - 1 >= 0 && vis[row][col - 1] == false && m[row][col - 1] == 1)
        {
            vis[row][col] = 1;
            path.push_back('L');
            solve(row, col - 1, m, n, ans, path, vis);
            path.pop_back();
            vis[row][col] = 0;
        }
        if (col + 1 < n && vis[row][col + 1] == false && m[row][col + 1] == 1)
        {
            vis[row][col] = 1;
            path.push_back('R');
            solve(row, col + 1, m, n, ans, path, vis);
            path.pop_back();
            vis[row][col] = 0;
        }
        if (row - 1 >= 0 && vis[row - 1][col] == false && m[row - 1][col] == 1)
        {
            vis[row][col] = 1;
            path.push_back('U');
            solve(row - 1, col, m, n, ans, path, vis);
            path.pop_back();
            vis[row][col] = 0;
        }
    }
    vector<string> findPath(vector<vector<int>> &m, int n)
    {
        vector<vector<int>> vis(n, vector<int>(n, 0));
        vector<string> ans;
        string path = "";
        if (m[0][0] == 1)
        {
            solve(0, 0, m, n, ans, path, vis);
        }
        return ans;
    }
};

class PalindromePartitioner
{
    /*
 &    This code solves the problem of partitioning a string into all possible palindromic substrings. The function `partition` takes a string `s` as input and returns a 2D vector `res` containing all possible partitions.

& The main logic is implemented in the `func` function, which is a recursive backtracking function. It takes the current index `idx`, the input string `s`, a vector `path` to store the current partition, and the result vector `res` to store all valid partitions.

& The base case is when the `idx` reaches the end of the string, indicating that we have formed a complete partition. In this case, we add the current `path` to the `res` vector and return.

& In the recursive case, we iterate from the `idx` to the end of the string. For each index `i`, we check if the substring from `idx` to `i` is a palindrome using the `isPalindrome` function. If it is a palindrome, we add it to the `path`, recursively call `func` for the next index `i+1`, and then remove the added substring from the `path` using `path.pop_back()`. This backtracking step allows us to explore all possible partitions.

& The `isPalindrome` function checks if a substring of `s` from index `idx` to `i` is a palindrome. It compares the characters at corresponding indices from both ends of the substring and returns `false` if any characters are different. If all characters are the same, it returns `true`, indicating a palindrome.

& The intuition behind this approach is to generate all possible partitions by exploring all possible palindromic substrings in the input string. By using backtracking, we backtrack to the previous partition when we have exhausted all possibilities for the current partition.

& The time complexity of this code is O(n * 2^n), where n is the length of the input string `s`. This is because there can be 2^n possible partitions, and for each partition, we need to check if each substring is a palindrome, which takes O(n) time. The space complexity is O(n) for the recursive call stack and the result vector `res`.
     */
public:
    vector<vector<string>> partition(string &s)
    {
        vector<vector<string>> res;
        vector<string> path;
        func(0, s, path, res);
        return res;
    }

    void func(int idx, string &s, vector<string> &path, vector<vector<string>> &res)
    {
        if (idx == s.size())
        {
            res.push_back(path);
            return;
        }
        for (int i = idx; i < s.size(); i++)
        {
            if (isPalindrome(s, idx, i))
            {
                path.push_back(s.substr(idx, i + 1 - idx));
                func(i + 1, s, path, res);
                path.pop_back();
            }
        }
    }
    bool isPalindrome(string &s, int idx, int i)
    {
        while (idx <= i)
        {
            if (s[idx++] != s[i--])
            {
                return false;
            }
        }
        return true;
    }
};
class Sudoku
{
private:
    /*
    &- The code implements a Sudoku solver using a backtracking algorithm. It includes two functions: isValidConfig and solve.

    &- The isValidConfig function checks whether placing a character c at a specific position (row, col) on the Sudoku board is a valid configuration or not.

    &- The function iterates over three checks to validate the configuration:
    ~ It checks if c already exists in the same column. If it does, it returns false.
    ~ It checks if c already exists in the same row. If it does, it returns false.
    ~ It checks if c already exists in the 3x3 sub-grid to which the position (row, col) belongs. If it does, it returns false.

    &- If none of the checks fail, it returns true, indicating that the configuration is valid.

    &- The solve function performs the backtracking algorithm to solve the Sudoku puzzle recursively.

    &- It iterates over each cell of the Sudoku board using two nested loops.
    ~ If the cell contains a '.' (empty cell), it proceeds to fill in a valid number from '1' to '9'.
    ~ It checks each number from '1' to '9' and calls the isValidConfig function to determine if it is a valid configuration at the current cell position.
    ~ If a valid configuration is found, it places the number c in the current cell (board[i][j] = c).
    ~ It then recursively calls the solve function to continue solving the puzzle.
    ~- If solve returns true, it means a solution is found, and it returns true to the previous recursive call, propagating the solution.
    ~- If solve returns false, it means the current configuration did not lead to a valid solution, so it backtracks by resetting the current cell to '.' (board[i][j] = '.') and continues with the next number.

    &- If no empty cell is found (i.e., the entire board is filled), it returns true to indicate a solution is found.

    &- If all possibilities are exhausted and no solution is found, it returns false.

    * O(9^NxN) T.C | O(NxN) S.C
     */
public:
    bool isValidConfig(vector<vector<char>> &board, int row, int col, char c)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[i][col] == c)
                return false;
            if (board[row][i] == c)
                return false;
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
                return false;
        }
        return true;
    }

    bool solve(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    for (char c = '1'; c <= '9'; c++)
                    {
                        if (isValidConfig(board, i, j, c))
                        {
                            board[i][j] = c;
                            if (solve(board))
                            {

                                cout << "Found a match!\n";
                                return true;
                            }
                            else
                            {

                                board[i][j] = '.';
                                cout << "no match!\n";
                            }
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>> &board)
    {
        solve(board);
    }
};

//^ Kth permutation of a number 1 -> N
/*
& Initialize variables:

~    Set fact to 1 to store the factorial value.
~    Create an empty vector numbers to store the numbers to be permuted.
~    Initialize an empty string ans to store the final permutation.

& Generate initial permutation:

~    Iterate from 1 to n-1 (excluding n itself).
~    Update fact by multiplying it with the current iteration value.
~    Add the current iteration value to the numbers vector.

& Add the last number:

~    Add n to the numbers vector.
~    This completes the generation of the initial permutation.

& Adjust k for 0-based indexing:

~    Decrement k by 1 since the code uses 0-based indexing for calculations.

& Generate the permutation:

~    Enter an infinite loop (break condition inside).
~    Append the character representation of numbers[k / fact] to the ans string.
~    Remove the element at index k / fact from the numbers vector.
~    If the numbers vector is empty, break the loop.

& Update k and fact for the next iteration:

~    Update k by taking the remainder of k divided by fact.
~    Reduce fact by dividing it by the size of the numbers vector.

& Return the final permutation stored in ans.

& The code generates the kth permutation of the numbers from 1 to n using a factorial-based approach. It calculates the permutation by determining the digit at each position iteratively based on the remaining available numbers.
 */
string getPermutation(int n, int k)
{
    int fact = 1;
    vector<int> numbers;
    string ans = "";
    for (int i = 1; i < n; i++)
    {
        fact *= i;
        numbers.emplace_back(i);
    }
    numbers.push_back(n);
    k--;
    while (true)
    {
        ans += to_string(numbers[k / fact]);
        numbers.erase(numbers.begin() + k / fact);
        if (numbers.size() == 0)
            break;

        k = k % fact;
        fact /= numbers.size();
    }
    return ans;
}

//^ Generate All parentheses
class AllParens
{
private:
    /*
    @ Recursion
    The given code generates all valid combinations of parentheses for a given value of n. Let's understand the code and its execution using an example.

Example: n = 3

1. Initially, an empty vector `ans` is created to store the generated combinations.

2. The function `solve()` is called with the initial values `open = n`, `close = n`, and an empty string `temp`.

3. Inside the `solve()` function:
   - If both `open` and `close` are zero, it means we have used up all the available parentheses, and we have found a valid combination. In this case, the current combination `temp` is added to the `ans` vector using `ans.push_back(temp)`.
   - If `open` is greater than zero, we can add an opening parenthesis '(' to the current combination `temp`. The function `solve()` is recursively called with `open-1`, `close`, and `temp+'('`.
   - If `close` is greater than `open`, it means we have more closing parentheses available than opening parentheses. In this case, we can add a closing parenthesis ')' to the current combination `temp`. The function `solve()` is recursively called with `open`, `close-1`, and `temp+')'`.

4. Initially, `solve(n, n, "", ans)` is called. Here, `open = 3`, `close = 3`, and `temp` is an empty string.

5. Inside the `solve()` function, the following steps are executed:

   - `solve(2, 3, "(", ans)`:
     - `solve(1, 3, "((", ans)`:
       - `solve(0, 3, "(((", ans)`:
         - `solve(0, 2, "((()", ans)`:
           - `solve(0, 1, "((())", ans)`:
             - `solve(0, 0, "((()))", ans)`:
               - `ans.push_back("((()))")` (valid combination found)
           - `solve(1, 1, "(()", ans)`:
             - `solve(0, 1, "(()(", ans)`:
               - `solve(0, 0, "(()())", ans)`:
                 - `ans.push_back("(()())")` (valid combination found)
           - `solve(1, 2, "(())", ans)`:
             - `solve(0, 2, "(())(", ans)`:
               - `solve(0, 1, "(())()", ans)`:
                 - `solve(0, 0, "(())())", ans)`:
                   - `ans.push_back("(())())")` (valid combination found)
       - `solve(2, 2, "()", ans)`:
         - `solve(1, 2, "()((", ans)`:
           - `solve(0, 2, "()(()", ans)`:
             - `solve(0, 1, "()(())", ans)`:
               - `solve(0, 0, "()(())", ans)`:
                 - `ans.push_back("()(())")` (valid combination found)
         - `solve(2, 1, "()(", ans)`:
           - `solve(1, 1, "())(", ans)`:
             - `solve(0, 1, "())()", ans)`:
               - `solve(0, 0, "())())", ans)`:
                 - `ans.push_back("())())")` (valid combination found)
   - `solve(3, 2, ")", ans)`
     */
public:
    void solve(int open, int close, string temp, vector<string> &ans)
    {
        if (open == 0 && close == 0)
        {
            ans.push_back(temp);
            return;
        }
        if (open > 0)
        {
            solve(open - 1, close, temp + '(', ans);
        }
        if (close > open)
        {
            solve(open, close - 1, temp + ')', ans);
        }
    }
    vector<string> AllParenthesis(int n)
    {
        // Your code goes here
        vector<string> ans;
        solve(n, n, "", ans);
        return ans;
    }
};
int main()
{

    vector<int> arr = {1, 3, 2};
    vector<string> sub, ds;
    vector<vector<int>> res;
    string s = "";
    //    cout <<  reverseInt(2061,4);
    //    cout <<  countZeroes(2060020420);
    // string s1 = "aayehIdontknowwho  ur";
    // s2 = skipChar(s1,s2);
    // cout << s2 << endl;
    // cout << isSorted(arr,0);
    // triangle(5,5);
    // printAllSubsequence(arr,sub,0);
    // printSubsequenceSum(arr, sub, 0, 0, 5);
    // SubsetSum(arr,ds,0,0,sub);
    // sort(sub.begin(),sub.end());
    // printAllPermutations(arr,0,res);
    // vector<vector<bool>> maze = {{true,true,true},{false,true,false},{false,true,true}};
    // pathWithObstacles(s,0,0,maze);
    // possibleWay(ds,6,s);
    // getMazePath(1, 1, 3, 3,s);
    printPermutations("ABA");

    return 0;
}
