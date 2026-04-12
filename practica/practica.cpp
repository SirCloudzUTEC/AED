#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution{
    public:
        vector<int> twoSum(vector<int>& nums, int target){
            int len=nums.size();

            for (int i=0; i<len; i++){
                for(int j=i+1; j<len; j++){
                    if(nums[i]+nums[j]==target){
                        return {i,j};
                    }
                }
            }
            return {};
        }  

        // 121   1221
        bool isPalindrome(int x) {
            string conv=to_string(x);
            for (int i=0;i<conv.length();i++){
                if (conv[i]!=conv[conv.length()-i-1]){
                    return 0;
                }
            }
            return 1;
        }

        int lengthOfLastWord(string s) {
            int cont=0;
            for (int i= s.length()-1; i>=0;i--){
                if (s[i]!=' '){
                    cont++;
                }
                else if (cont>0 && s[i]==' '){
                    break;
                }
            }
            return cont;
        }

        vector<int> plusOne(vector<int>& digits) {
            for (int i = digits.size()-1; i>=0; i--){
                if (digits[i]+1 < 10){
                    digits[i]++;
                    return digits;
                }
                digits[i]=0;
            }
            digits.insert(digits.begin(),1);
            return digits;
        }

        string longestCommonPrefix(vector<string>& strs) {
            if (strs.empty()) return "";

            string prefix=strs[0];
            
            for (int i=1; i<strs.size();i++){
                while(strs[i].find(prefix) != 0){
                    prefix.pop_back();
                    if (prefix.empty()) return "";
                }
                
            }
            return prefix;
        }

        bool isValid(string s) {
            string temp = "";

            for (char c : s) {
                if (c == '(' || c == '[' || c == '{') {
                    temp += c;
                } 
                else 
                {
                    if (temp.empty()) return false;

                    char last = temp.back();
                    temp.pop_back();

                    if ((c == ')' && last != '(') ||
                        (c == ']' && last != '[') ||
                        (c == '}' && last != '{')) {
                        return false;
                    }
                 }
            }
        return temp.empty();
    }

        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
           if (list1 != nullptr && list2 != nullptr){
                if (list1->val < list2->val){
                    list1->next = mergeTwoLists(list1->next, list2);
                    return list1;
                }
                else{
                    list2->next = mergeTwoLists(list1, list2->next);
                    return list2;
                }
           }
           if (list1 == nullptr) return list2;
           return list1;
    }

        int strStr(string haystack, string needle) {
            if (needle.empty()) return 0;
            
            int lenNeedle=needle.length(), j=0;
            for (int i=0; i<haystack.length(); i++){
                if (haystack[i]==needle[j]){
                    j++;
                    if (lenNeedle == j){
                    return i-j + 1;
                }
                }
                else{
                    i=i-j;
                    j=0;
                }
            }
            return -1;
    }


};


int main(){
    Solution res;
    string sub="([)])";
    bool sal=res.isValid(sub);

    cout<<sal<<endl;
    return 0;
}