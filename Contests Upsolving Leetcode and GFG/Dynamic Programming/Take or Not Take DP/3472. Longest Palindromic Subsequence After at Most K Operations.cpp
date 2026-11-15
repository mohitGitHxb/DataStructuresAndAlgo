#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
static int init = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution
{
private:
    /*
You are given a string s and an integer k.

In one operation, you can replace the character at any position with the next or previous letter in the alphabet (wrapping around so that 'a' is after 'z'). For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y'.

Return the length of the longest

of s that can be obtained after performing at most k operations.



Example 1:

Input: s = "abced", k = 2

Output: 3

Explanation:

    Replace s[1] with the next letter, and s becomes "acced".
    Replace s[4] with the previous letter, and s becomes "accec".

The subsequence "ccc" forms a palindrome of length 3, which is the maximum.

Example 2:

Input: s = "aaazzz", k = 4

Output: 6

Explanation:

    Replace s[0] with the previous letter, and s becomes "zaazzz".
    Replace s[4] with the next letter, and s becomes "zaazaz".
    Replace s[3] with the next letter, and s becomes "zaaaaz".

The entire string forms a palindrome of length 6.

     */
public:
    int dp[201][201][201];

    int costToConvert(char a, char b)
    {
        return min(abs(a - b), 26 - abs(a - b));
    }

    int helper(string &s, int leftIndex, int rightIndex, int k)
    {
        if (leftIndex > rightIndex)
            return 0;
        if (leftIndex == rightIndex)
            return 1;
        // cache check
        if (dp[leftIndex][rightIndex][k] != -1)
            return dp[leftIndex][rightIndex][k];
        int moveLeft = helper(s, leftIndex + 1, rightIndex, k);
        int moveRight = helper(s, leftIndex, rightIndex - 1, k);
        int moveBoth = INT_MIN;
        if (costToConvert(s[leftIndex], s[rightIndex]) <= k)
        {
            moveBoth = 2 + helper(s, leftIndex + 1, rightIndex - 1, k - costToConvert(s[leftIndex], s[rightIndex]));
        }
        return dp[leftIndex][rightIndex][k] = max({moveLeft, moveRight, moveBoth});
    }
    int longestPalindromicSubsequence(string s, int k)
    {
        const int n = s.length();
        memset(dp, -1, sizeof(dp));
        return helper(s, 0, n - 1, k);
    }
};

class TabulationSolution
{
public:
    // Function to calculate the cost of changing character 'c' to 'b'
    int calcost(char c, char b)
    {
        return min(abs(c - b), 26 - abs(c - b)); // Considering wrap-around distance
    }

    int longestPalindromicSubsequence(string s, int total)
    {
        int n = s.size();

        // 3D DP array: dp[i][j][k] stores the longest palindromic subsequence in s[i..j]
        // using at most k modifications.
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(total + 1, 0)));

        // Base case: A single character is always a palindrome of length 1
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= total; j++)
            {
                dp[i][i][j] = 1;
            }
        }

        // Base case: Two consecutive characters
        for (int i = 0; i < n - 1; i++)
        {
            int cost = calcost(s[i], s[i + 1]);
            for (int j = 0; j <= total; j++)
            {
                if (j >= cost)
                    dp[i][i + 1][j] = 2; // We can make them equal
                else
                    dp[i][i + 1][j] = 1; // Otherwise, the best we can do is 1 character as palindrome
            }
        }

        // DP transition: Expanding for substrings of length 3 to n
        for (int len = 3; len <= n; len++)
        {
            for (int i = 0; i <= n - len; i++)
            {
                int start = i, end = i + len - 1;
                int cost = calcost(s[start], s[end]);

                for (int j = 0; j <= total; j++)
                {
                    // If we can make s[start] == s[end], consider two possibilities:
                    // 1. Use `cost` operations to make them equal and take the middle palindrome
                    // 2. Do not modify them and just take the middle palindrome
                    if (j >= cost)
                    {
                        dp[start][end][j] = max(2 + dp[start + 1][end - 1][j - cost], dp[start + 1][end - 1][j]);
                    }

                    // Always maximize with cases where we ignore one of the ends
                    dp[start][end][j] = max({dp[start][end][j], dp[start][end - 1][j], dp[start + 1][end][j]});
                }
            }
        }
        return dp[0][n - 1][total];
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    cout << obj.minimizeXor(4214, 5) << endl;
    return 0;
}
#endif