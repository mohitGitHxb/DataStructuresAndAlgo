#include <bits/stdc++.h>
using namespace std;
/*
* DYNAMIC PROGRAMMING
 @ -> Tabulation (bottom-up approach)
 @ -> Memoization (top-down approach)
 */
//^ 1 Fibonacci Number
class Fibonnaci
{
public:
    vector<int> dp;
    Fibonnaci(int n)
    {
        dp.resize(n + 1);
        fill(dp.begin(), dp.end(), -1);
    }
    //! Recursive solution
    int fibonacci(int n)
    {
        if (n <= 1)
            return n;
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    /*
    * DP memoization solution with T.C : O(N) and S.C : O(2N)
 @   Dynamic programming is a technique for solving problems by breaking them down into smaller overlapping subproblems and solving each subproblem only once. Memoization is a specific technique within dynamic programming that involves storing the results of expensive function calls and reusing them when the same inputs occur again.

& In the given code, the function fibonacci_dp takes an integer n and a reference to a vector dp as input. The vector dp is used to store the computed Fibonacci numbers, so that they can be reused when needed.

& The function checks if the Fibonacci number for the given n is already computed and stored in the dp vector. If it is, then the function directly returns the stored value (dp[n]). This check is performed using the condition dp.at(n) != -1. Initially, the dp vector is assumed to be filled with -1 values.

& If the Fibonacci number for the given n is not computed yet, the function recursively calculates it using the formula fibonacci_dp(n-1,dp) + fibonacci_dp(n-2,dp). This formula represents the recurrence relation of the Fibonacci sequence, where each Fibonacci number is the sum of the two preceding numbers.

& After calculating the Fibonacci number for the given n, the result is stored in the dp vector at the corresponding index (dp[n] = ...). This way, the computed value is saved for future use and prevents redundant calculations for the same n.

& By using memoization, the function avoids redundant calculations and improves the efficiency of the Fibonacci sequence calculation, especially for large values of n. The initial call to the function fibonacci_dp with the desired n will compute and store all necessary Fibonacci numbers up to n, so subsequent calls for the same n will have constant time complexity, O(1), instead of exponential time complexity, O(2^n), of the naive recursive approach.
     */
    int fibonacci_dp(int n, vector<int> &dp)
    {
        if (n <= 1)
            return n;
        else if (dp.at(n) != -1)
            return dp[n];
        return dp[n] = fibonacci_dp(n - 1, dp) + fibonacci_dp(n - 2, dp);
    }

    /*
    * Tabulation method: O(N) S.C [better than memoization for this function]
    Tabulation is a bottom-up approach in dynamic programming, where the solutions to smaller subproblems are computed iteratively and stored in a table (or an array) for later use.

    In the code, the function fibonacci_dp_tabulation takes an integer n and a reference to a vector dp as input. The vector dp is used as a table to store the computed Fibonacci numbers.

    The function first initializes the base cases of the Fibonacci sequence, dp[0] = 0 and dp[1] = 1, as these are known values.

    Then, a loop is started from i = 2 up to n, and in each iteration, the Fibonacci number for the current index i is calculated using the formula dp[i] = dp[i-1] + dp[i-2]. This formula represents the recurrence relation of the Fibonacci sequence, where each Fibonacci number is the sum of the two preceding numbers.

    By iterating from i = 2 up to n and calculating the Fibonacci numbers for each index, the function fills up the dp vector with the Fibonacci sequence up to n. This process of computing and storing the results in a table is known as tabulation.

    Finally, the function returns dp[n], which represents the Fibonacci number at the nth index. This is the desired Fibonacci number requested by the function's input.

    Using tabulation, the function avoids redundant calculations by iteratively building up the Fibonacci sequence from the base cases. The time complexity of this approach is linear, O(n), as it only requires a single pass through the loop to compute all Fibonacci numbers up to n. This is more efficient than the exponential time complexity, O(2^n), of the naive recursive approach.
     */
    int fibonacci_dp_tabulation(int n, vector<int> &dp)
    {
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
    /*
    * Space optimization over tabulation method : O(1) Space
    In this updated code, we no longer need the dp vector. Instead, we initialize three variables: prev2, prev1, and current. These variables represent the Fibonacci numbers at n-2, n-1, and n, respectively.

    The loop starts from i = 2 and iterates up to n. In each iteration, we update the value of current by adding prev1 and prev2. Then, we shift the values of prev1 and prev2 by assigning prev1 = current and prev2 = prev1. This way, we maintain the values of the Fibonacci numbers for the next iteration.

    After the loop completes, current will hold the Fibonacci number at the nth index, which is then returned as the result.

    This optimized implementation eliminates the need for extra space to store the Fibonacci sequence, reducing the space complexity from O(n) to O(1). It still maintains a linear time complexity of O(n) as it computes the Fibonacci numbers iteratively.
     */
    int fibonacci_dp_optimized(int n)
    {
        if (n <= 1)
            return n;

        int prev2 = 0;   // Fibonacci number at n-2
        int prev1 = 1;   // Fibonacci number at n-1
        int current = 0; // Fibonacci number at n

        for (int i = 2; i <= n; i++)
        {
            current = prev1 + prev2;
            prev2 = prev1;
            prev1 = current;
        }

        return current;
    }
};

//^ 2 Count the number of ways to reach nth stair
/*
~ Shortcut trick to find whether the problem is a 1d DP problem
& Includes words like ["count all ways","minimum way to reach x","maximum way to reach"]
? Try to represent the problem in terms of index
? Do all possible processes/stuffs on that index according to the given problem statement
! sum of all processes/stuffs --> count all ways to ...
! min(all processes/stuffs) --> minimum way to reach
! max(all processes/stuffs) --> maximum way to reach
 */

class ClimbStairs
{
    vector<int> dp;
    const int mod = 1e9 + 7;

public:
    ClimbStairs(int n)
    {
        dp.resize(n + 1, -1);
    }

    int countWays_Recursive(int n)
    {
        if (n < 0)
            return 0;
        if (n == 0)
            return 1;
        return countWays_Recursive(n - 1) % mod + countWays_Recursive(n - 2) % mod;
    }

    int countWays_Memoization(vector<int> &dp, int n)
    {
        if (n < 0)
            return 0;
        if (n == 0)
            return 1;
        if (dp[n] != -1)
        {
            return dp[n] % mod;
        }
        dp[n] = (countWays_Memoization(dp, n - 1) % mod + countWays_Memoization(dp, n - 2) % mod) % mod;
    }

    int countWays_Tabulation(vector<int> &dp, int n)
    {
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 2] % mod + dp[i - 1] % mod;
        }
        return dp[n] % mod;
    }

