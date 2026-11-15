#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define bigInt __int128_t
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
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

class Solution
{
private:
    /*
        You are given a list of strings of the same length words and a string target.

Your task is to form target using the given words under the following rules:

    target should be formed from left to right.
    To form the ith character (0-indexed) of target, you can choose the kth character of the jth string in words if target[i] = words[j][k].
    Once you use the kth character of the jth string of words, you can no longer use the xth character of any string in words where x <= k. In other words, all characters to the left of or at index k become unusuable for every string.
    Repeat the process until you form the string target.

Notice that you can use multiple characters from the same string in words provided the conditions above are met.

Return the number of ways to form target from words. Since the answer may be too large, return it modulo 109 + 7.



Example 1:

Input: words = ["acca","bbbb","caca"], target = "aba"
Output: 6
Explanation: There are 6 ways to form target.
"aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
"aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
"aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
"aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
"aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
"aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")

Example 2:

Input: words = ["abba","baab"], target = "bab"
Output: 4
Explanation: There are 4 ways to form target.
"bab" -> index 0 ("baab"), index 1 ("baab"), index 2 ("abba")
"bab" -> index 0 ("baab"), index 1 ("baab"), index 3 ("baab")
"bab" -> index 0 ("baab"), index 2 ("baab"), index 3 ("baab")
"bab" -> index 1 ("abba"), index 2 ("baab"), index 3 ("baab")

&- For each index i, store the frequency of each character in the ith row.
&- Use dynamic programing to calculate the number of ways to get the target string using the frequency array,
     */
public:
    const int MOD = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    char intoChar(int i) { return 'a' + i; }
    vector<vector<int>> indexFrequency;
    vector<vector<ll>> dp;

    ll solve(int targetIdx, int wordsIdx, string &target, int k)
    {
        // base case
        if (targetIdx == target.size())
        {
            return 1;
        }
        // pruning
        if (wordsIdx == k)
        {
            return 0;
        }
        // cache check
        if (dp[targetIdx][wordsIdx] != -1)
        {
            return dp[targetIdx][wordsIdx];
        }
        // choices
        ll notTakeThis = solve(targetIdx, wordsIdx + 1, target, k);
        ll takeThis = indexFrequency[wordsIdx][target[targetIdx] - 'a'] *
                      solve(targetIdx + 1, wordsIdx + 1, target, k);
        return dp[targetIdx][wordsIdx] = (takeThis % MOD + notTakeThis % MOD) % MOD;
    }

    int numWays(vector<string> &words, string target)
    {
        const int m = target.size();
        const int n = words.size();
        const int k = words[0].size();
        indexFrequency.resize(k, vector<int>(26, 0));
        dp.resize(m + 1, vector<ll>(k + 1, -1));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < k; j++)
            {
                indexFrequency[j][words[i][j] - 'a']++;
            }
        }
        return solve(0, 0, target, k);
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}
