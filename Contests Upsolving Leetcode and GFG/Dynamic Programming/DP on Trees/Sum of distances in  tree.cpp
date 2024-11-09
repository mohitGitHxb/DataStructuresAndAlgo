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
        There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

        You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

        Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.



        Example 1:

        Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
        Output: [8,12,6,10,10,10]
        Explanation: The tree is shown above.
        We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
        equals 1 + 1 + 2 + 2 + 2 = 8.
        Hence, answer[0] = 8, and so on.
     */
public:
    /*
    @ Concept of re-rooting dp
    %  It is also pretty easy to spot, since such problems typically ask "find some value for each root".
     */
    int totalNodes;
    vi ans, count;
    vvi graph;
    /*
        This function will initialize the answer for the root node (here it is 0) by calculating the sum of distance from root to all of its children

        NO need to have an extra visited array because the given graph is a tree
     */
    void dfsPreprocess(int node, int parent)
    {
        for (auto &child : graph[node])
        {
            if (child == parent)
                continue;
            dfsPreprocess(child, node);
            count[node] += count[child];
            //* this equation will calculate the sum of distance from current node to all of its children (while coming back)
            ans[node] += ans[child] + count[child];
        }
    }
    void dfs(int node, int parent)
    {
        for (auto &child : graph[node])
        {
            if (child == parent)
                continue;
            // re rooting at child (while going down)
            //* ans of existing parent - count of current node child + add remaining number of nodes
            ans[child] = ans[node] - count[child] + (totalNodes - count[child]);
            dfs(child, node);
        }
    }
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
    {
        totalNodes = n;
        ans.resize(n);
        count.resize(n, 1);
        graph.resize(n);
        for (auto &edge : edges)
        {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        dfsPreprocess(0, -1);
        dfs(0, -1);
        return ans;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;
    cout
        << "\n\n\tProgram ended\n\n";
    return 0;
}
