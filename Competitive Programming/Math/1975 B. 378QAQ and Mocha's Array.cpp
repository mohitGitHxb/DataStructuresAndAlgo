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
Mocha likes arrays, so before her departure, 378QAQ gave her an array a
consisting of n

positive integers as a gift.

Mocha thinks that a
is beautiful if there exist two numbers i and j (1≤i,j≤n, i≠j) such that for all k (1≤k≤n), ak is divisible† by either ai or aj

.

Determine whether a

is beautiful.

†
x is divisible by y if there exists an integer z such that x=y⋅z.
 */
ll LCM(ll a, ll b) { return (a * b) / __gcd(a, b); }
void solve()
{
    int n;
    cin >> n;
    vl a(n);
    hsll hs;
    forn(i, n)
    {
        cin >> a[i];
        hs.insert(a[i]);
    }
    sortall(a);
    // ! WRONG APPROACH
    // int p = -1, q = -1, r = -1;
    // // get divisors of largest element;
    // set<int> divisors;
    // for (int i = 1; i * i <= a.back(); i++)
    // {
    //     if (a.back() % i == 0)
    //     {
    //         if (hs.count(i))
    //         {
    //             divisors.insert(i);
    //         }
    //         if (hs.count(a.back() / i))
    //         {
    //             divisors.insert(a.back() / i);
    //         }
    //     }
    // }
    // p = *divisors.begin();
    // forn(i, n)
    // {
    //     if (divisors.count(a[i]) == 0)
    //     {
    //         r = a[i];
    //         break;
    //     }
    // }
    // if (divisors.size() == 1)
    // {
    //     int count = 0;
    //     forn(i, n)
    //     {
    //         if (a[i] % p == 0 or a[i] % r == 0)
    //         {
    //             count++;
    //         }
    //     }
    //     if (count == n)
    //     {
    //         puts("YES");
    //         return;
    //     }
    //     else
    //     {
    //         puts("NO");
    //         return;
    //     }
    // }
    // else
    // {
    //     divisors.erase(p);
    //     q = *divisors.begin();

    //     int count1 = 0, count2 = 0;
    //     forn(i, n)
    //     {
    //         if (a[i] % p == 0 or a[i] % q == 0)
    //         {
    //             count1++;
    //         }
    //         if (a[i] % p == 0 or a[i] % r == 0)
    //         {
    //             count2++;
    //         }
    //     }
    //     if (count1 == n || count2 == n)
    //     {
    //         puts("YES");
    //         return;
    //     }
    //     else
    //     {
    //         puts("NO");
    //         return;
    //     }
    // }
    bitset<100001> vis;
    // smallest number and second smallest element which isn't divisible by first one
    //% this way we can ensure that the chances of beautiful array are maximum.
    //% if all numbers are still not divisible then the array is not beautiful
    int firstDivisor = a.front(), secondDivisor = INT_MAX;
    forn(i, n)
    {
        if (a[i] % firstDivisor == 0 || a[i] % secondDivisor == 0)
        {
            vis.set(i);
        }
        else
        {
            if (secondDivisor == INT_MAX)
            {
                secondDivisor = a[i];
                vis.set(i);
            }
        }
    }
    // if (secondDivisor == -1)
    // {
    //     puts("YES");
    //     return;
    // }
    // forn(i, n)
    // {
    //     if (!vis[i] and a[i] % secondDivisor == 0)
    //     {
    //         vis.set(i);
    //     }
    // }
    if (vis.count() == n)
    {
        puts("YES");
    }
    else
    {
        puts("NO");
    }
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