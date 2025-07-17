#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/*
 * CUSTOM hash function which avoids collisions and hence makes unordered maps / sets faster
 */
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
#define gc getchar_unlocked
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(x) memset(x, false, sizeof(x))
#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define SUM(v) accumulate(all(v), 0LL)
#define endl "\n"
#define sortall(x) sort(all(x))
#define forv(it, a) for (auto &it : a)
#define PI 3.1415926535897932384626
ll MOD = 998244353;
double eps = 1e-12;
#define forsn(i, s, e) for (ll i = s; i < e; i++)
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
typedef vector<vvl> vvvl;
template <class T = pii>
using oset =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T = pii>
using mset = tree<T, null_type, less_equal<T>, rb_tree_tag,
                  tree_order_statistics_node_update>;
#define sz(x) ((ll)(x).size())

void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
template <class T = int>
void customPrint(const T &t)
{
    cout << t << " ";
}

template <class T = int>
void customPrint(const vector<T> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const vector<vector<T>> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int, class U = int>
void customPrint(const pair<T, U> &p)
{
    cout << "{" << customPrint(p.first) << ":";
    customPrint(p.second);
    cout << "}\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_map<T, U, custom_hash> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":";
        customPrint(i.second);
        cout << "}\n";
    }
    cout << "]\n";
}

template <class T = int, class U = int>
void customPrint(const map<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":";
        customPrint(i.second);
        cout << "}\n";
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const set<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const unordered_set<T, custom_hash> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(priority_queue<T> pq)
{
    cout << "[";
    while (!pq.empty())
    {
        customPrint(pq.top());
        pq.pop();
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(stack<T> st)
{
    cout << "[";
    while (!st.empty())
    {
        customPrint(st.top());
        st.pop();
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(queue<T> q)
{
    cout << "[";
    while (!q.empty())
    {
        customPrint(q.front());
        q.pop();
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(deque<T> dq)
{
    cout << "[";
    for (auto &i : dq)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_multimap<T, U> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        cout << "{" << i.first << ":";
        customPrint(i.second);
        cout << "}\n";
    }
    cout << "]\n";
}

template <class T = int>
void customPrint(const unordered_multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}
void printBitRepresentation(long long n)
{
    string binary = bitset<64>(n).to_string(); // converts to binary
    cout << "Binary representation: " << binary << "\n";
}
bool isPrime_sqrt(ll n)
{
    if (n == 1)
        return false;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
long long binaryExponentiation(long long base, long long exponent, long long mod)
{
    long long res = 1;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exponent >>= 1;
    }
    return res;
}
long long getModularMultiplicativeInverse(long long num, long long mod)
{
    // multiplicative inverse only exists if num and mod are relatively prime (coprime) i.e gcd(num, mod) = 1
    if (__gcd(num, mod) != 1)
    {
        return -1;
    }
    return binaryExponentiation(num, mod - 2, mod);
}

class Solution
{
private:
    /*


You are given an integer array nums and a positive integer k.

A
subsequence
sub of nums with length x is called valid if it satisfies:

    (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.

Return the length of the longest valid subsequence of nums.



Example 1:

Input: nums = [1,2,3,4,5], k = 2

Output: 5

Explanation:

The longest valid subsequence is [1, 2, 3, 4, 5].

Example 2:

Input: nums = [1,4,2,3,1,4], k = 3

Output: 4

Explanation:

The longest valid subsequence is [1, 4, 1, 4].

@ Approach:
&- Firstly take modulo with K for all elements in the array
&- Doing this you will notice that for a subsequence we can see an alternating pattern something like x y x y x y ...
&- Now we try to build this subsequence
% We will check whether adding this current element increases our subsequence length or not to do this we can try all pairs of element that will make our first two elements in our subsequence

~ Assume subsequence as this x,y,x,y,x,y,x,y
&- y : findThis, x: previousTaken
&- now we will try to find y in the left range but this new y index has to be smaller than x index (previousTaken)
&- To perform this operation we will use lower_bound on indexMap

~ TIP: we are using indices instead of values as using indices it is easier to find index smaller than previousTaken and also index provides the value as well
~ Default length would be 2 as we are taking 2 elements atleast.

* Time complexity O(N^2LogN)
     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    unordered_map<int, vi, custom_hash> indexMap;
    vvi dp;
    int solve(int findThis, int previousTaken, vi &nums)
    {
        int length = 2;
        if (dp[findThis][previousTaken] != -1)
        {
            return dp[findThis][previousTaken];
        }
        int findThis_index = lower_bound(all(indexMap[nums[findThis]]), previousTaken) - indexMap[nums[findThis]].begin();
        if (findThis_index != 0)
        {
            findThis_index--;
            length = max(length, 1 + solve(previousTaken, indexMap[nums[findThis]].at(findThis_index), nums));
        }
        return dp[findThis][previousTaken] = length;
    }

    int maximumLength(vector<int> &nums, int k)
    {
        forsn(i, 0, sz(nums))
        {
            indexMap[nums[i] % k].eb(i);
            nums[i] = nums[i] % k;
        }
        dp.resize(sz(nums) + 1, vi(sz(nums) + 1, -1));
        int ans = 0;
        rforsn(i, sz(nums) - 1, 1)
        {
            rforsn(j, i - 1, 0)
            {
                ans = max(ans, solve(i, j, nums));
            }
        }
        return ans;
    }
};

class SolutionLISVariant
{
public:
    int maximumLength(vector<int> &nums, int k)
    {
        // Using same LIS bottom up code

        int n = nums.size();

        // vector<int> dp1(n, 1); //mod1
        // vector<int> dp0(n, 1); //mod0
        //  dp0 {} //mod0
        //  dp1 {} //mod1
        //{
        //   {}, 0th row for mod0
        //  {}  1st row for mod1

        int n = nums.size();

        // vector<int> dp1(n, 1); //mod1
        // vector<int> dp0(n, 1); //mod0
        //  dp0 {} //mod0
        //  dp1 {} //mod1
        //{
        //   {}, 0th row for mod0
        //  {}  1st row for mod1
        //}

        // row = 0 is for mod0
        // row = 1 is for mod1
        // row = 2 is for mod2
        //....
        // row = k-1 is for mod k-1
        vector<vector<int>> dp(k, vector<int>(n, 1));
        int maxSub = 1;

        // mod = 1
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                int mod = (nums[j] + nums[i]) % k;
                // mod = 0 = 0th row , %2 = 0 waale case ka result
                // mod = 1 = 1st row, %2 = 1 waale case ka result
                dp[mod][i] = max(dp[mod][i], 1 + dp[mod][j]);
                maxSub = max(maxSub, dp[mod][i]);
            }
        }

        return maxSub;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;
    vi nums{1, 4, 2, 3, 1, 4};
    int k = 3;
    cout << obj.maximumLength(nums, k);
    cout << "\nProgram Started\n\n";
    return 0;
}
