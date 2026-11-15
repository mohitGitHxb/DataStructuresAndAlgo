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
#define deb(x) cerr << #x << "=" << x << endl
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
#define sz(x) ((ll)(x).size())
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
template <class T = pii>
using oset =
	tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T = pii>
using mset = tree<T, null_type, less_equal<T>, rb_tree_tag,
				  tree_order_statistics_node_update>;

vpii dirs4 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
vpii dirs8 = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
void fast_read()
{
	ios_base::sync_with_stdio(false);
	ios::sync_with_stdio(false);
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
Satyam is given n distinct points on the 2D coordinate plane. It is guaranteed that 0≤yi≤1 for all given points (xi,yi). How many different nondegenerate right triangles∗

can be formed from choosing three different points as its vertices?

Two triangles a
and b are different if there is a point v such that v is a vertex of a but not a vertex of b

.

∗
A nondegenerate right triangle has positive area and an interior 90∘ angle.
 @ Maths
 Initially, the obvious case one might first consider is an upright right triangle (specifically, the triangle with one of its sides parallel to the y-axis). This side can only be made with two points in the form (x,0) and (x,1). We only need to search third point. Turns out, the third point can be any other unused vertex! If the third point has y=0, then it will be an upright triangle, but if the third point has y=1

, it will simply be upside down.

One of the other case is in the form of (x,0),(x+1,1),(x+2,0)
. Let's see why this is a right triangle. Recall that in right triangle, the sum of the squares of two of the sides must equal to the square of the third side. The length between the first and the second point is 2–√ because it is the diagonal of 1 by 1 unit block. Similarily, the second and third point also has length 2–√. Obviously, the length between the first and third point is 2. Since we have 2–√2+2–√2=22, this is certainly a right triangle. Of course, we can flip the y values of each point and it will still be a valid right triangle, just upside down.
 */

void solve()
{
	ll n;
	cin >> n;
	map<pair<int, int>, int> m;
	vector<int> cnt(2);

	forsn(i, 0, n)
	{
		int x, y;
		cin >> x >> y;
		m[{x, y}]++;
		cnt[y]++;
	}
	ll answer = 0;
	for (auto &[i, j] : m)
	{
		auto [x, y] = i;
		if (m.count({x, 1 - y}))
		{
			answer += cnt[y] - 1;
		}
		if (m.count({x + 1, 1 - y}) && m.count({x - 1, 1 - y}))
			answer++;
	}

	cout << answer << "\n";
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
	forsn(i, 0, t)
	{
		cerr << "\nTestcase " << i + 1 << " started\n";
		solve();
	}

	return 0;
}