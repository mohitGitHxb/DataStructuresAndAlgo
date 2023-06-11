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

//^ Maximum sum of array such that no two elements are adjacent to each other
class HouseRobber
{
private:
public:
    int n;
    vector<int> dp;
    HouseRobber(int n)
    {
        this->n = n;
        this->dp.resize(n, -1);
    }
    int solve(vector<int> &arr, int idx)
    {
        if (idx == 0)
            return arr[idx];
        if (idx < 0)
            return 0;
        int pick = arr[idx] + solve(arr, idx - 2);
        int notpick = 0 + solve(arr, idx - 1);
        return max(pick, notpick);
    }

    int solve_memo(vector<int> &arr, int idx)
    {
        if (idx == 0)
            return arr[idx];
        if (idx < 0)
            return 0;
        if (dp[idx] != -1)
        {
            return dp[idx];
        }
        int pick = arr[idx] + solve_memo(arr, idx - 2);
        int notpick = 0 + solve_memo(arr, idx - 1);
        return dp[idx] = max(pick, notpick);
    }
    int solve_tabular(vector<int> &arr, int idx)
    {
        dp.at(0) = arr.at(0);
        for (int i = 1; i < arr.size(); i++)
        {
            int pick = (i > 1) ? arr.at(i) + dp[i - 2] : arr.at(i);
            int notPick = 0 + arr.at(i - 1);

            dp.at(i) = max(pick, notPick);
        }
        return dp.back();
    }
    int solve_optimized(vector<int> &arr, int idx)
    {
        int prev1 = arr.front();
        int prev2 = 0;
        for (int i = 1; i < arr.size(); i++)
        {
            int pick = (i > 1) ? arr.at(i) + prev2 : arr.at(i);
            int notPick = 0 + prev1;
            int curr = max(pick, notPick);
            prev2 = prev1;
            prev1 = curr;
        }
        return prev1;
    }
    //^ House Robber 2 [Follow up] what if the last house is adjacent to the first house
    int maximumSumWithoutRotation(vector<int> &nums)
    {
        int n = nums.size();
        int prev = nums[0];
        int prev2 = 0;

        for (int i = 0; i < n; i++)
        {
            int take = nums[i];
            if (i > 1)
                take += prev2;

            int notPick = 0 + prev;

            int curr = max(take, notPick);
            prev2 = prev;
            prev = curr;
        }
        return prev;
    }
    int rob(vector<int> &nums)
    {
        vector<int> temp1, temp2;
        if (nums.size() == 1)
            return nums.front();
        for (int i = 0; i < nums.size(); i++)
        {
            if (i != 0)
                temp1.push_back(nums.at(i));
            if (i != nums.size() - 1)
                temp2.push_back(nums.at(i));
        }

        return max(maximumSumWithoutRotation(temp1), maximumSumWithoutRotation(temp2));
    }
};

