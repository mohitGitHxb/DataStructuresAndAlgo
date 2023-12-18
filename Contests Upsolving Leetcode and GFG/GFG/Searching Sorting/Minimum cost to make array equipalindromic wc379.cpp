#include <bits/stdc++.h>
#define ll long long

using namespace std;

/*
Approach

    We have to take median first and then check for the nearest possible palindrom of the median

    To find the possible palindrom, nearest to the median there are three cases need to check :
        case 1: simply take the mirror image of the left half
        case 2: take mirror image of the (left half + 1)
        case 3: take mirror image of the (left half - 1)
        You may check this : find-the-closest-palindrome

    finally just check the cost with all three palindrom and then take the minimum cost.

Note : We have to take median not mean. Why so ?

    Lets say the the x is the value we are looking for and we have to take summ of all abs(nums[i] - x) to minimum.
    Now lets assume we have only two numbers [1, 100]. In this case it does not matter what value you choose in between [1, 100], cost will be same for all. But as soon as we add on e more number to it 1 or 100 then the cost will be min depending on what value we add. When we add 1, we have [1,1, 100] => Here the cost of first 1 and the 100 will be still 100 irrespective what value you consider for x, but for the middle 1 we have to add an extra cost of abs(1 - x) to the total cost. And minimise this we should set value of x = 1.

Its worth remembering - when ever you want to equalize values in an array and the absolute value change in each item to make it equal we should consider the median value as the final value.
Complexity

    Time complexity: O(N.logN)
    Space complexity: O(1)

Note : can be optimise further by checking case 1, if it is larger or smaller then midean. If its same then thats the nearest one. If it is higher then only check -1 from left half case. If it is smaller then ceck only the +1 case.
*/



class Solution
{
public:
    bool isPalindrome(string n)
    {
        for (int i = 0; i < n.size() / 2; i++)
            if (n[i] != n[n.size() - 1 - i])
                return false;
        return true;
    }
    ll getCost(vector<int> &nums, ll x)
    {
        ll cost = 0;
        for (int &i : nums)
        {
            cost += abs(i - x);
        }
        return cost;
    }
    long long minimumCost(vector<int> &nums)
    {
        ll ans = 1e15;
        unsigned n = nums.size();
        sort(nums.begin(), nums.end());
        ll median = (n % 2 == 0) ? (nums[n / 2] + nums[n / 2 - 1]) / 2 : nums[n / 2];
        string medianString = to_string(median);
        vector<ll> candidates;
        // get left half of the palindrome
        for (int i = 0; i < medianString.size() / 2; i++)
        {
            medianString[medianString.size() - 1 - i] = medianString[i];
        }
        candidates.emplace_back(stoll(medianString)); // this string is a palindrome
        // get left half + 1 of the palindrome
        string medianStringLeft = to_string(stoll((medianString.substr(0, (medianString.size() + 1) / 2))) + 1LL);
        string medianStringRight = medianStringLeft;
        if (medianString.size() % 2 == 1)
            medianStringRight.pop_back();
        reverse(medianStringRight.begin(), medianStringRight.end());
        string newPlus1String = medianStringLeft + medianStringRight;
        candidates.emplace_back(stoll(newPlus1String));

        // get left half - 1 of the palindrome
        medianStringLeft = to_string(stoll((medianString.substr(0, (medianString.size() - 1) / 2))) - 1LL);
        medianStringRight = medianStringLeft;
        if (medianString.length() % 2 == 1)
            medianStringRight.pop_back();
        reverse(medianStringRight.begin(), medianStringRight.end());
        string newMinus1String = medianStringLeft + medianStringRight;
        candidates.emplace_back(stoll(newMinus1String));

        // check for all the valid candidates;
        for (ll num : candidates)
        {
            ll sum = getCost(nums, num);
            ans = min(sum, ans);
        }
        return ans;
    }
};
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