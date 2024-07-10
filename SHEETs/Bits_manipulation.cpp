#include <bits/stdc++.h>
using namespace std;

void printBinaryDigits(int n)
{
    cout << "binary of " << n << ": ";
    for (int i = 10; i >= 0; i--)
    {
        cout << ((n >> i) & 1);
    }
    cout << "\n";
}

//^ 1 Odd Even check for a number
void checkNumber(int n)
{
    if (n & 1)
    {
        cout << "odd number\n";
    }
    else
    {
        cout << "even number\n";
    }
}

/*
 % Random Tricks and tips
 ?  (n >> i) is equivalent to n / 2^i
 ?  (n << i) is equivalent to n * 2^i

 ?  lower case letter -> upper case letter (unset 5th bit or take OR with " " space)
 ?  upper case letter -> lower case letter (set 5th bit or just take AND with "_")

 ? n & (n - 1) to check whether a number is a power of two (n&(n-1) == 0 means it is a power of 2 )

 ? Swap elements using XoR operations a -> a ^ b then b = b ^ a finally a -> a ^ b;

 CF blog : https://codeforces.com/blog/entry/73558
 */

//^ 2 clear bits till ith LSB
void clearTillIthLSB(int n, int i)
{
    int newNumber = (n & (~((1 << (i + 1)) - 1)));
    int setAllBitsTillMSB = (n & ((1 << (i + 1))) - 1);
    printBinaryDigits(newNumber);
}

//^ 3 Find intersection of two arrays in O(1) [0 TO 31]
//& can go upto 0 to 64
vector<int> findIntersection(vector<int> &arr1, vector<int> &arr2)
{

    // Initialize bitmasks for both arrays
    int bitmask1 = 0, bitmask2 = 0;

    // Iterate over the first array
    for (int num : arr1)
    {
        // Set the bit at the position corresponding to the current number
        bitmask1 |= (1 << num);
    }

    // Iterate over the second array
    for (int num : arr2)
    {
        // Set the bit at the position corresponding to the current number
        bitmask2 |= (1 << num);
    }

    // The intersection of the two arrays is represented by the bits that are set in both bitmasks
    // We can find this by performing a bitwise AND operation
    int intersection = bitmask1 & bitmask2;

    // Convert the intersection bitmask to a vector
    vector<int> result;
    for (int i = 0; i < 32; i++)
    {
        // If the bit at the current position is set, add the corresponding number to the result
        if (intersection & (1 << i))
        {
            result.push_back(i);
        }
    }

    return result;
}

//^ 4 Generate all subsets of an array [Power Set]
vector<vector<int>> subsets(vector<int> &nums)
{
    // Calculate the total number of subsets
    int totalSubsets = pow(2, nums.size());

    // Create a vector to store all the subsets
    vector<vector<int>> ans;

    // Iterate through all possible subsets
    for (int mask = 0; mask < totalSubsets; mask++)
    {
        // Create a temporary vector to store the current subset
        vector<int> temp;

        // Iterate through the elements of the input array
        for (int idx = 0; idx < nums.size(); idx++)
        {
            // Check if the current element is included in the subset
            if (mask & (1 << idx))
            {
                // Add the current element to the subset
                temp.emplace_back(nums.at(idx));
            }
        }

        // Add the current subset to the vector of subsets
        ans.emplace_back(temp);
    }

    // Return the vector of subsets
    return ans;
}

//^ 5 Count total set bits from 1 to n
int countSetBits(int n)
{
    // Time complexity: O(log N) because we are reducing the problem size approximately by half in each recursive call.
    // Space complexity: O(log N) because of the recursive call stack.
    // If n is less than or equal to 1, return n
    if (n <= 1)
        return n;

    // Find the closest power of 2 less than or equal to n
    int closestPowerOf2 = log2(n);

    // Calculate the value of x as 2 raised to the power of closestPowerOf2
    int x = 1 << closestPowerOf2;

    // Calculate the value of y as 2 raised to the power of (closestPowerOf2 - 1)
    int y = 1 << (closestPowerOf2 - 1);

    // Calculate the total number of set bits from 1 to n
    int totalBits = (y * closestPowerOf2) + (n - x + 1) + countSetBits(n - x);

    // Return the total number of set bits
    return totalBits;
}

