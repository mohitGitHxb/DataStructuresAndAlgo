#include <bits/stdc++.h>
using namespace std;

int maximumSetSize(vector<int> &nums1, vector<int> &nums2)
{
    // Create two sets from the input arrays to remove duplicates
    unordered_set<int> set1(nums1.begin(), nums1.end()), set2(nums2.begin(), nums2.end());

    // Get the size of the input arrays
    int n = nums1.size();

    // Calculate the number of elements to take from each set
    // We can't take more than n/2 elements from each set
    // If a set has less than n/2 elements, we take all of them
    int take_from_set1 = min((int)set1.size(), n / 2);
    int take_from_set2 = min((int)set2.size(), n / 2);

    // Merge the two sets into one
    // This will remove any duplicates between the two sets
    set1.insert(set2.begin(), set2.end());

    // The maximum possible size of the set is the sum of the elements we can take from each set
    // However, we can't have more elements than the total number of unique elements in the two sets
    // So we return the minimum of these two values
    return min((int)set1.size(), take_from_set1 + take_from_set2);
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