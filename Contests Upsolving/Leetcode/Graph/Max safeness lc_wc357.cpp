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

class Solution
{
    int dx[4] = {1, -1, 0, 0};
    int dy[4] = {0, 0, 1, -1};
    // This function finds the minimum Distance of each cell from any thief cell.
    // Multisource BFs from the theif cells gives the minimum Distance.
    // TC : O(N*N)
    // Iterating and pushing the theif cells takes O(N*N) time.
    // Finding the Minimum Disance from theif cell to each cell takes O(N*N) time.
    // SC : O(N*N)
    // space for the distance and the Vsiited matrix.

    void findMinimumDistance(vector<vector<int>> &grid, vector<vector<int>> &distance)
    {
        int n = grid.size();
        /*visited array to avoid duplicate visits*/
        vector<vector<int>> visited(n, vector<int>(n, 0));
        queue<pair<int, int>> q;
        /*Taking all the thief cells into the queue*/
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j])
                {
                    q.push({i, j});
                    visited[i][j] = 1;
                }
            }
        }
        /*Doing multi surface BFs and updating the distance when the cell is visited first*/
        for (int dist = 0; !q.empty(); ++dist)
        {
            for (int i = q.size(); i > 0; --i)
            {
                auto it = q.front();
                q.pop();
                int x = it.first, y = it.second;
                distance[x][y] = dist;
                for (int j = 0; j < 4; ++j)
                {
                    int nx = x + dx[j], ny = y + dy[j];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && visited[nx][ny] == 0)
                    {
                        q.push({nx, ny});
                        visited[nx][ny] = 1;
                    }
                }
            }
        }
    }
    // This function will return if there exists a path in the grid whose maximum safeness
    // factor is >= k
    // We do BFs to explore all the paths starting from the (0,0).
    // Consider only the cells in the path whose distance from the any thief cell is >= k.

    // TC : O(N*N)
    // At max while loop runs for O(N*N) time.
    // SC : O(N*N)
    // space for the queue and the visited matrix.
    bool isPathExists(int n, vector<vector<int>> &distance, int k)
    {
        queue<pair<int, int>> q;
        /*If the cell (0,0) distance from theif cell is < k then In any path we choose the cell (0,0)
        is present, so there is no path in grid with each cell >= k minimum distance from any thief*/
        if (distance[0][0] < k)
            return false;
        q.push({0, 0});
        vector<vector<int>> visited(n, vector<int>(n, 0));
        visited[0][0] = 1;
        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            int x = it.first, y = it.second;
            if (x == n - 1 && y == n - 1)
                return true;
            for (int j = 0; j < 4; ++j)
            {
                int nx = x + dx[j], ny = y + dy[j];
                /*Take into queue only when the Manhatten distance >= k from current cell to thief cell*/
                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    visited[nx][ny] == 0 && distance[nx][ny] >= k)
                {
                    q.push({nx, ny});
                    visited[nx][ny] = 1;
                }
            }
        }
        return false;
    }

public:
    // TC : O(N*N + O(N*N)log(2*n-1))
    // N*N for finding the minimum Distance of each cell to any thief cell.
    // N*Nlog(2*n-1) for finding the maximum safeness factor of all paths.
    // SC : O(N*N)
    // Space used for the distance,visited matrix and the queue.
    int maximumSafenessFactor(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<vector<int>> distance(n, vector<int>(n));
        findMinimumDistance(grid, distance);
        // Range of binary search
        // Max distance between any two cells is equal to distance b/w (0,0) and (n-1,n-1).
        // Manhatten distance b/w them is 2*n-1.
        // Min Distance is 0.
        // So low = 0 high = 2*n-1
        int low = 0, high = 2 * n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            isPathExists(n, distance, mid) ? low = mid + 1 : high = mid - 1;
        }
        return high;
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