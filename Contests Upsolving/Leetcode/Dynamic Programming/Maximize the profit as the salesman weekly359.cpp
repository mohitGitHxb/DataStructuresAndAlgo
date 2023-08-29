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

int calculateMaxEarnings(int house, vector<vector<int>> &offers, vector<int> &maxEarnings)
{
    if (house < 0)
    {
        return 0;
    }

    if (maxEarnings[house] != -1)
    {
        return maxEarnings[house];
    }

    // Find the maximum earnings without considering the current house
    int earningsWithoutCurrentHouse = calculateMaxEarnings(house - 1, offers, maxEarnings);

    // Find the maximum earnings by considering the current house and its offers
    int earningsWithCurrentHouse = 0;
    for (const vector<int> &offer : offers)
    {
        if (offer[1] == house)
        {
            int startHouse = offer[0];
            int goldAmount = offer[2];

            int earningsFromOffer = (startHouse > 0) ? calculateMaxEarnings(startHouse - 1, offers, maxEarnings) : 0;
            earningsWithCurrentHouse = max(earningsWithCurrentHouse, earningsFromOffer + goldAmount);
        }
    }
    deb(earningsWithoutCurrentHouse);
    deb(earningsWithCurrentHouse);
    // Store the maximum of the two earnings scenarios in the memoization array
    cout << "max(earningsWithoutCurrentHouse, earningsWithCurrentHouse) : " << max(earningsWithoutCurrentHouse, earningsWithCurrentHouse) << "\n\n";
    maxEarnings[house] = max(earningsWithoutCurrentHouse, earningsWithCurrentHouse);
    return maxEarnings[house];
}

int maximizeTheProfit(int n, vector<vector<int>> &offers)
{
    sort(offers.begin(), offers.end(), [](const std::vector<int> &a, const std::vector<int> &b)
         { return a[1] < b[1]; });

    vector<int> maxEarnings(n, -1);
    return calculateMaxEarnings(n - 1, offers, maxEarnings);
}

//^ Tabulation
int maximizeTheProfit(int n, vector<vector<int>>& offers) {
    // Sort offers based on ending index
    sort(offers.begin(), offers.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        return a[1] < b[1];
    });
    
    vector<int> maxEarnings(n);
    int offerIndex = 0;
    
    for (int house = 0; house < n; house++) {
        maxEarnings[house] = (house > 0) ? maxEarnings[house - 1] : 0;
        
        // Process offers that end at the current house
        while (offerIndex < offers.size() && offers[offerIndex][1] == house) {
            int startHouse = offers[offerIndex][0];
            int goldAmount = offers[offerIndex][2];
            
            // Calculate maximum earnings considering the offer
            maxEarnings[house] = max(maxEarnings[house], (startHouse > 0 ? maxEarnings[startHouse - 1] : 0) + goldAmount);
            offerIndex++;
        }
    }
    
    return maxEarnings[n - 1];
}

/* 

Intuition

The intuition behind this solution is to sort the offers by their starting positions and then use dynamic programming to compute the maximum profit that can be achieved while considering each offer.
Approach

Here's how the code approaches the problem:

    Sort the offers based on their starting positions. This step ensures that the offers are considered in ascending order of their starting positions.

    Create a vector first to store the starting positions of each offer. This vector will help in finding the index of the next available offer for each offer.

    Initialize a dynamic programming vector dp of size n+1 (where n is the number of offers) to store the maximum profit that can be obtained starting from each offer.

    Iterate through the offers in reverse order (from the last offer to the first offer).

    For each offer, find the index of the next available offer whose starting position is greater than or equal to the ending position of the current offer. This is done using upper_bound, which returns an iterator pointing to the first element that is greater than tar (the ending position of the current offer). The difference between this index and n indicates how many offers are available to be considered.

    Calculate the maximum profit that can be obtained by either skipping the current offer (taking dp[i+1]) or by considering the current offer and adding its gold value (v[i][2]) to the maximum profit that can be obtained from the next available offer (dp[ind]).

    Update the dp array for the current offer with the maximum profit calculated in step 6.

    Finally, the maximum profit that can be obtained starting from the first offer (index 0) will be stored in dp[0], so return dp[0].

Complexity

    Time complexity: The code first sorts the offers, which takes O(nlog(n)) time. Then, it iterates through the offers once, performing operations that take O(log(n)) time in each iteration. Therefore, the overall time complexity is O(nlog(n)).

    Space complexity: The code uses additional vectors (first and dp) to store information, both of which have sizes proportional to the number of offers (n). Therefore, the space complexity is O(n).

 */
//^ Tabulation w/ Binary search
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