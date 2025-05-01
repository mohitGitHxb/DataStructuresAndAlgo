#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ull unsigned long long
#define ll long long
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

static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution {
private:
/* 
@ 2500+ Rated
Here's what the solution does:

    First, it processes the input string to count consecutive same characters. For example, "aaabbb" becomes [3,3] representing 3 'a's and 3 'b's.

    While counting consecutive characters, it also calculates the total number of possibilities by multiplying the counts (this represents the total ways we can reduce each group).

    The main DP approach:
        Uses two arrays: currentDP and nextDP
        currentDP[j] represents the number of ways to form a string of length j
        For each group of consecutive characters:
            Uses prefix sum for optimization
            For each remaining length, calculates how many characters can be taken from current group
            Updates the DP states accordingly

    The final answer is the total possibilities minus the number of invalid possibilities (strings shorter than required length k).


 */
public:
    const int MOD = 1e9 + 7;  // Modulo constant
    int possibleStringCount(string word, int targetLength) {
        int wordLength = word.size();
        ll totalPossibilities = 1;
        
        // Store consecutive character counts
        vector<int> consecutiveCharCounts;
        int i = 0;
        
        // Count consecutive same characters
        while (i < wordLength) {
            int consecutiveCount = 1;
            // Count how many times current character repeats
            while ((i < wordLength - 1) && (word[i] == word[i + 1])) {
                i++;
                consecutiveCount++;
            }
            // Multiply total possibilities with current consecutive count
            totalPossibilities = (totalPossibilities * consecutiveCount) % MOD;
            consecutiveCharCounts.push_back(consecutiveCount);
            i++;
        }
        
        // dp[j] represents number of ways to form string of length j
        vector<ll> currentDP(targetLength, 1);
        vector<ll> nextDP(targetLength);
        
        // Process each group of consecutive characters from right to left
        for (int groupIdx = min((int)(consecutiveCharCounts.size()), targetLength + 2) - 1; 
             groupIdx >= 0; 
             groupIdx--) {
            
            // Calculate prefix sum for optimization
            vector<ll> prefixSum(targetLength + 1, 0);
            for (int j = 0; j < targetLength; j++) {
                prefixSum[j + 1] = (prefixSum[j] + currentDP[j]) % MOD;
            }
            
            // For each remaining length
            for (int remainingLen = 0; remainingLen < targetLength; remainingLen++) {
                // Calculate how many characters we can take from current group
                int charsToTake = min(consecutiveCharCounts[groupIdx], remainingLen);
                // Update next DP state using prefix sum
                nextDP[remainingLen] = (prefixSum[remainingLen] - 
                                      prefixSum[remainingLen - charsToTake] + MOD) % MOD;
            }
            currentDP = nextDP;
        }
        
        // Final answer is total possibilities minus invalid possibilities
        totalPossibilities = (totalPossibilities - currentDP[targetLength - 1] + MOD) % MOD;
        return (int)(totalPossibilities);
    }
};