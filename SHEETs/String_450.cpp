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
    
    /* 

&    The code uses a loop to iterate through the text string from index 0 up to txt.length() - pat.length(). This ensures that the remaining portion of the text is at least the length of the pattern, so there is a possibility of finding a match.

&    Within the loop, it checks if the substring of txt starting from index i and of length pat.length() is equal to the pattern string pat. It does this by using the substr function to extract the substring and then comparing it with pat using the == operator.

&    If a match is found, it means the pattern is present at index i in the text. So, it adds i+1 to the ans vector to store the index where the pattern starts. Note that i+1 is used because the problem statement might require the index to be 1-based instead of 0-based.

&    After the loop, it checks if any matches were found. If the ans vector is not empty, it means at least one match was found. In that case, it directly returns the ans vector.

&    If no matches were found, it means the pattern is not present in the text. In that case, it adds -1 to the ans vector to indicate that no match was found, and then returns the ans vector.

@ Simplified version of Naive pattern matching
     */

                vector<int> ans;
            for(int i = 0; i <= s.length() - pat.length(); i++){
                if(pat == s.substr(i,pat.length()))
                    ans.push_back(i+1);
            }
            if(!ans.empty())
                return ans;
            ans.push_back(-1);
            return ans;
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
/* 
&    The getZarr function is used to calculate the Z-array, which stores the length of the longest substring starting from each position that is also a prefix of the given string. It takes two parameters: zarr (reference to a vector to store the Z-array values) and str (the input string).

&    The algorithm initializes the variables L and R to keep track of the left and right boundaries of a Z-box (a substring with the same prefix as the given string). It also initializes k to track the index difference from the left boundary.

&    The algorithm iterates through the characters of the string starting from the second character (i = 1) up to the last character (i < n). For each i, it performs the following steps:

&    a. If L is greater than R, it means there is no Z-box that covers the current position i. So, it sets L and R to i and increments R until the characters at positions R-L and R are equal. It then calculates the Z-array value for position i as R-L and decrements R by 1.

&    b. If L is less than or equal to R, it means there is an existing Z-box that covers the current position i. In this case, it calculates k as i - L. If the Z-array value at index k is less than R-i+1, it means the Z-box extends to position i without reaching R. So, it directly assigns the Z-array value of k to zarr[i]. Otherwise, it sets L to i and increments R until the characters at positions R-L and R are equal. It then calculates the Z-array value for position i as R-L and decrements R by 1.

&    The Zalgo function is the main function that uses the Z-array to find all occurrences of a pattern in a given text. It takes two parameters: pat (the pattern string) and txt (the text string).

&    It concatenates the pattern string, a special character ('$' in this case), and the text string to form the concat string.

&    It initializes an empty vector res to store the indices where the pattern is found.

&    It calls the getZarr function to calculate the Z-array for the concat string.

&    It iterates through the Z-array and checks if the Z-array value at index i is equal to the length of the pattern. If it is, it means a match is found at position i - pat.length(), and it adds this index to the res vector.

&    Finally, it returns the res vector containing the indices where the pattern is found in the text.
 */
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
        The function findPermutationUtil is a recursive helper function that takes three parameters: s (a reference to the input string), index (the current index for swapping elements), and st (a reference to a set to store unique permutations).

    The function first checks if the current index is equal to the size of the string s. If it is, it means all elements have been fixed, and a permutation is complete. So, it inserts the current permutation s into the set st to store unique permutations.

    If the current index is not equal to the size of the string, it means there are more elements to consider in the permutation. In that case, it enters a loop starting from index up to the length of the string s.

    Within the loop, it performs the following steps:

    a. It swaps the character at index i with the character at index index using the swap function. This is done to generate different permutations by fixing one character at a time and permuting the remaining characters.

    b. It calls the findPermutationUtil function recursively with index+1 to process the next index and generate permutations for the remaining characters.

    c. After the recursive call, it swaps the characters back to their original positions to backtrack and explore other possibilities. This ensures that the original string s is restored before the next iteration of the loop.

    Once the loop finishes executing for all indices, the function returns.
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

