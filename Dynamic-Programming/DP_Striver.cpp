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
    /*
        & This code implements a recursive function countWays_Recursive to calculate the number of ways to reach a given step n using either 1 or 2 steps at a time. The function returns the count of possible ways modulo a specified value mod.

& The function countWays_Recursive takes an integer n as input.

& The base cases are handled as follows:
~ If the value of n is less than 0, indicating an invalid step, the function returns 0.
~ If the value of n is 0, indicating that the destination step has been reached, the function returns 1, as there is one way to reach that step (by not taking any step).

& The function recursively calls itself twice:
~ countWays_Recursive(n - 1) % mod represents the count of ways to reach the step n - 1 using 1 or 2 steps at a time.
~ countWays_Recursive(n - 2) % mod represents the count of ways to reach the step n - 2 using 1 or 2 steps at a time.

& The results of the recursive calls are summed up, and the modulo operation with mod is performed to calculate the total count of ways to reach the step n.
     */
    int countWays_Recursive(int n)
    {
        if (n < 0)
            return 0;
        if (n == 0)
            return 1;
        return countWays_Recursive(n - 1) % mod + countWays_Recursive(n - 2) % mod;
    }
    /*
    &- The code implements a function countWays_Memoization that uses memoization to calculate the number of ways to reach a given step n using either 1 or 2 steps at a time. The function returns the count of possible ways modulo a specified value mod.

    &- The function countWays_Memoization takes a reference to a vector dp and an integer n as inputs.

    &- The vector dp is used to store the computed results for each step to avoid redundant calculations.

    &- The base cases are handled as follows:
    ~ If the value of n is less than 0, indicating an invalid step, the function returns 0.
    ~ If the value of n is 0, indicating that the destination step has been reached, the function returns 1, as there is one way to reach that step (by not taking any step).

    &- Before proceeding with the recursive calls, the function checks if the result for the current step n is already computed and stored in the dp vector. If it is, the function returns the stored result (dp[n] % mod).

    &- If the result for the current step n is not computed yet, the function recursively calls itself twice:
    ~ countWays_Memoization(dp, n - 1) % mod represents the count of ways to reach the step n - 1 using 1 or 2 steps at a time.
    ~ countWays_Memoization(dp, n - 2) % mod represents the count of ways to reach the step n - 2 using 1 or 2 steps at a time.

    &- The results of the recursive calls are summed up, and the modulo operation with mod is performed to calculate the total count of ways to reach the step n. The result is stored in the dp vector at the index n for future use.
     */
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

    /*
    &- The code implements a function countWays_Tabulation that uses tabulation to calculate the number of ways to reach a given step n using either 1 or 2 steps at a time. The function returns the count of possible ways modulo a specified value mod.

    &- The function countWays_Tabulation takes a reference to a vector dp and an integer n as inputs.

    &- The vector dp is used as a table to store the computed results for each step.

    &- The base cases are handled as follows:
    ~ dp[0] = dp[1] = 1 indicates that there is one way to reach step 0 and step 1.

    &- The function uses a loop to iteratively calculate the results for each step starting from 2 up to n.
    ~ dp[i] = dp[i - 2] % mod + dp[i - 1] % mod represents the count of ways to reach step i by summing up the counts for reaching step i - 2 and step i - 1 using 1 or 2 steps at a time.

    &- Finally, the function returns dp[n] % mod, which represents the count of ways to reach the step n modulo mod.

    ? Now, let's see how this code can be derived from the previous memoization code:

    ?    Initialize dp[0] = dp[1] = 1 to store the base case results.
    ?    Replace the memoization check in the previous code with the assignment statement: dp[n] = dp[n - 2] % mod + dp[n - 1] % mod.
    ?    Return dp[n] % mod as the final result.

    ? By making these changes, we transform the memoization code into the tabulation code. The tabulation code directly fills up the dp table by iteratively computing the results for each step, whereas the memoization code stores the computed results in the dp table on-demand during recursive calls.
    */
    int countWays_Tabulation(vector<int> &dp, int n)
    {
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 2] % mod + dp[i - 1] % mod;
        }
        return dp[n] % mod;
    }
    /*
    @ The optimization process involves using only three variables (curr, prev1, prev2) instead of an array or vector to store the counts, reducing the space complexity to constant O(1) space. By updating the variables in each iteration, we avoid the overhead of maintaining a separate array or vector, resulting in an optimized implementation.
    &- The function countWays_optimized takes an integer n as input.

&- Three variables are used to track the counts:
~ curr stores the current count of ways to reach the current step.
~ prev1 stores the count of ways to reach the previous step.
~ prev2 stores the count of ways to reach the step before the previous step.

&- The base cases are handled as follows:
~ prev1 = prev2 = 1 indicates that there is one way to reach step 0 and step 1.

&- The function uses a loop to iteratively calculate the counts for each step starting from 2 up to n.
~ curr = prev1 % mod + prev2 % mod calculates the count of ways to reach the current step i by summing up the counts for reaching the previous step i - 1 and the step before the previous step i - 2.

&- In each iteration of the loop, the values of prev1 and prev2 are updated:
~ prev2 = prev1 assigns the value of prev1 to prev2, which updates the count for the step before the previous step.
~ prev1 = curr assigns the current count curr to prev1, which updates the count for the previous step.

&- After the loop completes, the final count of ways to reach the step n is stored in prev1.

&- Finally, the function returns prev1 % mod, which represents the count of ways to reach the step n modulo mod.
     */
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
            if (idx - 2 >= 0)
            {
                cost2 = findMinCost(idx - 2, arr, pathCost) + abs(arr[idx] - arr[idx - 2]);
            }
            pathCost = min(cost1, cost2);
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

