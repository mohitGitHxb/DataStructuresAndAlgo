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
@ Problem
Given an array of strings arr[]. You have to find the longest string such that also all of its prefix strings are already present in the array. If there are multiple possible strings of the same length, return the one which is lexicographically smallest.

Example 1:

Input: ab a abc abd
Output: abc
Explanation: We can see that length of the longest
string is 3. And there are two string "abc" and "abd"
of length 3. But for string "abc" , all of its prefix
"a" "ab" "abc" are present in the array. So the
output is "abc".

Example 2:

Input: ab a aa abd abc abda abdd abde abdab
Output: abdab
Explanation: We can see that each string is fulfilling
the condition. For each string, all of its prefix
are present in the array.And "abdab" is the longest
string among them. So the ouput is "abdab".
 */

/*
@ Approach - 1 Brute force
The function first creates an unordered_set hs to store all the strings in the input vector for fast lookup. It then sorts the input vector in lexicographical order. The function then iterates through each string in the sorted vector and checks if all its prefix strings are present in the set hs. If all prefix strings are present, the function updates the length of the longest string and stores the current string as the answer.

The time complexity of this function is O(n * k^2 * log n), where n is the number of strings in the input vector and k is the maximum length of a string in the input vector. This is because the function sorts the input vector, which takes O(n * log n) time, and then iterates through each string and checks all its prefix strings, which takes O(n * k^2) time. The space complexity is O(n), because the function creates an unordered_set to store all the strings in the input vector.
 */
string longestString(vector<string> &words)
{
    // code here
    unordered_set<string> hs(words.begin(), words.end());
    sort(words.begin(), words.end());
    int len = 0;
    string ans;
    for (auto &it : words)
    {
        int currlen = len;
        for (int i = 1; i < it.size() - 1; i++)
        {
            auto res = hs.find(it.substr(0, i));
            if (res == hs.end())
            {
                break;
            }
            else if (i == it.size() - 2)
            {
                currlen = it.length();
                break;
            }
            else
            {
                currlen = max(currlen, i);
            }
        }
        if (currlen > len)
        {
            len = it.length();
            ans = it;
        }
    }
    return ans;
}

class Solution{
    public:
        static bool cmp(string a,string b){
        if(a.size() != b.size()){
            return a.size() > b.size();
        };
        return a<b;
    }
    string longestString(vector<string> &words)
    {
        // code here
        sort(words.begin(),words.end(),cmp);
        unordered_set<string> hs(words.begin(),words.end());
        string ans;
        for(auto &it : words){
            string temp = "";
            bool flag = true;
            for(int i = 0; i < it.size(); i++){
                temp.push_back(it[i]);
                ans = temp;
                if(hs.find(temp) == hs.end()){
                    flag = false;
                    break;
                }
            }
            if(flag){
                if(ans.size() == 1){
                    return "";
                }
                else 
                    return ans;
            }

        }
        return "";
    }
};
int main()
{
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