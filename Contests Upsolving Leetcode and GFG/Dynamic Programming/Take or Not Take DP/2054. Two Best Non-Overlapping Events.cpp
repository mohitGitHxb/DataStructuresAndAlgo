#include <bits/stdc++.h>
using namespace std;

/*
You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.

Return this maximum sum.

Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.



Example 1:

Input: events = [[1,3,2],[4,5,2],[2,4,3]]
Output: 4
Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.

Example 2:
Example 1 Diagram

Input: events = [[1,3,2],[4,5,2],[1,5,5]]
Output: 5
Explanation: Choose event 2 for a sum of 5.

Example 3:

Input: events = [[1,5,3],[1,5,1],[6,6,5]]
Output: 8
Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.

*/
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given events with [startTime, endTime, value]
     * - Can attend at most 2 non-overlapping events
     * - Events overlap if one starts while another is ongoing
     * - Goal: Maximize sum of values from chosen events
     *
     * KEY INSIGHT - Two-Pass Greedy with Suffix Maximum:
     *
     * For each event, we have two choices:
     * 1. Take only this event (value = event.value)
     * 2. Take this event + best non-overlapping future event
     *
     * Strategy:
     * - Sort events by start time
     * - Precompute: "What's the best event starting at or after time T?"
     * - For each event: Look up best future event that doesn't overlap
     *
     * EXAMPLE: events = [[1,3,2], [4,5,2], [2,4,3]]
     * After sorting by start time: [[1,3,2], [2,4,3], [4,5,2]]
     *
     * Timeline visualization:
     * Time:  1  2  3  4  5
     * Ev0:  [====2====]
     * Ev1:     [====3====]
     * Ev2:              [==2==]
     *
     * Pass 1 (Build suffix max map from right to left):
     * - Start from last event, track max value seen so far
     * - suffixMaxValue[1] = 2 (best event starting at time 1+)
     * - suffixMaxValue[2] = 3 (best event starting at time 2+)
     * - suffixMaxValue[4] = 2 (best event starting at time 4+)
     *
     * Pass 2 (Check each event + best future event):
     * - Event [1,3,2]: ends at 3, next valid start is 4
     *   → Can pair with event starting at 4+ (value 2)
     *   → Total: 2 + 2 = 4
     * - Event [2,4,3]: ends at 4, next valid start is 5
     *   → No event starts at 5+
     *   → Total: 3
     * - Event [4,5,2]: ends at 5, next valid start is 6
     *   → No event starts at 6+
     *   → Total: 2
     *
     * Maximum = 4 ✓
     *
     * TIME: O(n log n) - sorting + map operations
     * SPACE: O(n) - suffix map storage
     */

    /**
     * Builds a map of suffix maximums
     * For each start time, stores the maximum event value from that time onward
     *
     * @param events - sorted list of events [startTime, endTime, value]
     * @return map where key=startTime, value=max event value from that time to end
     */
    map<int, long long> buildSuffixMaxMap(const vector<vector<int>> &events)
    {
        map<int, long long> suffixMaxValue;
        int maxValueSeen = 0;

        // Traverse from last event to first (right to left)
        for (int i = events.size() - 1; i >= 0; i--)
        {
            int startTime = events[i][0];
            int value = events[i][2];

            // Update the maximum value seen so far (from right)
            maxValueSeen = max(maxValueSeen, value);

            // Store: "Best event value if we start at or after this time"
            suffixMaxValue[startTime] = maxValueSeen;
        }

        return suffixMaxValue;
    }

    /**
     * Finds the best non-overlapping event that starts after current event ends
     *
     * @param currentEndTime - when current event ends
     * @param suffixMaxValue - map of best values for each start time
     * @return maximum value of event starting after currentEndTime, or 0 if none exists
     */
    long long findBestFutureEvent(int currentEndTime,
                                  const map<int, long long> &suffixMaxValue)
    {
        // Next valid start time (must be strictly after current event ends)
        int nextValidStartTime = currentEndTime + 1;

        // Find first event that starts at or after nextValidStartTime
        auto it = suffixMaxValue.lower_bound(nextValidStartTime);

        if (it != suffixMaxValue.end())
        {
            return it->second; // Return the best value from that point onward
        }

        return 0; // No future non-overlapping event exists
    }

