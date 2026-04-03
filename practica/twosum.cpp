#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
};


int main(){
    Solution res;
    vector<int> digits={9,9};
    vector<int> sal=res.plusOne(digits);

    for (int i=0; i<sal.size();i++){
        cout<<sal[i]<<endl;
    }
    return 0;
}