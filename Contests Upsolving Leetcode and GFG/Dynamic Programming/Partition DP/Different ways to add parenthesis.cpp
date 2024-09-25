#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
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

static auto init = []
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();

class Solution
{
private:
    /*
Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.

The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.



Example 1:

Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0
(2-(1-1)) = 2

Example 2:

Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34
((2*3)-(4*5)) = -14
((2*(3-4))*5) = -10
(2*((3-4)*5)) = -10
(((2*3)-4)*5) = 10



Constraints:

    1 <= expression.length <= 20
    expression consists of digits and the operator '+', '-', and '*'.
    All the integer values in the input expression are in the range [0, 99].
    The integer values in the input expression do not have a leading '-' or '+' denoting the sign.


     */
public:
    unordered_map<string, vector<int>> memo;
    static const uint32_t MOD = 1e9 + 7;
    static constexpr bool isOperator(char c)
    {
        return c == '+' || c == '-' || c == '*';
    }

    static constexpr int eval(int a, int b, char op)
    {
        switch (op)
        {
        case '+':
            return (a + b);
        case '-':
            return (a - b);
        case '*':
            return (a * b);
        }
        return 0;
    }

    vector<int> solve(string s)
    {
        if (s.length() == 0)
        {
            return {0};
        }
        if (memo.count(s))
        {
            return memo[s];
        }
        vector<int> res;
        for (int i = 0; i < s.length(); i++)
        {
            if (isOperator(s[i]))
            {
                //&- solve for both left side and right side by splitting the string at the operator
                vector<int> left = solve(s.substr(0, i));
                vector<int> right = solve(s.substr(i + 1));

                /* 
                
                &- for each possible combination of left and right, we will push the result in the res vector
                 */
                for (int &x : left)
                {
                    for (int &y : right)
                    {
                        res.push_back(eval(x, y, s[i]));
                    }
                }
            }
        }
        //&- If there are no possible combinations, we will push the result in the res vector because it is a single number
        if (res.empty())
        {
            res.push_back(stoi(s));
        }
        return memo[s] = res;
    }

    vector<int> diffWaysToCompute(string &expression)
    {
        return solve(expression);
    }
};