//^ 13 longest palindromic substring
/* 
~ Method 1: Naive
& Generate all possible subsequences of the string and check if they are pallindrome or not
!O(N!) T.C

~ Method 2: Using Even and Odd length method
& Initialize start and end. start = 0 and end = 1 (this is our assumed substring and we will extend this)

& let two variables low and high points to i - 1 and i (even length) and i - 1 and i + 1 (odd length)

& while str[low] == str[high] and low is greater equal to 0 and high is less than string length | check if the size (high-low+1) becomes greater than previous length (denoted by end)

& if it exceeds end then update end and start = low | low-- and high++
& at the end our desired palindromic substring is from [start to start+end-1]
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

//^ 14 Print all subsequences of a string
//* O(2*N) T.C
void printAllSubsequences(int index,string &temp,string &str){
    if(index>= str.size()){
        cout << temp << "\n";
        return;
    }
    //& Adding char into a temporary string to take this char into account
    temp.push_back(str[index]);
    //& Generating all subsequences including this character
    printAllSubsequences(index+1,temp,str);
    //& removing this character (excluding this character) and generating all subsequences
    temp.pop_back();
    printAllSubsequences(index+1,temp,str);
}

//^ 15 Split the binary string into substrings with equal number of 0s and 1s
/* 

& Initialize count = 0 and traverse the string character by character and keep track of the number of 0s and 1s so far,
& whenever the count of 0s and 1s become equal increment the count. As in the given question, if it is not possible to split string then on that time count of 0s must not be equal to count of 1s then return -1 else print the value of count after the traversal of the complete string.

*O(N) T.C | O(1) S.C
 */

int split01(const string &str){
    int count = 0;
    int counter = 0;
    int i = 0;
    while(i < str.length()){
        if(str[i] == '0')counter++;
        else counter--;
        if(counter == 0){
            count++;
        }
    }
    return counter == 0 ? count : -1;
}

//^ 16 Balanced brackets
class BalancedBrackets{
/* 
& isMatching function cares only about comparing two brackets
& Create a stack of characters it will keep track of opening and closing brackets
& if str[i] is a opening bracket => add it to the stack
& else check if stack is empty (false case) else if str[i] and stack.top() is not a match pair (false case) else just pop the element

& check if stack is empty(true)

*O(N) T.C | O(N) S.C

 */
public:
    bool isMatching(char a,char b){
    return ((a=='('&&b==')'))||((a=='{'&&b=='}'))||((a=='['&&b==']'));
    }
    bool isParenthesis(const string &str){
        if(str.empty())return false;
        stack<char> s;
   for (int i = 0; i < str.length(); i++)
    {
        if(str.at(i)=='('||str.at(i)=='{'||str.at(i)=='['){
            s.push(str[i]);
        }
        else{
            if(s.empty())
                return false;
            else if(isMatching(s.top(),str[i])==false)
                return false;
            else 
                s.pop();
        }
    }
    return s.empty();
    }

};

//^ 17 count of number of string in a 2D character array
class CharacterCount{
    private:
    /* 
&    Step 1– Traverse matrix character by character and take one character as string start 
&    Step 2– For each character find the string in all the four directions recursively 
&    Step 3– If a string found, we increase the count 
&    Step 4– When we are done with one character as start, we repeat the same process for the next character 
&    Step 5– Calculate the sum of count for each character 
&    Step 6– Final count will be the answer
    * O(n*m)^2 T.C || O(n*m)
     */
    public:
    int internalSearch(string needle, int row,
				int col, string hay[],
				int row_max, int col_max, int xx)
{
	int found = 0;

	if (row >= 0 && row <= row_max && col >= 0 &&
		col <= col_max && needle[xx] == hay[row][col])
	{
		char match = needle[xx];
		xx += 1;

		hay[row][col] = 0;

		if (needle[xx] == 0)
		{
			found = 1;
		}
		else
		{

			// through Backtrack searching
			// in every directions
			found += internalSearch(needle, row,
									col + 1, hay,
									row_max, col_max,xx);
			found += internalSearch(needle, row, col - 1,
									hay, row_max, col_max,xx);
			found += internalSearch(needle, row + 1, col,
									hay, row_max, col_max,xx);
			found += internalSearch(needle, row - 1, col,
									hay, row_max, col_max,xx);
		}
		hay[row][col] = match;
	}
	return found;
}

// Function to search the string in 2d array
int searchString(string needle, int row, int col,
				string str[], int row_count,
								int col_count)
{
	int found = 0;
	int r, c;

	for (r = 0; r < row_count; ++r)
	{
		for (c = 0; c < col_count; ++c)
		{
			found += internalSearch(needle, r, c, str,
									row_count - 1,
									col_count - 1, 0);
		}
	}
	return found;
}
};

//^ 18 Find the string in grid (not in zig-zag form). The 8 directions are, horizontally left, horizontally right, vertically up, vertically down, and 4 diagonal directions.