class UniquePaths
{
public:
    /*
    @ Recursion approach
    &- The code includes a function called uniquePaths that takes the current row (row), current column (col), the grid, and a string path as input.

    &- The base case of the recursion is when the function reaches the top-left corner of the grid (row == 0 and col == 0).
    ~ In this case, it prints the current path using cout << path << "\n".
    ~ It returns 1 to indicate that a unique path has been found.

    &- The function initializes two variables left and right to keep track of the number of unique paths.
    ~ left represents the number of unique paths when moving leftwards (decreasing the row).
    ~ right represents the number of unique paths when moving downwards (decreasing the column).

    &- If there is a valid move to the left (i.e., row - 1 >= 0), the function considers that move:
    ~ It appends 'R' (representing a rightward movement) to the path string.
    ~ It recursively calls the uniquePaths function with the updated row (row - 1), the same column (col), the grid, and the updated path.
    ~ After the recursive call, it removes the last character from the path string using path.pop_back() to backtrack.

    &- If there is a valid move downwards (i.e., col - 1 >= 0), the function considers that move:
    ~ It appends 'D' (representing a downward movement) to the path string.
    ~ It recursively calls the uniquePaths function with the same row (row), the updated column (col - 1), the grid, and the updated path.
    ~ After the recursive call, it removes the last character from the path string using path.pop_back() to backtrack.

    &- Finally, the function returns the sum of left and right, representing the total number of unique paths found so far.

    ! O(M^N) T.C | O(M+N) S.C
     */
    int uniquePaths(int row, int col, vector<vector<int>> &grid, string &path)
    {
        if (row == 0 && col == 0)
        {
            cout << path << "\n";
            return 1;
        }
        int left = 0, right = 0;
        if (row - 1 >= 0)
        {
            path.push_back('R');
            left = uniquePaths(row - 1, col, grid, path);
            path.pop_back();
        }
        if (col - 1 >= 0)
        {
            path.push_back('D');
            right = uniquePaths(row, col - 1, grid, path);
            path.pop_back();
        }
        return (left + right);
    }
    /*
    @ Memoization
    &- The code includes a function called uniquePaths_memoized that takes the current row (row), current column (col), and the memoization table (dp) as input.

&- The base case of the recursion is when the function reaches the top-left corner of the grid (row == 0 and col == 0).
~ In this case, it returns 1 to indicate that a unique path has been found.

&- The function initializes two variables left and right to keep track of the number of unique paths when moving leftwards (decreasing the row) and downwards (decreasing the column), respectively.

&- If there is a valid move to the left (i.e., row - 1 >= 0), the function considers that move:
~ It checks if the value for the left cell (dp[row - 1][col]) is already computed and stored in the memoization table (dp).
~ If the value is available in the memoization table, it assigns it to left.
~ Otherwise, it recursively calls the uniquePaths_memoized function with the updated row (row - 1), the same column (col), and the memoization table (dp).

&- If there is a valid move downwards (i.e., col - 1 >= 0), the function considers that move:
~ It checks if the value for the cell below (dp[row][col - 1]) is already computed and stored in the memoization table (dp).
~ If the value is available in the memoization table, it assigns it to right.
~ Otherwise, it recursively calls the uniquePaths_memoized function with the same row (row), the updated column (col - 1), and the memoization table (dp).

&- Finally, the function assigns the sum of left and right to the current cell in the memoization table (dp[row][col]).
~ This value represents the total number of unique paths to reach the current cell.
~ It also returns the computed value.
* O(MxN) T.C || O(MxN) + O(M+N) S.C
     */
    int uniquePaths_memoized(int row, int col, vector<vector<int>> &dp)
    {
        if (row == 0 && col == 0)
            return 1;
        int left = 0, right = 0;
        if (row - 1 >= 0)
        {
            if (dp[row - 1][col] != -1)
                left = dp[row - 1][col];
            else
                left = uniquePaths_memoized(row - 1, col, dp);
        }
        if (col - 1 >= 0)
        {
            if (dp[row][col - 1] != -1)
                right = dp[row][col - 1];
            else
                right = uniquePaths_memoized(row, col - 1, dp);
        }
        return dp[row][col] = (left + right);
    }
    /*
    @ Tabulation
    &- The code includes a function called uniquePaths_tabulation that takes the number of rows (row), number of columns (col), and the DP table (dp) as input.

&- The function initializes the top-left cell in the DP table (dp[0][0]) to 1 since there is only one way to reach that cell.

&- It then iterates through each cell in the grid using two nested loops:
~ The outer loop represents the rows, ranging from 0 to row - 1.
~ The inner loop represents the columns, ranging from 0 to col - 1.

&- At each cell (i, j), the function checks if it's the top-left corner. If so, it skips the current iteration using the continue statement since the top-left corner is already initialized.

&- For each non-top-left cell, the function computes the number of unique paths to reach that cell by summing the number of paths from the cell above (dp[i - 1][j]) and the cell to the left (dp[i][j - 1]).
~ The variables left and right store the number of paths from the above and left cells, respectively.
~ If there is no cell above (i - 1 < 0), left is set to 0.
~ If there is no cell to the left (j - 1 < 0), right is set to 0.
~ The number of paths to reach the current cell (dp[i][j]) is then computed as the sum of left and right.

&- After filling in the DP table, the function returns the value at the bottom-right corner (dp[row - 1][col - 1]), which represents the total number of unique paths to reach that corner.
* O(M*N) T.C | O(MxN) S.C
     */
    int uniquePaths_tabulation(int row, int col, vector<vector<int>> &dp)
    {
        dp[0][0] = 1;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (i == 0 && j == 0)
                    continue;
                int left = (i - 1 >= 0) ? dp[i - 1][j] : 0;
                int right = (j - 1 >= 0) ? dp[i][j - 1] : 0;
                dp[i][j] = left + right;
            }
        }

        return dp[row - 1][col - 1];
    }
    /*
    @ Space Optimization
    &- The code includes a function called uniquePaths_optimized that takes the number of rows (row) and number of columns (col) as input.

&- The function initializes the prevRow vector with col number of zeros. This vector represents the previous row in the grid.

&- The algorithm iterates through each row in the grid using the outer loop:
~ It creates a temp vector with col number of zeros to store the number of paths for the current row.
~ The inner loop iterates through each column in the grid.
~ For each cell (i, j), the algorithm checks if it's the top-left corner. If so, it sets the value in temp at index j to 1, representing the only possible path to reach the top-left corner.

&- For each non-top-left cell, the algorithm computes the number of unique paths to reach that cell by summing the number of paths from the cell above (prevRow[j]) and the cell to the left (temp[j - 1]).
~ The variables left and right store the number of paths from the left and above cells, respectively.
~ If there is no cell above (i > 0), right is set to 0.
~ If there is no cell to the left (j > 0), left is set to 0.
~ The number of paths to reach the current cell (temp[j]) is then computed as the sum of left and right.

&- After processing each column in the current row, the temp vector becomes the new prevRow vector for the next row.

&- Once the algorithm completes iterating through all rows, it returns the value at the last index of the prevRow vector (prevRow[col - 1]), representing the total number of unique paths to reach the bottom-right corner.
* O(M*N) T.C | O(N) S.C
     */
    int uniquePaths_optimized(int row, int col)
    {
        vector<int> prevRow(col, 0);
        for (int i = 0; i < row; i++)
        {
            vector<int> temp(col, 0);
            for (int j = 0; j < col; j++)
            {
                if (i == 0 && j == 0)
                    temp[j] = 1;
                else
                {
                    int left = 0, right = 0;
                    if (i > 0)
                        right = prevRow[j];
                    if (j > 0)
                        left = temp[j - 1];
                    temp[j] = left + right;
                }
            }
            prevRow = temp;
        }
        return prevRow[col - 1];
    }
    //^ Same problem as above but this time we have obstacles
    int uniquePaths2(int i, int j, vector<vector<int>> &grid)
    {
        if (i >= 0 && j >= 0 && grid[i][j] == -1)
            return 0;
        if (i == 0 && j == 0)
        {
            return 1;
        }
        if (i < 0 || j < 0)
        {
            return 0;
        }
        int up = uniquePaths2(i - 1, j, grid);
        int left = uniquePaths2(i, j - 1, grid);
        return up + left;
    }

    int uniquePaths2_memoized(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (i >= 0 && j >= 0 && grid[i][j] == -1)
        {
            return 0;
        }
        if (i == 0 && j == 0)
        {
            return 1;
        }
        if (i < 0 || j < 0)
        {
            return 0;
        }
        if (dp[i][j] != -1)
            return dp[i][j];
        int up = uniquePaths2_memoized(i - 1, j, grid, dp);
        int left = uniquePaths2_memoized(i, j - 1, grid, dp);
        return dp[i][j] = up + left;
    }

    int uniquePaths2_tabulation(vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        dp[0][0] = 1;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == -1)
                    dp[i][j] = 0;
                if (i == 0 && j == 0)
                    dp[i][j] = 1;
                int left = (i - 1 >= 0) ? dp[i - 1][j] : 0;
                int right = (j - 1 >= 0) ? dp[i][j - 1] : 0;
                dp[i][j] = left + right;
            }
        }

        return dp[grid.size() - 1][grid.back().size() - 1];
    }
    int uniquePaths2_optimized(vector<vector<int>> &grid)
    {
        vector<int> prev(grid.front().size());
        for (int i = 0; i < grid.size(); i++)
        {
            vector<int> curr(grid.at(i).size());
            for (int j = 0; j < grid[i].size(); j++)
            {
                if (grid[i][j] == 1)
                    curr[j] = 0;
                else if (i == 0 && j == 0)
                    curr[j] = 1;
                else
                {

                    int up = (i - 1 >= 0) ? prev[j] : 0;
                    int left = (j - 1 >= 0) ? curr[j - 1] : 0;
                    curr[j] = left + up;
                }
            }
            prev = curr;
        }
        return prev.back();
    }
};

class MinimumPathSum
{
public:
    /*
    @ Recursion
    &- The code includes a function called minimumPathSum that takes the current row (r), current column (c), and a matrix (mat) as input.

    &- The base case of the recursion is when the algorithm reaches the top-left corner of the grid (r == 0 and c == 0). In this case, it simply returns the value at the top-left cell of the matrix (mat[0][0]).

    &- Another base case is when the algorithm goes out of bounds of the grid (r < 0 or c < 0). In this case, it returns a large value (10e7) to ensure it doesn't affect the minimum calculation in the subsequent recursive calls.

    &- The algorithm recursively explores two directions: left and up. It calculates the minimum path sum for each direction by adding the value of the current cell (mat[r][c]) to the minimum path sum of the previous cell in that direction. The minimum path sum is computed by recursively calling the minimumPathSum function with updated row and column indices.

    &- Finally, the algorithm returns the minimum sum among the two paths, obtained using the min function.

    !The time complexity of this recursive approach can be quite high because it explores all possible paths from the top-left corner to the bottom-right corner. In the worst case, where the grid size is m x n, the number of recursive calls can be exponential, leading to a time complexity of O(2^(m+n)).

    !The space complexity of the recursive approach depends on the depth of the recursive calls, which is determined by the maximum distance from the top-left corner to any cell in the grid. In the worst case, the depth of the recursive calls can be m + n, resulting in a space complexity of O(m + n) for the call stack.
     */
    int minimumPathSum(int r, int c, vector<vector<int>> &mat)
    {
        if (r == 0 && c == 0)
        {
            return mat[0][0];
        }
        if (r < 0 || c < 0)
        {
            return 10e7;
        }
        int left = mat[r][c] + minimumPathSum(r, c - 1, mat);
        int up = mat[r][c] + minimumPathSum(r - 1, c, mat);
        return min(left, up);
    }
    /*
    @
    &- The code includes a function called minimumPathSum_memoized that takes the current row (r), current column (c), the matrix (mat), and a memoization array (dp) as input.

&- The base cases and recursive logic are similar to the previous implementation. The function checks if the current cell has already been computed and stored in the dp array. If it has, it simply returns the stored value, avoiding redundant computations.

&- If the current cell's value has not been computed, the function calculates the minimum path sum for the current cell by adding the value of the current cell (mat[r][c]) to the minimum path sum of the previous cell in the left and up directions. The minimum path sum is computed by recursively calling the minimumPathSum_memoized function with updated row and column indices.

&- Finally, the minimum path sum for the current cell is stored in the dp array before being returned.

* The time complexity of this memoized approach is significantly improved compared to the previous recursive approach. Since each cell's value is computed only once and stored in the dp array, the number of computations is reduced. In the worst case, where the grid size is m x n, the time complexity is O(m * n).

* The space complexity of this approach is O(m * n) as well. It is determined by the size of the dp array, which has the same dimensions as the input grid. The memoization array stores the minimum path sum for each cell, reducing the need for redundant computations.
     */
    int minimumPathSum_memoized(int r, int c, vector<vector<int>> &mat, vector<vector<int>> &dp)
    {
        if (r == 0 && c == 0)
        {
            return mat[0][0];
        }
        if (r < 0 || c < 0)
        {
            return 10e7;
        }
        if (dp[r][c] != 10e7)
            return dp[r][c];
        int left = mat[r][c] + minimumPathSum(r, c - 1, mat);
        int up = mat[r][c] + minimumPathSum(r - 1, c, mat);
        return dp[r][c] = min(left, up);
    }

