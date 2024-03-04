#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/* 
& Applying Simple floyd warshall algorithm O(N^3),
& Can use BFS to lower time complexity to O(N^2)

 */
class BruteForce
{
public:
    vector<long long> countOfPairs(int n, int x, int y)
    {
        vector<vector<int>> graph(n + 1);
        for (int i = 1; i < n; i++)
        {
            graph[i].push_back(i + 1);
            graph[i + 1].push_back(i);
        }
        graph[x].push_back(y);
        graph[y].push_back(x);

        vector<long long> ans(n, 0);
        for (int i = 1; i <= n; i++)
        {
            vector<int> dist(n + 1, n + 1);
            dist[i] = 0;
            queue<int> q;
            q.push(i);
            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                for (int next : graph[node])
                {
                    if (dist[next] == n + 1)
                    {
                        dist[next] = dist[node] + 1;
                        q.push(next);
                    }
                }
            }
            for (int j = i + 1; j <= n; j++)
            {
                ans[dist[j] - 1]++;
            }
        }

        for (auto &i : ans)
            i *= 2;
        return ans;
    }
};

//^ Maths, Line Sweep method O(N) T.C
/*
Intuition

Understanding the problem, we can conclude that there will be one cycle. If the cycle was not there, we can solve the problem easily with a formula, but cycle will affect distance between many pair of house. Lets divide the problem in subproblems and solve them individually, eventually merge them.
Approach

We will divide the houses into three groups (let xxx < yyy):

    GroupCycleGroup CycleGroupCycle: the houses between xxx and yyy
    GroupLeftGroup LeftGroupLeft: the houses before house xxx
    GroupRightGroup RightGroupRight: the houses after house yyy

Now, our problem reduces to calculate distances between:

    T1T1T1 - All pairs in GroupCycleGroupCycleGroupCycle
    T2T2T2 - All pairs in GroupLeftGroupLeftGroupLeft
    T3T3T3 - All pairs in GroupRightGroupRightGroupRight
    T4T4T4 - All house in GroupLeftGroupLeftGroupLeft to all houses in GroupCycleGroupCycleGroupCycle
    T5T5T5 - All house in GroupRightGroupRightGroupRight to all houses in GroupCycleGroupCycleGroupCycle
    T6T6T6 - All house in GroupLeftGroupLeftGroupLeft to all houses in GroupRightGroupRightGroupRight

At the end, we will multiply the answer with 222, as the a pair will contribute to our final answer two times, one with being (house1,house2)(house1, house2)(house1,house2) and other with (house2,house1)(house2, house1)(house2,house1).
Calculating answer for a Straight Line

GroupLeftGroupLeftGroupLeft and GroupRightGroupRightGroupRight can be considered as a straight line. It can be observed that if number of houses in the line (length of the line) is LLL, then pairs with:

    length iii will be L−iL - iL−i

So, contributions of T2T2T2 and T3T3T3 can be easily calculated by this observation.
Calculating answer for a Cycle

GroupCycleGroupCycleGroupCycle is a cycle. Lets see how will we calculate answer for it. Let say number of houses in cycle (length of cycle) is LLL. The observation for a cycle is:

    A pair of house having distance iii will also have a path of streets with distance L−iL - iL−i. As we need to take the minimum distance between houses, we will take the smaller one. This indicates that we don't need to find pairs with distance greater than LLL / 222.

Now we can easily derive the formula from observation for few smaller values of LLL.

    LLL is odd

        Pairs with distance ddd (ddd <= LLL / 222) will be LLL. Yes, you read it right, all the distances will apprear exactly LLL times.

    LLL is even

        Pairs with distance ddd (ddd < LLL / 222) will be LLL.
        Pairs with distance ddd (ddd = LLL / 222) will be LLL / 222.
        Because the pair will repeat here. We will multiple whole answer by two at the end, so no need to count two times here.

So, these observations will help to find answer contribution of T1T1T1.
Calculating answer for a Straight Line and a Cycle

Here we will see how to calculate answer for T4T4T4 and T5T5T5. We will use a concept of Line Sweep to calculate our answers in this section. Considering length of line to be LLL and length of cycle to be CCC. Let say the point of contact between Stright line and Cycle is xxx.

Key Observations are :

        For each house in Straight Line we will calculate number of pairs with other house in cycle.
        222 house in cycle will give same length for a house in line, as we can go either way from xxx in the cycle.

    For each house in the line with distance ddd to xxx:

        Minimum contribution to answer, MNMNMN: ddd
        Maximum contribution to answer, MXMXMX: ddd + CCC / 222

We will add contribution of 222 for each length above. We can use line sweep from MNMNMN to MXMXMX and calculate the contributions for each house in Stright Line.

NOTE: When CCC is even, we need to add its contribution as 111 for the house at maximum distance in cycle. As no other house in cycle will have same distance as this house.

So, contributions of T4T4T4 and T5T5T5 can be easily calculated by this observation.
Calculating answer for Two Stright Lines

Here we will see how to calculate the contribution of pairs with all house in GroupLeftGroupLeftGroupLeft to all houses in GroupRightGroupRightGroupRight. Again, we will use the concept of Line Sweep to solve this sub problem. Let say the lines are L1L1L1 and L2L2L2.

For each house in L1L1L1 we will see its contribution to the answer:

        MNMNMN: pair with minimum distance having this house from L1L1L1.
        MXMXMX: pair with maximum distance having this house from L1L1L1.

We can use line sweep from MNMNMN to MXMXMX and calculate the contributions for each pair. So, this gives us the contribution of T6T6T6.
Calculating final answer

We will just add contributions of T1T1T1, T2T2T2, T3T3T3, T4T4T4, T5T5T5 and T6T6T6. Don't forget to multiply final answer by 222.
Complexity

    Time complexity: O(n)O(n)O(n)

    Upvote if you find the solution easy to understand!
    Suggestions and improvements are appreciated.


 */
