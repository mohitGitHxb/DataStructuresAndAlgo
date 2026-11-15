#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - n rooms numbered 0 to n-1
     * - Meetings have [start, end) time intervals
     * - Allocation rules:
     *   1. Use lowest numbered available room
     *   2. If no room available, delay meeting until one is free
     *   3. Delayed meetings keep same duration
     *   4. Earlier meetings get priority when room becomes free
     * - Goal: Return room number that held the most meetings (ties → lowest number)
     *
     * KEY INSIGHT - Event-Driven Simulation:
     *
     * Process meetings in chronological order (sorted by start time).
     * Track two sets of rooms:
     * 1. AVAILABLE: Rooms currently free (set sorted by room number)
     * 2. OCCUPIED: Rooms in use (set sorted by end time, then room number)
     *
     * For each meeting:
     * - Free up rooms that finished by current meeting's start time
     * - If room available → assign lowest numbered room
     * - If no room available → delay meeting, use room that finishes first
     *
     * EXAMPLE: n=2, meetings=[[0,10],[1,5],[2,7],[3,4]]
     *
     * Time 0:
     *   Available: {0, 1}
     *   Meeting [0,10): Assign room 0
     *   Occupied: {[10, room 0]}
     *   Available: {1}
     *
     * Time 1:
     *   Meeting [1,5): Assign room 1
     *   Occupied: {[5, room 1], [10, room 0]}
     *   Available: {}
     *
     * Time 2:
     *   Meeting [2,7) delayed (no rooms available)
     *   Room 1 finishes first at time 5
     *   Delayed meeting: [5, 5+5) = [5, 10)
     *   Occupied: {[10, room 0], [10, room 1]}
     *
     * Time 3:
     *   Meeting [3,4) delayed
     *   Room 0 finishes first at time 10
     *   Delayed meeting: [10, 10+1) = [10, 11)
     *   Occupied: {[10, room 1], [11, room 0]}
     *
     * Room counts: room 0 = 2, room 1 = 2
     * Answer: 0 (tie, choose lowest number)
     *
     * TIME: O(n log n + n*m log m) where n=meetings, m=rooms
     * SPACE: O(m) for tracking room states
     */

    /**
     * Frees up all rooms whose meetings have ended by the given time
     * Moves rooms from occupied set back to available set
     *
     * @param currentTime - the current time in the simulation
     * @param availableRooms - set of available room numbers
     * @param occupiedRooms - set of {endTime, roomNumber} pairs
     */
    void freeCompletedMeetings(long long currentTime,
                               set<int> &availableRooms,
                               set<pair<long long, int>> &occupiedRooms)
    {
        // Check rooms in order of end time (earliest first)
        while (!occupiedRooms.empty())
        {
            auto [meetingEndTime, roomNumber] = *occupiedRooms.begin();

            // If this meeting hasn't ended yet, we're done
            // (since occupiedRooms is sorted by end time)
            if (meetingEndTime > currentTime)
            {
                break;
            }

            // This meeting has ended, free up the room
            occupiedRooms.erase(occupiedRooms.begin());
            availableRooms.insert(roomNumber);
        }
    }

    /**
     * Assigns a meeting to an available room
     * Uses the lowest numbered available room
     *
     * @param meetingEndTime - when the meeting will end
     * @param availableRooms - set of available room numbers (modified)
     * @param occupiedRooms - set of {endTime, roomNumber} pairs (modified)
     * @param meetingCounts - array tracking meetings per room (modified)
     * @return room number assigned
     */
    int assignToAvailableRoom(long long meetingEndTime,
                              set<int> &availableRooms,
                              set<pair<long long, int>> &occupiedRooms,
                              vector<int> &meetingCounts)
    {
        // Get lowest numbered available room
        int roomNumber = *availableRooms.begin();

        // Mark room as occupied
        availableRooms.erase(availableRooms.begin());
        occupiedRooms.insert({meetingEndTime, roomNumber});

        // Increment meeting count for this room
        meetingCounts[roomNumber]++;

        return roomNumber;
    }

    /**
     * Delays a meeting until the earliest room becomes available
     * Uses the room that finishes first (ties → lowest room number)
     *
     * @param meetingDuration - how long the meeting lasts
     * @param occupiedRooms - set of {endTime, roomNumber} pairs (modified)
     * @param meetingCounts - array tracking meetings per room (modified)
     * @return room number assigned
     */
    int delayMeetingToNextAvailableRoom(long long meetingDuration,
                                        set<pair<long long, int>> &occupiedRooms,
                                        vector<int> &meetingCounts)
    {
        // Get room that will be free earliest
        // occupiedRooms is sorted by {endTime, roomNumber}, so first element is optimal
        auto [earliestEndTime, roomNumber] = *occupiedRooms.begin();
        occupiedRooms.erase(occupiedRooms.begin());

        // Schedule delayed meeting: starts when room is free
        long long newEndTime = earliestEndTime + meetingDuration;
        occupiedRooms.insert({newEndTime, roomNumber});

        // Increment meeting count for this room
        meetingCounts[roomNumber]++;

        return roomNumber;
    }

    /**
     * Finds the room with the most meetings
     * In case of tie, returns the lowest room number
     *
     * @param meetingCounts - array of meeting counts per room
     * @return room number with most meetings
     */
    int findRoomWithMostMeetings(const vector<int> &meetingCounts)
    {
        int maxMeetings = 0;
        int roomWithMostMeetings = 0;

        for (int roomNumber = 0; roomNumber < meetingCounts.size(); roomNumber++)
        {
            if (meetingCounts[roomNumber] > maxMeetings)
            {
                maxMeetings = meetingCounts[roomNumber];
                roomWithMostMeetings = roomNumber;
            }
        }

        return roomWithMostMeetings;
    }

