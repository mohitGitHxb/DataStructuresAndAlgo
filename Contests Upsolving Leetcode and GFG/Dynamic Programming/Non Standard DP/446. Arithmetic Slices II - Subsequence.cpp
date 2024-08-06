#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
using mset = tree<long long, null_type, less_equal<long long>, rb_tree_tag,
                  tree_order_statistics_node_update>;
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

class Solution
{
private:
    /*
Given an integer array nums, return the number of all the arithmetic subsequences of nums.

A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

    For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
    For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.

A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.

    For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].

The test cases are generated so that the answer fits in 32-bit integer.

@ Observation:
& We can see that for a particular element we have choices whether to combine it with any previous element or not.
& If we combine it with any previous element then the difference will be same and if we don't combine it then the difference will be different.

& we can check for every element j such that j < i then calculate common difference and update the values in dp[i][diff]
^ This make sures that we are storing {diff,freqOfDiff} and then we can simply add it to the answer
     */
public:
    Solution()
    {
        fast_read();
    }

    int numberOfArithmeticSlices(vector<int> &nums)
    {
        //* Use map because the values are in large range -INT_MAX to INT_MAX
        vector<unordered_map<ll, ll>> dp(nums.size(), unordered_map<ll, ll>());
        int ans = 0;
        for (int i = 1; i < nums.size(); i++)
        {

            for (int j = 0; j < i; j++)
            {
                ll diff = (nums[i] - nums[j]) * 1LL;
                dp[i][diff] += dp[j][diff] + 1; // add this to already existing difference for this index
                ans += dp[j][diff];
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}