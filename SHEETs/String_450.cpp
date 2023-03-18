#include <bits/stdc++.h>
using namespace std;

//^ 1 Reverse the string;
void reverseString(string &s){
    reverse(s.begin(), s.end());
}

//^ 2 Palindrome string
bool checkPalindrome(string &s){
    int low = 0, high = s.length() - 1;
    while(low < high){
        if(s[low]!= s[high])
            return false;
        low++;
        high--;
    }
    return true;
}

//^ 3 Duplicate character in a string
void duplicatesInString(string &s){
    vector<int> hash(255);
    for(int i = 0; i < s.length(); i++){
        hash[s[i]]++;
    }
    string ans = "";
    for(int i = 0; i < 255; i++){
        if(hash[i] > 0){
            ans.push_back((char)hash[i]);
        }
    }
    cout << ans;

}

//^ 4 Why strings are immutable in java
/* 

& In Java, strings are immutable because the designers of the language wanted to ensure that strings were thread-safe and that they could be safely shared between multiple threads without any risk of data corruption or synchronization issues.

& When a string is created in Java, it is stored as a sequence of characters in a contiguous block of memory. This block of memory is allocated on the heap, and the string object contains a reference to it. Once a string is created, its contents cannot be modified. If you try to change the value of a string by concatenating or modifying it, a new string object will be created with the modified value, and the original string object will be left unchanged.

& This approach has several advantages. First, it simplifies the implementation of string operations, since the original string does not need to be modified in place. Second, it makes it easier to reason about the behavior of strings in a multithreaded environment, since there is no risk of two threads modifying the same string object simultaneously. Finally, it makes strings more secure, since an attacker cannot modify the contents of a string object once it has been created.

& In summary, strings are immutable in Java to ensure thread-safety, simplify implementation, and improve security. While immutability can sometimes be a limitation, in the case of strings, it has proven to be a useful design decision.

%Here are 4-5 key differences between C++ strings and Java strings:

 %   String handling: In C++, strings are typically handled using the std::string class, which is part of the standard library. In Java, strings are implemented as objects of the java.lang.String class.

 %   Null-termination: C++ strings are null-terminated, which means that they end with a null character ('\0'). Java strings are not null-terminated.

 %   Memory management: In C++, memory for strings is typically managed manually using new and delete, or using smart pointers. In Java, memory is managed automatically by the garbage collector.

 %   Immutable vs mutable: As mentioned in a previous question, Java strings are immutable, which means that once a string object is created, its contents cannot be changed. In C++, the std::string class provides both mutable and immutable string options.

 %   String manipulation: In C++, string manipulation is typically done using functions from the <string> header, such as substr, find, and replace. In Java, strings provide a rich set of methods for manipulation, such as substring, indexOf, and replace.

%In general, C++ strings provide more flexibility and control over memory management and mutability, while Java strings offer more convenience and ease of use with built-in methods for string manipulation.

 */

//^ 5 Check if a string is a rotation of other string
/* 
@ Method - 1:
& Create a vector which stores the indices of occurrence of chars according to rotated string
& Then just traverse the original string [i + index]%length (to keep ptr in range)
& If every char of original string matches with rotated return true else move to the next index (from the vector and do the same)
! O(N + M) T.C | O(N) S.C
@Method - 2:
& Just concatenate the original string to itself and use find method
* O(N) T.C | O(1) S.C
 */
bool rotateString(string A, string B) {                
    return A.size() == B.size() && (A + A).find(B) != string::npos;
}   

//^ 6 Check if two strings are anagram or not
/* 
& Just create a count array which uses ascii values as indicies 
& For string s, each occurrence of a char increases count by 1
& For string t, each occurrence of a char decreases count by 1
& If s , t are anagrams then the count array should remain zero
* O(N) T.C | O(N) S.C
 */
