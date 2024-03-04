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
Problem statement:You are given a 0-indexed integer array nums, an integer modulo, and an integer k.

Your task is to find the count of subarrays that are interesting.

A subarray nums[l..r] is interesting if the following condition holds:

    Let cnt be the number of indices i in the range [l, r] such that nums[i] % modulo == k. Then, cnt % modulo == k.

Return an integer denoting the count of interesting subarrays.

Note: A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [3,2,4], modulo = 2, k = 1
Output: 3
Explanation: In this example the interesting subarrays are: 
The subarray nums[0..0] which is [3]. 
- There is only one index, i = 0, in the range [0, 0] that satisfies nums[i] % modulo == k. 
- Hence, cnt = 1 and cnt % modulo == k.  
The subarray nums[0..1] which is [3,2].
- There is only one index, i = 0, in the range [0, 1] that satisfies nums[i] % modulo == k.  
- Hence, cnt = 1 and cnt % modulo == k.
The subarray nums[0..2] which is [3,2,4]. 
- There is only one index, i = 0, in the range [0, 2] that satisfies nums[i] % modulo == k. 
- Hence, cnt = 1 and cnt % modulo == k. 
It can be shown that there are no other interesting subarrays. So, the answer is 3.
 */






/* 
Initialization:

    unordered_map<long long, long long> mp: This unordered map is used to store the frequency of each prefix sum encountered in the array.
    mp[0]++: Initialize the map with the prefix sum of 0 (before processing any elements in nums) and set its count to 1.
    long long prefix = 0: Initialize the prefix variable to keep track of the running prefix sum.
    long long ans = 0: Initialize the ans variable to store the count of interesting subarrays.

Iterating Through nums:

    The code iterates through each element in the nums array using a for loop.

Checking for Interesting Subarrays:

    For each element nums[i], it checks whether nums[i] % m is equal to k. If this condition is met, it means that the current element contributes to the count of interesting subarrays.
    It increments the prefix by 1 if the condition is met, effectively calculating the running prefix sum.

Calculating the Count of Interesting Subarrays:

    The code calculates the count of interesting subarrays as follows:
        It calculates (prefix - k + m) % m to determine the target prefix sum that would make the subarray interesting.
        It uses this target sum as a key to access the count of subarrays that would result in this sum in the mp map. This count is added to the ans variable.
        Finally, it updates the frequency of the current prefix sum in the mp map by incrementing it.

Returning the Result:

    The code returns the ans variable, which contains the count of interesting subarrays.

Time Complexity:

    The code iterates through the nums array once, resulting in O(n) time complexity.

Space Complexity:

    The code uses additional space for the unordered_map mp, which can have a maximum of n entries, where n is the length of the nums array. Therefore, the space complexity is O(n).

Hint:

    The code efficiently tracks the prefix sum and calculates the count of interesting subarrays by utilizing an unordered_map. It uses the modulo operation to determine the target prefix sum for interesting subarrays.

 */

        long long countInterestingSubarrays(vector<int>& nums, int m, int k) {
        unordered_map<long long,long long> mp;
        mp[0]++;
        long long prefix = 0,ans = 0;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] % m == k){
                prefix++;
            }
            prefix = prefix%m;
            ans += mp[(prefix - k + m)%m];
            mp[prefix]++; 

        }
        return ans;
    }


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