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

Iva and Pav are a famous Serbian competitive programming couple. In Serbia, they call Pav "papuca" and that's why he will make all of Iva's wishes come true.

Iva gave Pav an array a
of n

elements.

Let's define f(l,r)=al & al+1 &…& ar
(here &

denotes the bitwise AND operation).

Note that f(l,r)
is not defined when l>r

.

Iva also gave Pav q

queries.

Each query consists of 2 numbers, k
and l, and she wants Pav to find the largest index r (l≤r≤n), such that f(l,r)≥k

.

Pav wants to solve this problem fast because he doesn't want to upset Iva. He needs your help.

	@ Observations / approach
	&- Maintain a bit prefix map of size n for all elements
	&- AND of values always decreases or remain same
	&- in range L...R if count of bit 1 is R-L+1 then it is safe to say that this bit remains same
	&- if count is less than R-L+1 then it has been turned to zero

	%- Now can we have certain bits in bit prefix map can we find the overlapping range that satisfies the condition?
	%- Using binary search we can pinpoint the ending range (R)

 */

void solve()
{
	int n;
	cin >> n;
	vi a(n + 1);
	forsn(i, 1, n + 1) cin >> a[i];
	vvi bitPrefix(n + 1, vi(32, 0));
	forsn(i, 1, n + 1)
	{
		forsn(j, 0, 32)
		{
			if (a[i] & (1 << j))
				bitPrefix[i][j] = 1;
			else
				bitPrefix[i][j] = 0;

			bitPrefix[i][j] += bitPrefix[i - 1][j];
		}
	}
	function<bool(int, int, int)> check = [&](int midLen, int k, int l)
	{
		ll totalSum = 0;
		forsn(i, 0, 32)
		{
			//&- All bits if are equal to midLen - l + 1 that means it has not been changed to 0
			if (bitPrefix[midLen][i] - bitPrefix[l - 1][i] == (midLen - l + 1))
			{
				totalSum += (1 << i); //&- If ith bit is set then add the value power(2,i);
			}
		}
		return totalSum >= k; // &- If total sum is greater than or equal to k return true
	};
	int q;
	cin >> q;
	while (q--)
	{
		int l, k;
		cin >> l >> k;
		if (a[l] < k)
		{
			cout << -1 << " ";
			continue;
		}
		int low = l, high = n;
		int ans = -1;
		while (low <= high)
		{
			int midLen = (low + high) / 2;
			if (check(midLen, k, l))
			{
				ans = midLen;
				low = midLen + 1;
			}
			else
			{
				high = midLen - 1;
			}
		}
		cout << ans << " ";
	}
	cout << endl;
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