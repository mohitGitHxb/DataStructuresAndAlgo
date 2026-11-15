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
Sasha gave Anna a list a of n

integers for Valentine's Day. Anna doesn't need this list, so she suggests destroying it by playing a game.

Players take turns. Sasha is a gentleman, so he gives Anna the right to make the first move.

	On her turn, Anna must choose an element ai

from the list and reverse the sequence of its digits. For example, if Anna chose the element with a value of 42, it would become 24; if Anna chose the element with a value of 1580, it would become 851
. Note that leading zeros are removed. After such a turn, the number of elements in the list does not change.
On his turn, Sasha must extract two elements ai
and aj (i≠j) from the list, concatenate them in any order and insert the result back into the list. For example, if Sasha chose the elements equal to 2007 and 19, he would remove these two elements from the list and add the integer 200719 or 192007. After such a turn, the number of elements in the list decreases by 1

	.

Players can't skip turns. The game ends when Sasha can't make a move, i.e. after Anna's move there is exactly one number left in the list. If this integer is not less than 10m
(i.e., ≥10m

), Sasha wins. Otherwise, Anna wins.

It can be shown that the game will always end. Determine who will win if both players play optimally.
 */

int countTrailingZeros(string &s)
{
	int cnt = 0;
	rforsn(i, sz(s) - 1, 0)
	{
		if (s[i] == '0')
		{
			cnt++;
		}
		else
		{
			break;
		}
	}
	return cnt;
}

void solve()
{
	int n, m;
	cin >> n >> m;
	/*
	~ For ANNA pick those numbers which have trailing zeros so that length decreases
	~ For SASHA combine two numbers in such a way such that there are no trailing zeros;
	% If the length of a number becomes equal or greater to (m+1) means sasha wins
	^ We can conclude that numbers which don't have trailing zeros can always be combined regardless
	^ So now the only concern is to greedily pick those numbers which have trailing zeros
	 */
	vi trailingCount;
	forsn(i, 0, n)
	{
		string s;
		cin >> s;
		int trailingZeros = countTrailingZeros(s);
		if (trailingZeros > 0)
		{
			m -= (s.size() - trailingZeros); // these digits won't be affected by reversal
			trailingCount.eb(trailingZeros);
		}
		else
		{
			m -= s.size();
		}
	}
	if (m < 0)
	{
		cout << "Sasha\n";
		return;
	}
	// &- First element with maximum trailingZeros will be taken by anna
	//&- Then sasha will pick second element with maximum trailingZeros and combine with some other non trailing zero number
	//&- Then anna again picks third element with maximum trailingZeros and so on
	sort(rall(trailingCount));
	forsn(i, 1, sz(trailingCount))
	{
		m -= trailingCount.at(i);
		i++;
	}
	if (m < 0)
	{
		cout << "Sasha\n";
	}
	else
	{
		cout << "Anna\n";
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
	forsn(i, 0, t)
	{
		cerr << "\nTestcase " << i + 1 << " started\n";
		solve();
	}

	return 0;
}