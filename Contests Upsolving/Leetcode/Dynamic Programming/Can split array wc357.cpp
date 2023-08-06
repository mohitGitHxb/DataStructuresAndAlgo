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

@ DP MCM based
Intuition:

    The problem can be solved using dynamic programming, where we check whether it is possible to split the array into non-empty arrays by performing a series of steps.
    The main idea is to find if there exist valid subarrays in the given array that satisfy the conditions mentioned in the problem statement.
    We can use recursion with memoization (dynamic programming) to efficiently check all possible subarrays and find if it is possible to split the array.

Explanation of the code:

    The function Mcm is a recursive function that checks if it is possible to split the subarray from index i to index j (inclusive) into multiple non-empty arrays that satisfy the given conditions.
    The function takes four parameters: i and j are the starting and ending indices of the current subarray being considered, nums is the input array, and m is the threshold value that the sum of elements in a subarray should be greater than or equal to.
    The base cases of the recursion are when the subarray has only one element, in which case it is always valid, and when the sum of elements in the subarray is less than m, in which case it is not possible to split the array.
    The function uses memoization to avoid redundant calculations. The dp array is used to store the results of subproblems.
    The main function canSplitArray calculates the prefix sum of the input array to efficiently compute the sum of elements in any subarray.
    It initializes the dp array with -1 to indicate that no subproblem has been solved yet.
    It then calls the Mcm function with the entire array to check if it is possible to split the entire array into non-empty arrays that satisfy the given conditions.

Time Complexity:

    The time complexity of the code is O(n^3), where n is the size of the input array nums.
    The function Mcm is called for all possible subarrays of nums, resulting in a time complexity of O(n^2) for calculating the prefix sum.
    Each call to the Mcm function can have a complexity of O(n) in the worst case due to the for-loop inside the function.

Space Complexity:

    The space complexity of the code is O(n^2) due to the dp array, which stores the results of subproblems for memoization.
    The prefix array also requires O(n) space to store the prefix sum of nums.

Hints:

    The problem can be efficiently solved using dynamic programming with memoization, as the recursive approach can lead to redundant calculations.
    Use the prefix sum technique to calculate the sum of elements in any subarray efficiently.
    Handle the base cases in the recursion to terminate the recursion and return the correct result.
    Memoize the results of subproblems to avoid redundant calculations and improve the overall efficiency.
 */
class Solution
{
private:
    vector<vector<int>> dp;
    vector<int> prefix;

public:
    bool Mcm(int i, int j, vector<int> &nums, int m)
    {
        if (i == j)
            return true;
        if (dp[i][j] != -1)
            return dp[i][j];

        int sum = 0;
        if (i == 0)
            sum = prefix[j];
        else
            sum = prefix[j] - prefix[i - 1];

        if (sum >= m && j - i == 1)
            return dp[i][j] = true;
        if (sum < m)
            return dp[i][j] = false;
        bool ans = false;
        for (int k = i; k < j; k++)
        {
            if (Mcm(i, k, nums, m) && Mcm(k + 1, j, nums, m))
            {
                ans = true;
                break;
            }
        }
        return dp[i][j] = ans;
    }
    bool canSplitArray(vector<int> &nums, int m)
    {
        const int n = nums.size();
        if (n <= 2)
            return true;
        prefix.resize(n);
        partial_sum(nums.begin(), nums.end(), prefix.begin());
        dp.resize(n, vector<int>(n, -1));
        return Mcm(0, n - 1, nums, m);
    }
};

/*
@ Easy solution in O(1)
Explanation of the updated code:

    The updated code takes a simpler approach to check if it is possible to split the array into non-empty arrays that satisfy the given conditions.
    It first checks the base cases: if the array has 2 or fewer elements, it is always possible to split it into non-empty arrays.
    Then, it checks the conditions for the first and last elements of the array separately. If the sum of the first two elements or the last two elements is greater than or equal to m, it is possible to split the array.
    Finally, it iterates through the array and checks if there exists any pair of adjacent elements whose sum is greater than or equal to m. If such a pair is found, it is also possible to split the array.

Time Complexity:

    The time complexity of the updated code is O(n), where n is the size of the input array nums.
    The function iterates through the array once, performing constant time operations for each element.

Space Complexity:

    The space complexity of the code is O(1) because it uses only a constant amount of extra space to store variables.

Hints:

    The problem can be solved with a simple linear scan of the array to check for valid pairs of adjacent elements.
    Consider the special cases of the first and last elements of the array separately.
    Check if the sum of adjacent elements is greater than or equal to m to determine if it is possible to split the array.

 */

bool canSplit(vector<int> &nums, int m)
{
    const int n = nums.size();
    if (n <= 2)
        return true;
    if (nums.at(0) + nums.at(1) >= m || nums.at(n - 1) + nums.at(n - 2) >= m)
    {
        return true;
    }
    int s1 = 0;
    for (int i = 1; i < n - 1; i++)
    {
        if (nums.at(i) + nums.at(i + 1) >= m)
            return true;
    }
    return false;
}
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