    /*
    @ Tabulation
    &- The code includes a function called minimumPathSum_tabulation that takes the number of rows (r), number of columns (c), the matrix (mat), and a tabulation array (dp) as input.

&- The function uses nested loops to iterate through each cell in the matrix. For each cell, it calculates the minimum path sum by considering the minimum of the path sum from the left and the path sum from above. The minimum path sum is computed by adding the current cell's value to the minimum path sum of the previous cells.

&- The first cell (top-left corner) is treated as a special case. Its minimum path sum is equal to its own value since there are no previous cells.

&- The calculated minimum path sum for each cell is stored in the dp array.

&- Finally, the function returns the minimum path sum stored in the bottom-right cell of the dp array.

*  The time complexity of this tabulation approach is O(r * c) since it iterates through each cell once to fill the dp array.

*  The space complexity of this approach is also O(r * c) since it uses the dp array to store the minimum path sums for each cell. The space required is proportional to the size of the input matrix.
     */
    int minimumPathSum_tabulation(int r, int c, vector<vector<int>> &mat, vector<vector<int>> &dp)
    {
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (i == 0 && j == 0)
                {
                    dp[0][0] = mat[0][0];
                    continue;
                }
                int left = 10e7, up = 10e7;
                if (j - 1 >= 0)
                {
                    left = mat[i][j] + dp[i][j - 1];
                }
                if (i - 1 >= 0)
                {
                    up = mat[i][j] + dp[i - 1][j];
                }
                dp[i][j] = min(left, up);
            }
        }
        return dp[r - 1][c - 1];
    }
    /*
    @ Space optimization
    &- The code includes a function called minimumPathSum_optimized that takes the number of rows (r), number of columns (c), and the matrix (mat) as input.

&- The function initializes a vector prev with size equal to the number of columns (c). This vector represents the minimum path sums for the previous row.

&- It then uses nested loops to iterate through each cell in the matrix. For each cell, it calculates the minimum path sum by considering the minimum of the path sum from the left (using the current row's temp vector) and the path sum from above (using the previous row's prev vector). The minimum path sum is computed by adding the current cell's value to the minimum path sum of the adjacent cells.

&- The first cell (top-left corner) is treated as a special case. Its minimum path sum is equal to its own value since there are no previous cells.

&- The calculated minimum path sum for each cell is stored in the temp vector.

&- After iterating through all cells in a row, the prev vector is updated with the values from the temp vector, representing the minimum path sums for the current row.

&- Finally, the function returns the last element of the prev vector, which represents the minimum path sum for the bottom-right cell of the matrix.

* The time complexity of this optimized approach is O(r * c) since it iterates through each cell once to calculate the minimum path sum.

* The space complexity of this approach is O(c) since it only uses two vectors (prev and temp) of size equal to the number of columns (c). The space required is proportional to the number of columns in the input matrix.
     */
    int minimumPathSum_optimized(int r, int c, vector<vector<int>> &mat)
    {
        vector<int> prev(c);
        for (int i = 0; i < r; i++)
        {
            vector<int> temp(c);
            for (int j = 0; j < c; j++)
            {
                if (i == 0 && j == 0)
                {
                    temp[0] = mat[0][0];
                    continue;
                }
                int left = 10e7, up = 10e7;
                if (j - 1 >= 0)
                {
                    left = mat[i][j] + temp[j - 1];
                }
                if (i - 1 >= 0)
                {
                    up = mat[i][j] + prev[j];
                }
                temp[j] = min(left, up);
            }
            prev = temp;
        }
        return prev.back();
    }
};

class TriangleSum
{

public:
    /*
    @ Recursion

    ! O(2^N) T.C | O(N) S.C
     */
    int minimumTriangleSum(int r, int c, vector<vector<int>> &triangle)
    {
        if (r == triangle.size() - 1)
        {
            return triangle.back().at(c);
        }
        int down = 10e7, downright = 10e7;
        if (r + 1 < triangle.size())
            down = triangle[r][c] + minimumTriangleSum(r + 1, c, triangle);
        downright = triangle[r][c] + minimumTriangleSum(r + 1, c + 1, triangle);
        return min(down, downright);
    }
    /*
    @ Memoization

    *O(N^2) T.C | O(N) + O(N^2) S.C
     */

    int minimumTriangleSum_memo(int r, int c, vector<vector<int>> &triangle, vector<vector<int>> &dp)
    {
        if (r == triangle.size() - 1)
        {
            return triangle.back().at(c);
        }
        int down = 10e7, downright = 10e7;
        if (dp[r][c] != -1)
        {
            return dp[r][c];
        }
        if (r + 1 < triangle.size())
            down = triangle[r][c] + minimumTriangleSum_memo(r + 1, c, triangle, dp);
        downright = triangle[r][c] + minimumTriangleSum_memo(r + 1, c + 1, triangle, dp);
        return dp[r][c] = min(down, downright);
    }
    /*
    @ Tabulation
    * O(N^2) T.C | O(N^2) S.C
     */
    int minimumTriangleSum_tabulation(int r, int c, vector<vector<int>> &triangle, vector<vector<int>> &dp)
    {
        for (int i = 0; i < triangle.size(); i++)
            dp[triangle.size() - 1][i] = triangle.back()[i];
        for (int i = triangle.size() - 2; i >= 0; i--)
        {
            for (int j = i; j >= 0; i--)
            {
                int down = triangle[i][j] + dp[i + 1][j];
                int downright = triangle[i][j] + dp[i + 1][j + 1];
                dp[i][j] = min(down, downright);
            }
        }
        return dp[0][0];
    }
    /*
    @ Space optimization
    * O(N^2) T.C | O(N) S.C
     */
    int minimumTriangleSum_optimized(int r, int c, vector<vector<int>> &triangle)
    {
        vector<int> front(triangle.back().size()), curr(triangle.front().size());
        for (int i = 0; i < triangle.size(); i++)
            front[i] = triangle.back()[i];
        for (int i = triangle.size() - 2; i >= 0; i--)
        {
            for (int j = i; j >= 0; i--)
            {
                int down = triangle[i][j] + front[j];
                int downright = triangle[i][j] + front[j + 1];
                curr[j] = min(down, downright);
            }
            front = curr;
        }
        return front.front();
    }
};

