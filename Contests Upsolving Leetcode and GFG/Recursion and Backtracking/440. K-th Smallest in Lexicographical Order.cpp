#include <bits/stdc++.h>
using namespace std;
#define ll long long
class Solution
{
private:
    int calc_number_in_cur_pref(ll cur_pref, int n)
    {
        ll nxt_grt_pref = cur_pref + 1; // 1 + 1 = 2

        int sum = 0;

        while (cur_pref <= n)
        {
            // int range = nxt_grt_pref - cur_pref;
            int range = min((ll)n + 1, nxt_grt_pref) - cur_pref;

            // sum the counted number
            sum += range;

            // adding smallest suffix '0' at last place
            nxt_grt_pref *= 10;
            cur_pref *= 10;
        }

        return sum;
    }

public:
    int findKthNumber(int n, int k)
    {
        k--; // to make things for 0 based index

        int cur_pref = 1;

        while (k > 0)
        {
            int nums = calc_number_in_cur_pref(cur_pref, n); // 1, 111

            if (nums > k)
            {
                // move inwards of branch
                cur_pref *= 10;
                k--;
            }
            else
            {
                // move to next branch
                cur_pref += 1;
                k -= nums;
            }
        }

        return cur_pref;
    }
};
int main()
{
    return 0;
}