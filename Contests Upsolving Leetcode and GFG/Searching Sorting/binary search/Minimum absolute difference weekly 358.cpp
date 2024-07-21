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
#define forn(i,e) for(ll i = 0; i < e; i++)
#define forsn(i,s,e) for(ll i = s; i < e; i++)
#define rforn(i,s) for(ll i = s; i >= 0; i--)
#define rforsn(i,s,e) for(ll i = s; i >= e; i--)
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<string> vsr;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef unordered_map<int,int> hmpi;
typedef unordered_map<ll,ll> hmpll;
typedef unordered_map<int,pii> hmppi;
typedef unordered_map<int,vi> hmpvi;
typedef unordered_set<int> hsi;
typedef unordered_set<ll> hsll;
typedef unordered_set<pii> hspi;
typedef unordered_set<pl> hspl;
typedef map<int,int> mpi;
typedef map<ll,ll> mpll;
typedef map<int,pii> mppi;
typedef map<int,vi> mpvi;
typedef set<int> si;
typedef set<ll> sll;
typedef set<pii> spi;
typedef set<pl> spl;
#define sz(x) ((ll)(x).size())

/* 
You are given a 0-indexed integer array nums and an integer x.

Find the minimum absolute difference between two elements in the array that are at least x indices apart.

In other words, find two indices i and j such that abs(i - j) >= x and abs(nums[i] - nums[j]) is minimized.

Return an integer denoting the minimum absolute difference between two elements that are at least x indices apart.

 

Example 1:

Input: nums = [4,3,2,4], x = 2
Output: 0
Explanation: We can select nums[0] = 4 and nums[3] = 4. 
They are at least 2 indices apart, and their absolute difference is the minimum, 0. 
It can be shown that 0 is the optimal answer.

Example 2:

Input: nums = [5,3,2,10,15], x = 1
Output: 1
Explanation: We can select nums[1] = 3 and nums[2] = 2.
They are at least 1 index apart, and their absolute difference is the minimum, 1.
It can be shown that 1 is the optimal answer.

 */

/* 
@ Simple brute force
 */
class BruteForce {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
    int n = nums.size(), res = 1e9;
    forn(i,n){
        forsn(j,i+x,n){
            res = min(res, abs(nums[i] - nums[j]));
        }
    }
    return res;
    }
};

/* 
Intuition:

The problem requires finding the minimum absolute difference between two elements in the array that are at least x indices apart. One approach is to maintain a sliding window of size x and keep track of the minimum absolute difference encountered within this window as it moves through the array.

Algorithm / Code Explanation:

    Initialize variables: n as the size of the input array nums, and res to store the minimum absolute difference. Initialize s as a multiset to maintain elements within the sliding window.
    Loop through the array using a forsn loop (which iterates from x to n-1).
    Insert the element at index i - x into the multiset s to maintain a sliding window of size x.
    Find the iterator it that points to the first element in s that is greater than or equal to nums[i].
    Calculate the absolute difference between nums[i] and the element pointed by it, and update res with the minimum of the current res and this absolute difference.
    If it is not pointing to the beginning of s, calculate the absolute difference between nums[i] and the element pointed by the iterator before it (*prev(it)), and update res with the minimum of the current res and this absolute difference.
    Return the final value of res which holds the minimum absolute difference between two elements that are at least x indices apart.

Time Complexity:

The time complexity of this algorithm is O(n * log x), where n is the size of the input array nums, and x is the difference between the indices of the elements being compared. The multiset operations insert, upper_bound, and prev take O(log x) time each, and they are performed for each element in the array.

Space Complexity:

The space complexity is O(x), as the multiset s stores at most x elements at any given time, representing the sliding window.

This code snippet effectively uses a sliding window with a multiset to efficiently find the minimum absolute difference between two elements that are at least x indices apart. It leverages the properties of the multiset data structure to achieve this efficiently.

Note that this code snippet assumes the existence of the forsn function, which is used to iterate through the array with an offset. Make sure to replace it with appropriate loop conditions if not available in the context you're using this code.
 */
class Solution {
public:
    Solution(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    }
    int minAbsoluteDifference(vector<int>& nums, int x) {
    int n = nums.size(), res = 1e9;
    multiset<int> s;
        forsn(i,x,n){
            s.insert(nums[i-x]);
            auto it = s.upper_bound(nums[i]);
            if(it != s.end()) res = min(res,abs(nums[i] - *it));
            if(it != s.begin()) res = min(res,abs(nums[i] - *prev(it)));
        }
        return res;
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
        //write code here
    }
    return 0;
}