//^ Maximum falling path sum
class MaximumSum
{
public:
    /*
    @ Recursion


& This code includes a function called maximumSum that takes a 2D matrix (mat), a current row index (i), and a current column index (j) as input.

& The function first checks if the current column index is out of bounds (less than 0 or greater than or equal to the number of columns in the first row of the matrix). If so, it returns a very small value (-10e7) indicating an invalid path.

& If the current row index is 0 (indicating the first row), it returns the value of the corresponding cell in the first row. This is the base case for the recursion.

& If the current row index is not 0, the function recursively calculates the maximum sum by considering three possible paths:

~    Upward path: The function recursively calls maximumSum with the previous row index (i - 1) and the same column index (j). It adds the value of the current cell to the maximum sum of the upward path.

~    Right diagonal path: The function recursively calls maximumSum with the previous row index (i - 1) and the next column index (j + 1). It adds the value of the current cell to the maximum sum of the right diagonal path.

~    Left diagonal path: The function recursively calls maximumSum with the previous row index (i - 1) and the previous column index (j - 1). It adds the value of the current cell to the maximum sum of the left diagonal path.

& Finally, the function returns the maximum value among the three calculated sums using the max function.

? The recursive approach explores all possible paths from the top to the bottom of the matrix, considering the maximum sum at each step. It effectively evaluates the sum of all possible paths and returns the maximum sum achieved.

? However, note that the given code does not perform any memoization or dynamic programming optimization, so it may have exponential time complexity and repeated calculations for overlapping subproblems. To optimize the solution, one could incorporate memoization or dynamic programming techniques to store and reuse intermediate results, reducing the time complexity to a more efficient leve
    ! O(3^N) T.C | O(N) S.C
     */
    int maximumSum(vector<vector<int>> &mat, int i, int j)
    {
        if (j < 0 || j >= mat.front().size())
        {
            return -10e7;
        }
        if (i == 0)
            return mat.front().at(j);
        int up = mat[i][j] + maximumSum(mat, i - 1, j);
        int rightDiagonal = mat[i][j] + maximumSum(mat, i - 1, j + 1);
        int leftDiagonal = mat[i][j] + maximumSum(mat, i - 1, j - 1);
        return max(up, max(leftDiagonal, rightDiagonal));
    }
    /*
    @ Memoization
    & This code includes a function called maximumSum_memo that takes a 2D matrix (mat), a current row index (i), a current column index (j), and a memoization table (dp) as input.

& The function first checks if the current column index is out of bounds (less than 0 or greater than or equal to the number of columns in the first row of the matrix). If so, it returns a very small value (-10e7) indicating an invalid path.

& If the current row index is 0 (indicating the first row), it returns the value of the corresponding cell in the first row. This is the base case for the recursion.

& Next, the function checks if the value for the current cell has already been calculated and stored in the memoization table (dp). If so, it directly returns the stored value instead of recomputing it.

& If the value for the current cell has not been memoized, the function recursively calculates the maximum sum by considering three possible paths:

~    Upward path: The function recursively calls maximumSum_memo with the previous row index (i - 1) and the same column index (j). It adds the value of the current cell to the maximum sum of the upward path.

~    Right diagonal path: The function recursively calls maximumSum_memo with the previous row index (i - 1) and the next column index (j + 1). It adds the value of the current cell to the maximum sum of the right diagonal path.

~    Left diagonal path: The function recursively calls maximumSum_memo with the previous row index (i - 1) and the previous column index (j - 1). It adds the value of the current cell to the maximum sum of the left diagonal path.

& Finally, the function calculates the maximum sum among the three calculated sums using the max function and stores the result in the memoization table (dp) for future reference.

& The function returns the memoized maximum sum for the current cell.

~ By using memoization, the function avoids redundant calculations for overlapping subproblems. It stores the results of already computed subproblems in the memoization table, allowing them to be reused when needed, which improves the overall efficiency of the solution.

* The time complexity of this memoized solution depends on the number of unique subproblems, which is determined by the size of the matrix. Therefore, the time complexity is O(r * c), where r is the number of rows and c is the number of columns in the matrix. The space complexity is also O(r * c) to store the memoization table.
     */
    int maximumSum_memo(vector<vector<int>> &mat, int i, int j, vector<vector<int>> &dp)
    {
        if (j < 0 || j >= mat.front().size())
        {
            return -10e7;
        }
        if (i == 0)
            return mat.front().at(j);
        if (dp[i][j] != -10e7)
            return dp[i][j];
        int up = mat[i][j] + maximumSum_memo(mat, i - 1, j, dp);
        int rightDiagonal = mat[i][j] + maximumSum_memo(mat, i - 1, j + 1, dp);
        int leftDiagonal = mat[i][j] + maximumSum_memo(mat, i - 1, j - 1, dp);
        return dp[i][j] = max(up, max(leftDiagonal, rightDiagonal));
    }
    /*
    @ Tabulation
    & Initialize the first row of the memoization table (dp) with the values from the first row of the matrix.
& Iterate over the remaining rows of the matrix starting from the second row.
~ For each cell in the current row:
~ Calculate the maximum sum considering three possible paths: upward, left diagonal, and right diagonal.
- Upward path: Add the value of the current cell to the value of the corresponding cell in the previous row (dp[i - 1][j]).
- Left diagonal path: If the current cell is not in the leftmost column, add the value of the current cell to the value of the cell in the previous row and previous column (dp[i - 1][j - 1]).
- Right diagonal path: If the current cell is not in the rightmost column, add the value of the current cell to the value of the cell in the previous row and next column (dp[i - 1][j + 1]).
~ Update the current cell in the memoization table (dp[i][j]) with the maximum value among the three paths calculated.
& Find the maximum value in the last row of the memoization table (dp) and store it in the variable ans.
& Return the value of ans, which represents the maximum sum.
    *O(N*M) T.C | O(N*M) S.C
     */
    int maximumSum_tabulation(vector<vector<int>> &mat, vector<vector<int>> &dp)
    {
        for (int i = 0; i < mat.back().size(); i++)
        {
            dp.front().at(i) = mat.front().at(i);
        }

        for (int i = 1; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                int up = mat[i][j] + dp[i - 1][j];
                int leftDiagonal = (j >= 1) ? (mat[i][j] + dp[i - 1][j - 1]) : -10e7;
                int rightDiagonal = (j < mat[i].size() - 1) ? (mat[i][j] + dp[i - 1][j + 1]) : -10e7;

                dp[i][j] = max(up, max(leftDiagonal, rightDiagonal));
            }
        }

        int ans = -10e7;
        for (int i = 0; i < mat[0].size(); i++)
        {
            ans = max(ans, dp.back()[i]);
        }
        return ans;
    }
    /*
    @ Space optimization
    *O(N*M) T.C | O(M) S.C
 &   If we closely look the relation,

&dp[i][j] = matrix[i][j] + max(dp[i-1][j],dp[i-1][j-1], dp[i-1][j+1]))

&We see that we only need the previous row, in order to calculate dp[i][j]. Therefore we can space optimize it.

&Initially, we can take a dummy row ( say prev). We initialize this row to the input matrix’s first row( as done in tabulation).

&Now the current row(say cur) only needs the prev row’s value inorder to calculate dp[i][j].
     */
    int maximumSum_optimized(vector<vector<int>> &mat)
    {
        vector<int> prevRow(mat.size()), cur(mat.size());
        for (int i = 0; i < mat.back().size(); i++)
        {
            prevRow.at(i) = mat.front().at(i);
        }

        for (int i = 1; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[i].size(); j++)
            {
                int up = mat[i][j] + prevRow[j];
                int leftDiagonal = (j >= 1) ? (mat[i][j] + prevRow[j - 1]) : -10e7;
                int rightDiagonal = (j < mat[i].size() - 1) ? (mat[i][j] + prevRow[j + 1]) : -10e7;

                cur[j] = max(up, max(leftDiagonal, rightDiagonal));
            }
            prevRow = cur;
        }

        int ans = -10e7;
        for (int i = 0; i < mat[0].size(); i++)
        {
            ans = max(ans, prevRow[i]);
        }
        return ans;
    }
};

//^ Cherry pickup 2 [3D DP]
class Cherry
{
public:
    /*
    @ Recursion
&     Express the problem in terms of indexes.

& This question is slightly different from all the previous questions, here we are given two starting points from where Alice and Bob can move.

& We are given an ‘N*M’ matrix. We need to define the function with four parameters  i1,j1,i2, and j2 to describe the positions of Alice and Bob at a time.
& If we observe, initially Alice and Bob are at the first row, and they always move to the row below them every time, so they will always be in the same row. Therefore two different variables i1 and i2, to describe their positions are redundant. We can just use single parameter i, which tells us in which row of the grid both of them are.

&Therefore, we can modify the function. It now takes three parameters: i,j1, and j2. f(i,j1,j2) will give us the maximum number of chocolates collected by Alice and Bob from their current positions to the last position.

~ Base Case:

&There will be the following base cases:

~    When i == N-1, it means we are at the last row, so we need to return from here. Now it can happen that at the last row, both Alice and Bob are at the same cell, in this condition we will return only chocolates collected by Alice, mat[i][j1]( as question states that the chocolates cannot be doubly calculated), otherwise we return sum of chocolates collected by both, mat[i][j1] + mat[i][j1][j2].

&At every cell, we have three options to go: to the bottom cell (↓), to the bottom-right cell(↘) or to the bottom-left cell(↙)

&As we are moving to the bottom cell (↓), at max we will reach the last row, from &where we return, so we will never go out of the bounding index.

&To move to the bottom-right cell(↘) or to the bottom-left cell(↙), it can happen that we may go out of bound as shown in the figure(below). So we need to handle it, we can return -1e9, whenever we go out of bound, in this way this path will not be selected by the calling function as we have to return the maximum chocolates.

   ~ If j1<0 or j1>=M or j2<0 or j2>=M  , then we return -1e9

&The pseudocode till this step will be:

? Step 2: Try out all possible choices at a given index.

& At every cell, we have three options to go: to the bottom cell (↓), to the bottom-right cell(↘) or to the bottom-left cell(↙)

& Now, we need to understand that we want to move Alice and Bob together. Both of them can individually move three moves but say Alice moves to bottom-left, then Bob can have three different moves for Alice’s move, and so on. The following figures will help to understand this:

& Hence we have a total of 9 different options at every f(i,j1,j2) to move Alice and Bob. Now we can manually write these 9 options or we can observe a pattern in them, first Alice moves to one side and Bob tries all three choices, then again Alice moves, then Bob, and so on. This pattern can be easily captured by using two nested loops that change the column numbers(j1 and j2).

& Note: if (j1===j2), as discussed in the base case, we will only consider chocolates collected by one of them otherwise we will consider chocolates collected by both of them.

& Step 3:  Take the maximum of all choices

& As we have to find the maximum chocolates collected of all the possible paths, we will return the maximum of all the choices(the 9 choices of step 2). We will take a maxi variable( initialized to INT_MIN). We will update maxi to the maximum of the previous maxi and the answer of the current choice. At last, we will return maxi from our function as the answer.f
     */

