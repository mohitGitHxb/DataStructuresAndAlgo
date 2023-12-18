#include <bits/stdc++.h>
using namespace std;

/* 
You are given a 0-indexed string num representing a non-negative integer.

In one operation, you can pick any digit of num and delete it. Note that if you delete all the digits of num, num becomes 0.

Return the minimum number of operations required to make num special.

An integer x is considered special if it is divisible by 25.

 

Example 1:

Input: num = "2245047"
Output: 2
Explanation: Delete digits num[5] and num[6]. The resulting number is "22450" which is special since it is divisible by 25.
It can be shown that 2 is the minimum number of operations required to get a special number.

Example 2:

Input: num = "2908305"
Output: 3
Explanation: Delete digits num[3], num[4], and num[6]. The resulting number is "2900" which is special since it is divisible by 25.
It can be shown that 3 is the minimum number of operations required to get a special number.

Example 3:

Input: num = "10"
Output: 1
Explanation: Delete digit num[0]. The resulting number is "0" which is special since it is divisible by 25.
It can be shown that 1 is the minimum number of operations required to get a special number.


 */
class Solution {
private:
/* 
    isDivisibleBy25 Function:
        This function checks if an integer n is divisible by 25 by checking if it's divisible by 100 (since 25 * 4 = 100).
        It returns true if n is divisible by 25; otherwise, it returns false.

    helper Function:
        This is a recursive helper function that calculates the minimum number of operations required to make the substring of num from index idx to the end special.
        It takes four parameters:
            idx: The current index being considered.
            prev: The previous index that can be deleted.
            num: The string representing the non-negative integer.
        The function first checks the base cases:
            If idx is less than 0, it returns 1 if the previous digit (at index prev) is not '0', indicating that the last digit is not zero.
            If the combination of the current digit and the previous digit (in integer form) is divisible by 25, it returns 0, as no more operations are needed.
            It checks if the result for this idx and prev has already been calculated and stored in the memo table. If so, it returns the stored result.
        It calculates two possible scenarios:
            left: The result of recursively calling the helper function with the same idx and the same prev because the current digit is not deleted.
            right: The result of recursively calling the helper function with idx decremented by 1 and prev decremented by 1 because the current digit is deleted.
        It returns the minimum of left and right plus 1 (indicating the current operation).

    minimumOperations Function:
        This is the main function that calculates the minimum number of operations to make the entire num special.
        It first checks if the length of the input string num is less than 2. If so, it returns the length of num because there are no operations needed to make a single-digit number special.
        It initializes the memo table, a 2D vector, with values of -1.
        It calls the helper function with initial parameters: n - 2 (second-to-last index), n - 1 (last index), and num.
        The result is the minimum number of operations needed to make num special.

    Time Complexity:
        The time complexity of this code is O(n^2), where n is the length of the input string num. This is because the helper function is called recursively with multiple combinations of idx and prev, resulting in a double loop.

    Space Complexity:
        The space complexity is O(n^2) as well due to the memoization table (memo) that stores results for different combinations of idx and prev.

    Hint:
        The code is using dynamic programming with memoization to avoid recomputation of the same subproblems.
        It recursively explores two possibilities at each step: deleting the current digit or keeping it.
        The base cases are for when idx goes below 0 or when a combination of digits is divisible by 25.
        The memo table stores intermediate results, allowing the code to avoid redundant calculations and significantly improve efficiency.
 */
public:
bool isDivisibleBy25(int n) {
    return (n % 25 == 0);
}

vector<vector<int>> memo;

int helper(int idx, int prev, string &num) {
    if (idx < 0) return !(num[prev] == '0');
    if (isDivisibleBy25((num[idx] - '0') * 10 + (num[prev] - '0'))) {
        return 0;
    }
    if (memo[idx][prev] != -1) return memo[idx][prev];
    int left = 1 + helper(idx - 1, prev, num);
    int right = 1 + helper(idx - 1, prev - 1, num);
    return memo[idx][prev] = min(left, right);
}

int minimumOperations(string num) {
    int n = num.size();
    if (n < 2) return n;
    memo.resize(101, vector<int>(101, -1));
    return helper(n - 2, n - 1, num);
}

};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        //write code here
    }
    return 0;
}