#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (int i = 0; i < n; i++)
#define Fo(i, k, n) for (int i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
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
#define mod 1000000007
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

class BruteForce
{
public:
    BruteForce()
    {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    ll minimumRemoval(vi &beans)
    {
        unsigned size = beans.size();
        ll steps = 1e9;
        sort(beans.begin(), beans.end());
        forn(i, size)
        {
            ll currSteps = 0;
            forn(j, size)
            {
                if (i == j || beans[i] == beans[j])
                {
                    continue;
                }
                else
                {
                    if (beans[j] < beans[i])
                    {
                        currSteps += beans[j];
                    }
                    else
                    {
                        currSteps += (beans[j] - beans[i]);
                    }
                }
            }
            steps = min(steps, currSteps);
        }
        return steps;
    }
};

class Solution
{
public:
    Solution()
    {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    ll minimumRemoval(vi &beans)
    {
        unsigned ll size = beans.size();
        ll steps = LLONG_MAX;
        ll totalSum = accumulate(beans.begin(), beans.end(), 0 * 1LL);
        sort(beans.begin(), beans.end());
        forn(i, size)
        {
            steps = min(steps, (ll)(totalSum - (ll)(size - i) * (ll)(beans.at(i))));
            //? For each beans[i] elements less than beans[i] will be changed to 0 and for the higher values to beans[i]

            //? to optimize this we have calculated totalSum - (n-i)*beans[i] to get the steps required to make the elements equal 
            //? why n - i ? because if we subtract the (n-i) means elements that are greater than beans[i] and if we subtract the (n-i) * beans[i] we get the steps required to make the elements before beans[i] = 0 and after beans[i] to beans[i];
        }
        return steps;
    }
};
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}