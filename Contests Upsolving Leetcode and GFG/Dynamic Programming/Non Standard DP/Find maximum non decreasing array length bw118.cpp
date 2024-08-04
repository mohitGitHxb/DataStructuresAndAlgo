#include <bits/stdc++.h>
using namespace std;
// Idea:
// 1. say max_len[i] is the result/answer for first i elements
//1a. max_len[0] = 0; max_len[1] = 1
// 2. say last_val[i] is last value of array
// after performing optimal operations for first i elements
// 3. max_len[i] = max(max_len[i], max_len[q]+1) for all valid 'q'
//See below for valid 'q' definition
//3a. q < i
//3b. last_val[q] <= nums[q] + nums[q+1] + ...+ nums[i-1]
//    => last_val[q] <= prefix_sum[i] - prefix_sum[q]
//    => last_val[q] + prefix_sum[q] <= prefix_sum[i]  (for O(n) solution)
//

// O(n^2) solution

int findMaximumLength(vector<int> A)
{
    int n = A.size();
    vector<int> max_len(n + 1);
    vector<long long> last_val(n + 1);
    vector<long long> prefix_sum(n + 1);

    for (int j = 1; j <= n; j++)
    {
        prefix_sum[j] = prefix_sum[j - 1] + A[j - 1];
    }

    for (int i = 1; i <= n; i++)
    {
        for (int q = 0; q < i; q++)
        {
            if (last_val[q] <= prefix_sum[i] - prefix_sum[q])
            {
                // if (max_len[q] + 1 >= max_len[i]) { //not need as max_len[q] <= max_len[q+1]
                max_len[i] = max_len[q] + 1;
                last_val[i] = prefix_sum[i] - prefix_sum[q];
                //}
            }
        }
    }

    return max_len[n];
}

// optimized solution
// O(n) because the two below while-loops in their life time cannot be more than n-times.
//      => O( n    +  n   +   n  )  =  O(n)
//            |       |       |
//      for-loop   while-loop  while-loop

int findMaximumLength(vector<int> A)
{
    int n = A.size();
    vector<int> max_len(n + 1);
    vector<int> last_val(n + 1);
    vector<long long> prefix_sum(n + 1);
    vector<int> stk;

    for (int j = 1; j <= n; j++)
    {
        prefix_sum[j] = prefix_sum[j - 1] + A[j - 1];
    }

    stk.push_back(0);
    size_t stk_ptr = 0;
    int q = 0;
    for (int i = 1; i <= n; i++)
    {

        // need below step to not to increase q prematurely. Eg, A = [5, 2, 2]
        stk_ptr = min(stk_ptr, stk.size() - 1);
        while (stk_ptr < stk.size() - 1 and last_val[stk[stk_ptr + 1]] + prefix_sum[stk[stk_ptr + 1]] <= prefix_sum[i])
        {
            stk_ptr++;
        }

        // below step is same as O(n^2) solution
        q = stk[stk_ptr];
        max_len[i] = max_len[q] + 1;
        last_val[i] = prefix_sum[i] - prefix_sum[q];

        // below step is implementation of monotonic increasing stack
        while (!stk.empty() and
               last_val[stk.back()] + prefix_sum[stk.back()] >= last_val[i] + prefix_sum[i])
        {
            stk.pop_back();
        }
        stk.push_back(i);
    }
    return max_len[n];
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
        // write code here
    }
    return 0;
}