#include <bits/stdc++.h>
using namespace std;
#define gc getchar_unlocked
#define fo(i, n) for (i = 0; i < n; i++)
#define Fo(i, k, n) for (i = k; k < n ? i < n : i > n; k < n ? i += 1 : i -= 1)
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
#define pb push_back
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
#define fi first
#define se second
#define sz(x) ((ll)(x).size())

/* 
Imagine an imaginary array of length N containing balls. Given 2 arrays color and radius of length N each, where color[i] represents the color of the ith ball while radius[i] represents the radius of ith ball. If two consecutive balls have the same color and size, both are removed from the array. Geek wants to know the length of the final imaginary array.

Example 1:

Input:
N = 3
color[] = {2, 2, 5}
radius[] = {3, 3, 4}
Output: 
1
Explanation: 
First ball and second ball have same color 2 and 
same radius 3.So,after removing only one ball 
is left.It could not be removed from the array. 
Hence, the final array has length 1.

Example 2:

Input:
N = 4 
color[] = {1, 3, 3, 1}
radius[] = {2, 5, 5, 2}
Output: 
0
Explanation: 
Ball 2 and ball 3 have same color 3 and same radius
5.So,they are removed. Now, we have got our 
color[]={1, 1} and radius[]={2, 2}.Both the left 
balls are consecutive now and they are having 
same color and radius. So,these two balls are 
removed as well. Now,we are left with empty 
final array. Hence, the length of final array is 0.

 */



/* 

& Don't use the technique to sort an array according to another array because the question is slightly different

& we aren't required to find "UNIQUE" pairs actually
& Instead of that use stack to store previous pairs and compare with current pair
& Every time you see a match just remove the item from the stack and decrease length and skip the current pair


 */
class Solution
{
public:
    bool isSame(pair<int, int> a, pair<int, int> b)
    {
        return (a.first == b.first) && (a.second == b.second);
    }
    int finLength(int N, vector<int> color, vector<int> radius)
    {
        // code here
        if (color.size() != radius.size())
            return 0;
        stack<pair<int, int>> merged;
        int len = 1;
        const int n = color.size();
        if (n == 1)
            return 1;
        int i = 1;
        merged.push({color[0], radius[0]});
        while (i < n)
        {
            if (!merged.empty() && isSame({color[i], radius[i]}, merged.top()))
            {
                merged.pop();
                i++;
                len--;
            }
            else
            {
                merged.push({color[i], radius[i]});
                len++;
                i++;
            }
        }
        // return len;

        return len;
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
    return 0;
}