    int maximumCherries(int i, int j1, int j2, vector<vector<int>> &mat)
    {
        if (j1 < 0 || j1 >= mat.front().size() || j2 < 0 || j2 >= mat.front().size())
        {
            return -10e7;
        }
        if (i == mat.size() - 1)
        {
            if (j1 != j2)
            {
                return mat[i][j1] + mat[i][j2];
            }
            else
            {
                return mat[i][j1];
            }
        }
        int maxi = INT_MIN;
        for (int dirR = -1; dirR <= 1; dirR++)
        {
            for (int dirC = -1; dirC <= 1; dirC++)
            {
                if (j1 == j2)
                    int ans = mat[i][j1] + maximumCherries(i, j1 + dirR, j2 + dirC, mat);
                else
                {
                    maxi = max(maxi, mat[i][j2] + maximumCherries(i, j1 + dirR, j2 + dirC, mat));
                }
            }
        }
        return maxi;
    }

    /*
    @ Memoizaton

    * O(N*M*M) T.C | O(NMM) + O(N) S.C
     */
    int maximumCherries_memo(int i, int j1, int j2, vector<vector<int>> &mat, vector<vector<vector<int>>> &dp)
    {
        if (j1 < 0 || j1 >= mat.front().size() || j2 < 0 || j2 >= mat.front().size())
        {
            return -10e7;
        }
        if (i == mat.size() - 1)
        {
            if (j1 != j2)
            {
                return mat[i][j1] + mat[i][j2];
            }
            else
            {
                return mat[i][j1];
            }
        }
        if (dp[i][j1][j2] != -1)
            return dp[i][j1][j2];
        int maxi = INT_MIN;
        for (int dirR = -1; dirR <= 1; dirR++)
        {
            for (int dirC = -1; dirC <= 1; dirC++)
            {
                if (j1 == j2)
                    int ans = mat[i][j1] + maximumCherries_memo(i, j1 + dirR, j2 + dirC, mat, dp);
                else
                {
                    maxi = max(maxi, mat[i][j2] + maximumCherries_memo(i, j1 + dirR, j2 + dirC, mat, dp));
                }
            }
        }
        return dp[i][j1][j2] = maxi;
    }
    /*
    @ Tabulation
    For the tabulation approach, it is better to understand what a cell in the 3D DP array means. As we had done in memoization, we will initialize a dp[] array of size [N][M][M].

So now, when we say dp[2][0][3], what does it mean? It means that we are getting the value of the maximum chocolates collected by Alice and Bob, when Alice is at (2,0) and Bob is at (2,3).

The below figure gives us a bit more clarity.

Next, we need to initialize the base value conditions. In the recursive code, our base condition is when we reach the last row, therefore in our dp array, we will also initialize dp[n-1][][], i.e (the last plane of 3D Array) as the base condition. Dp[n-1][j1][j2] means Alice is at (n-1,j1) and Bob is at (n-1,j2). As this is the last row, its value will be equal to mat[i][j1], if (j1==j2) and mat[i][j1] + mat[i][j2] otherwise.

Once we have filled the last plane, we can move to the second-last plane and so on, we will need three nested loops to do this traversal.

The steps to convert to the tabular solution are given below:

    Declare a dp[] array of size [N][M][M]
    First, initialize the base condition values as explained above.
    We will then move from dp[n-2][][] to dp[0][][]. We will set three nested loops to do this traversal.
    Inside the three nested loops( say i,j1,j2 as loop variables), we will use the recursive relations, i.e we will again set two nested loops to try all the nine options.
    The outer three loops are just for traversal, and the inner two loops that run for 9 times mainly decide, what should be the value of the cell. If you are getting confused, please see the code.
    Inside the inner two nested loops, we will calculate an answer as we had done in the recursive relation, but this time using values from the next plane of the 3D DP Array( dp[i+1][x][y] instead of recursive calls, where x and y will vary according to inner 2 nested loops).
    At last, we will set dp[i][j1][j2] as the maximum of all the 9 options.
    After the outer three nested loops iteration has ended, we will return dp[0][0][m-1] as our answer.
    * O(NM^2) | O(NMM) S.c
     */

    int maximumChocolates_tabulation(int n, int m, vector<vector<int>> &grid)
    {
        // Write your code here.
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m,
                                                              vector<int>(m, 0)));

        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                if (j1 == j2)
                    dp[n - 1][j1][j2] = grid[n - 1][j1];
                else
                    dp[n - 1][j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
            }
        }

        // Outer Nested Loops for travering DP Array
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j1 = 0; j1 < m; j1++)
            {
                for (int j2 = 0; j2 < m; j2++)
                {

                    int maxi = INT_MIN;

                    // Inner nested loops to try out 9 options
                    for (int di = -1; di <= 1; di++)
                    {
                        for (int dj = -1; dj <= 1; dj++)
                        {

                            int ans;

                            if (j1 == j2)
                                ans = grid[i][j1];
                            else
                                ans = grid[i][j1] + grid[i][j2];

                            if ((j1 + di < 0 || j1 + di >= m) ||
                                (j2 + dj < 0 || j2 + dj >= m))

                                ans += -1e9;
                            else
                                ans += dp[i + 1][j1 + di][j2 + dj];

                            maxi = max(ans, maxi);
                        }
                    }
                    dp[i][j1][j2] = maxi;
                }
            }
        }

        return dp[0][0][m - 1];
    }
    /*
    @ Space optimization
    If we look closely, to compute dp[i][j1][j2], we need values only from dp[i+1][][]. Therefore it is not necessary to store a three-dimensional array. Instead, we can store a two-dimensional array and update it as we move from one plane to the other in the 3D Array.

The Steps to space optimize the tabulation approach are as follows:

    Initially, we can take a dummy 2D Array ( say front). We initialize this 2D Array as we had done in the Tabulation Approach.
    Next, we also initialize a 2D Array( say cur), which we will need in the traversal.
    Now we set our three nested loops to traverse the 3D Array, from the second last plane.
    Following the same approach as we did in the tabulation approach, we find the maximum number of chocolates collected at each cell. To calculate it we have all the values in our ‘front’ 2D Array.
    Previously, we assigned dp[i][j1][j2] to maxi, now we will simply assign cur[j1][j2] to maxi.
    Then whenever the plane of the 3D DP(the first parameter) is going to change, we assign the front to cur.

At last, we will return front[0][m-1] as our answer
     */
    int maximumChocolates_optimized(int n, int m, vector<vector<int>> &grid)
    {
        // Write your code here.
        vector<vector<int>> front(m, vector<int>(m, 0)), cur(m, vector<int>(m, 0));

        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                if (j1 == j2)
                    front[j1][j2] = grid[n - 1][j1];
                else
                    front[j1][j2] = grid[n - 1][j1] + grid[n - 1][j2];
            }
        }

        // Outer Nested Loops for travering DP Array
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j1 = 0; j1 < m; j1++)
            {
                for (int j2 = 0; j2 < m; j2++)
                {

                    int maxi = INT_MIN;

                    // Inner nested loops to try out 9 options
                    for (int di = -1; di <= 1; di++)
                    {
                        for (int dj = -1; dj <= 1; dj++)
                        {

                            int ans;

                            if (j1 == j2)
                                ans = grid[i][j1];
                            else
                                ans = grid[i][j1] + grid[i][j2];

                            if ((j1 + di < 0 || j1 + di >= m) ||
                                (j2 + dj < 0 || j2 + dj >= m))

                                ans += -1e9;
                            else
                                ans += front[j1 + di][j2 + dj];

                            maxi = max(ans, maxi);
                        }
                    }
                    cur[j1][j2] = maxi;
                }
            }
            front = cur;
        }

        return front[0][m - 1];
    }
};

