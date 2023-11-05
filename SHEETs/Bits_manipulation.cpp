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
 */

//^ 2 clear bits till ith LSB
void clearTillIthLSB(int n,int i){
    int newNumber = (n & (~((1 << (i + 1)) - 1)));
    int setAllBitsTillMSB = (n & ((1 << (i + 1))) - 1);
    printBinaryDigits(newNumber);
}
int main()
{
    printBinaryDigits(59);
    clearTillIthLSB(59,4);
    return 0;
}