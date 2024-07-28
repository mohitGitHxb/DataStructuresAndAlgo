#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].

Given two integers n and k, return the number of different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.



Example 1:

Input: n = 3, k = 0
Output: 1
Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.

Example 2:

Input: n = 3, k = 1
Output: 2
Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.


     */
public:
    const int MOD = 1e9 + 7;
    unordered_map<int, unordered_map<int, int>> memoTable;
    int memo(int n, int k)
    {
        //! Time complexity: O(n*k*min(k,n)) and Space complexity: O(n*k);
        //! THROWS TIME LIMIT EXCEEDED
        if (n == 0)
            return 0;
        if (k == 0)
            return 1;
        if (memoTable.count(n) && memoTable[n].count(k))
            return memoTable[n][k];
        int ans = 0;
        for (int i = 0; i <= min(n - 1, k); i++)
        {
            ans = (ans + memo(n - 1, k - i)) % MOD;
        }
        memoTable[n][k] = ans;
        return ans;
    }
    int tabulation(int n, int k)
    {
        //! Time complexity: O(n*k*min(k,n)) and Space complexity: O(n*k);
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (j == 0)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    for (int x = 0; x <= min(i - 1, j); x++)
                    {
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - x]) % MOD;
                    }
                }
            }
        }
        return dp[n][k];
    }

    int tabulationOptimized(int n, int k)
    {
        //! Time complexity: O(n*k) and Space complexity: O(n*k);
        vector<vector<int>> dp(n + 1, vector<int>(k + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (j == 0)
                {
                    dp[i][j] = 1;
                }
                else
                {
                    dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
                    if (j >= i)
                    {
                        dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + MOD) % MOD;
                    }
                }
            }
        }
        return dp[n][k];
    }

    int spaceOptimized(int n, int k)
    {
        //* Time complexity: O(n*k) and Space complexity: O(k);
        vector<int> prev(k + 1), curr(k + 1);
        prev[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 0; j <= k; j++)
            {
                if (j == 0)
                {
                    curr[j] = 1;
                }
                else
                {
                    curr[j] = (prev[j] + curr[j - 1]) % MOD;
                    if (j >= i)
                    {
                        curr[j] = (curr[j] - prev[j - i] + MOD) % MOD;
                    }
                }
            }
            prev = curr;
        }
        return prev[k];
    }

    int kInversePairs(int n, int k)
    {
        return memo(n, k);
    }
};

int main()
{
    return 0;
}