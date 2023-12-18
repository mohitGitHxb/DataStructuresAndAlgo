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
@ problem:
Bob is very fond of balloons. Once he visited an amusement park with his mother. The mother told Bob that she would buy him a balloon only if he answer her problem right. She gave Bob a string s and asked him to use the characters of string to form as many instances of the word "balloon" as possible. Return the maximum number of instances that can be formed.

Help Bob to solve the problem.

Note: You can use each character in the string at most once.

Example 1:

Input:
S: nlaebolko
Output: 1
Explanation:
Here, the number of occurence of 'b' = 1
of occurence of 'a' = 1
of occurence of 'l' = 2
of occurence of 'o' = 2
of occurence of 'n' = 1
So, we can form 1 "balloon" using the letters.


Example 2:

Input:
S: loonbalxballpoon
Output: 2
Explanation:
Here, the number of occurence of 'b' = 2
of occurence of 'a' = 2
of occurence of 'l' = 4
of occurence of 'o' = 4
of occurence of 'n' = 2
So, we can form 2 "balloon" using the letters.


 */

/*
@ Explanation  : approach 1 intuitive
This code is a function that takes a string s as input and returns the maximum number of instances of the word “balloon” that can be formed using the characters in s. The function uses an unordered_map to keep track of the frequency of each character in s. It then iterates through the characters in the word “balloon” and decrements their frequency in the map. If any character’s frequency becomes negative, it means that no more instances of “balloon” can be formed and the loop breaks. The counter variable keeps track of the number of instances of “balloon” that have been formed.

The time complexity of this function is O(n), where n is the length of string s, because it iterates through all the characters in s once to build the frequency map and then iterates through the characters in “balloon” a constant number of times. The space complexity is O(1), because the size of the unordered_map is constant (it only needs to store the frequency of 26 characters).




@ approach 2 : taking minimum frequency
The function uses an unordered_map to keep track of the frequency of each character in s that is also present in the word “balloon”. It then iterates through the map and finds the minimum frequency of all characters. For characters ‘l’ and ‘o’, their frequency is divided by 2 because each instance of “balloon” requires 2 'l’s and 2 'o’s. The minimum frequency is returned as the result.

The time complexity of this function is O(n), where n is the length of string s, because it iterates through all the characters in s once to build the frequency map and then iterates through the map once to find the minimum frequency. The space complexity is O(1), because the size of the unordered_map is constant (it only needs to store the frequency of 5 characters).
 */
int maxInstance(string &s)
{
    string txt = "balloon";
    unordered_map<char, int> mp;
    for (auto &i : s)
    {
        mp[i]++;
    }
    int counter = 0;
    while (true)
    {
        bool flag = false;
        for (int i = 0; i < txt.size(); i++)
        {
            if (--mp[txt[i]] < 0)
            {
                flag = true;
                break;
            }
        }
        counter++;
        if (flag)
        {
            counter--;
            break;
        }
    }
    return counter;
}

int maxInstance_2(string s)
{
    string txt = "balloon";
    unordered_map<char, int> hmp;
    for (auto &i : s)
    {
        if (i == 'b' || i == 'a' || i == 'l' || i == 'o' || i == 'n')
        {
            hmp[i]++;
            /* code */
        }
    }
    int minimumFrequency = 1e8;
    for (auto &it : hmp)
    {
        if (it.first == 'l' || it.first == 'o')
            minimumFrequency = min(minimumFrequency, it.second / 2);
        else
            minimumFrequency = min(minimumFrequency, it.second);
    }

    return minimumFrequency;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
    string s = "bnlbllanmbaamnmobbanablboolonlol";
}