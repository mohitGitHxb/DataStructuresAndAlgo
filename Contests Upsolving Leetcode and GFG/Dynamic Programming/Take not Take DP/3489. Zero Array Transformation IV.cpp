#include <bits/stdc++.h>
using namespace std;
/*
Intution :

    But here the changes is, we need to subtract exact val from each index selected & also we can select any indices in the range given ( don't have to apply the operation on each indices in the range given and this makes this problem a bit simpler)

    As we can select any indices in the range given, now we can think it up in this way -> consider one item in the nums at a time and then figure out - how many queries required to make it zero. also while doing so we have option to apply a query or skip the query. This implies the corelation with seen problem -> target sum from a given array -> given a target and a set of items check if the target sum is achieved by taking sum of some of the items -> typical Kanpsack dp problem of pick/not-to-pick type.
    Once we identified that we need to apply dp, then the solution will be:
        for each items find out the least index of the query where it can be sum up to zero.
        for any of the items there is no such combination found then return -1
        take the maximum index as the answer out of all items

Complexity :

    Time : O(sizeof(nums) * max(nums[i]) * sizeof(queries))
    Space : O(max(nums[i]) * sizeof(queries))


*/
class Solution
{
public:
    int solve(vector<vector<int>> &q, int i, int target, int k, vector<vector<int>> &dp)
    {
        if (target == 0)
            return k; // we found  a valid sum equal to target so return current index of query.
        if (k >= q.size() || target < 0)
            return q.size() + 1; // return a larger number to invalidate this flow
        if (dp[target][k] != -1)
            return dp[target][k];
        int res = solve(q, i, target, k + 1, dp); // skip current query val
        if (q[k][0] <= i && i <= q[k][1])
            res = min(res, solve(q, i, target - q[k][2], k + 1, dp)); // pick the val if its range is in the range of target index
        return dp[target][k] = res;
    }

    int minZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
        int ans = -1;
        for (int i = 0; i < nums.size(); ++i)
        {
            vector<vector<int>> dp(nums[i] + 1, vector<int>(queries.size() + 1, -1));
            ans = max(ans, solve(queries, i, nums[i], 0, dp));
        }
        return (ans > queries.size()) ? -1 : ans;
    }
};
int main()
{
    return 0;
}