//^ DP on subsequences and subsets
class SubsetSum
{
private:
public:
    /*
    @ Recursive
    ! O(2^n) T.C || O(N) S.C
     */
    bool findSubsetSum(int idx, vector<int> &arr, int target)
    {
        if (target == 0)
            return true;
        if (idx == 0)
            return arr[0] == target;
        bool notPick = findSubsetSum(idx + 1, arr, target);
        bool pick = (target >= arr[idx]) ? findSubsetSum(idx + 1, arr, target - arr[idx]) : false;
        return pick || notPick;
    }
    /*
    @ Memoization

    * O(N*target) || O(N*target) + O(N) S.C
     */

    bool findSubsetSum_memo(int idx, vector<int> &arr, int target, vector<vector<int>> &dp)
    {
        if (target == 0)
            return true;
        if (idx == 0)
            return arr[0] == target;
        if (dp[idx][target] != -1)
        {
            return dp[idx][target];
        }
        bool notPick = findSubsetSum_memo(idx + 1, arr, target, dp);
        bool pick = (target >= arr[idx]) ? findSubsetSum_memo(idx + 1, arr, target - arr[idx], dp) : false;
        return dp[idx][target] = pick || notPick;
    }
    /*
    @ Tabulation
  &      Initialize the first column of the DP table dp as true. This is because for any index i, an empty subset (with no elements) can always achieve a sum of 0, regardless of the target value. Therefore, dp[i][0] is set to true.

  &  Initialize the first row of the DP table dp as false, except for dp[0][arr[0]] which is set to true. This is because for i = 0, the only possibility of achieving a sum equal to arr[0] is by including arr[0] itself in the subset.

  &  Iterate through the remaining cells of the DP table dp, starting from i = 1 and t = 1. For each cell (i, t), consider two possibilities:
  &  a. notTake: The element at index i is not included in the subset, so the result depends on whether the subset sum t can be achieved by considering elements up to index i - 1.
  &  b. take: The element at index i is included in the subset, so the result depends on whether the subset sum t - arr[i] can be achieved by considering elements up to index i - 1.

  &  Set dp[i][t] to take || notTake, indicating whether the subset sum t can be achieved by considering elements up to index i.

  &  Finally, return the value of dp[arr.size() - 1][target], which represents whether the target sum can be achieved using all the elements of the array.

~ The intuition behind this approach is to build a dynamic programming table dp that tracks the possibilities of achieving different subset sums using elements up to a certain index. By considering each element in the array and updating the table accordingly, we can determine whether the target sum is achievable by any subset of the array. The approach exploits the principle of overlapping subproblems and optimal substructure to efficiently solve the Subset Sum problem in a bottom-up manner.

~ Time Complexity: The code has a nested loop iterating over the size of the array and the target value, resulting in a time complexity of O(arr.size() * target).

~ Space Complexity: The space complexity is determined by the size of the DP table, which is O(arr.size() * target) in this case.
    * O(N*target) | O(N*target) S.C
     */
    bool findSubsetSum_tabulation(vector<int> &arr, int target, vector<vector<bool>> &dp)
    {
        for (int i = 0; i < arr.size(); i++)
            dp[i].front() = true;
        dp[0][arr[0]] = true; // arr[0] has to be less than equal to target
        for (int i = 1; i < arr.size(); i++)
        {
            for (int t = 1; t <= target; t++)
            {
                bool notTake = dp[i - 1][t];
                bool take = false;
                if (arr[i] <= t)
                {
                    take = dp[i - 1][t - arr[i]];
                }
                dp[i][t] = take || notTake;
            }
        }
        return dp[arr.size() - 1][target];
    }

    /*
    @ Space optimization
 &        Initialize the size of the array as n and create two boolean vectors, prev and temp, of size sum + 1. These vectors will store the subset sum possibilities for different target values.

  &   Set temp.front() to true for all elements of the array. This represents the possibility of achieving a sum of zero by considering an empty subset.

 &    Set prev[arr[0]] to true, indicating that the first element of the array itself can achieve a sum equal to its value.

 &    Iterate through the remaining elements of the array, starting from i = 1. For each element arr[i], iterate through the possible target values from 1 to sum.

  &   For each target value target, consider two possibilities:
  &   a. notTake: The element at index i is not included in the subset, so the result depends on whether the subset sum target can be achieved by considering elements up to index i - 1.
  &   b. take: The element at index i is included in the subset, so the result depends on whether the subset sum target - arr[i] can be achieved by considering elements up to index i - 1.

 &    Set temp[target] to take || notTake, indicating whether the subset sum target can be achieved by considering elements up to index i.

 &    Update the prev vector to be the same as the temp vector after processing each element of the array.

  &   After processing all elements of the array, the value at index sum in the prev vector will represent whether the target sum can be achieved using the given array. Return this value.

& The code effectively uses the dynamic programming concept to build a table of subset sum possibilities and uses the results of previously calculated subproblems to compute the final result. This approach ensures that each subproblem is solved only once, improving efficiency.

& Time Complexity: The code has two nested loops iterating over the size of the array and the target sum, resulting in a time complexity of O(n * sum), where n is the size of the array and sum is the target sum.

& Space Complexity: The code uses two boolean vectors, prev and temp, of size sum + 1, resulting in a space complexity of O(sum).
    * O(N*target) T.C | O(target) S.C
     */
    bool isSubsetSum(vector<int> arr, int sum)
    {
        // code here
        int n = arr.size();
        vector<bool> prev(sum + 1), temp(sum + 1);
        for (int i = 0; i < arr.size(); i++)
        {
            temp.front() = true;
        }
        prev[arr[0]] = true; // arr[0] has to be less than equal to sum
        for (int i = 1; i < n; i++)
        {
            for (int target = 1; target <= sum; target++)
            {
                bool notTake = prev[target];
                bool take = false;
                if (target >= arr[i])
                {
                    take = prev[target - arr[i]];
                }
                temp[target] = take || notTake;
            }
            prev = temp;
        }
        return prev[sum];
    }
};

