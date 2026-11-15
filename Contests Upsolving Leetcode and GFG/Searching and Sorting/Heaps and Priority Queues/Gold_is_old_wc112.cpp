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
&   The problem statement describes a scenario where you are playing a game with an initial number of experience points and `n` available quests. Each quest has a minimum experience requirement and provides a certain amount of experience points upon completion. You can complete at most `k` quests, and your goal is to determine the maximum number of experience points you can accumulate.

&   The provided solution uses a priority queue to solve this problem. The function `MaxXP` takes as input the number of quests `n`, the maximum number of quests that can be completed `k`, the initial number of experience points `initial_exp`, a vector of integers representing the minimum experience requirement for each quest `exp_req`, and a vector of integers representing the experience gain for each quest `exp_gain`.

&   First, it creates a vector of pairs `quests`, where each pair represents a quest with its minimum experience requirement and experience gain. It then sorts this vector in ascending order of minimum experience requirement.

&   The function then iterates over all quests. For each quest, it checks if the current number of experience points is less than the minimum requirement for the current quest. If it is, it uses a priority queue to select the quests with the highest experience gain that have already been considered and completes them until either the current number of experience points is greater than or equal to the minimum requirement for the current quest, or there are no more quests that can be completed (`k == 0`). If there are no more quests that can be completed, it breaks out of the loop.

&   If the current number of experience points is greater than or equal to the minimum requirement for the current quest, it adds its experience gain to the priority queue.

&   After iterating over all quests, it checks if there are still quests that can be completed (`k > 0`). If there are, it completes the remaining quests with the highest experience gain using the priority queue.

~ Finally, it returns the maximum number of experience points that can be accumulated.

* The time complexity of this solution is O(n log n), where n is the number of quests, since it sorts the vector of quests and uses a priority queue. The space complexity is O(n), since it uses a vector and a priority queue to store up to n values.

Here's a step-by-step explanation of how the code works:
&- The function `MaxXP` takes as input the number of quests `n`, the maximum number of quests that can be completed `k`, the initial number of experience points `initial_exp`, a vector of integers representing the minimum experience requirement for each quest `exp_req`, and a vector of integers representing the experience gain for each quest `exp_gain`.
&-  It creates a vector of pairs `quests`, where each pair represents a quest with its minimum experience requirement and experience gain.
&-  It then sorts this vector in ascending order of minimum experience requirement.
&-  The function then iterates over all quests.
&-  For each quest, it checks if the current number of experience points is less than the minimum requirement for the current quest.
&-  If it is, it uses a priority queue to select the quests with the highest experience gain that have already been considered and completes them until either the current number of experience points is greater than or equal to the minimum requirement for the current quest, or there are no more quests that can be completed (`k == 0`).
&-  If there are no more quests that can be completed, it breaks out of the loop.
&-  If the current number of experience points is greater than or equal to the minimum requirement for the current quest, it adds its experience gain to the priority queue.
&-  After iterating over all quests, it checks if there are still quests that can be completed (`k > 0`).
&-  If there are, it completes the remaining quests with the highest experience gain using the priority queue.
&-  Finally, it returns the maximum number of experience points that can be accumulated.

 */

class Solution
{
public:
    long long MaxXP(int n, int k, int initial_exp, vector<int> &exp_req, vector<int> &exp_gain)
    {
        vector<pair<int, int>> quests;
        for (int i = 0; i < n; i++)
        {
            quests.emplace_back(make_pair(exp_req[i], exp_gain[i]));
        }
        sort(quests.begin(), quests.end()); //? This will help to determine which quests to take
        priority_queue<int> pq; //? This will help to choose the highest experience gain out of the selected quests (which are under current experience)
        long long current = initial_exp;
        for (int i = 0; i < n; i++)
        {
            while (!pq.empty() && current < quests[i].first && k > 0)
            {
                current += pq.top();
                pq.pop();
                k--;
            }
            if (k == 0)
                break;
            if (current >= quests[i].first)
            {
                pq.push(quests[i].second);
            }
        }
        while (!pq.empty() && k > 0)
        {
            current += pq.top();
            pq.pop();
            k--;
        }
        return current;
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