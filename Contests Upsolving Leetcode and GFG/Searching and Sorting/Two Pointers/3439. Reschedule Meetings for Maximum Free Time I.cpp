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
        You are given an integer eventTime denoting the duration of an event, where the event occurs from time t = 0 to time t = eventTime.

        You are also given two integer arrays startTime and endTime, each of length n. These represent the start and end time of n non-overlapping meetings, where the ith meeting occurs during the time [startTime[i], endTime[i]].

        You can reschedule at most k meetings by moving their start time while maintaining the same duration, to maximize the longest continuous period of free time during the event.

        The relative order of all the meetings should stay the same and they should remain non-overlapping.

        Return the maximum amount of free time possible after rearranging the meetings.

        Note that the meetings can not be rescheduled to a time outside the event.



        Example 1:

        Input: eventTime = 5, k = 1, startTime = [1,3], endTime = [2,5]

        Output: 2

        Explanation:

        Reschedule the meeting at [1, 2] to [2, 3], leaving no meetings during the time [0, 2].

        Example 2:

        Input: eventTime = 10, k = 1, startTime = [0,2,9], endTime = [1,4,10]

        Output: 6

        Explanation:

        Reschedule the meeting at [2, 4] to [1, 3], leaving no meetings during the time [3, 9].

        Example 3:

        Input: eventTime = 5, k = 2, startTime = [0,1,2,3,4], endTime = [1,2,3,4,5]

        Output: 0

        Explanation:

        There is no time during the event not occupied by meetings.


     */
public:
    int maxFreeTime(int eventTime, int k, vector<int> &startTime, vector<int> &endTime)
    {

        const int n = startTime.size();
        vector<int> freeTimes(n + 1);
        freeTimes[0] = startTime[0]; // free time before the first meeting
        for (int i = 1; i < n; i++)
        {
            freeTimes[i] = startTime[i] - endTime[i - 1]; // free time between meetings
        }
        freeTimes[n] = eventTime - endTime[n - 1]; // free time after the last meeting
        int start = 0;
        const int m = freeTimes.size();
        int maxFreeTime = 0;     // this wil store the maximum free time of subarray length of k + 1;
        int currentFreeTime = 0; // this will store the current free time of subarray length of k + 1;
        for (int end = 0; end < m; end++)
        {
            currentFreeTime += freeTimes[end];
            if (end - start + 1 > k + 1)
            {
                currentFreeTime -= freeTimes[start];
                start++;
            }
            maxFreeTime = max(maxFreeTime, currentFreeTime);
        }
        return maxFreeTime;
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    // Test cases for local testing
    return 0;
}
#endif