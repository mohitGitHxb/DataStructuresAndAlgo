#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    void assignKey(pair<int, char> top, unordered_map<char, int> &keyPressCount, int iteration)
    {
        if (iteration <= 8)
        {
            keyPressCount[top.second] = 1;
        }
        else if (iteration > 8 && iteration <= 16)
        {
            keyPressCount[top.second] = 2;
        }
        else if (iteration > 16 && iteration <= 24)
        {
            keyPressCount[top.second] = 3;
        }
        else
        {
            keyPressCount[top.second] = 4;
        }
    }
    int minimumPushes(string word)
    {
        // Create a map to store the frequency of each character in the word
        unordered_map<char, int> charFrequency;
        // Create a map to store the key press count for each character
        unordered_map<char, int> keyPressCount;
        // Create a priority queue to store characters with their frequencies in descending order
        priority_queue<pair<int, char>> charFrequencyPQ;

        // Count the frequency of each character in the word
        for (char c : word)
        {
            charFrequency[c]++;
        }

        // Push the characters and their frequencies into the priority queue
        for (auto &entry : charFrequency)
        {
            charFrequencyPQ.push({entry.second, entry.first});
        }

        // Iterate through the priority queue and assign key press count for each character
        int iteration = 1;
        while (!charFrequencyPQ.empty())
        {
            auto top = charFrequencyPQ.top();
            charFrequencyPQ.pop();
            assignKeyPress(top, keyPressCount, iteration);
            iteration++;
        }

        // Calculate the total key presses required for the word
        int totalKeyPresses = 0;
        for (char c : word)
        {
            totalKeyPresses += keyPressCount[c];
        }
        return totalKeyPresses;
    }
};
int main()
{
    return 0;
}