//^ 6 Number of bits to flip to convert A to B
int countBitsFlip(int a, int b)
{

    // Your logic here
    bitset<32> a1(a), b1(b);
    int counter = 0;
    for (int i = 0; i < 32; i++)
    {
        if (a1[i] != b1[i])
            counter++;
    }
    return counter;

    // or
    /*
    Take the xor of a and b which gives only different bits as a set bit.
    Now call the function __builtin_popcount to count the number of set bit.
    Return the count of setBit.
    return __builtin_popcount(a^b)
    */
}
/*
^ 7 Single element occurring once

To use this approach you first need to understand about Bitwise XOR operator.
Most of us who have a background in physics ( highschool level ) , are aware of the LOGIC GATES.
One of such gates is the XOR Gate :
According to this gate , the output is true , only if both the inputs are of opposite kind .
That is ,
A B Y
0 0 0
0 1 1
1 0 1
1 1 0

We apply the extended version of this gate in our bitwise XOR operator.
If we do "a^b" , it means that we are applying the XOR gate on the 2 numbers in a bitwise fashion ( on each of the corresponding bits of the numbers).
Similarly , if we observe ,

    A^A=0
    A^B^A=B
    (A^A^B) = (B^A^A) = (A^B^A) = B This shows that position doesn't matter.
    Similarly , if we see , a^a^a......... (even times)=0 and a^a^a........(odd times)=a

Google It for more details.

We apply the above observations :

    Traverse the array and take the Bitwise XOR of each element.
    Return the value.

Why does this work ??
Because , the elements with frequency=2 will result in 0. And then the only element with frequency=1 will generate the answer.
TC: O(N)
SC: O(1)
CODE : */

class SingleElement
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ans = 0;
        for (auto x : nums)
            ans ^= x;
        return ans;

        //& one liner
        //* return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
    }
};

//^ 8 Find XOR from L to R
class FindXORLR
{
public:
    // Function to compute XOR from 1 to n.
    int computeXOR(int n)
    {
        // XOR of all numbers from 1 to n can be evaluated with the help of the following observations:
        // If n mod 4 equals 0, then XOR will be same as n.
        // If n mod 4 equals 1, then XOR will be 1.
        // If n mod 4 equals 2, then XOR will be n+1.
        // If n mod 4 equals 3, then XOR will be 0.
        // For example, if n = 6, then n mod 4 = 2, so XOR of all numbers from 1 to 6 will be 6+1 = 7.
        if (n % 4 == 0)
            return n;
        if (n % 4 == 1)
            return 1;
        if (n % 4 == 2)
            return n + 1;
        return 0;
    }

    // Function to compute XOR of all numbers in range [L, R].
    int rangeXOR(int L, int R)
    {
        // XOR of a range can be computed with the help of the following observations:
        // XOR of all numbers from 1 to R XOR XOR of all numbers from 1 to L-1 gives XOR of all numbers in range L to R.
        // For example, if L = 3 and R = 6, then XOR of all numbers from 3 to 6 will be XOR(1 to 6) XOR XOR(1 to 2) = 7 XOR 1 = 6.
        return computeXOR(L - 1) ^ computeXOR(R);
    }
};

