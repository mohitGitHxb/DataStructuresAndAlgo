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
You have n tasks and m workers. Each task has a strength requirement stored in a 0-indexed integer array tasks, with the ith task requiring tasks[i] strength to complete. The strength of each worker is stored in a 0-indexed integer array workers, with the jth worker having workers[j] strength. Each worker can only be assigned to a single task and must have a strength greater than or equal to the task's strength requirement (i.e., workers[j] >= tasks[i]).

Additionally, you have pills magical pills that will increase a worker's strength by strength. You can decide which workers receive the magical pills, however, you may only give each worker at most one magical pill.

Given the 0-indexed integer arrays tasks and workers and the integers pills and strength, return the maximum number of tasks that can be completed.

@approach:
Strategy Details

    Binary Search (O(log n)):
        Tests different task counts from 0 to min(tasks, workers)
        Uses canComplete() to validate feasibility

    Greedy Assignment:
        Always tries to use the weakest possible worker for each task
        Processes tasks in descending order to handle largest tasks first
        Uses pills only when necessary

    Pill Usage:
        A pill allows a worker to handle tasks up to worker_strength + pill_strength
        When using a pill, we look for task_requirement - pill_strength as threshold


     */
public:
    bool canComplete(vector<int> &tasks, vector<int> &workers, int pills, int strength, int index)
    {
        multiset<int> st(workers.begin(), workers.end());
        for (int i = index - 1; i >= 0; i--)
        {
            auto it = st.lower_bound(tasks[i]);
            if (it != st.end())
            {
                st.erase(it);
            }
            else
            {
                if (pills <= 0)
                    return false;
                it = st.lower_bound(tasks[i] - strength);
                if (it == st.end())
                    return false;
                st.erase(it);
                pills--;
            }
        }
        return true;
    }
    int maxTaskAssign(vector<int> &tasks, vector<int> &workers, int pills, int strength)
    {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());

        int low = 0, high = min(tasks.size(), workers.size());

        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (canComplete(tasks, workers, pills, strength, mid))
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return high;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    vector<string> words = {"aba", "bcb", "ece", "aa", "e"};
    vector<vector<int>> queries = {{0, 2}, {1, 4}, {1, 1}};
    obj.vowelStrings(words, queries);
    // Test cases for local testing
    return 0;
}
#endif