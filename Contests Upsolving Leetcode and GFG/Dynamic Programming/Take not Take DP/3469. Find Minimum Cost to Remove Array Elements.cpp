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
You are given an integer array nums. Your task is to remove all elements from the array by performing one of the following operations at each step until nums is empty:

    Choose any two elements from the first three elements of nums and remove them. The cost of this operation is the maximum of the two elements removed.
    If fewer than three elements remain in nums, remove all the remaining elements in a single operation. The cost of this operation is the maximum of the remaining elements.

Return the minimum cost required to remove all the elements.



Example 1:

Input: nums = [6,2,8,4]

Output: 12

Explanation:

Initially, nums = [6, 2, 8, 4].

    In the first operation, remove nums[0] = 6 and nums[2] = 8 with a cost of max(6, 8) = 8. Now, nums = [2, 4].
    In the second operation, remove the remaining elements with a cost of max(2, 4) = 4.

The cost to remove all elements is 8 + 4 = 12. This is the minimum cost to remove all elements in nums. Hence, the output is 12.

Example 2:

Input: nums = [2,1,3,3]

Output: 5

Explanation:

Initially, nums = [2, 1, 3, 3].

    In the first operation, remove nums[0] = 2 and nums[1] = 1 with a cost of max(2, 1) = 2. Now, nums = [3, 3].
    In the second operation remove the remaining elements with a cost of max(3, 3) = 3.

The cost to remove all elements is 2 + 3 = 5. This is the minimum cost to remove all elements in nums. Hence, the output is 5.


@Approach:
    &- Use DP as per the constraints
    &- Assume three elements as idx-1,idx,idx+1 instead of other way around because we can always derive the element which are still left through this way
    &- dp[prevIdx][currIdx] = min({way1,way2,way3})
    &- way1 = max(nums.at(prevIdx), nums.at(currIdx)) + solve(currIdx + 1, currIdx + 2);
    &- way2 = max(nums.at(currIdx), nums.at(currIdx + 1)) + solve(prevIdx, currIdx + 2);
    &- way3 = max(nums.at(prevIdx), nums.at(currIdx + 1)) + solve(currIdx, currIdx + 2);

     */
public:
    vector<int> nums;
    vector<vector<int>> dp;
    int n;
    int solve(int prevIdx, int currIdx)
    {
        if (currIdx == n)
        {
            return nums.at(prevIdx);
        }
        else if (currIdx == n - 1)
        {
            return max(nums.at(prevIdx), nums.at(currIdx));
        }
        if (dp[prevIdx][currIdx] != -1)
        {
            return dp[prevIdx][currIdx];
        }
        // take the first two elements
        const int way1 = max(nums.at(prevIdx), nums.at(currIdx)) + solve(currIdx + 1, currIdx + 2);
        // take the last two elements
        const int way2 = max(nums.at(currIdx), nums.at(currIdx + 1)) + solve(prevIdx, currIdx + 2);
        // take the first and last element
        const int way3 = max(nums.at(prevIdx), nums.at(currIdx + 1)) + solve(currIdx, currIdx + 2);
        return dp[prevIdx][currIdx] = min({way1, way2, way3});
    }
    int minCost(vector<int> &_nums)
    {
        nums = _nums;
        this->n = nums.size();
        dp.resize(n + 1, vector<int>(n + 1, -1));
        return solve(0, 1);
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