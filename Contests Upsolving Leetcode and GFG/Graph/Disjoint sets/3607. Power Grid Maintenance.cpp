#include <bits/stdc++.h>
using namespace std;
class DSU
{
public:
    vector<int> parent, size;
    DSU(int n)
    {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b)
        {
            return;
        }
        if (size[a] < size[b])
        {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

class Solution
{
public:
    vector<int> processQueries(int c, vector<vector<int>> &connections,
                               vector<vector<int>> &queries)
    {
        DSU dsu(c);

        // Step 1: Build connected components
        for (auto &conn : connections)
        {
            dsu.unite(conn[0], conn[1]);
        }

        // Step 2: Prepare set for each component
        unordered_map<int, set<int>> onlineStations;
        vector<bool> isOnline(c + 1, true);

        for (int i = 1; i <= c; ++i)
        {
            int root = dsu.find(i);
            onlineStations[root].insert(i);
        }

        vector<int> result;

        // Step 3: Process queries
        for (auto &q : queries)
        {
            int type = q[0];
            int x = q[1];
            int root = dsu.find(x);

            if (type == 1)
            {
                if (isOnline[x])
                {
                    result.push_back(x);
                }
                else
                {
                    auto &st = onlineStations[root];
                    if (st.empty())
                    {
                        result.push_back(-1);
                    }
                    else
                    {
                        result.push_back(
                            *st.begin()); // smallest online station
                    }
                }
            }
            else if (type == 2)
            {
                if (isOnline[x])
                {
                    isOnline[x] = false;
                    onlineStations[root].erase(x);
                }
            }
        }

        return result;
    }
};

int main()
{
    return 0;
}
