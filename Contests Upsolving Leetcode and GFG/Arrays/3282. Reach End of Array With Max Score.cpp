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
    @ Key learnings
     ( i - J) * arr[i] --> common expression
     (i - j) * min/max(arr[i], arr[j]) --> common expression for water trapping like problems
     */
public:
    const int mod = 1e9 + 7;
    Solution()
    {
        fast_read();
    }
    ll findMaximumScore(vi &nums)
    {
        ll best = 0;
        ll ans = 0;
        forsn(i, 0, sz(nums) - 1)
        {
            best = max<ll>(best, nums[i - 1]);
            ans += best;
        }
        return ans;
    }
};
int main(int argc, char const *argv[])
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    return 0;
}