class PartitionInto2
{
public:
    /*
    @ Recursive approach #1
     */
    bool isPartition(int idx, vector<int> &arr, int sum1, int sum2)
    {
        if (idx == 0)
        {
            if (sum1 + arr[0] == sum2 || sum2 + arr[0] == sum1)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        return isPartition(idx - 1, arr, sum1, sum2 + arr[idx]) || isPartition(idx - 1, arr, sum1 + arr[idx], sum2);
    }
    /*
    @ Recursive approach #2
    & Use the subset sum = k code after checking whether the sum of the array is odd or even. if the sum of the array is odd, then it is not possible to divide the array into two equal sum subarrays. For even case use the same code with k = sum of array / 2

    ~ Memoization and tabulation can be done using the same code too.
     */

    /*
    @ Tabulation
    & Step 1: Calculate the sum of all elements in the nums vector and store it in the variable sum.

& Step 2: Check if the sum is odd (not divisible by 2). If it is odd, return false as it's not possible to partition the array into two subsets with equal sums.

& Step 3: Calculate the target sum for each subset by dividing the sum by 2.

& Step 4: Create a 2D boolean vector dp with dimensions nums.size() and target + 1. Each element of dp will represent whether a subset with a specific sum can be formed using elements up to a certain index.

& Step 5: Set the first element of each row in dp to true since it's always possible to form a subset with a sum of 0 using an empty set.

& Step 6: Check if the first element of nums is less than or equal to the target sum. If it is, mark the corresponding element in dp as true to indicate that it's possible to form a subset with that specific sum.

& Step 7: Iterate through the remaining elements of nums starting from the second element (i = 1).

& Step 8: For each element nums[i], iterate through the possible target sums from 1 to target.

& Step 9: For each target sum t, consider two possibilities:

    notTake: The element at index i is not included in the subset, so the result depends on whether the subset sum t can be achieved by considering elements up to index i - 1.
    take: The element at index i is included in the subset, so the result depends on whether the subset sum t - nums[i] can be achieved by considering elements up to index i - 1.

& Step 10: Set the element dp[i][t] to take || notTake, indicating whether it's possible to form a subset with a sum of t using elements up to index i.

& Step 11: After iterating through all elements, the value at dp[nums.size() - 1][target] will represent whether it's possible to partition the array into two subsets with equal sums. Return this value as the result.
    * O(N*target) T.C | O(N*target) S.C
     */
    bool canPartition(vector<int> &nums)
    {
        int sum = 0;
        for (auto &x : nums)
        {
            sum += x;
        }
        if (sum % 2 != 0)
            return false;
        int target = sum / 2;
        vector<vector<bool>> dp(nums.size(), vector<bool>(target + 1, false));
        for (int i = 0; i < nums.size(); i++)
        {
            dp[i].front() = true;
        }
        if (nums[0] <= target)
            dp[0][nums[0]] = true;
        for (int i = 1; i < nums.size(); i++)
        {
            for (int t = 1; t <= target; t++)
            {
                bool notTake = dp[i - 1][t];
                bool take = false;
                if (nums[i] <= t)
                {
                    take = dp[i - 1][t - nums[i]];
                }
                dp[i][t] = take || notTake;
            }
        }
        return dp[nums.size() - 1][target];
    }
};

//^ Partition with minimum absolute difference of two subsets of array (+ve nums)
class PartitionWithMin
{
    /*
    & Step 1: Calculate the total sum of all elements in the nums vector using the accumulate function.

& Step 2: Build a 2D boolean vector dp with dimensions nums.size() and totalSum + 1. Each element dp[i][target] represents whether it's possible to achieve the target sum target using elements up to index i.

& Step 2.1: Set the first element of each row in dp to true since it's always possible to achieve a sum of 0 using an empty set.

& Step 2.2: Mark the corresponding element in dp as true if the element at index 0 of nums is equal to the target sum, indicating that a subset with that specific sum can be formed.

& Step 2.3: Iterate through the remaining elements of nums starting from the second element (i = 1).

& Step 2.4: For each element nums[i], iterate through the possible target sums from 0 to totalSum.

& Step 2.5: For each target sum target, consider two possibilities:

    notTake: The element at index i is not included in the subset, so the result depends on whether the target sum target can be achieved by considering elements up to index i - 1.
    take: The element at index i is included in the subset, so the result depends on whether the target sum target - nums[i] can be achieved by considering elements up to index i - 1.

& Step 2.6: Set the element dp[i][target] to take or notTake, indicating whether it's possible to achieve the target sum target using elements up to index i.

& Step 3: Iterate through the sums from 0 to totalSum/2 and find the minimum difference between the total sum and all possible sums. This is done by checking if the last row of dp (representing using all elements) has a true value at each sum i. If it does, calculate the absolute difference between the total sum and twice the current sum, and update minDiff if necessary.

Finally, return the minimum difference obtained.
     */
public:
    int minimumDifference(vector<int> &nums)
    {
        int totalSum = 0;
        totalSum = accumulate(nums.begin(), nums.end(), totalSum);

        cout << "Total sum: " << totalSum << endl;
        vector<vector<bool>> dp(nums.size(), vector<bool>(totalSum + 1));
        for (int i = 0; i < nums.size(); i++)
            dp[i][0] = true;
        dp[0][nums[0]] = true;
        for (int i = 1; i < nums.size(); i++)
        {
            for (int target = 0; target <= totalSum; target++)
            {
                bool notTake = dp[i - 1][target];
                bool take = (target >= nums[i]) ? dp[i - 1][target - nums[i]] : false;
                dp[i][target] = take or notTake;
            }
        }
        int minDiff = 1e8;
        for (int i = 0; i <= totalSum / 2; i++)
        {
            if (dp.back()[i])
                minDiff = min(minDiff, abs(totalSum - 2 * i));
        }
        return minDiff;
    }
};

//^ Count subsets with sum K (+ve nums)
class CountSubsetK
{
public:
    /*
    @ Recursion
    & Step 1: The base case checks if the target sum has been achieved. If the target is zero, it means that the current subset's elements sum up to the target, so we return 1 to indicate that one way has been found.

& Step 2: Another base case checks if we have considered all the elements in the arr. If we have reached the first element (index 0), we check if it is equal to the target. If it is, we return 1 to indicate one way to achieve the target.

& Step 3: We have not reached the base case, so we make recursive calls to find the ways to achieve the target sum.

& Step 3.1: We make a recursive call without considering the current element. This means that we move to the next index (idx - 1) and keep the target sum the same. The result is stored in the variable notTake.

& Step 3.2: We check if the current element can be included in the sum (its value is less than or equal to the target).

& Step 3.2.1: If the condition is true, we make a recursive call by subtracting the current element from the target sum. This represents including the current element in the sum. The result is stored in the variable take.

& Step 4: Finally, we return the total number of ways to achieve the target sum by summing the results of notTake and take. This accounts for all possible ways to reach the target sum either by including or excluding the current element at the given index.
    !O(2^N) T.C | O(N) S.C
     */
    int findWays(int idx, int target, vector<int> &arr)
    {
        if (target == 0)
            return 1;
        if (idx == 0)
            return arr[0] == target;
        int notTake = findWays(idx - 1, target, arr);
        int take = 0;
        if (arr[idx] <= target)
            take = findWays(idx - 1, target - arr[idx], arr);
        return take + notTake;
    }
    /*
    @ Memoization

    * O(N^2) T.C | O(N^2) + O(N) S.C
     */
    int findWays_memo(int idx, int target, vector<int> &arr, vector<vector<int>> &dp)
    {
        if (target == 0)
            return 1;
        if (idx == 0)
            return arr[0] == target;
        if (dp[idx][target] != -1)
            return dp[idx][target];
        int notTake = findWays_memo(idx - 1, target, arr, dp);
        int take = 0;
        if (arr[idx] <= target)
            take = findWays_memo(idx - 1, target - arr[idx], arr, dp);
        return dp[idx][target] = take + notTake;
    }
    /*
    @ Tabulation
    & Step 1: We obtain the size of the input array arr to determine the number of elements.

& Step 2: We create a 2D table dp to store the computed results. It has n rows (corresponding to the elements of arr) and tar + 1 columns (representing the possible target sums from 0 to tar).

& Step 3: We initialize the base cases in the dp table.

& Step 3.1: We set the first column of dp to 1 because there is one way to achieve a sum of 0, which is by not taking any element.

& Step 3.2: We check if the first element of arr is less than or equal to tar. If it is, we set the corresponding value in the dp table to 1, indicating that there is one way to achieve that sum using the first element.

& Step 4: We compute the remaining values in the dp table using a tabulation approach.

& Step 4.1: We iterate over the elements of arr starting from the second element (index 1).

& Step 4.2: For each element, we iterate over the possible target sums from 0 to tar.

& Step 4.3: We compute the number of ways to achieve the current target sum by considering the current element.

& Step 4.3.1: We calculate the number of ways without taking the current element, which is stored in the variable notTake.

& Step 4.3.2: We check if the current element can be included in the sum (its value is less than or equal to the sum).

& Step 4.3.2.1: If it can be included, we calculate the number of ways by taking the current element, which is stored in the variable take.

& Step 4.3.3: We store the total number of ways (sum of take and notTake) in the dp table.

& Step 5: Finally, we return the result from the last row and the target column of the dp table, representing the total number of ways to achieve the target sum.
    * O(N^2) T.C | O(N^2) S.C
     */

    int findWays_tabulation(vector<int> &arr, int tar)
    {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(tar + 1));
        for (int i = 0; i < n; i++)
            dp[i].front() = 1;
        if (arr[0] <= tar)
            dp[0][arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            for (int sum = 0; sum <= tar; sum++)
            {
                int notTake = dp[i - 1][sum];
                int take = (arr[i] <= sum) ? dp[i - 1][sum - arr[i]] : 0;
                dp[i][sum] = take + notTake;
            }
        }

        return dp.back().at(tar);
    }

    /*
    @ Space optimization

     */
    int findWays_optimized(vector<int> &arr, int tar)
    {
        int n = arr.size();
        vector<int> prev(tar + 1), cur(tar + 1);
        prev.front() = cur.front() = 1;
        if (arr[0] <= tar)
            prev[arr[0]] = 1;

        for (int i = 1; i < n; i++)
        {
            for (int sum = 0; sum <= tar; sum++)
            {
                int notTake = prev[sum];
                int take = (arr[i] <= sum) ? prev[sum - arr[i]] : 0;
                cur[sum] = take + notTake;
            }
            prev = cur;
        }

        return prev.back();
    }
};