    int countWays_optimized(int n)
    {
        int curr = 0;
        int prev1 = 1;
        int prev2 = 1;
        for (int i = 2; i <= n; i++)
        {
            curr = prev1 % mod + prev2 % mod;
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1 % mod;
    }
};

class FrogJump
{
public:
    int findMinCost(int idx, vector<int> &arr, int pathCost)
    {
        if (idx == 0)
        {
            return pathCost;
        }
        else
        {
            int cost1 = INT_MAX, cost2 = INT_MAX;
            cost1 = findMinCost(idx - 1, arr, pathCost) + abs(arr[idx] - arr[idx - 1]);
            // cout << "cost1 after recur : " << cost1 <<" - " << idx << endl;
            if (idx - 2 >= 0)
            {
                cost2 = findMinCost(idx - 2, arr, pathCost) + abs(arr[idx] - arr[idx - 2]);
            }
            // cout << "cost2 after recur : " << cost2 << " - " << idx << endl;
            // cout << "Current PathCost : " << pathCost << endl;
            pathCost = min(cost1, cost2);
            // cout << "Current minPathCost : " << pathCost << endl;
            return pathCost;
        }
    }

    int findMinCost_dp(int idx, vector<int> &dp, vector<int> &arr)
    {
        if (idx == 0)
        {
            return 0;
        }
        else if (dp[idx] != 1000000)
        {
            return dp[idx];
        }
        else
        {
            dp[idx] = findMinCost_dp(idx - 1, dp, arr) + abs(arr[idx] - arr[idx - 1]);
            if (idx - 2 >= 0)
            {
                dp[idx] = min(dp[idx], (findMinCost_dp(idx - 2, dp, arr) + abs(arr[idx] - arr[idx - 2])));
            }
            return dp[idx];
        }
    }
    int findMinCost_dp_tabulation(vector<int> &dp, vector<int> &arr)
    {
        dp[0] = 0;
        dp[1] = abs(arr[1] - arr[0]);
        for (int idx = 2; idx < arr.size(); idx++)
        {
            int c1 = abs(arr[idx] - arr[idx - 1]);
            int c2 = abs(arr[idx] - arr[idx - 2]);
            dp[idx] = min(dp[idx - 1] + c1, dp[idx - 2] + c2);
        }
        return dp[arr.size() - 1];
    }
    int findMinCost_dp_optimized(vector<int> &arr)
    {
        int prev1 = abs(arr[1] - arr[0]);
        int prev2 = 0;
        for (int idx = 2; idx < arr.size(); idx++)
        {
            int c1 = abs(arr[idx] - arr[idx - 1]);
            int c2 = abs(arr[idx] - arr[idx - 2]);
            int curr = min(prev1 + c1, prev2 + c2);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }

    //^ Follow up Question : allowed K jumps

        int frogJump(int n, vector<int> &heights, int k)
    {

        vector<int> dp(n, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i < n; i++)
        {

            for (int j = 1; j <= k; j++)
            {

                if (i >= j)
                {

                    dp[i] = min(dp[i], dp[i - j] + abs(heights[i] - heights[i - j]));
                }
            }
        }

        return dp[n - 1];
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}
