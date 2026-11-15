#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
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
You are given two positive integer arrays nums and target, of the same length.

In a single operation, you can select any
subarray
of nums and increment or decrement each element within that subarray by 1.

Return the minimum number of operations required to make nums equal to the array target.



Example 1:

Input: nums = [3,5,1,2], target = [4,6,2,4]

Output: 2

Explanation:

We will perform the following operations to make nums equal to target:
- Increment nums[0..3] by 1, nums = [4,6,2,3].
- Increment nums[3..3] by 1, nums = [4,6,2,4].

Example 2:

Input: nums = [1,3,2], target = [2,1,4]

Output: 5

Explanation:

We will perform the following operations to make nums equal to target:
- Increment nums[0..0] by 1, nums = [2,3,2].
- Decrement nums[1..1] by 1, nums = [2,2,2].
- Decrement nums[1..1] by 1, nums = [2,1,2].
- Increment nums[2..2] by 1, nums = [2,1,3].
- Increment nums[2..2] by 1, nums = [2,1,4].

     */
public:
    const int MOD = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    long long minimumOperations(vector<int> &nums, vector<int> &target)
    {
        ll operations = 0;
        ll previous = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            ll difference = target[i] - nums[i];
            if (difference < 0 && previous > 0) //~ difference transition from positive to negative hence assume previous as 0 now we only need abs(difference) amount of increments to make it 0
            {
                operations += abs(difference);
            }
            else if (difference >= 0 && previous < 0) //~ difference transition from negative to positive hence we need abs(difference) amount of decrements to make it 0
            {
                operations += difference;
            }
            // in this case if difference is positive and so is the previous
            // then count the number of extra changes in case diff > prev;

            // if difference is negative and so is the previous
            // then count the number of extra changes in case diff < prev (both are negative)
            else if (abs(difference) > abs(previous))
            {
                operations += abs(difference) - abs(previous);
            }

            // update previous to current difference value
            previous = difference;
        }
        return operations;
    }
};

int main()
{
    return 0;
}