class StringsInGrid {
    /* 
% Uses DFS algorithm
&    Here's a step-by-step explanation of the code:

&    Initialize a 2D vector d representing the 8 possible directions to traverse in the grid.

&    Define a helper function patternStarts that takes in the current row and col indices, the grid, the word, a vector v representing the direction to traverse, the idx representing the current index of the word. The function returns true if the given word is found in the grid starting from the current row and col position in the given direction v.

&    In the searchWord function, initialize an empty 2D vector matrix to store the positions where the given word is found.

&    Traverse the entire grid in row-major order using two nested loops.

&    If the current character in the grid matches the first character of the given word, then traverse in all 8 directions using the patternStarts helper function. If the word is found in any of the directions, then add the current position (row, col) to the matrix vector.

&    Sort the matrix vector lexicographically.

@    Return the matrix vector.

*O(N*M*Constant) T.C | O(1) S.C 
     */
private:
vector<vector<int>> d={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};
public:
    bool patternStarts(int row,int col,vector<vector<char>> &grid,string &word,vector<int> &v,int idx){
        if(idx == word.length())return true;
        if(row < 0 || col < 0 || row >= grid.size() || col >= grid.front().size() || grid[row][col]!=word[idx])
            return false;
        return patternStarts(row+v[0],col+v[1],grid,word,v,idx+1);
    }
	vector<vector<int>>searchWord(vector<vector<char>> &grid, string &word){
	    // Code here
	    vector<vector<int>> matrix;
	    for(int i = 0; i < grid.size(); i++){
	        for(int j = 0 ;j < grid.front().size(); j++){
	            if(grid[i][j] == word[0]){
	                for(auto &it : d){
	                    if(patternStarts(i,j,grid,word,it,0)){
	                        matrix.push_back({i,j});
	                        break;
	                    }
	                }
	            }
	        }
	    }
	    sort(matrix.begin(),matrix.end());
	    return matrix;
	}
};

//^ 19 Roman number to integer conversion
/* 
& Just create a hashmap of roman no. and their respective integer values
& Whenever a smaller roman number is encountered before a larger roman number perform subtraction
& else if a larger roman number is encountered just add the roman number

*O(N) T.C | O(1) S.C (switch case can be used)
 */
int romanToDecimal(string &str) {
    unordered_map<char,int> mp;
        mp['I'] = 1;
        mp['V'] = 5;
        mp['X'] = 10;
        mp['L'] = 50;
        mp['C'] = 100;
        mp['D'] = 500;
        mp['M'] = 1000;
        int ans = 0;
        for(int i = str.length() - 1; i >=0 ; i--){
            if(i < str.length()-1 && mp[str[i]]<mp[str[i+1]]){
                ans -= mp[str[i]];
            }   
            else{
                ans += mp[str[i]];
            }
        }
        return ans;
    }

//^ 20 Longest Common Prefix
class LongestCommonPrefix{
    private:
    /*

 & The longest common prefix is common to all the strings. So, we can fix one string and check the common prefix of this string with other strings. The minimum such length is found and the answer is the substring of the fixed string starting from 0 to the length of the above such minimum.
Here, I have fixed 0th string and checked other strings with this. 
     */

    public:
    string longestCommonPrefix(vector<string>& s) {
int ans = s[0].length(), n = s.size();
        for(int i=1; i<n; i++){
            int j = 0;
            while(j<s[i].length() && s[i][j]==s[0][j])j++;
            ans = min(ans, j);
        }
        return s[0].substr(0, ans);
    }
};

//^ 21 Second most frequent string
/* 
& Use unordered_map to store string and its frequency
& find the most frequent string
& find the second most frequent string

*O(N) T.C | O(N) S.C
 */
    string secFrequent (string arr[], int n)
    {
        //code here.
        unordered_map<string,int> mp;
        for(int i = 0; i < n; i++){
            mp[arr[i]]++;
        }
        int mostRepeated=-1;
        for(auto &x : mp){
            mostRepeated = max(x.second,mostRepeated);
        }
        int secondRepeated = -1;
        string ans;
        for(auto &x : mp){
            if(secondRepeated!=mostRepeated && x.second!=mostRepeated){
                  if(secondRepeated<x.second)
                {
                    secondRepeated = x.second;
                  ans = x.first;
                }
            }
              
        }
        return ans;
    }

