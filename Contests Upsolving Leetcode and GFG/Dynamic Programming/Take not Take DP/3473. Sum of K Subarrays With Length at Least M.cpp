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
You are given an integer array nums and two integers, k and m.
Return the maximum sum of k non-overlapping
of nums, where each subarray has a length of at least m.

Example 1:
Input: nums = [1,2,-1,3,3,4], k = 2, m = 2
Output: 13
Explanation:
The optimal choice is:
    Subarray nums[3..5] with sum 3 + 3 + 4 = 10 (length is 3 >= m).
    Subarray nums[0..1] with sum 1 + 2 = 3 (length is 2 >= m).
The total sum is 10 + 3 = 13.

Example 2:

Input: nums = [-10,3,-1,-2], k = 4, m = 1

Output: -10

Explanation:

The optimal choice is choosing each element as a subarray. The output is (-10) + 3 + (-1) + (-2) = -10.


     */
public:
    const int NEG_INF = -1000000000;
    int dp[2002][2002][2];
    int solve(const vector<int> &nums, const vector<int> &prefix, int index, int remaining, int canExtend, int m)
    {
        if (index == nums.size())
            return remaining == 0 ? 0 : NEG_INF;
        if (dp[index][remaining][canExtend] != -1)
            return dp[index][remaining][canExtend];

        int best = NEG_INF;
        if (canExtend)
        {
            best = max(best, nums[index] + solve(nums, prefix, index + 1, remaining, 1, m));
            best = max(best, solve(nums, prefix, index, remaining, 0, m));
        }
        else
        {
            if (remaining == 0)
                return 0;
            best = max(best, solve(nums, prefix, index + 1, remaining, 0, m));
            if (nums.size() - index >= m)
            {
                int currentSum = prefix[index + m] - prefix[index];
                best = max(best, currentSum + solve(nums, prefix, index + m, remaining - 1, 1, m));
            }
        }

        return dp[index][remaining][canExtend] = best;
    }

    int maxSum(vector<int> &nums, int k, int m)
    {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        partial_sum(nums.begin(), nums.end(), prefix.begin() + 1);
        memset(dp, -1, sizeof(dp));
        return solve(nums, prefix, 0, k, 0, m);
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