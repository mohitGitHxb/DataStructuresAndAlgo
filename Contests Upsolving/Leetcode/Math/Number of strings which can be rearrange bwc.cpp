#include <bits/stdc++.h>
using namespace std;

/* Intuition

Happy Diwali!!
I'll be sharing my though process during contest.

As we can see that we need atleast 1 L, 1 T and 2 E somewhere in our string. They need not be present in order as it can be rearranged afterwards. Hence, out of nnn letters, 444 are fixed and for the rest of n−4n-4n−4 letters we have to make permutations and combinations.

Out of those n−4n-4n−4 letters, suppose we take

a = x1 times
b = x2 times
.
.
z = x26 times

Constraint that x1 + x2 + ... + x26 = n - 4
0 <= x1, x2, ..., x26 <= n - 4

Therefore, in total we have

a = x1 times
b = x2 times
.
.
e = x5 + 2 times
.
.
l = x12 + 1 times
.
.
t = x20 + 1 times
.
.
z = x26 times

Number of ways to arrange these letters on nnn indices is given by:

n!x1!x2!...(x5+2)!...(x12+1)!...(x20+1)!...x26!\displaystyle\frac{n!}{x_{1}!x_{2}!...(x_{5}+2)!...(x_{12}+1)!...(x_{20}+1)!...x_{26}!}x1​!x2​!...(x5​+2)!...(x12​+1)!...(x20​+1)!...x26​!n!​

And, ofcourse we can precompute factorials, mod inverse factorials. But the problem is we have to try all possible combinations of variables (x1,x2,...,x26)(x_1,x_2,...,x_{26})(x1​,x2​,...,x26​).

It is not feasible to do it the forward way. Hence, start thinking backwards.
What are the total number of strings regardless good or bad? Since, every index has 262626 choices, it is 26n26^n26n.
What if we somehow calculate number of bad strings and subtract the answer from it to get good strings?

What makes a string bad?

C1 = 0 L (no L present in whole string)
C2 = 0 T (no T present in whole string)
C3 = 0 E (no E present in whole string)
C4 = 1 E (only 1 E present in whole string)

These 4 cases (C1,C2,C3,C4)(C_1, C_2, C_3, C_4)(C1​,C2​,C3​,C4​) make a string bad, or a combination of them.
This gives the intuition of Inclusion Exclusion Principle.

Count of bad strings can be written as

singletons−pairs+triplets−quadruplessingletons - pairs + triplets - quadruplessingletons−pairs+triplets−quadruples

=⋃i∣Ci∣−⋃i,j∣Ci∩Cj∣+⋃i,j,k∣Ci∩Cj∩Ck∣−⋃i,j,k,l∣Ci∩Cj∩Ck∩Cl∣= \bigcup_{i} |C_i| - \bigcup_{i,j} |C_i \cap C_j| + \bigcup_{i,j,k} |C_i \cap C_j \cap C_k| - \bigcup_{i,j,k,l} |C_i \cap C_j \cap C_k \cap C_l| =⋃i​∣Ci​∣−⋃i,j​∣Ci​∩Cj​∣+⋃i,j,k​∣Ci​∩Cj​∩Ck​∣−⋃i,j,k,l​∣Ci​∩Cj​∩Ck​∩Cl​∣

Expanding, it can be written as
+(∣C1∣+∣C2∣+∣C3∣+∣C4∣)+(|C_1| + |C_2| + |C_3| + |C_4|)+(∣C1​∣+∣C2​∣+∣C3​∣+∣C4​∣)

−(∣C1∩C2∣+∣C1∩C3∣+∣C1∩C4∣+∣C2∩C3∣+∣C2∩C4∣+∣C3∩C4∣)-(|C_1 \cap C_2| + |C_1 \cap C_3| + |C_1 \cap C_4| + |C_2 \cap C_3| + |C_2 \cap C_4| + |C_3 \cap C_4|)−(∣C1​∩C2​∣+∣C1​∩C3​∣+∣C1​∩C4​∣+∣C2​∩C3​∣+∣C2​∩C4​∣+∣C3​∩C4​∣)

+(∣C1∩C2∩C3∣+∣C1∩C2∩C4∣+∣C1∩C3∩C4∣+∣C2∩C3∩C4∣)+(|C_1 \cap C_2 \cap C_3| + |C_1 \cap C_2 \cap C_4| + |C_1 \cap C_3 \cap C_4| + |C_2 \cap C_3 \cap C_4|)+(∣C1​∩C2​∩C3​∣+∣C1​∩C2​∩C4​∣+∣C1​∩C3​∩C4​∣+∣C2​∩C3​∩C4​∣)

−(∣C1∩C2∩C3∩C4∣)-(|C_1 \cap C_2 \cap C_3 \cap C_4|)−(∣C1​∩C2​∩C3​∩C4​∣)

Now,

    C3∩C4=ϕC_3 \cap C_4 = \phiC3​∩C4​=ϕ (a string can't have 0 E and 1 E simultaneously)
    ∣C1∣|C_1|∣C1​∣ can be calculated as the number of ways to form string with 0 L. Means we have 252525 choices for all nnn letters. ∣C1∣=25n|C_1|=25^n∣C1​∣=25n.
    ∣C4∣|C_4|∣C4​∣ can be calculated as the number of ways to form string with 1 E. First select 111 position out of nnn indices on which E should be placed (nC1{}^nC_1nC1​ choices). Then for remaining n−1n-1n−1 letters we have 25n−125^{n-1}25n−1 choices. ∣C4∣=nC1.25n−1|C_4| = {}^nC_1.25^{n-1}∣C4​∣=nC1​.25n−1.

Similarly, calculate other values.

Number of bad strings will be
+(25n+25n+25n+nC1.25n−1)+(25^n + 25^n + 25^n + {}^nC_1.25^{n-1})+(25n+25n+25n+nC1​.25n−1)

−(24n+24n+nC1.24n−1+24n+nC1.24n−1+0)-(24^n + 24^n + {}^nC_1.24^{n-1} + 24^n + {}^nC_1.24^{n-1} + 0)−(24n+24n+nC1​.24n−1+24n+nC1​.24n−1+0)

+(23n+nC1.23n−1+0+0)+(23^n + {}^nC_1.23^{n-1} + 0 + 0)+(23n+nC1​.23n−1+0+0)

−(0)-(0)−(0)

=(n+75).25n−1−(2n+72).24n−1+(n+23).23n−1=(n+75).25^{n-1} - (2n+72).24^{n-1} + (n+23).23^{n-1}=(n+75).25n−1−(2n+72).24n−1+(n+23).23n−1

Number of good strings will be
26n−(n+75).25n−1+(2n+72).24n−1−(n+23).23n−126^n - (n+75).25^{n-1} + (2n+72).24^{n-1} - (n+23).23^{n-1}26n−(n+75).25n−1+(2n+72).24n−1−(n+23).23n−1
Approach

Modulo Arithmetic and Binary Exponentiation
We need a function to calculate power with modulo. Library functions can't be used (in most of the langugages) because powers can be much larger than the numbers stored in intintint data type. We need to handle overflow while calculating power using the fact:

(a∗b)mod  m=((amod  m)∗(bmod  m))mod  m(a * b) \mod m = ((a \mod m) * (b \mod m)) \mod m(a∗b)modm=((amodm)∗(bmodm))modm

And power can be calculated as
xnmod  m=((xmod  m)∗(xmod  m)∗...ntimes...∗(xmod  m))mod  mx^n \mod m = ((x \mod m) * (x \mod m) * ... n \enspace times ... * (x \mod m)) \mod mxnmodm=((xmodm)∗(xmodm)∗...ntimes...∗(xmodm))modm
xnmod  m=((xn−1mod  m)∗(xmod  m))mod  mx^n \mod m = ((x^{n-1} \mod m) * (x \mod m)) \mod mxnmodm=((xn−1modm)∗(xmodm))modm

pow(x, n, mod)
    result = 1
    for i = 1 to n:
        result = (result * x) % mod
    return result

Time complexity of this approach would be O(n)O(n)O(n). But, there is another method to calculate powers using binary exponentiation with time O(log⁡n)O(\log n)O(logn).

Taking an example, calculate 211mod  10002^{11} \mod 1000211mod1000:

    Convert exponent in binary form (11)10=(1011)2(11)_{10}=(1011)_2(11)10​=(1011)2​.
    Result can be written as
    21011=223+21+20=223.221.2202^{1011}=2^{2^3 + 2^1 + 2^0}=2^{2^3}.2^{2^1}.2^{2^0}21011=223+21+20=223.221.220
    In below program, we maintain variable ppp having value of 22bmod  m2^{2^b} \mod m22bmodm.
    22b+1mod  m2^{2^{b+1}} \mod m22b+1modm can be calculated by squaring ppp.
    22b+1mod  m=(22bmod  m)2mod  m2^{2^{b+1}} \mod m = (2^{2^b} \mod m)^2 \mod m22b+1modm=(22bmodm)2modm
    Traversing on the exponent bit by bit, whenever the Least Signifacnt Bit is 111, we multiply this value of ppp to the resultresultresult. */