//^ Ninja's training ( Similar to House Robber but in 2D)
class Training
{
private:
    /*
&    Step 1: Express the problem in terms of indexes.

&Now given an example, what is the one clear parameter which breaks the problem in different steps?
It is the number of days. Clearly, we have n days (from 0 to n-1), so one changing parameter which can be expressed in terms of indexes is ‘day’.

&Every day we have the option of three activities(say 0,1,2) to be performed. Suppose that we are at a day_i ( shown in the fig) in the example given below. What is one more parameter along with the day that we must know to try out the correct choices at day_i?

&It is the ‘last’ choice that we tried out on day_i+1 ( i+1 in case of top-down recursion). Unless we know the last choice we made, how can we decide whether a choice we are making is correct or not?
&Now there are three options each day(say 0,1,2) which becomes the ‘last’ of the next day. If we are just starting from the day_n-1, then for the day_n-1 we can try all three options. We can say ‘last’ for day_n-1 is 3.

&Therefore our function will take two parameters – day and last.

&   Step 2: Try out all possible choices at a given index.

&   We are writing a top-down recursive function. We start from day_n-1 to day_0. Therefore whenever we call the recursive function for the next day we call it for f(day-1, //second parameter).
&   Now let’s discuss the second parameter. The choices we have for a current day depend on the ‘last’ variable. If we are at our base case (day=0), we will have the following choices.

&   Other than the base case, whenever we perform an activity ‘i’ its merit points will be given by points[day][i] and to get merit points of the remaining days we will let recursion do its job by passing f(d-1, i). We are passing the second parameter as i because the current day’s activity will become the next day’s last.

Step 3:  Take the maximum of all choices

& As the problem statement wants us to find the maximum merit points, we will take the maximum of all choices.


Steps to memoize a recursive solution:

& If we draw the recursion tree, we will see that there are overlapping subproblems. In order to convert a recursive solution to the following steps will be taken:

&     Create a dp array of size [n][4]. There are total ‘n’ days and for every day, there can be 4 choices (0,1,2 and 3). Therefore we take the dp array as dp[n][4].
&    Whenever we want to find the answer of particular parameters (say f(day,last)), we first check whether the answer is already calculated using the dp array(i.e dp[day][last]!= -1 ). If yes, simply return the value from the dp array.
&    If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[day][last] to the solution we get.
s
     */
public:
    int f(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp)
    {

        if (dp[day][last] != -1)
            return dp[day][last];

        if (day == 0)
        {
            int maxi = 0;
            for (int i = 0; i <= 2; i++)
            {
                if (i != last)
                    maxi = max(maxi, points[0][i]);
            }
            return dp[day][last] = maxi;
        }

        int maxi = 0;
        for (int i = 0; i <= 2; i++)
        {
            if (i != last)
            {
                int activity = points[day][i] + f(day - 1, i, points, dp);
                maxi = max(maxi, activity);
            }
        }

        return dp[day][last] = maxi;
    }

    /*
    @ Tabulation
    &    Declare a dp[] array of size [n][4]
&    First initialize the base condition values. We know that base condition arises when day = 0. Therefore, we can say that the following will be the base conditions
&        dp[0][0] = max(points[0][1], points[0][2])
&        dp[0][1] = max(points[0][0], points[0][2])
&        dp[0][2] = max(points[0][0], points[0][1])
&        dp[0][3] = max(points[0][0], points[0][1] and points[0][2])
&    Set an iterative loop which traverses dp array (from index 1 to n) and for every index set its value according to the recursive logic

* O(12N) T.C | O(4N) S.C
     */

    int ninjaTraining(int n, vector<vector<int>> &points)
    {
        vector<vector<int>> dp(n, vector<int>(4, 0));
        dp[0][0] = max(points[0][1], points[0][2]);
        dp[0][1] = max(points[0][0], points[0][2]);
        dp[0][2] = max(points[0][0], points[0][1]);
        dp[0][3] = max(points[0][0], max(points[0][2], points[0][1]));
        for (int day = 1; day < n; day++)
        {
            for (int last = 0; last < 4; last++)
            {
                dp[day][last] = 0;

                for (int task = 0; task < 3; task++)
                {
                    int point = points[day][task] + dp[day - 1][task];
                    dp[day][last] = max(dp[day][task], point);
                }
            }
        }
        return dp[n - 1][3];
    }
    /*
    @ Space Optimization
~    If we closely look the relation,

&dp[day][last] =  max(dp[day][last],points[day][task] + dp[day-1][task])

&Here the task can be anything from 0 to 3 and day-1 is the previous stage of recursion. So in order to compute any dp array value, we only require the last row to calculate it.

&    So rather than storing the entire 2D Array of size N*4, we can just store values of size 4(say prev).
&    We can then take a dummy array, again of size 4 (say temp) and calculate the next row’s value using the array we stored in step 1.
&    After that whenever we move to the next day, the temp array becomes our prev for the next step.
&    At last prev[3] will give us the answer.
* O(12N) T.C | O(4) S.C
     */

    int ninjaTraining_optimized(int n, vector<vector<int>> &points)
    {

        vector<int> prev(4, 0);

        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max(points[0][0], max(points[0][1], points[0][2]));

        for (int day = 1; day < n; day++)
        {

            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++)
            {
                temp[last] = 0;
                for (int task = 0; task <= 2; task++)
                {
                    if (task != last)
                    {
                        temp[last] = max(temp[last], points[day][task] + prev[task]);
                    }
                }
            }

            prev = temp;
        }

        return prev[3];
    }
};
int main(int argc, char const *argv[])
{

    return 0;
}
