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
    /*You are given an integer n. There are n rooms numbered from 0 to n - 1.

You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.

Meetings are allocated to rooms in the following manner:

    Each meeting will take place in the unused room with the lowest number.
    If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
    When a room becomes unused, meetings that have an earlier original start time should be given the room.

Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.

A half-closed interval [a, b) is the interval between a and b including a and not including b.



Example 1:

Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0
Explanation:
- At time 0, both rooms are not being used. The first meeting starts in room 0.
- At time 1, only room 1 is not being used. The second meeting starts in room 1.
- At time 2, both rooms are being used. The third meeting is delayed.
- At time 3, both rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
- At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
Both rooms 0 and 1 held 2 meetings, so we return 0.

Example 2:

Input: n = 3, meetings = [[1,20],[2,10],[3,5],[4,9],[6,8]]
Output: 1
Explanation:
- At time 1, all three rooms are not being used. The first meeting starts in room 0.
- At time 2, rooms 1 and 2 are not being used. The second meeting starts in room 1.
- At time 3, only room 2 is not being used. The third meeting starts in room 2.
- At time 4, all three rooms are being used. The fourth meeting is delayed.
- At time 5, the meeting in room 2 finishes. The fourth meeting starts in room 2 for the time period [5,10).
- At time 6, all three rooms are being used. The fifth meeting is delayed.
- At time 10, the meetings in rooms 1 and 2 finish. The fifth meeting starts in room 1 for the time period [10,12).
Room 0 held 1 meeting while rooms 1 and 2 each held 2 meetings, so we return 1.


     */
public:
    int mostBooked(int rooms, vector<vector<int>> &meetings)
    {
        const int N = meetings.size();
        sort(meetings.begin(), meetings.end());
        vector<int> roomCount(rooms, 0); // Count of meetings held in each room
        set<ll> availableRooms;          // stores the available rooms.
        set<pair<ll, int>> usedRooms;    // {pair<startTime, roomNumber>}

        for (int i = 0; i < rooms; i++)
        {
            availableRooms.insert(i); // Initially all rooms are available at time 0
        }
        for (int i = 0; i < N; i++)
        {
            const ll startTime = meetings[i][0], endTime = meetings[i][1];
            const ll meetingDuration = endTime - startTime;
            // Free up rooms that have finished their meetings
            while (!usedRooms.empty() && usedRooms.begin()->first <= startTime)
            {
                auto it = usedRooms.begin();
                int roomNumber = it->second;
                availableRooms.insert(roomNumber);
                usedRooms.erase(it);
            }

            const bool isRoomAvailable = !availableRooms.empty();
            if (isRoomAvailable)
            {
                const int roomNumber = *availableRooms.begin();
                availableRooms.erase(availableRooms.begin());
                usedRooms.insert({endTime, roomNumber});
                roomCount[roomNumber]++;
            }
            else
            {
                auto [endTimeOfFirstUsedRoom, roomNumber] = *usedRooms.begin();
                usedRooms.erase(usedRooms.begin());

                const ll newStartTime = endTimeOfFirstUsedRoom + meetingDuration;
                usedRooms.insert({newStartTime, roomNumber});
                roomCount[roomNumber]++;
                // No need to update availableRooms since the room is still in use
            }
        }
        // Find the room with the maximum meetings held
        int maxMeetings = 0, roomWithMaxMeetings = 0;
        for (int i = 0; i < rooms; i++)
        {
            if (roomCount[i] > maxMeetings)
            {
                maxMeetings = roomCount[i];
                roomWithMaxMeetings = i;
            }
        }
        return roomWithMaxMeetings;
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