//^ 9 Two odd occuring numbers in an array
/*
Intuition

Idea is to use the property of XOR.
1) XOR of any number n with itself gives us 0, i.e., n ^ n = 0
2) XOR of any number n with 0 gives us n, i.e., n ^ 0 = n
3) XOR is cumulative and associative.

Let the two odd occurring numbers be x and y. We use bitwise XOR to get x and y. We try to make 2 groups such that x and y go to different groups. E.g. [a, a, b, b, x], . Then the problem will become “Find ‘one’ number with odd occurrence in an unsorted array”, which becomes a simple problem and will be solved using XOR. Below are steps to group x and y differently.

Step 1: calculate xor of all the elements.

So we have XOR of x and y after the first step, in decimal form. E.g. 5 ^ 6 returns 3, which is computed in bit form as 101 ^ 110 = 011. Let the ‘value’ of XOR be xor2. Every Set bit** in xor2 indicates that ‘the corresponding bits in x and y have values different from each other’ (XOR property- ‘1 when bits are different’). ** ( Set-bits are 1’s in binary form. E.g. 101 has 2 set bits(1’s), at 0th index and at 2nd index. )
For example, if x = 6 (0110) and y = 15 (1111), then xor2 will be (1001), the two set bits in xor2 indicate that the corresponding bits in x and y are different, at 0th index and at 3rd index both.

Step 2: we pick a set bit of xor2.

Idea is to use the fact that xor2 is ‘1’ in indexes where bits of x and y are different. So we separate x and y to different groups, along with rest of the numbers of list, based on whether the number has same set-bit or not.
    We choose the rightmost set bit of xor2 as it is easy to get rightmost set bit of a number (bit magic). If we bitwise AND a number with its negative counterpart, we get rightmost set bit. (just an observation based property, do remember). So, (xor2) & (-xor2) will give us right set bit. Find (-number) by 2’s complement, that is ((1’s complement) +1 ). It can also be written as (~number)+1.

Step 3: we separate x and y in different groups

We now know that for selected set bit index, x and y have different corresponding bits. If we AND all numbers in list with set bit, some will give 0 and others will give 1. We will put all numbers giving zeroes in one group and ones in another. x and y will fall in different groups.
Implementation

Explanation of approach with help of an example:

E.g. arr = [4, 2, 4, 10, 2, 3, 3, 12] ,
& -Step 1) XOR of all in arr will cancel all repeating nos. 10 ^12 will be ans. 1010 ^ 1100 will be 0110 that is xor=6.
& -Step 2) Set bit is 10 from 0110 from visualization. (number) & (-number) is also a quick way to find right set bit.
xor & (-xor) can be coded directly. 6 is 0110 and finding -6 by flipping digits and adding 1, 1001 +1 = 1010.
So 6 AND -6 is essentially 0110 & 1010, that is 0010 i.e. 2 – Set-bit Number.
& -Step 3) AND of all in list with 2 (Set bit no.) will give us numbers that give either 1 or 0, and we make groups.
[4, 4, 12] and [2, 10, 2, 3, 3], giving 0 and 1 respectively on AND with Set-bit number.
Step 4) XOR of 1st group will give us x=12, and the 2nd group will give us y=10. We can calculate y by doing this. x ^ y is known from 1st step i.e. 6. x ^(x ^y) will give us y. 12 ^6 is 10.

x=12, y=10
This step works because of the same properties of XOR. All the occurrences of a number will go in same set. XOR of all occurrences of a number which occur even number of times will result in 0 in its set. And the xor of a set will be one of the odd occurring elements.
Complexity

Time Complexity:  As we are running two loop of size n, so the time complexity is O(n), n is size of the array.
Space Complexity: As we are using only two variable of type int, so the space complexity is O(1).

 */

vector<long long int> twoOddNum(long long int Arr[], long long int N)
{
    long long int xorSum = accumulate(Arr, Arr + N, 0, bit_xor<long long int>());

    long long int setBit = xorSum & ~(xorSum - 1);
    // deb(setBit);

    long long int x = 0, y = 0;
    for (long long int i = 0; i < N; i++)
    {
        if (Arr[i] & setBit)
        {
            x = x ^ Arr[i];
        }
        else
        {
            y = y ^ Arr[i];
        }
        // cout << x << " " << y << "\n";
    }
    vector<long long int> ans(2);
    ans[0] = max(x, y);
    ans[1] = min(x, y);
    return ans;
}

class Questions
{
private:
public:
    //^ Monk and his father
    long solve(long initial, long target)
    {
        bitset<32> b1(target);
        return b1.count();
    }
    void getMaximumXOR(long n)
    {
        // Convert n to binary representation
        bitset<16> b1(n);

        long x = 0, y = 0;
        vector<long> set_bits;

        // Iterate over each bit of n
        for (int i = 0; i < 16; i++)
        {
            if (b1[i])
            {
                // If bit is set, add it to the set_bits vector
                set_bits.push_back(i);
            }
            else
            {
                // If bit is not set, set the corresponding bits of x and y to 1
                x |= (1 << i);
                y |= (1 << i);
            }
        }

        long ans = 1;
        int sz = 1 << set_bits.size();

        // Iterate over all possible combinations of set bits
        for (int mask = 0; mask < sz; mask++)
        {
            long x_copy = x;
            long y_copy = y;

            // Iterate over each bit in set_bits vector
            for (int j = 0; j < set_bits.size(); j++)
            {
                if (mask & (1 << j))
                {
                    // If bit is set in mask, set the corresponding bit of x_copy to 1
                    x_copy |= (1 << set_bits[j]);
                }
                else
                {
                    // If bit is not set in mask, set the corresponding bit of y_copy to 1
                    y_copy |= (1 << set_bits[j]);
                }
            }

            // Calculate the maximum XOR and update ans if necessary
            ans = max(ans, x_copy * y_copy);
        }

        // Print the maximum XOR
        cout << ans << "\n";
        return;
    }
};