public:
    int maxTwoEvents(vector<vector<int>> &events)
    {
        // Sort events by start time (ascending)
        // This allows us to process events chronologically
        sort(events.begin(), events.end());

        // Build suffix maximum map: for each start time, what's the best event from there?
        map<int, long long> suffixMaxValue = buildSuffixMaxMap(events);

        long long maxSum = 0;

        // Try each event as the first event
        for (const auto &event : events)
        {
            int startTime = event[0];
            int endTime = event[1];
            int value = event[2];

            // Option 1: Take only this event
            maxSum = max(maxSum, static_cast<long long>(value));

            // Option 2: Take this event + best non-overlapping future event
            long long bestFutureValue = findBestFutureEvent(endTime, suffixMaxValue);
            maxSum = max(maxSum, value + bestFutureValue);
        }

        return maxSum;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: events = [[1,3,2], [4,5,2], [2,4,3]]
 *
 * ===== STEP 1: Sort by start time =====
 * Sorted: [[1,3,2], [2,4,3], [4,5,2]]
 *
 * Visual timeline:
 * Time:     1   2   3   4   5
 * Event 0: [===2===]
 * Event 1:     [===3===]
 * Event 2:             [==2==]
 *
 * ===== STEP 2: Build suffix max map (right to left) =====
 *
 * i=2: Event [4,5,2]
 *   maxValueSeen = max(0, 2) = 2
 *   suffixMaxValue[4] = 2
 *
 * i=1: Event [2,4,3]
 *   maxValueSeen = max(2, 3) = 3
 *   suffixMaxValue[2] = 3
 *
 * i=0: Event [1,3,2]
 *   maxValueSeen = max(3, 2) = 3
 *   suffixMaxValue[1] = 3
 *
 * Final map: {1→3, 2→3, 4→2}
 * Meaning: "Best event starting at time X or later"
 *
 * ===== STEP 3: Try each event as first choice =====
 *
 * Event 0: [1,3,2]
 *   endTime = 3, nextValid = 4
 *   Find event starting at 4+: suffixMaxValue.lower_bound(4) → points to {4→2}
 *   Option A: Take only event 0 → value = 2
 *   Option B: Event 0 + best from time 4+ → 2 + 2 = 4 ✓
 *   maxSum = 4
 *
 * Event 1: [2,4,3]
 *   endTime = 4, nextValid = 5
 *   Find event starting at 5+: suffixMaxValue.lower_bound(5) → end() (none)
 *   Option A: Take only event 1 → value = 3
 *   Option B: No future event → 3 + 0 = 3
 *   maxSum = max(4, 3) = 4
 *
 * Event 2: [4,5,2]
 *   endTime = 5, nextValid = 6
 *   Find event starting at 6+: suffixMaxValue.lower_bound(6) → end() (none)
 *   Option A: Take only event 2 → value = 2
 *   Option B: No future event → 2 + 0 = 2
 *   maxSum = max(4, 2) = 4
 *
 * Final Answer: 4 ✓
 * Optimal pair: Event 0 [1,3,2] + Event 2 [4,5,2]
 *
 * ===================================================================
 *
 * WHY THIS WORKS - The Suffix Maximum Technique:
 *
 * 1. SORTING BY START TIME:
 *    - Ensures we process events chronologically
 *    - Makes it easy to find "future" events
 *
 * 2. SUFFIX MAXIMUM MAP:
 *    - Precomputes "best event from time T onward"
 *    - Avoids checking every future event for each current event
 *    - O(log n) lookup instead of O(n) scan
 *
 * 3. UPPER_BOUND USAGE:
 *    - Finds first event starting AFTER current event ends
 *    - Ensures no overlap (events can't share endpoints)
 *
 * 4. TWO CHOICES PER EVENT:
 *    - Solo: Just take this event
 *    - Pair: Take this + best future non-overlapping event
 *    - Try both, keep maximum
 *
 * 5. OPTIMALITY:
 *    - We try every possible first event
 *    - For each first event, we pair with optimal second event
 *    - Guaranteed to find the best pair (or solo event)
 *
 * ALTERNATIVE APPROACHES:
 * - DP with sorting by end time (more complex state management)
 * - Priority queue/sweep line (similar complexity)
 * - This approach is cleaner and more intuitive
 */
int main()
{
    return 0;
}