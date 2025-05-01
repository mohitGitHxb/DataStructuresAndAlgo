#include <bits/stdc++.h>
// ordered sets (policy based data structures)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
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
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
static int init = []
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
template <class T = int32_t>
using mset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;

class Solution
{
private:
    /*
Bob is stuck in a dungeon and must break n locks, each requiring some amount of energy to break. The required energy for each lock is stored in an array called strength where strength[i] indicates the energy needed to break the ith lock.

To break a lock, Bob uses a sword with the following characteristics:

    The initial energy of the sword is 0.
    The initial factor X by which the energy of the sword increases is 1.
    Every minute, the energy of the sword increases by the current factor X.
    To break the ith lock, the energy of the sword must reach at least strength[i].
    After breaking a lock, the energy of the sword resets to 0, and the factor X increases by a given value K.

Your task is to determine the minimum time in minutes required for Bob to break all n locks and escape the dungeon.

Return the minimum time required for Bob to break all n locks.



Example 1:

Input: strength = [3,4,1], K = 1

Output: 4

Explanation:
Time	Energy	X	Action	Updated X
0	0	1	Nothing	1
1	1	1	Break 3rd Lock	2
2	2	2	Nothing	2
3	4	2	Break 2nd Lock	3
4	3	3	Break 1st Lock	3

The locks cannot be broken in less than 4 minutes; thus, the answer is 4.

Example 2:

Input: strength = [2,5,4], K = 2

Output: 5

Explanation:
Time	Energy	X	Action	Updated X
0	0	1	Nothing	1
1	1	1	Nothing	1
2	2	1	Break 1st Lock	3
3	3	3	Nothing	3
4	6	3	Break 2nd Lock	5
5	5	5	Break 3rd Lock	7

The locks cannot be broken in less than 5 minutes; thus, the answer is 5.
@ Approach
&- It is not GREEDY | Binary search on answer
&- Try absolute brute force (backtracking and memoization)
&- Try to break the locks in all possible manner.
     */
public:
    const int mod = 1e9 + 7;
    int dp[256];
    int solve(vector<int> &strength, int brokenMask, int XFactor, int K)
    {
        if (brokenMask == (1 << strength.size()) - 1)
        {
            return 0;
        }
        if (dp[brokenMask] != -1)
        {
            return dp[brokenMask];
        }
        int time = INT_MAX;
        for (int i = 0; i < strength.size(); i++)
        {
            if ((brokenMask & (1 << i)) == 0)
            {
                int newTime = (strength[i] + XFactor - 1) / XFactor; // ceiling division
                int newBrokenMask = brokenMask | (1 << i);
                int newXFactor = XFactor + K;
                time = min(time, newTime + solve(strength, newBrokenMask, newXFactor, K));
            }
        }
        return dp[brokenMask] = time;
    }
    int findMinimumTime(vector<int> &strength, int K)
    {
        memset(dp, -1, sizeof(dp));
        return solve(strength, 0, 1, K);
    }
};
