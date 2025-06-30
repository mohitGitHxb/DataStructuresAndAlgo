#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
static int init = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution
{
private:
    /*
    You have information about n different recipes. You are given a string array recipes and a 2D string array ingredients. The ith recipe has the name recipes[i], and you can create it if you have all the needed ingredients from ingredients[i]. A recipe can also be an ingredient for other recipes, i.e., ingredients[i] may contain a string that is in recipes.

    You are also given a string array supplies containing all the ingredients that you initially have, and you have an infinite supply of all of them.

    Return a list of all the recipes that you can create. You may return the answer in any order.

    Note that two recipes may contain each other in their ingredients.



    Example 1:

    Input: recipes = ["bread"], ingredients = [["yeast","flour"]], supplies = ["yeast","flour","corn"]
    Output: ["bread"]
    Explanation:
    We can create "bread" since we have the ingredients "yeast" and "flour".

    Example 2:

    Input: recipes = ["bread","sandwich"], ingredients = [["yeast","flour"],["bread","meat"]], supplies = ["yeast","flour","meat"]
    Output: ["bread","sandwich"]
    Explanation:
    We can create "bread" since we have the ingredients "yeast" and "flour".
    We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".

    Example 3:

    Input: recipes = ["bread","sandwich","burger"], ingredients = [["yeast","flour"],["bread","meat"],["sandwich","meat","bread"]], supplies = ["yeast","flour","meat"]
    Output: ["bread","sandwich","burger"]
    Explanation:
    We can create "bread" since we have the ingredients "yeast" and "flour".
    We can create "sandwich" since we have the ingredient "meat" and can create the ingredient "bread".
    We can create "burger" since we have the ingredient "meat" and can create the ingredients "bread" and "sandwich".

    @ Approach:
    To solve this problem, we can think of it as topological sorting on a graph:

    Nodes: Recipes and ingredients.
    Edges: A directed edge from ingredient to recipe, indicating that the recipe depends on the ingredient.
    Topological Sort: We process nodes (recipes) in the order of their dependencies. If a recipe’s dependencies are met (all required ingredients are available), we can make it.

🔑 Steps to Solve

1️⃣ Build the Graph:

    Create an adjacency list where each ingredient points to the recipes that depend on it.
    Track the in-degree (number of required ingredients) for each recipe.

2️⃣ Breadth-First Search (BFS):

    Add all initial supplies (ingredients you already have) to the queue.
    Process each ingredient:
        Reduce the in-degree of the recipes that depend on this ingredient.
        If a recipe’s in-degree becomes 0, add it to the queue and mark it as possible to create.

3️⃣ Return all possible recipes in any order.
     */
public:
    vector<string> findAllRecipes(vector<string> &recipes,
                                  vector<vector<string>> &ingredients,
                                  vector<string> &supplies)
    {
        const int r = recipes.size();
        const int s = supplies.size();
        unordered_map<string, vector<string>> graph;
        unordered_map<string, int> indegree;
        // use kahn's algo (topological sorting) to get the linear ordering of
        // recipes for example bread -> sandwich -> burger. We need to prepare
        // the dishes in optimal order.
        for (int i = 0; i < r; i++)
        {
            for (string &ingredient : ingredients[i])
            {
                graph[ingredient].emplace_back(recipes[i]);
            }
            indegree[recipes[i]] = ingredients.at(i).size();
        }

        // kahn's algo
        vector<string> ordered;
        queue<string> q(supplies.begin(), supplies.end());

        while (!q.empty())
        {
            const string supply = q.front();
            q.pop();
            for (string &recipe : graph[supply])
            {
                indegree[recipe]--;
                if (indegree[recipe] == 0)
                {
                    ordered.emplace_back(recipe);
                    q.emplace(recipe); // this is now a part of supply
                }
            }
        }
        return ordered;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    cout << "\nProgram Started\n\n";
    cout << obj.minimizeXor(4214, 5) << endl;
    return 0;
}
#endif