class Solution
{
public:
    vector<ll> lineAndCycle(ll n, ll lineLen, ll cycleLen)
    {
        vector<ll> res(n);

        for (ll d = 1; d <= lineLen; d++)
        {
            ll mn = d + 1;
            ll mx = d + (cycleLen / 2);
            res[mn - 1] += 2;
            res[mx - 1] -= 2;
        }

        ll mn = cycleLen / 2 + 1;
        ll mx = cycleLen / 2 + lineLen;

        ll add = (cycleLen & 1 ? 2 : 1);

        res[mn - 1] += add;
        if (mx < n)
            res[mx] -= add;

        for (ll i = 1; i < n; i++)
            res[i] += res[i - 1];

        for (ll len = 1; len <= lineLen; len++)
            res[len - 1]++;

        return res;
    }

    vector<ll> lineAnswer(ll n, ll lineLen)
    {
        vector<ll> res(n);

        for (ll len = 1, add = lineLen - 1; len < lineLen; len++, add--)
            res[len - 1] += add;

        return res;
    }

    vector<ll> cycleAnswer(ll n, ll cycleLen)
    {
        vector<ll> res(n);

        for (ll len = 1; len < cycleLen / 2; len++)
            res[len - 1] += cycleLen;

        if (cycleLen & 1)
        {
            int len = cycleLen / 2;
            if (len - 1 >= 0)
                res[len - 1] += cycleLen;
        }
        else
        {
            int len = cycleLen / 2;
            if (len - 1 >= 0)
                res[len - 1] += (cycleLen / 2);
        }

        return res;
    }

    vector<ll> twoLineAnswer(ll n, ll lineLen1, ll lineLen2, ll x, ll y)
    {
        vector<ll> res(n);

        if (lineLen1 > lineLen2)
            swap(lineLen1, lineLen2);
        ll plus = (x != y ? 1 : 0);

        for (ll i = 0; i < lineLen1; i++)
        {
            ll mn = i + plus + 2;
            ll mx = i + plus + 1 + lineLen2;

            res[mn - 1]++;
            if (mx < n)
                res[mx]--;
        }

        for (int i = 1; i < n; i++)
            res[i] += res[i - 1];

        return res;
    }

    vector<long long> countOfPairs(int n, int x, int y)
    {
        vector<ll> res(n);
        if (x > y)
            swap(x, y);

        ll lineLen1 = x - 1;
        ll lineLen2 = n - y;
        ll cycleLen = y - x + 1;
        ll finalLen = lineLen1 + lineLen2 + 2;

        auto line1ans = lineAnswer(n, lineLen1);
        auto line2ans = lineAnswer(n, lineLen2);
        auto cycleAns = cycleAnswer(n, cycleLen);
        auto l1c = lineAndCycle(n, lineLen1, cycleLen);
        auto l2c = lineAndCycle(n, lineLen2, cycleLen);
        auto l1l2 = twoLineAnswer(n, lineLen1, lineLen2, x, y);

        for (int i = 0; i < n; i++)
        {
            res[i] += line1ans[i];
            res[i] += line2ans[i];
            res[i] += cycleAns[i];
            res[i] += l1c[i];
            res[i] += l2c[i];
            res[i] += l1l2[i];
            res[i] *= 2;
        }

        return res;
    }
};
int main()
{
    return 0;
}