public:
    int mostBooked(int numRooms, vector<vector<int>> &meetings)
    {
        // Sort meetings by start time (process chronologically)
        sort(meetings.begin(), meetings.end());

        // Track how many meetings each room has held
        vector<int> meetingCounts(numRooms, 0);

        // Available rooms (sorted by room number for "lowest numbered" rule)
        set<int> availableRooms;

        // Occupied rooms: {endTime, roomNumber}
        // Sorted by endTime first (for finding earliest available)
        // Then by roomNumber (for tie-breaking)
        set<pair<long long, int>> occupiedRooms;

        // Initially all rooms are available
        for (int i = 0; i < numRooms; i++)
        {
            availableRooms.insert(i);
        }

        // Process each meeting in chronological order
        for (const auto &meeting : meetings)
        {
            long long startTime = meeting[0];
            long long endTime = meeting[1];
            long long duration = endTime - startTime;

            // Step 1: Free up rooms that have finished by this meeting's start time
            freeCompletedMeetings(startTime, availableRooms, occupiedRooms);

            // Step 2: Assign meeting to a room
            if (!availableRooms.empty())
            {
                // Case A: Room available → use lowest numbered room
                assignToAvailableRoom(endTime, availableRooms, occupiedRooms, meetingCounts);
            }
            else
            {
                // Case B: No room available → delay meeting, use earliest-to-finish room
                delayMeetingToNextAvailableRoom(duration, occupiedRooms, meetingCounts);
            }
        }

        // Return room that held the most meetings
        return findRoomWithMostMeetings(meetingCounts);
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: n=2, meetings=[[0,10],[1,5],[2,7],[3,4]]
 *
 * Initial State:
 * - Available: {0, 1}
 * - Occupied: {}
 * - Counts: [0, 0]
 *
 * ===== Meeting [0, 10) (duration=10) =====
 * Time: 0
 * Free rooms ending by time 0: none
 * Available rooms: {0, 1} ✓
 * → Assign to room 0 (lowest available)
 *
 * State after:
 * - Available: {1}
 * - Occupied: {[10, room0]}
 * - Counts: [1, 0]
 *
 * ===== Meeting [1, 5) (duration=4) =====
 * Time: 1
 * Free rooms ending by time 1: none
 * Available rooms: {1} ✓
 * → Assign to room 1
 *
 * State after:
 * - Available: {}
 * - Occupied: {[5, room1], [10, room0]}
 * - Counts: [1, 1]
 *
 * ===== Meeting [2, 7) (duration=5) =====
 * Time: 2
 * Free rooms ending by time 2: none
 * Available rooms: {} ✗ → DELAY
 * → Earliest room: room1 finishes at time 5
 * → Delay meeting to [5, 5+5) = [5, 10)
 * → Assign to room 1
 *
 * State after:
 * - Available: {}
 * - Occupied: {[10, room0], [10, room1]}
 * - Counts: [1, 2]
 *
 * ===== Meeting [3, 4) (duration=1) =====
 * Time: 3
 * Free rooms ending by time 3: none
 * Available rooms: {} ✗ → DELAY
 * → Earliest room: room0 finishes at time 10 (room1 also at 10, but 0 < 1)
 * → Delay meeting to [10, 10+1) = [10, 11)
 * → Assign to room 0
 *
 * State after:
 * - Available: {}
 * - Occupied: {[10, room1], [11, room0]}
 * - Counts: [2, 2]
 *
 * ===== Final Result =====
 * Room counts: [2, 2]
 * Both rooms held 2 meetings → return room 0 (lowest number) ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Key Design Decisions:
 *
 * 1. SORTING BY START TIME:
 *    - Ensures we process meetings in chronological order
 *    - Respects "earlier original start time" priority rule
 *
 * 2. TWO SETS DESIGN:
 *    - availableRooms: set<int> → automatically sorted by room number
 *      Ensures we always pick lowest numbered room
 *    - occupiedRooms: set<pair<long long, int>> → sorted by (endTime, roomNum)
 *      Ensures we find earliest-finishing room for delays
 *
 * 3. FREEING ROOMS FIRST:
 *    - Before processing each meeting, free all rooms that have finished
 *    - This ensures we don't unnecessarily delay meetings
 *
 * 4. DELAY LOGIC:
 *    - When delaying, we preserve the meeting duration
 *    - New end time = (earliest room end time) + (meeting duration)
 *    - This correctly implements the "same duration" rule
 *
 * 5. TIE-BREAKING:
 *    - set<pair<long long, int>> naturally breaks ties by room number
 *    - When two rooms finish at same time, lower room number comes first
 *    - Final result loop also picks lowest room number in case of count ties
 *
 * COMPLEXITY ANALYSIS:
 * - Sorting: O(n log n) where n = number of meetings
 * - For each meeting:
 *   - Free rooms: O(m log m) worst case (m = number of rooms)
 *   - Insert/erase from sets: O(log m)
 * - Total: O(n log n + n*m log m)
 * - In practice, much faster since we don't always free all rooms
 */
int main()
{
    return 0;
}