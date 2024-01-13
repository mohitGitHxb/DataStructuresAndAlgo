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

class ModularArithmetic
{
private:
    /*
    1. Addition: (a + b) mod n = ((a mod n) + (b mod n)) mod n
    2. Subtraction: (a - b) mod n = ((a mod n) - (b mod n) + n) mod n
    3. Multiplication: (a * b) mod n = ((a mod n) * (b mod n)) mod n
    4. Division: Division is not directly applicable in modular arithmetic. However, multiplicative inverse can be used. If you want to compute (a / b) mod n, you need to find the multiplicative inverse of b, let's call it b_inv, such that (b * b_inv) mod n = 1. Then, (a / b) mod n = (a * b_inv) mod n.
    5. Power: (a^b) mod n = ((a mod n)^b) mod n
    6. Distributive Laws: a mod n = (a mod m) mod n if m > n.
    7. Negative Numbers: If a < 0, then a mod n = n - ((-a) mod n), unless a is a multiple of n, in which case a mod n = 0.
    8. Modulo of a Modulo: (a mod n) mod n = a mod n
    9. Modulo of a Sum: (a + b) mod n = ((a mod n) + (b mod n)) mod n
    10. Modulo of a Difference: (a - b) mod n = ((a mod n) - (b mod n) + n) mod n
    11. Modulo of a Product: (a * b) mod n = ((a mod n) * (b mod n)) mod n

    Note: These rules are applicable under the assumption that the numbers are integers and the moduli are positive. Also, the division operation in modular arithmetic requires that the divisor has a multiplicative inverse, which is not always the case.


    The modular multiplicative inverse of a number 'num' under modulo 'mod' can be found using the Extended Euclidean Algorithm. The modular multiplicative inverse of 'num' modulo 'mod' is a number 'x' such that the product 'num*x' is equivalent to 1 modulo 'mod'.


    Fermat's Little Theorem states that if 'p' is a prime number, then for any integer 'a', the number 'a^p' is congruent to 'a' modulo 'p'. In the special case when 'a' is not divisible by 'p', Fermat's Little Theorem is equivalent to the statement that 'a^(p-1) - 1' is an integer multiple of 'p'.

    If 'p' is a prime number and 'a' is an integer not divisible by 'p', then 'a^(p-1) ≡ 1 (mod p)'. This can be used to find the modular multiplicative inverse when 'mod' is a prime number. The modular inverse of 'a' under 'mod' is 'a^(mod-2) % mod'.
     */
public:
    long long binaryExponentiation(long long base, long long exponent, long long mod)
    {
        long long res = 1;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                res = (res * base) % mod;
            }
            base = (base * base) % mod;
            exponent >>= 1;
        }
        return res;
    }
    long long getModularMultiplicativeInverse(long long num, long long mod)
    {
        // multiplicative inverse only exists if num and mod are relatively prime (coprime) i.e gcd(num, mod) = 1
        if (__gcd(num, mod) != 1)
        {
            return -1;
        }
        return binaryExponentiation(num, mod - 2, mod);
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    return 0;
}