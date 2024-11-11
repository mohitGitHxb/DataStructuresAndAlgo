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
#define ull unsigned long long
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

static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
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
You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Return the sum of all possible good subsequences of nums.

Since the answer may be very large, return it modulo 109 + 7.

Note that a subsequence of size 1 is considered good by definition.



Example 1:

Input: nums = [1,2,1]

Output: 14

Explanation:

    Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
    The sum of elements in these subsequences is 14.

Example 2:

Input: nums = [3,4,5]

Output: 40

Explanation:

    Good subsequences are: [3], [4], [5], [3,4], [4,5], [3,4,5].
    The sum of elements in these subsequences is 40.

Intuition:

Instead of checking all possible subsequences explicitly (which would be inefficient), we can use dynamic programming or a counting approach to calculate the number of good subsequences that can end with each number in the array.
Approach:
Variables:

    cnt[i]: This variable tracks the number of good subsequences that end with the element i.
    sum[i]: This variable tracks the sum of all good subsequences that end with the element i.

Algorithm:

    Initialize cnt and sum:
        For each number i in nums, we need to consider how subsequences can be formed that end with i. We add the possible subsequences formed by adding i to subsequences that end with i-1, i+1, or just the subsequence {i} itself.

    Update cnt and sum:
        For each element i in nums, we update cnt[i] based on subsequences ending at i-1 and i+1 (since the difference between consecutive elements should be 1).
        Similarly, sum[i] is updated by adding contributions from i-1, i+1 subsequences and also considering the sum of the subsequences that end at i.

    Final Calculation:
        After processing all elements, we sum up all the values in sum to get the final result, which is the total sum of all good subsequences modulo ( 10^9 + 7 ).

Example: nums = [1, 2, 1]
Step 1: Process the first element 1

    i = 1
        cnt[1] is updated by considering subsequences ending with 0, 1, and 2. Since there's no subsequence yet, we initialize cnt[1] = 1 (the subsequence {1} itself).
        sum[1] is updated to reflect the subsequences that end with 1. Since only {1} exists, sum[1] = 1.
    After processing 1:
        cnt = {1: 1}
        sum = {1: 1}

Step 2: Process the second element 2

    i = 2
        cnt[2] is updated by considering subsequences ending with 1 (since abs(2 - 1) = 1), and 2. cnt[2] is updated as:
            cnt[2] = cnt[1] + 1 = 1 + 1 = 2 (this accounts for {2} and {1, 2}).
        sum[2] is updated by considering the sum of subsequences that end with 1 and 3. sum[2] is updated as:
            sum[2] = sum[1] + 1 * cnt[1] = 1 + 1 * 1 = 2.
    After processing 2:
        cnt = {1: 1, 2: 2}
        sum = {1: 1, 2: 2}

Step 3: Process the third element 1

    i = 1
        cnt[1] is updated by considering subsequences ending with 0, 1, and 2. Since the subsequences {1}, {2, 1}, and {1, 2, 1} are valid, we update cnt[1]:
            cnt[1] = cnt[2] + 1 = 2 + 1 = 3.
        sum[1] is updated by considering subsequences that end with 0, 1, and 2:
            sum[1] = sum[2] + 1 * cnt[2] = 2 + 1 * 2 = 4.
    After processing 1:
        cnt = {1: 3, 2: 2}
        sum = {1: 4, 2: 2}

Final Step: Calculate the Total Sum

    The final step is to sum up all the values in sum, which gives us the sum of all good subsequences.
    sum[1] + sum[2] = 4 + 2 = 6

Thus, the result is 6, which is the sum of all good subsequences.
Recap of the cnt and sum Maps:

    cnt[i]: Tracks how many good subsequences end with i.
    sum[i]: Tracks the sum of all good subsequences ending with i.


     */
public:
    const int mod = 1e9 + 7;
    int sumOfGoodSubsequences(vector<int> &nums)
    {
        map<int, int> cnt, sum;

        // Loop through all numbers in the nums array
        for (int i : nums)
        {
            // Update cnt[i] by considering subsequences from i-1, i, and i+1
            cnt[i] += (cnt[i - 1] + cnt[i + 1] + 1) % mod;
            cnt[i] %= mod;

            // Update sum[i] by considering subsequences from i-1, i, and i+1
            sum[i] += (sum[i - 1] + sum[i + 1]) % mod;
            sum[i] %= mod;

            // Add the contribution of the subsequences that end at i
            sum[i] += (long long)(cnt[i - 1] + cnt[i + 1] + 1) % mod * i % mod;
            sum[i] %= mod;
        }

        // Calculate the final result by summing all the values in sum
        int res = 0;
        for (auto &p : sum)
        {
            res += p.second;
            res %= mod;
        }

        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;
    cout
        << "\n\n\tProgram ended\n\n";
    return 0;
}
