#include <bits/stdc++.h>
using namespace std;
#include <bits/stdc++.h>
using namespace std;

/*
  Problem:
  For a sliding window of size k in an array nums,
  find the sum of top x elements based on (frequency * element) in each window.
*/

class Solution
{
    // Count of each element in current window
    map<long long, int> count;

    // Two multisets to maintain top-x elements and the rest
    multiset<pair<long long, int>> top;    // top x elements (largest freq*value)
    multiset<pair<long long, int>> bottom; // remaining elements

    // Running sum of elements in top
    long long topSum = 0;

    // Maintain top multiset to always have exactly x largest elements
    void balance(int x)
    {
        // Move largest from bottom -> top if top has less than x elements
        while (top.size() < x && !bottom.empty())
        {
            auto it = prev(bottom.end()); // largest in bottom
            top.insert(*it);
            topSum += it->first * it->second; // update sum
            bottom.erase(it);
        }

        // Move smallest from top -> bottom if top has more than x elements
        while (top.size() > x)
        {
            auto it = top.begin();            // smallest in top
            topSum -= it->first * it->second; // update sum
            bottom.insert(*it);
            top.erase(it);
        }
    }

    // Add an element into the current window
    void add(int ele, int x)
    {
        long long oldCount = count[ele]++;
        pair<long long, int> oldP = {oldCount, ele};
        pair<long long, int> newP = {oldCount + 1, ele};

        // Remove old pair from top/bottom if present
        if (top.count(oldP))
        {
            top.erase(top.find(oldP));
            topSum -= oldP.first * oldP.second;
        }
        else if (bottom.count(oldP))
        {
            bottom.erase(bottom.find(oldP));
        }

        // Add new pair tentatively to top
        top.insert(newP);
        topSum += newP.first * newP.second;

        // Rebalance multisets to maintain top-x invariant
        balance(x);
    }

    // Remove an element leaving the current window
    void remove(int ele, int x)
    {
        long long oldCount = count[ele]--;
        pair<long long, int> oldP = {oldCount, ele};
        pair<long long, int> newP = {oldCount - 1, ele};

        // Remove old pair from top/bottom
        if (top.count(oldP))
        {
            top.erase(top.find(oldP));
            topSum -= oldP.first * oldP.second;
        }
        else if (bottom.count(oldP))
        {
            bottom.erase(bottom.find(oldP));
        }

        // Insert the updated pair into bottom (rebalance will fix top)
        if (count[ele] > 0)
            bottom.insert(newP);

        balance(x);
    }

public:
    vector<long long> findXSum(vector<int> &nums, int k, int x)
    {
        vector<long long> ans;
        int n = nums.size();

        // Initialize the first k-1 elements (window not full yet)
        for (int i = 0; i < k - 1; ++i)
            add(nums[i], x);

        // Slide the window across the array
        for (int i = k - 1; i < n; ++i)
        {
            add(nums[i], x);            // Add new element to window
            ans.push_back(topSum);      // Store sum of top-x
            remove(nums[i - k + 1], x); // Remove outgoing element
        }

        return ans;
    }
};
int main()
{
    return 0;
}