class BitManipulationCrashCourse
{
private:
    /*
    @ Key points
    & And of multiple values always either decreases or remain same it never increases!
    & OR of multiple values always either remains same or it increases it never decreases
    & XOR is used to flip bits at ith location
    % A^A = 0 && A^0 = A && 0^A = A
    % It detects odd number of ones in binary representation
    & Left shifting is same as multiplying by 2
    & Right shifting is same as dividing by 2
    & While solving problems on AND operator and can't  decide which value to take as initial value always use "-1" as it has all set bits(1s)


        Difference between upper case letter and lower case letter binary is that
 In upper case letter 5th bit!=1;
 In lower case letter 5th bit =1;
 cout<<char('A'|(1<<5))<<endl;     //Convert Char to lower case;
 cout<<char('a'&(~(1<<5)))<<endl;    //Convert Char to upper case;

 Actually char of 1<<5 is _(space);
 Take any upper case letter and its |(or) with space will get the corresponding lower case letter;

 cout<<char('C'|' ')<<endl;   // will make it small c

Take any lower case letter and its &(and) with _(underscore) will get the corresponding upper //case letter;`

 cout<<char('c'&'_')<<endl;   // will make it capital C


Find a letter’s position in alphabet
We can easily find a letter’s position [1-26] in the
alphabet by taking its bitwise AND with ASCII 31 (00011111 in binary).
The case of the letter is irrelevant here.

 eg.
 (‘A’ & 31) returns position 1
 (‘c’ & 31) returns position 3



 Set union A | B
Set intersection A & B
Set subtraction A & ~B
Set negation ALL_BITS ^ A or ~A
Set bit A |= 1 << bit
Clear bit A &= ~(1 << bit)
Test bit (A & 1 << bit) != 0
Extract last bit A&-A or A&~(A-1) or x^(x&(x-1))
Remove last bit A&(A-1)
Get all 1-bits ~0==-1

     */

public:
    void swapXor(int &a, int &b)
    {
        a = a ^ b;
        b = a ^ b;
        a = a ^ b;
    }

    // Binary Number to gray Code
    vector<int> grayCode(int n)
    {
        vector<int> v;
        for (int i = 0; i < (1 << n); i++)
            v.push_back(i ^ (i >> 1));
        return v;
    }

    // Gray Code to Binary Number
    int rev_grayCode(int g)
    {
        int n = 0;
        for (; g; g >>= 1)
            n ^= g;
        return n;
    }
    //     The given number n is a power of 4 if it is a power of 2 and
    // its remainder is 1 when it is divided by 3.
    bool checkPowerOf4(unsigned n)
    {
        // return true if `n` is a power of 2, and
        // the remainder is 1 when divided by 3
        return !(n & (n - 1)) && (n % 3 == 1);
    }
    /*
    The two numbers that appear only once must differ at some bit, this is how we can distinguish between them. Otherwise, they will be one of the duplicate numbers.

    One important point is that by XORing all the numbers, we actually get the XOR of the two target numbers (because XORing two duplicate numbers always results in 0). Consider the XOR result of the two target numbers; if some bit of the XOR result is 1, it means that the two target numbers differ at that location.

    Let’s say the at the ith bit, the two desired numbers differ from each other. which means one number has bit i equaling: 0, the other number has bit i equaling 1.

    Thus, all the numbers can be partitioned into two groups according to their bits at location i.
    the first group consists of all numbers whose bits at i is 0.
    the second group consists of all numbers whose bits at i is 1.

    Notice that, if a duplicate number has bit i as 0, then, two copies of it will belong to the first group. Similarly, if a duplicate number has bit i as 1, then, two copies of it will belong to the second group.

    by XoRing all numbers in the first group, we can get the first number.
    by XoRing all numbers in the second group, we can get the second number.

     */
    vector<int> singleNumber(vector<int> &nums)
    {
        unsigned xorr = 0;
        for (int &i : nums)
            xorr ^= i;
        unsigned rightmost = (xorr) & (-xorr);
        int a = 0, b = 0;
        for (int &i : nums)
        {
            if (i & rightmost)
            {
                a ^= i;
            }
            else
            {
                b ^= i;
            }
        }
        return {a, b};
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}