//^ 22 Longest common prefix
/* 
& The comparision function is defined to compare two strings and return their common prefix. It takes two string arguments a and b by reference, initializes two integer variables i and j to 0, and creates an empty string res to store the common prefix.

& It then enters a while loop and compares the characters at index i of string a and index j of string b. If the characters are the same and the index values are within the bounds of the strings, it appends the character to the res string, increments both i and j, and continues. If the characters at i and j are not the same, it breaks out of the loop.

& The longestCommonPrefix function takes a vector of strings s as an argument. It initializes two integer variables ans and n to the length of the first string in the vector and the size of the vector, respectively.

& It then enters a for loop, starting from the second string in the vector and comparing each string with the first string in the vector. It initializes an integer variable j to 0 and enters a while loop. The while loop compares the characters at index j of the current string and the first string in the vector. If the characters are the same and the index value is within the bounds of the current string, it increments j and continues. If the characters are not the same, it breaks out of the loop.

& The ans variable is then updated to the minimum of its current value and j. This is done to find the length of the longest common prefix among all the strings.

& Finally, the function returns a substring of the first string in the vector, starting from index 0 and ending at index ans. This substring represents the longest common prefix of all the strings in the vector.
 */
class LongestCommonPrefix {
public:
    string comparision(string &a,string &b){
        int i = 0;
        int j = 0;
        string res="";
        while(a[i] == b[j] && i < a.length() && j < b.length()){
            res.push_back(a[i]);
            i++;
            j++;
            if(a[i]!=b[i]){
                break;
            }
        }
        return res;
    }
    string longestCommonPrefix(vector<string>& s) {
int ans = s[0].length(), n = s.size();
        for(int i=1; i<n; i++){
            int j = 0;
            while(j<s[i].length() && s[i][j]==s[0][j])j++;
            ans = min(ans, j);
        }
        return s[0].substr(0, ans);
    }
};

//^ 23 Minimum number of flips to make the binary string an alternating sequence
/* 
&    It initializes two variables flips1 and flips2 to keep track of the number of flips required for two different scenarios: when the string starts with '0' and when it starts with '1'.
&    It also initializes a boolean variable flag to false. This variable is not used in the given code and can be ignored.
&    The code then enters a loop that iterates through each character in the string S. The loop variable i represents the index of the current character being examined.
&    Inside the loop, there are two conditions based on i%2, which checks if i is an even or odd number. This is used to handle different positions in the string.
&    If i is even (i.e., divisible by 2), it checks the character at index i in the string S. If it is '1', it means a flip is required to make it alternating in the first scenario, so flips1 is incremented by 1. If it is '0', it means a flip is required to make it alternating in the second scenario, so flips2 is incremented by 1.
&    If i is odd, the same logic is applied, but the roles of flips1 and flips2 are reversed.
&    After iterating through the entire string, the code returns the minimum value between flips1 and flips2, which represents the minimum number of flips required to make the string S alternating.

* O(N) T.C | O(1) S.C
 */
int minFlips (string S)
{
    // your code here
    int flips1 = 0;
    int flips2 = 0;
    bool flag = false;
    
    for(int i = 0; i < S.length(); i++){
        if(i%2==0){
            if(S[i]=='1')
            flips1++;
        }
        else{
            if(S[i]=='0')
                flips1++;
        }
        if(i%2==0){
            if(S[i]=='0')
            flips2++;
        }
        else{
            if(S[i]=='1')
                flips2++;
        }
        
    }
    
    return min(flips1,flips2);
    
}

//^ Print all anagrams from a vector of strings
/* 
&The code uses an unordered map mp to store the sorted version of each word as the key and the original word as the value. This map acts as a hash table where anagrams will have the same sorted key, allowing us to group them together efficiently.

Here's how the code works:

@    Create an empty vector of vector of strings ans to store the grouped anagrams.
@    Create an unordered map mp with the key as a sorted version of a word and the value as a vector of strings.
@    Iterate over each word in string_list.
@    Make a copy of the current word into temp.
@    Sort the characters of the current word in ascending order using sort(). This sorted version will be used as the key in the map.
@    Add the original word temp to the vector value corresponding to the sorted key in the map.
@    After processing all the words, iterate over each key-value pair in the map.
@    Append the vector value (which contains all anagrams of a particular key) to the ans vector.
@    Return the ans vector containing grouped anagrams.

& The code effectively groups the anagrams together by sorting the characters of each word and using the sorted version as the key in the map. Anagrams will have the same sorted key, allowing them to be grouped together in the output. The time complexity of this code is O(N * M * log M), where N is the number of words and M is the average length of the words.
 */
    vector<vector<string> > Anagrams(vector<string>& string_list) {
        
        vector<vector<string>> ans;
        unordered_map<string,vector<string>> mp;
        for(auto &it : string_list){
            string temp = it;
            sort(it.begin(),it.end());
            mp[it].push_back(temp);
        }
        
        for(auto &k : mp)
            ans.push_back(k.second);
        return ans;
    }

int main(){
    string str = "RiCantSnipe";
    duplicatesInString(str);
    return 0;
}