#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl
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

void fast_read()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
template <class T = int>
void customPrint(const T &t)
{
    cerr << t << " ";
}

template <class T = int>
void customPrint(const vector<T> &vec)
{
    cerr << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const vector<vector<T>> &vec)
{
    cerr << "[";
    for (auto &&i : vec)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_map<T, U> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        cerr << "{" << i.first << ":";
        customPrint(i.second);
        cerr << "}\n";
    }
    cerr << "]\n";
}

template <class T = int, class U = int>
void customPrint(const map<T, U> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        cerr << "{" << i.first << ":";
        customPrint(i.second);
        cerr << "}\n";
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const multiset<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const set<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const unordered_set<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(priority_queue<T> pq)
{
    cerr << "[";
    while (!pq.empty())
    {
        customPrint(pq.top());
        pq.pop();
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(stack<T> st)
{
    cerr << "[";
    while (!st.empty())
    {
        customPrint(st.top());
        st.pop();
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(queue<T> q)
{
    cerr << "[";
    while (!q.empty())
    {
        customPrint(q.front());
        q.pop();
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(deque<T> dq)
{
    cerr << "[";
    for (auto &i : dq)
    {
        customPrint(i);
    }
    cerr << "]\n";
}

template <class T = int, class U = int>
void customPrint(const unordered_multimap<T, U> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        cerr << "{" << i.first << ":";
        customPrint(i.second);
        cerr << "}\n";
    }
    cerr << "]\n";
}

template <class T = int>
void customPrint(const unordered_multiset<T> &mp)
{
    cerr << "[";
    for (auto &i : mp)
    {
        customPrint(i);
    }
    cerr << "]\n";
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

class DisjointSet
{
public:
    vector<int> rank, parent, size;
    DisjointSet(int n)
    {
        rank.resize(n + 1);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i < n + 1; i++)
        {
            parent.at(i) = i;
            size.at(i) = 1;
        }
    }

    int findUPar(int node)
    {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v)
    {
        int ultimateParentU = findUPar(u);
        int ultimateParentV = findUPar(v);
        if (ultimateParentU == ultimateParentV)
            return;
        if (rank.at(ultimateParentU) < rank.at(ultimateParentV))
        {
            parent.at(ultimateParentU) = ultimateParentV;
        }
        else if (rank.at(ultimateParentV) < rank.at(ultimateParentU))
        {
            parent.at(ultimateParentV) = ultimateParentU;
        }
        else
        {
            parent.at(ultimateParentV) = parent.at(ultimateParentU);
            rank.at(ultimateParentU)++;
        }
    }

    void unionBySize(int u, int v)
    {
        int ultimateParentU = findUPar(u);
        int ultimateParentV = findUPar(v);
        if (ultimateParentU == ultimateParentV)
            return;
        if (size.at(ultimateParentU) < size.at(ultimateParentV))
        {
            parent.at(ultimateParentU) = ultimateParentV;
            size.at(ultimateParentV) += size.at(ultimateParentU);
        }
        else
        {
            parent.at(ultimateParentV) = ultimateParentU;
            size.at(ultimateParentU) += size.at(ultimateParentV);
        }
    }
};

class Solution
{
private:
    /*
    You are given an unrooted weighted tree with n vertices representing servers numbered from 0 to n - 1, an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional edge between vertices ai and bi of weight weighti. You are also given an integer signalSpeed.

Two servers a and b are connectable through a server c if:

    a < b, a != c and b != c.
    The distance from c to a is divisible by signalSpeed.
    The distance from c to b is divisible by signalSpeed.
    The path from c to b and the path from c to a do not share any edges.

Return an integer array count of length n where count[i] is the number of server pairs that are connectable through the server i.


 &- Brute force using DFS
 ?- Perform DFS to find the count of nodes whose distances are divisible by signalSpeed
 ?- after this get the pairs using simple maths [x1,x2,x3] --> [y1,y2,y3,y4] then total pairs = 3 * 4 = 12
 ?- Do this for all nodes 0 to n - 1;
     */
public:
    const int mod = 1e9 + 7;
    vector<vpii> adj;
    int n, ss, ct;
    Solution()
    {
        fast_read();
    }
    void dfs(int node, int parent, int d)
    {
        if (d % ss == 0)
            ct++;
        for (auto &child : adj[node])
        {
            if (child.F == parent)
                continue;
            dfs(child.F, node, d + child.S);
        }
    }
    vi countPairsOfConnectableServers(vvi &edges, int signalSpeed)
    {
        adj.resize(edges.size() + 1);
        n = edges.size() + 1;
        ss = signalSpeed;
        forn(i, sz(edges))
        {
            adj[edges[i][0]].pb(mp(edges[i][1], edges[i][2]));
            adj[edges[i][1]].pb(mp(edges[i][0], edges[i][2]));
        }
        vi res(n);
        forn(par, n)
        {
            int ans = 0, sum = 0;
            vi temp;
            for (auto &child : adj[par])
            {
                ct = 0;
                dfs(child.F, par, child.S);
                temp.eb(ct);
                sum += ct;
            }
            for (auto &it : temp)
            {
                ans += (sum - it) * it;
            }
            res[par] = ans >> 1;
        }
        return res;
    }
};

int main(int argc, char const *argv[])
{
    Solution obj;
    return 0;
}
