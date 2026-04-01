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

        int romanToInt(string s) {
            int sum=0;
            for (int i=0;i<s.length();i++){
                if (s[i]=='M'){
                    sum+=1000;
                }
                else if (s[i]=='D'){
                    sum+=500;
                }
                else if (s[i]=='C'){
                    sum+=100;
                }
                else if (s[i]=='L'){
                    sum+=50;
                }
                else if (s[i]=='X'){
                    sum+=10;
                }
                else if (s[i]=='V'){
                    sum+=5;
                }
                else if(s[i]=='I'){
                    sum++;
                }
                else{
                    return 0;
                }

            }

        }
};


int main(){
    string h="MCMXCIV";
    Solution res;
    int num=res.romanToInt(h);
    cout<<num<<endl;
    return 0;
}