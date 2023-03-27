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

//^ 9 Z algorithm using longest prefix substring
class Zalgorithm{
    public:
    void getZarr(vector<int> &zarr,string str){
        int n = str.length();
        int L,R,k;
        L = R = 0;
        for (int i = 1; i < n; i++)
        {
            if(L > R){
                L = R = i;
                while (R < n && str[R-L] == str[R]) 
                {
                    R++;
                }
                zarr[i] = R-L;
                R--;
                
            }
            else
            {
                k = i - L;
                if(zarr[k] < R-i+1)
                    zarr[i] = zarr[k];
                else
                {
                    L = i;
                    while (R < n && str[R-L] == str[R])
                    {
                        R++;
                    }
                    zarr[i] = R - L;
                    R--;
                    
                }
                
            }
            
        }
        
    }

    vector<int> Zalgo(string pat,string txt){
        vector<int> res;
        string concat = pat + '$' + txt;
        int l = concat.length();

        vector<int> Z(l);
        getZarr(Z,concat);
        for(int i = 0; i < l; i++){
            if(Z[i] == pat.length())
                res.push_back(i - pat.length());
        }
        return res;
    }
};

//^ 10 KMP algorithm
class KMP{
    private:
    /* 
&    Build the prefix table: Create an array lps (longest prefix suffix) of length n (length of the pattern string) where lps[i] stores the length of the longest proper prefix of the pattern that is also a proper suffix of the first i characters of the pattern.

& Initialize pointers: Initialize two pointers i and j to 0, where i points to the current character in the text string being compared and j points to the current character in the pattern string being compared.

& Traverse the text string: While i is less than the length of the text string, do the following:

& a. If the current characters in the text and pattern strings match, increment both i and j.

& b. If j reaches the end of the pattern string, a match has been found. Return the starting index of the pattern in the text string.

& c. If the current characters in the text and pattern strings do not match: check if j is 0 if yes do i++ else j = lps[j-1];

& If the end of the text string is reached and no match has been found, return -1.

* O(N) T.C and O(M) S.C
     */
    public:
    void getLPSarray(string &pat,vector<int> &LPS){
        int len = 0;
        int i = 1;
        LPS[0] = 0;
        while(i < pat.length()){
            if(pat[i] == pat[len]){
                LPS[i++] = ++len;
            }
            else if(len == 0){
                LPS[i++] = 0;
            }
            else{
                len = LPS[len - 1];
            }
        }
    }
    vector<int> KMPAlgo(string txt,string pat){
        vector<int> ans;
        vector<int> lps(pat.length());
        getLPSarray(pat,lps);
        int i = 0,j = 0;
        while (i < txt.length()) 
        {
            if (pat[j] == txt[i])
            {
                i++;
                j++;
            }
            if (j == pat.length())
            {
                ans.push_back(i - j);
                j = lps[j - 1];
            }
            else if(i < txt.length() && pat[j] != txt[i])
            {
                if(j == 0)
                    i++;
                else
                    j = lps[j - 1];
            }
            
        }
        
        return ans;
    }
};

//^ 11 Count and say string
/* 
 @ 1.     1
 @ 2.     11
 @ 3.     21
 @ 4.     1211
 @ 5.     111221 
 @ 6.     312211
 @ 7.     13112221
 @ 8.     1113213211
 @ 9.     31131211131221
 @ 10.   13211311123113112211

& From the examples you can see, the (i+1)th sequence is the "count and say" of the ith sequence!

~ approach/method: 
& First check for the base case which is countAndSay(1) = "1"
& After this we'll recursively check for countAndSay(n-1); <-- This will return the string

& create empty string res which will hold the answer. 
& iterate over string obtained from the step 2 and append it to the res in this manner [frequency,character] make sure the counter always goes up;
& if prev[i]!=prev[i+1] or i is pointing to the end of the string reset counter and add result to res
& return res
 */
  string countAndSay(int n) {
        if(n == 1)
            return "1";
            string prev = countAndSay(n-1);
            string res = "";
            int counter = 0;
            for(int i=0;i<prev.length();i++){
                counter++;
                if(i == prev.length()-1 || prev[i]!=prev[i+1]){
                    string cnt = to_string(counter);
                    // res.append(cnt);
                    res += (cnt + prev[i]);
                    counter = 0;
                }
            }
            return res;
    }


//^ 12 Print all permutations of a string
class PermutationsString
{
    private:
    /* 
    
    *O(N*N!) T.C
     */
	public:
	    void findPermutationUtil(string &s , int index , set<string> &st){
	        if(index == s.size()){
	            st.insert(s);
	            return;
	        }
	        for(int i=index;i<s.length();i++){
	            swap(s[i],s[index]);
	            findPermutationUtil(s,index+1,st);
	            swap(s[i],s[index]);
	        }
	    }
		vector<string>find_permutation(string S)
		{
		    vector<string> ans;
		    if(S.size() == 0)
		        return ans;
            set<string> st;
            findPermutationUtil(S,0,st);
            for(auto &x : st)
                ans.push_back(x);
            return ans;
            
		}
        /* 
        ~ More concise code
                vector<string>find_permutation(string S)
        {
            vector<string>res;
            // sort the string in lexicographically order
            sort(S.begin(), S.end());
            do
            {
                // keep adding while there is next permutation
                res.push_back(S);
            }while(next_permutation(S.begin(), S.end()));
            return res;
        }
         */
};

//^ 13 longest pallindromic subtring
/* 
~ Method 1: Naive
& Generate all possible subsequences of the string and check if they are pallindrome or not
!O(N!) T.C

~ Method 2: Using Even and Odd length method
& Initialize start and end. start = 0 and end = 1 (this is our assumed substring and we will extend this)

& let two variables low and high points to i - 1 and i (even length) and i - 1 and i + 1 (odd length)

& while str[low] == str[high] and low is greater equal to 0 and high is less than string length | check if the size (high-low+1) becomes greater than previous length (denoted by end)

& if it exceeds end then update end and start = low | low-- and high++
& at the end our desired pallindromic substring is from [start to start+end-1]
* O(N*substringLen) T.C | O(N) space;
 */
string longestPalindrome(const string &s) {
        string ans = "";
        int low,high;
        int start=0,end=1;
        for(int i = 1; i < s.length(); i++){
            low = i - 1;
            high = i;
            while(low>=0 && high < s.length() && s[low]==s[high]){
                if(high - low + 1 > end){
                    end = high - low + 1;
                    start = low;
                }
                low--;
                high++;
            }
            low = i - 1;
            high = i + 1;
            while(low>=0 && high < s.length() && s[low]==s[high]){
                if(high - low + 1 > end){
                    end = high - low + 1;
                    start = low;
                }
                low--;
                high++;
            }
        }

        for(int i = start; i < (start+end); i++){
            ans.push_back(s[i]);
        }
        return ans;
    }
int main(){
    string str = "RiCantSnipe";
    duplicatesInString(str);
    return 0;
}