//^ 0/1 Knapsack
class Knapsack
{
public:
    /*
    @ Memoization
    & Step 1: We check if we have reached the first item (idx == 0).

& Step 1.1: If it is the first item, we check if the remaining capacity (W) is greater than or equal to the weight of the item. If it is, we can include the item and get its corresponding value (val[idx]), otherwise, we cannot include it and the value is 0.

& Step 2: We check if the result for the current subproblem (idx, W) has already been computed and stored in the dp table. If it is, we directly return the stored value.

& Step 3: We calculate the maximum value by considering two options: taking the current item or not taking it.

& Step 3.1: We calculate the value without taking the current item. This is done by recursively calling the solve_memo function for the previous item (idx - 1) and the same capacity (W).

& Step 3.2: We calculate the value by taking the current item.

& Step 3.2.1: We check if the remaining capacity (W) is sufficient to include the current item (wt[idx]).

& Step 3.2.1.1: If it is, we calculate the value by adding the value of the current item (val[idx]) to the result of recursively calling the solve_memo function for the previous item (idx - 1) and the remaining capacity after subtracting the weight of the current item (W - wt[idx]).

& Step 4: Finally, we choose the maximum value between the two options (take and notTake) and store it in the dp table for the current subproblem (idx, W) to avoid recomputation in future recursive calls. The maximum value is also returned as the result.
    * O(N*W) T.C | O(N*W) + O(N) S.C
     */
    int solve_memo(int idx, int W, int wt[], int val[], vector<vector<int>> &dp)
    {
        if (idx == 0)
        {
            return (W >= wt[idx]) ? val[idx] : 0;
        }
        if (dp[idx][W] != -1)
            return dp[idx][W];
        int notTake = 0 + solve_memo(idx - 1, W, wt, val, dp);
        int take = -1e8;
        if (W >= wt[idx])
            take = val[idx] + solve_memo(idx - 1, W - wt[idx], wt, val, dp);
        return dp[idx][W] = max(take, notTake);
    }
    /*
    @ Tabulation
        The dp table is initialized with dimensions (n, W+1), where n is the number of items and W is the maximum weight capacity.
    The loop initializes the values for the first item (index 0) in the dp table. For each weight from wt[0] to W, the value is set to val[0], as we can only choose the first item if its weight is less than or equal to the current weight.
    The nested loops iterate over the remaining items (indices 1 to n-1) and the possible weights (0 to W).
    For each subproblem (i, j), the code calculates the maximum value by considering two options: not taking the current item (dp[i-1][j]) and taking the current item if its weight is less than or equal to the current weight (dp[i-1][j-wt[i]] + val[i]).
    The maximum value between the two options is stored in the dp table at position dp[i][j].
    After filling the dp table, the maximum value for the full knapsack problem is stored in the bottom-right cell (dp[n-1][W]) and returned as the result.
    * O(N*W) T.C | O(N*W) S.C
     */
    int knapSack_tabulation(int W, int wt[], int val[], int n)
    {
        // Your code here
        vector<vector<int>> dp(n, vector<int>(W + 1));
        // return solve_memo(n-1,W,wt,val,dp)
        for (int i = wt[0]; i <= W; i++)
        {
            dp[0][i] = val[0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= W; j++)
            {
                int notTake = 0 + dp[i - 1][j];
                int take = (wt[i] <= j) ? val[i] + dp[i - 1][j - wt[i]] : -1e9;
                dp[i][j] = max(take, notTake);
            }
        }
        return dp[n - 1][W];
    }
    /*
    @ Space optimization 2 Row

    * O(N*W) T.C | O(2N) S.C
     */
    int knapSack_optimized(int W, int wt[], int val[], int n)
    {
        // Your code here
        vector<int> prev(W + 1), cur(W + 1);
        for (int i = wt[0]; i <= W; i++)
        {
            prev[i] = val[0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j <= W; j++)
            {
                int notTake = 0 + prev[j];
                int take = (wt[i] <= j) ? val[i] + prev[j - wt[i]] : -1e9;
                cur[j] = max(take, notTake);
            }
            prev = cur;
        }
        return prev[W];
    }
    /*
    @ God like optimization 1 ROW !!

    ~ JUST TRAVERSE FROM RIGHt TO LEFT SIDE AND BOOM no need for 2 rows one row should suffice
     */
    int knapSack_godlike(int W, int wt[], int val[], int n)
    {
        // Your code here
        vector<int> prev(W + 1);
        for (int i = wt[0]; i <= W; i++)
        {
            prev[i] = val[0];
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = W; j >= 0; j--)
            {
                int notTake = 0 + prev[j];
                int take = (wt[i] <= j) ? val[i] + prev[j - wt[i]] : -1e9;
                prev[j] = max(take, notTake);
            }
        }
        return prev[W];
    }
};

//^ Coin Change
class CoinChange
{
public:
    /*
    @ Recursion
     */
    int coinChange(int idx, int target, vector<int> &coins)
    {
        if (target == 0)
        {
            cout << "Target is achieved !!!\n\n";
            return 0;
        }
        if (idx == 0)
        {
            if (target % coins[idx] == 0)
            {
                cout << "Target is achieved at index 0!!!\n\n";
                return target / coins[idx];
            }
            else
            {
                return 1e9;
            }
        }
        int notTake = 0 + coinChange(idx - 1, target, coins);
        int take = 1e9;
        if (target >= coins[idx])
        {
            cout << "Taking this element " << coins[idx] << " remaining target is --> " << target - coins[idx] << "\n";
            take = 1 + coinChange(idx, target - coins[idx], coins);
        }
        return min(take, notTake);
    }
    /*
    @ Tabulation
    ? Skipping memoization because all you need to do is just change few lines
   &     The dp table is initialized with dimensions (n, amount+1), where n is the number of coins and amount is the target amount.
 &   The loop initializes the base case for the first coin (coins[0]) in the dp table. For each target amount from 0 to amount, if the amount is divisible by coins[0], it means the coins can be used to make the amount, so dp[0][target] is set to target/coins[0]. Otherwise, dp[0][target] is set to 1e9, indicating an invalid state or impossibility.
 &   The nested loops iterate over the remaining coins (coins[1] to coins[n-1]) and the possible amounts (0 to amount).
 &   For each subproblem (i, j), the code calculates the minimum number of coins required by considering two options: not taking the current coin (dp[i-1][j]) and taking the current coin if its value is less than or equal to the current amount (dp[i][j-coins[i]] + 1).
 &   The minimum number of coins between the two options is stored in the dp table at position dp[i][j].
  &  After filling the dp table, the minimum number of coins required to make the given amount is stored in the bottom-right cell (dp[n-1][amount]).
 &   If the value is still 1e9, it means it's not possible to make the amount with the given coins, so -1 is returned. Otherwise, the result is the minimum number of coins.

&  The algorithm effectively builds the solution by considering the different coin denominations and iteratively calculating the minimum number of coins required for various subproblems.
     */
    int coinChange_tabulation(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1));

        // Initialize the base case for the first coin (coins[0])
        for (int target = 0; target <= amount; target++)
        {
            if (target % coins[0] == 0)
            {
                dp[0][target] = target / coins[0];
            }
            else
            {
                dp[0][target] = 1e9; // Set a large value to indicate an invalid state
            }
        }

        // Iterate over the remaining coins (coins[1] to coins[n-1])
        for (int i = 1; i < n; i++)
        {
            // Iterate over the possible amounts (0 to amount)
            for (int j = 0; j <= amount; j++)
            {
                // Calculate the minimum number of coins required for the current subproblem (i, j)

                // Option 1: Not taking the current coin
                int notTake = 0 + dp[i - 1][j];

                // Option 2: Taking the current coin if its value is less than or equal to the current amount (j)
                int take = 1e9;
                if (j >= coins[i])
                {
                    take = 1 + dp[i][j - coins[i]];
                }

                // Choose the minimum number of coins between the two options and store it in the dp table
                dp[i][j] = min(take, notTake);
            }
        }

        // The minimum number of coins required to make the given amount is stored in the bottom-right cell of the dp table
        // If the value is still 1e9, it means it's not possible to make the amount with the given coins, so return -1
        return (dp.back()[amount] >= 1e9) ? -1 : dp.back()[amount];
    }

    /*
    @ Space optimization

     */
    int coinChange_optimized(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<int> prev(amount + 1), curr(amount + 1);

        // Step 1: Initialize the base case for the first coin (coins[0])
        for (int target = 0; target <= amount; target++)
        {
            if (target % coins[0] == 0)
            {
                prev[target] = target / coins[0];
            }
            else
            {
                prev[target] = 1e9;
            }
        }

        // Step 2: Iterate over the remaining coins (coins[1] to coins[n-1])
        for (int i = 1; i < n; i++)
        {
            // Step 3: Iterate over the possible amounts (0 to amount)
            for (int j = 0; j <= amount; j++)
            {
                // Step 4: Calculate the minimum number of coins required for the current subproblem (i, j)

                // Option 1: Not taking the current coin
                int notTake = 0 + prev[j];

                // Option 2: Taking the current coin if its value is less than or equal to the current amount (j)
                int take = 1e9;
                if (j >= coins[i])
                {
                    take = 1 + curr[j - coins[i]];
                }

                // Step 5: Choose the minimum number of coins between the two options and store it in the curr array
                curr[j] = min(take, notTake);
            }
            prev = curr; // Step 6: Update the prev array with the values of curr for the next iteration
        }

        // Step 7: Return the minimum number of coins required to make the given amount
        return (prev[amount] >= 1e9) ? -1 : prev[amount];
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}