class Solution
{
private:
    long pow(long x, long n, long mod)
    {
        long result = 1, p = x % mod;
        while (n)
        {
            if (n & 1)
            {
                result = (result * p) % mod;
            }
            p = (p * p) % mod;
            n >>= 1;
        }
        return result;
    }

public:
    int stringCount(int n)
    {
        long mod = 1e9 + 7;
        return ((
                    +pow(26, n, mod) - (n + 75) * pow(25, n - 1, mod) + (2 * n + 72) * pow(24, n - 1, mod) - (n + 23) * pow(23, n - 1, mod)) %
                    mod +
                mod) %
               mod;
    }
};

/* Complexity

    Time complexity: O(log⁡n)O(\log n)O(logn)
    Space complexity: O(1)O(1)O(1)

    Another way to think from the factorial formula.

Number of ways to arrange these letters on nnn indices is given by:

n!x1!x2!...(x5+2)!...(x12+1)!...(x20+1)!...x26!\displaystyle\frac{n!}{x_{1}!x_{2}!...(x_{5}+2)!...(x_{12}+1)!...(x_{20}+1)!...x_{26}!}x1​!x2​!...(x5​+2)!...(x12​+1)!...(x20​+1)!...x26​!n!​

Iterating over all possible values of (x1,x2,...x26)(x_1,x_2,...x_{26})(x1​,x2​,...x26​) where each one of them will have a loop for 000 to n−4n-4n−4. That's 26 nested loops (or 25 if you use x26=n−4−(x1+x2+...+x25)x_{26} =n-4-(x_1+x_2+...+x_{25})x26​=n−4−(x1​+x2​+...+x25​)) having times complexity n26n^{26}n26.

Mathematically it will work too and give correct answer.

This summation of all terms can be reduced to single formula using multinomial theorem.
The factorial term is just the coefficient of term ax1...zx26a^{x_1}...z^{x_{26}}ax1​...zx26​ in the expansion of (a+b+...z)n(a+b+...z)^n(a+b+...z)n. Sum of all these coefficients can be calculated by putting a=b=...=z=1a=b=...=z=1a=b=...=z=1 which comes out to be 26n26^n26n.

But if we want sum of good coefficients only, then either we calculate them using loops or we calculate it by first calculating bad coefficients. Now this will be dependent on question, which one will be easier to calculate. */

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