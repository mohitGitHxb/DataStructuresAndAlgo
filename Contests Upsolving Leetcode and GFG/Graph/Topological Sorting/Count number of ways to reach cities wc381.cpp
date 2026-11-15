#include <bits/stdc++.h>
using namespace std;
vector<int> countOfPairs(int n, int x, int y)
{
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, n + 1));
    for (int i = 1; i < n; i++)
    {
        graph[i][i + 1] = 1;
        graph[i + 1][i] = 1;
    }
    graph[x][y] = 1;
    graph[y][x] = 1;

    for (int i = 1; i <= n; i++)
        graph[i][i] = 0;

    for (int k = 1; k <= n; k++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }

    vector<int> ans(n, 0);
    for (int i = 1; i <= n; i++)
    {
        for (int j = i + 1; j <= n; j++)
        {
            ans[graph[i][j] - 1]++;
        }
    }

    for (int &i : ans)
        i *= 2;
    return ans;
}
int main()
{
    return 0;
}