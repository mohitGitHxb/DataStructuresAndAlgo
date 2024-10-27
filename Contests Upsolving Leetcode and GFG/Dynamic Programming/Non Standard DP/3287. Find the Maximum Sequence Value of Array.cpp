#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
/*
 * CUSTOM hash function which astatic voids collisions and hence makes unordered maps / sets faster
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
#define tr(it, a) for (auto it = a.begin(); it != a.end(); it++)
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

static int init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
template <class T = int>
static void customPrint(const T &t)
{
    cout << t << " ";
}

template <class T = int>
static void customPrint(const vector<T> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
static void customPrint(const vector<vector<T>> &vec)
{
    cout << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int, class U = int>
static void customPrint(const pair<T, U> &p)
{
    cout << "{" << customPrint(p.first) << ":";
    customPrint(p.second);
    cout << "}\n";
}

template <class T = int, class U = int>
static void customPrint(const unordered_map<T, U, custom_hash> &mp)
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
static void customPrint(const map<T, U> &mp)
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
static void customPrint(const multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
static void customPrint(const set<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
static void customPrint(const unordered_set<T, custom_hash> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int>
static void customPrint(priority_queue<T> pq)
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
static void customPrint(stack<T> st)
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
static void customPrint(queue<T> q)
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
static void customPrint(deque<T> dq)
{
    cout << "[";
    for (auto &i : dq)
    {
        customPrint(i);
    }
    cout << "]\n";
}

template <class T = int, class U = int>
static void customPrint(const unordered_multimap<T, U> &mp)
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
static void customPrint(const unordered_multiset<T> &mp)
{
    cout << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cout << "]\n";
}
static void printBitRepresentation(long long n)
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

static vvi dp(101, vi(1 << 10, -1));
static vvi mp(101, vi());

class Solution
{
private:
    /*
You are given an integer array nums and a positive integer k.

The value of a sequence seq of size 2 * x is defined as:

    (seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).

Return the maximum value of any
subsequence
of nums having size 2 * k.



Example 1:

Input: nums = [2,6,7], k = 1

Output: 5

Explanation:

The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.

Example 2:

Input: nums = [4,2,5,6,7], k = 2

Output: 2

Explanation:

The subsequence [4, 5, 6, 7] has the maximum value of (4 OR 5) XOR (6 OR 7) = 2.



Constraints:

    2 <= nums.length <= 400
    1 <= nums[i] < 27
    1 <= k <= nums.length / 2


    @ Beyond our capability (2500+)
     */
public:
    const int mod = 1e9 + 7;
    int maxValue(vector<int> &nums, int k)
    {
        int n = (int)nums.size();
        //* numbers are in the range 2^7 hence we have created dp1,dp2(prefix,suffix) of size 128
        //* this will hold whether it is feasible for us to make certain OR taking K elements (take not take on prefix side and suffix side)
        vector<vector<vector<bool>>> dp1(n + 1, vector<vector<bool>>(k + 1, vector<bool>(128)));
        vector<vector<vector<bool>>> dp2(n + 1, vector<vector<bool>>(k + 1, vector<bool>(128)));

        vector<vector<bool>> dp(k + 1, vector<bool>(128));
        dp[0][0] = true;
        // prepare the preprocessed prefix dp1
        for (int i = 0; i < n; i++)
        {
            for (int j = k - 1; j >= 0; j--)
            {
                for (int mask = 0; mask < 128; mask++)
                {
                    if (dp[j][mask])
                        dp[j + 1][mask | nums[i]] = true;
                }
            }
            for (int j = 0; j <= k; j++)
            {
                for (int mask = 0; mask < 128; mask++)
                {
                    dp1[i][j][mask] = dp[j][mask];
                }
            }
        }
        // prepare the preprocessed suffix dp2
        dp.assign(k + 1, vector<bool>(128));
        dp[0][0] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = k - 1; j >= 0; j--)
            {
                for (int mask = 0; mask < 128; mask++)
                {
                    if (dp[j][mask])
                        dp[j + 1][mask | nums[i]] = 1;
                }
            }
            for (int j = 0; j <= k; j++)
            {
                for (int mask = 0; mask < 128; mask++)
                {
                    dp2[i][j][mask] = dp[j][mask];
                }
            }
        }
        /*
        & We will use something similar to meet in the middle
        & if at any point it is feasible to achieve OR from K elements using prefix and suffix DPs
        & We will maximize the answer

         */
        int res = 0;
        for (int i = 0; i < n - 1; i++)
        {
            // we cannot use more than k elements (this is out of range)
            if (i + 1 < k or n - i - 1 < k)
                continue;

            for (int mask1 = 0; mask1 < 128; mask1++)
            {
                for (int mask2 = 0; mask2 < 128; mask2++)
                {
                    //* If there is a possibility to achieve OR from K elements using prefix and suffix DPs
                    if (dp1[i][k][mask1] && dp2[i + 1][k][mask2])
                    {
                        res = max(res, mask1 ^ mask2);
                    }
                }
            }
        }
        return res;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
