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

// class for Disjoint Set Union
class DSU
{
public:
    vector<int> parent, size;
    DSU(int n)
    {
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }
    void unionSet(int x, int y)
    {
        int xRoot = find(x);
        int yRoot = find(y);
        if (xRoot == yRoot)
            return;
        if (size[xRoot] < size[yRoot])
            swap(xRoot, yRoot);
        parent[yRoot] = xRoot;
        size[xRoot] += size[yRoot];
    }
};

class Solution
{
private:
    /*
        You are given an array of integers nums of size n and a positive integer threshold.

There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.

Return the number of connected components in this graph.

A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.

The term lcm(a, b) denotes the least common multiple of a and b.



Example 1:

Input: nums = [2,4,8,3,9], threshold = 5

Output: 4

Explanation:



The four connected components are (2, 4), (3), (8), (9).

Example 2:

Input: nums = [2,4,8,3,9,12], threshold = 10

Output: 2

Explanation:

The two connected components are (2, 3, 4, 8, 9), and (12).



Constraints:

    1 <= nums.length <= 105
    1 <= nums[i] <= 109
    All elements of nums are unique.
    1 <= threshold <= 2 * 105

    @ Approach
    &- Since lcm(x,y) <= threshold <= x * y. we can conclude that threshold value will be at max x * y
    &- the maximum value of threshold is 2 * 1e5 but nums[i] can go upto 1e9 that means numbers which are greater than 2 * 1e5 are not possible to connect.

     */
public:
    // this map will store the divisor and the lowest number (the index) which is divisible by that divisor (from the array)
    unordered_map<int, int, custom_hash> divisorMap;
    // utility function to check whether lcm of two numbers is less than threshold
    inline constexpr bool isLCMLessThanThreshold(const ll num1, const ll num2, const ll threshold)
    {
        const ll LCM = (num1 * 1LL * num2) / __gcd(num1, num2);
        return LCM <= threshold;
    }
    void buildDivisorMap(const vector<int> &nums, const int threshold, DSU &dsu)
    {
        // O(N * sqrt(Max(nums[i]))) --> less than 4 * 1e7
        forsn(i, 0, sz(nums))
        {
            for (int divisor = 1; divisor * divisor <= nums[i]; divisor++)
            {
                if (nums[i] % divisor == 0)
                {
                    // to make sure we only keep smallest number which is divisible by divisor
                    if (divisorMap.count(divisor))
                    {
                        const int divisorIndex = divisorMap[divisor];
                        if (isLCMLessThanThreshold(nums[i], nums[divisorIndex], threshold))
                        {
                            dsu.unionSet(i, divisorIndex);
                        }
                    }
                    else
                    {
                        divisorMap[divisor] = i;
                    }

                    // the other divisor
                    const int otherDivisor = nums[i] / divisor;
                    if (otherDivisor != divisor)
                    {
                        if (divisorMap.count(otherDivisor))
                        {
                            const int otherDivisorIndex = divisorMap[otherDivisor];
                            if (isLCMLessThanThreshold(nums[i], nums[otherDivisorIndex], threshold))
                            {
                                dsu.unionSet(i, otherDivisorIndex);
                            }
                        }
                        else
                        {
                            divisorMap[otherDivisor] = i;
                        }
                    }
                }
            }
        }
    }
    int countComponents(vector<int> &nums, int threshold)
    {
        // DSU initialization to keep the track of connected components
        DSU dsu(nums.size());

        // trimming down the nums vector to only store values that are <= threshold
        int extraComponents = 0; // extra components formed in case of nums[i] > threshold
        sortall(nums);
        while (!nums.empty() and nums.back() > threshold)
        {
            extraComponents++;
            nums.pop_back();
        }

        // early check if all numbers are greater than threshold
        if (nums.empty())
        {
            return extraComponents;
        }

        buildDivisorMap(nums, threshold, dsu);
        auto getComponents = [&]() -> int
        {
            int components = 0;
            for (int i = 0; i < nums.size(); i++)
            {
                if (dsu.find(i) == i)
                {
                    components++;
                }
            }
            return components;
        };
        return getComponents() + extraComponents;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;
    cout
        << "\n\n\tProgram ended\n\n";
    return 0;
}
