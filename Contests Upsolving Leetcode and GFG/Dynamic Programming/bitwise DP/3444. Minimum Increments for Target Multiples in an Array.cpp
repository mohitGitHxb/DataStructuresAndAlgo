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
You are given two arrays, nums and target.

In a single operation, you may increment any element of nums by 1.

Return the minimum number of operations required so that each element in target has at least one multiple in nums.



Example 1:

Input: nums = [1,2,3], target = [4]

Output: 1

Explanation:

The minimum number of operations required to satisfy the condition is 1.

    Increment 3 to 4 with just one operation, making 4 a multiple of itself.

Example 2:

Input: nums = [8,4], target = [10,5]

Output: 2

Explanation:

The minimum number of operations required to satisfy the condition is 2.

    Increment 8 to 10 with 2 operations, making 10 a multiple of both 5 and 10.

Example 3:

Input: nums = [7,9,10], target = [7]

Output: 0

Explanation:

Target 7 already has a multiple in nums, so no additional operations are needed.

@Approach:
 &- Get: all the lcm values of all subsets because in order to check if an element e is a multiple of some set of values from target (t1,t2,t3,..) it is best to use lcm(t1,t2,t3,..)

 &- Try for all possible subsets of target array on the entire nums array
 &- For each e in nums we have two choices either increment it or not increment it
 &- If we increment it then we have to check if it is a multiple of all the values in the target array



     */
public:
    // global vars
    vector<int> nums;
    vector<int> target;
    int numsSize, targetSize;
    // this is for the all subsets of target array
    vector<ll> preComputedLCM;

    // memoization
    ll dp[int(5e4 + 5)][16];
    // Helper functions
    inline constexpr ll findNextDivisible(const ll initialValue, const ll lcmValue)
    {
        return ((initialValue + lcmValue - 1) / lcmValue) * lcmValue;
    }

    inline constexpr ll lcm(const ll num1, const ll num2)
    {
        return (num1 * 1LL * num2) / __gcd(num1, num2);
    }

    void preComputeLCM()
    {
        const int subsetSize = 1 << targetSize; // this is 16 at max
        preComputedLCM.resize(subsetSize);
        for (int i = 1; i < subsetSize; i++)
        {
            preComputedLCM[i] = 1;
            for (int j = 0; j < targetSize; j++)
            {
                if (i & (1 << j))
                {
                    preComputedLCM[i] = lcm(preComputedLCM[i], target[j]);
                }
            }
        }
    }

    ll solve(int index, int bitmask)
    {
        if (bitmask == (1 << targetSize) - 1)
        {
            return 0;
        }
        if (index == numsSize)
        {
            return INT_MAX;
        }
        if (dp[index][bitmask] != -1)
        {
            return dp[index][bitmask];
        }
        ll ans = solve(index + 1, bitmask);
        for (int subset = 1; subset < (1 << targetSize); subset++)
        {
            ll currentSubsetLCM = preComputedLCM[subset];
            ll nextMultiple = findNextDivisible(nums[index], currentSubsetLCM);
            ans = min<ll>(ans, solve(index + 1, subset | bitmask) + (nextMultiple - nums[index]));
        }
        return dp[index][bitmask] = ans;
    }
    int minimumIncrements(vector<int> &_nums, vector<int> &_target)
    {
        nums = _nums;
        target = _target;
        numsSize = nums.size();
        targetSize = target.size();

        memset(dp, -1, sizeof(dp));
        preComputeLCM();

        return solve(0, 0);
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