bool isAnagram(string s,string t){
    if(s.length() != t.length())return false;
    vector<int> charMap(UCHAR_MAX);
    for(int i = 0; s.length(); i++){
        charMap[s[i]]++;
        charMap[t[i]]--;
    }
    for (int i = 0; i < charMap.size(); i++)
    {
        if(charMap[i] != 0)
        return false;
    }
    return true;
    
}

//^ 7 Pattern Searching in Strings Naive Method
vector<int> naivePatternSearch(const string &s,const string &pat){
    vector<int> result;
    for(int i=0; i<=s.length() - pat.length();i++){
        int j;
        for ( j = 0; j < pat.length(); j++)
        {
            if(s[i + j]!= pat[j])
            break;
        }
        if (j == pat.length())
        {
            result.push_back(j);
        }
        
    }
    return result;
}

//^ 8 Rabin Karp algorithm

/* 
&     Compute the hash value of the pattern using a rolling hash function. A rolling hash function calculates the hash value of a string by using the hash value of the previous string and the difference between the characters that are being added and removed from the string.

&     Compute the hash value of the first window of the larger string using the same rolling hash function.

&     Compare the hash values of the pattern and the first window. If they match, compare the pattern with the characters in the window to verify if they match.

&     If the pattern matches the window, return the starting position of the pattern in the larger string.

&     If the pattern does not match the window, slide the window by one character and re-calculate the hash value of the new window using the rolling hash function.

&     Repeat steps 3 to 5 until the end of the larger string is reached or the pattern is found.

&     If the pattern is not found after checking all windows, return a "not found" message.

&     Suppose we have a string of characters s = "abcd". We can represent this string as a base-26 number using the mapping a -> 1, b -> 2, c -> 3, and d -> 4. Therefore, the base-26 representation of the string is 1 * 26^3 + 2 * 26^2 + 3 * 26^1 + 4 * 26^0 = 73130.

& To calculate the hash value of a string using a polynomial rolling hash function, we can use the following formula:

& hash(s) = (s[0] * p^(n-1) + s[1] * p^(n-2) + ... + s[n-1] * p^0) mod m

& where s is the string to be hashed, n is the length of the string, p is a prime number (usually chosen to be a large prime number), and m is the size of the hash table.

& For example, if we choose p = 31 and m = 10^9 + 9, the hash value of the string "abcd" would be:

& hash("abcd") = (1 * 31^3 + 2 * 31^2 + 3 * 31^1 + 4 * 31^0) mod (10^9 + 9) = 287356804.

& When we slide the window of the string to "bcde", we can calculate the new hash value using the same formula, but subtracting the contribution of the first character (i.e., "a") and adding the contribution of the last character (i.e., "e"):

& hash("bcde") = ((hash("abcd") - 1 * 31^3) * 31 + 5 * 31^0) mod (10^9 + 9) = 57462760.

& This allows us to efficiently compute the hash value of the new window in constant time, without having to recompute the hash value  the entire string.

! O((N - M + 1)xM) T.C (performs better compared to naive method on average)

 */

bool search(string pat, string txt, int q) 
{ 
	// Your code here
    const int d = 256;
int m = pat.length();
	int n = txt.length();
	int h = 1,p=0,t=0;
	for(int i=0;i<m-1;i++)
	 h = (h*d)%q;
	 for(int i=0;i<m;i++)
	 {
	     p = (p*d+pat[i])%q;
	     t = (t*d+txt[i])%q;
	 }
	 for(int i=0;i<=n-m;i++)
	 {
	     if(t==p)
	     {
	         int j;
	         for(j=0;j<m;j++)
	         {
	             if(pat[j]!=txt[i+j])
	                   break;
	         }
	         if(j==m)
	         return true;
	     }
	      if(i<n-m)
	     {
	      t = (d*(t-txt[i]*h)+txt[i+m])%q;
	         if(t<0)
	         t = t+q;
	     }
	 }
return false;	
} 

int main(){
    string str = "RiCantSnipe";
    duplicatesInString(str);
    return 0;
}