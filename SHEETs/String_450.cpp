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
int main(){
    string str = "RiCantSnipe";
    duplicatesInString(str);
    return 0;
}