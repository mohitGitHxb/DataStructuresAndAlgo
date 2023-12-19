#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define clr(x) memset(x, false, sizeof(x))
#define sortall(x) sort(all(x))
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
#define PI 3.1415926535897932384626
#define mod 1000000007
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef unordered_map<int, int> hmpi;
typedef unordered_map<ll, ll> hmpll;
typedef unordered_map<int, pii> hmppi;
typedef unordered_map<int, vi> hmpvi;
typedef unordered_set<int> hsi;
typedef unordered_set<ll> hsll;
typedef unordered_set<pii> hspi;
typedef unordered_set<pl> hspl;
typedef map<int, int> mpi;
typedef map<ll, ll> mpll;
typedef map<int, pii> mppi;
typedef map<int, vi> mpvi;
typedef set<int> si;
typedef set<ll> sll;
typedef set<pii> spi;
typedef set<pl> spl;
#define sz(x) ((ll)(x).size())

/*
You are given a 0-indexed integer array nums and an integer k.

You can perform the following operation on the array at most k times:

    Choose any index i from the array and increase or decrease nums[i] by 1.

The score of the final array is the frequency of the most frequent element in the array.

Return the maximum score you can achieve.

The frequency of an element is the number of occurences of that element in the array.



Example 1:

Input: nums = [1,2,6,4], k = 3
Output: 3
Explanation: We can do the following operations on the array:
- Choose i = 0, and increase the value of nums[0] by 1. The resulting array is [2,2,6,4].
- Choose i = 3, and decrease the value of nums[3] by 1. The resulting array is [2,2,6,3].
- Choose i = 3, and decrease the value of nums[3] by 1. The resulting array is [2,2,6,2].
The element 2 is the most frequent in the final array so our score is 3.
It can be shown that we cannot achieve a better score.

Example 2:

Input: nums = [1,4,4,2,4], k = 0
Output: 3
Explanation: We cannot apply any operations so our score will be the frequency of the most frequent element in the original array, which is 3.


 */

/*

### Intuition:

The problem involves finding the maximum score achievable by performing a limited number of operations (at most `k`) on the array. The score is defined as the frequency of the most frequent element in the array after the operations.

### Hints:

1. The goal is to maximize the frequency of the most frequent element, which means trying to make as many elements equal to each other as possible.
2. Use binary search to find the maximum possible frequency.
3. For each potential frequency, check if it's achievable with the given operations using a sliding window approach.

### Algorithm:

1. Sort the array to simplify the problem.
2. Use binary search to find the maximum possible frequency. The range for binary search is from 1 to the size of the array.
3. For each potential frequency (`mid`), use a sliding window approach to check if it's achievable with the given operations. The sliding window moves from left to right, maintaining the count and sum of elements in the window.
4. If the cost of operations to achieve the potential frequency is less than or equal to `k`, update the answer (`ans`) and continue the search for higher frequencies.
5. Adjust the binary search range accordingly.

### Time Complexity:

The overall time complexity is O(n log n), where n is the size of the input array. The sorting step has a time complexity of O(n log n), and the binary search step has a time complexity of O(log n). The sliding window approach within the binary search has a linear time complexity.

### Space Complexity:

The space complexity is O(n) for the prefix sum array.

### Summary:

The code efficiently uses binary search and sliding window approaches to find the maximum achievable score in a sorted array. The use of binary search helps narrow down the search space for the maximum frequency, and the sliding window efficiently checks the feasibility of achieving a specific frequency with the given operations. The time and space complexities are reasonable for the given problem size.
 */
class Solution
{
public:
    bool isValid(int mid, vector<int> &nums, long long k, vector<long long> &prefixSum)
    {
        long long cost = 0;
        for (int i = 0, j = 0; i < nums.size(); i++)
        {
            if (i - j + 1 == mid)
            {
                int medianIdx = (i + j) >> 1;
                long long sumLeft = prefixSum.at(medianIdx) - prefixSum.at(j) + nums.at(j);
                long long countLeft = medianIdx - j + 1;
                long long sumRight = prefixSum.at(i) - prefixSum.at(medianIdx) + nums.at(medianIdx);
                long long countRight = i - medianIdx + 1;

                cost = nums.at(medianIdx) * countLeft - sumLeft + sumRight - nums.at(medianIdx) * countRight;
                if (cost <= k)
                {
                    return true;
                }
                j++;
            }
        }
        return cost <= k;
    }

    int maxFrequencyScore(vector<int> &nums, long long k)
    {
        sort(nums.begin(), nums.end());
        int low = 0, high = nums.size(), ans = 1;
        vector<long long> prefixSum(nums.size());
        prefixSum.front() = nums.front();
        for (int i = 1; i < nums.size(); i++)
        {
            prefixSum.at(i) = prefixSum.at(i - 1) + nums.at(i);
        }

        while (low <= high)
        {
            int mid = (low + high) >> 1;
            int lengthToTry = mid;
            if (isValid(lengthToTry, nums, k, prefixSum))
            {
                ans = max(mid, ans);
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return ans;
    }
};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}