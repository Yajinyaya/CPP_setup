
#include <iostream>
#include <iterator>
#include <unordered_set>
 
using namespace std;
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> myset;
        int i  =  0;
        int j = 0;
        int best  = 0;
        if (s==""){
            return  0;
        }
        while (i < s.length() && j <s.length()){
            
            
                if (myset.find(s[j])!=myset.end()){
                    myset.erase(s[i]);
                    ++i;
                } else {
                    myset.insert(s[j]);
                    if  (j-i>best){
                        best  =  j-i;
                    }
                    ++j;
                    
                }
            
        }
        
        return  best+1;
    
    }
};