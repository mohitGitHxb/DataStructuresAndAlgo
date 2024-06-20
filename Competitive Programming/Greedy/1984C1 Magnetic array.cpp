#include <bits/stdc++.h>
using namespace std;
/*

* THIS THING IS GANGSTA!!!
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
#define gc getchar_unlocked
#define ll long long
#define deb(x) cerr << #x << "=" << x << endl
#define pb push_back
#define eb emplace_back
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
#define forv(i, v) for (auto i : v)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef unordered_map<int, int, custom_hash> hmpi;
typedef unordered_map<ll, ll, custom_hash> hmpll;
typedef unordered_map<int, pii> hmppi;
typedef unordered_map<int, vi> hmpvi;
typedef unordered_set<int, custom_hash> hsi;
typedef unordered_set<ll, custom_hash> hsll;
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

vpii dirs4 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vpii dirs8 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
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
void customPrint(const unordered_map<T, U, custom_hash> &mp)
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
void customPrint(const unordered_set<T, custom_hash> &mp)
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
void customPrint(priority_queue<T, vector<T>, greater<T>> pq)
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
/*
The two versions of the problem are different. You may want to read both versions. You can make hacks only if both versions are solved.

You are given an array a
of length n. Start with c=0. Then, for each i from 1 to n

(in increasing order) do exactly one of the following:

    Option 1

: set c to c+ai
.
Option 2
: set c to |c+ai|, where |x| is the absolute value of x

    .

Let the maximum final value of c
after the procedure described above be equal to k. Find k.



We only need to pick option 2 once. Why? Assume we picked option 2 more than once, and consider the last two times it was picked. Both of these must occur when c+ai is negative, otherwise there is no reason to pick option 2 over option 1. Thus, if we chose option 1 the first of these times instead of option 2, that would cause the value of c before the second operation to decrease. Because it was negative, this increases the magnitude, and thus it was more optimal to choose option 1

for the first operation.

Because we only need to use option 2
once, we can brute force where we use that operation and compute the final value of c with prefix sums.
 */
void solve()
{
    ll n;
    cin >> n;
    vl a(n);
    forn(i, n) cin >> a[i];
    vl prefix(n);
    partial_sum(all(a), prefix.begin());
    ll c = 0,ans = prefix.back();
    forn(i,n)
    {
        c = abs(prefix[i]) + (prefix.back() - prefix[i]);
        ans = max(ans, c);
    }
    cout << ans << "\n";
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    fast_read();
    int t;
    cin >> t;
    forn(i, t)
    {
        cerr << "\nTestcase " << i + 1 << " started\n";
        solve();
    }
    return 0;
}