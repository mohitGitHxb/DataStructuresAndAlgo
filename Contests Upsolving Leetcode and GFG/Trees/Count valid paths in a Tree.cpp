#include <bits/stdc++.h>
using namespace std;

/* Intuition

The main concept is to count non-prime children of a prime node and merging them using disjoint set algorithm.
Approach

    Get all the prime numbers upto n and store them in a vector using sieve of eratosthenes.
    Implement class for DSU which merges nodes using their rank or count.
    Create an adj list for graph. If there exists an edge u-v such that both u and v are non-prime, unite them using dsu.
    Now count result. Iterate from 1 to n, if any prime number i is encountered, get all non-prime child of this number and put their merging count in a vector child. After that get total sum of this child vector. To count number of paths crossing this prime number i, we will use child array i.e., from child vector get an element, substract it from sum and increment the answer by sum*element.

Complexity

    Time complexity:

O(n)

    Space complexity:

O(n)

Code */

class DSU
{
public:
    vector<int> par;
    vector<int> cnt;

    DSU(int n)
    {
        par.resize(n + 1);
        cnt.resize(n + 1, 1);

        for (int i = 0; i <= n; i++)
            par[i] = i;
    }

    int abs_par(int x)
    {
        if (x == par[x])
            return x;
        return par[x] = abs_par(par[x]);
    }

    void unite(int a, int b)
    {
        int abs_a = abs_par(a);
        int abs_b = abs_par(b);

        if (abs_a == abs_b)
            return;

        if (cnt[abs_a] > cnt[abs_b])
            swap(a, b);

        cnt[abs_b] += cnt[abs_a];
        par[abs_a] = abs_b;
    }
};

class Solution
{
public:
    long long countPaths(int n, vector<vector<int>> &edges)
    {

        // getting all the prime numbers
        vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        for (int p = 2; p * p <= n; p++)
        {
            if (is_prime[p])
            {
                for (int i = p * p; i <= n; i += p)
                {
                    is_prime[i] = false;
                }
            }
        }

        // getting adjlist from edges and uniting nodes if none of them are prime
        DSU dsu(n);
        vector<int> adj[n + 1];
        for (auto &e : edges)
        {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);

            if (is_prime[e[0]] || is_prime[e[1]])
                continue;

            dsu.unite(e[0], e[1]);
        }

        long long ans = 0;
        for (int i = 1; i <= n; i++)
        {
            if (!is_prime[i])
                continue;

            vector<long long> child;
            for (auto &x : adj[i])
            {
                if (is_prime[x])
                    continue;
                int par_x = dsu.abs_par(x);
                child.push_back(dsu.cnt[par_x]);
            }
            long long sum = accumulate(child.begin(), child.end(), 1);
            for (auto &c : child)
            {
                sum -= c;
                ans += sum * c;
            }
        }

        return ans;
    }
};

class Solution
{
public:
    long long groupNumber;
    vector<bool> primes;
    vector<vector<long long>> adj;
    unordered_map<long long, long long> groupCount;
    unordered_map<long long, long long> vis;
    Solution()
    {
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
    }
    void sieve(long long n)
    {
        primes.resize(n + 1, true);
        primes[0] = primes[1] = false;
        for (long long i = 2; i <= n; i++)
        {
            if (primes[i])
            {
                for (long long j = i * i; j <= n; j += i)
                    primes.at(j) = false;
            }
        }
    }
    long long dfs(long long node)
    {
        if (primes[node] || vis[node] != 0)
            return 0;
        vis[node] = groupNumber;

        long long ans = 1;
        for (auto &c : adj[node])
        {
            ans += dfs(c);
        }
        return ans;
    }
    long long countPaths(long long n, vector<vector<int>> &edges)
    {
        sieve(n);
        adj.resize(n + 1, vector<long long>());
        for (auto &it : edges)
        {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        groupNumber = 1;
        for (long long i = 1; i <= n; i++)
        {
            long long count = dfs(i);
            groupCount[groupNumber++] = count;
        }
        long long ans = 0;
        for (long long i = 2; i <= n; i++)
        {
            if (primes.at(i))
            {
                vector<long long> v;
                long long sum = 0;
                for (auto &c : adj[i])
                {
                    v.push_back(groupCount[vis[c]]);
                    sum += groupCount[vis[c]];
                }
                long long curAns = 0;
                for (auto &c : v)
                {
                    curAns += ((sum - c) * c);
                }

                curAns /= 2;
                curAns += sum;
                ans += curAns;
            }
        }
        return ans;
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