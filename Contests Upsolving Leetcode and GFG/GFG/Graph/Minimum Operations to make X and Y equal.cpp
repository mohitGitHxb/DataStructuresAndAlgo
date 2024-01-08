#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    /*

    You are given two positive integers x and y.

    In one operation, you can do one of the four following operations:

        Divide x by 11 if x is a multiple of 11.
        Divide x by 5 if x is a multiple of 5.
        Decrement x by 1.
        Increment x by 1.

    Return the minimum number of operations required to make x and y equal.



    Example 1:

    Input: x = 26, y = 1
    Output: 3
    Explanation: We can make 26 equal to 1 by applying the following operations:
    1. Decrement x by 1
    2. Divide x by 5
    3. Divide x by 5
    It can be shown that 3 is the minimum number of operations required to make 26 equal to 1.

     */
public:
    // This function calculates the minimum number of operations required to make two numbers equal.
    // The function takes two integers x and y as input and returns the minimum number of operations.
    // The operations allowed are:
    // 1. Divide x by 11 if it is divisible, and add 1 to the number of steps.
    // 2. Divide x by 5 if it is divisible, and add 1 to the number of steps.
    // 3. Subtract 1 from x, and add 1 to the number of steps.
    // 4. Add 1 to x, and add 1 to the number of steps.
    int minimumOperationsToMakeEqual(int x, int y)
    {
        // Create a queue to perform breadth-first search.
        queue<pair<int, int>> q;

        // Create a set to keep track of visited numbers.
        unordered_set<int> visited;

        // Push the initial number x to the queue with 0 steps.
        q.push({x, 0});

        // Mark x as visited.
        visited.insert(x);

        // Perform breadth-first search until the queue is empty.
        while (!q.empty())
        {
            // Get the current number and the number of steps from the front of the queue.
            int current = q.front().first;
            int steps = q.front().second;
            q.pop();

            // If the current number is equal to y, return the number of steps.
            if (current == y)
            {
                return steps;
            }

            // Check if the current number is divisible by 11 and not visited.
            // If so, push the number divided by 11 to the queue with 1 more step and mark it as visited.
            if (current % 11 == 0 && visited.find(current / 11) == visited.end() && current > y)
            {
                q.push({current / 11, steps + 1});
                visited.insert(current / 11);
            }

            // Check if the current number is divisible by 5 and not visited.
            // If so, push the number divided by 5 to the queue with 1 more step and mark it as visited.
            if (current % 5 == 0 && visited.find(current / 5) == visited.end() && current > y)
            {
                q.push({current / 5, steps + 1});
                visited.insert(current / 5);
            }

            // Check if the current number minus 1 is not visited.
            // If so, push the number minus 1 to the queue with 1 more step and mark it as visited.
            if (visited.find(current - 1) == visited.end() && current > y)
            {
                q.push({current - 1, steps + 1});
                visited.insert(current - 1);
            }

            // Check if the current number plus 1 is not visited.
            // If so, push the number plus 1 to the queue with 1 more step and mark it as visited.
            if (visited.find(current + 1) == visited.end())
            {
                q.push({current + 1, steps + 1});
                visited.insert(current + 1);
            }
        }

        // If no path is found, return -1.
        return -1;
    }
};

int main()
{

    return 0;
}