#include <iostream>
#include <string>
#include <vector>
using namespace std;

string solve(const string& s) {
    int len = s.length();
    string sal;
    for (int i=0; i<len;i++){
        if (s[i]=='*'){
            i++;
            
        } 
        else{
            sal[i]=s[i];
        }
    }
    return sal;
}   

void runTest(int testNumber, const string& input, const string& expected) {
    string result = solve(input);
    if (result == expected) {
        cout << "Test " << testNumber << " OK\n";
    } else {
        cout << "Test " << testNumber << " FAILED\n";
        cout << "Input: " << input << "\n";
        cout << "Esperado: " << expected << "\n";
        cout << "Obtenido: " << result << "\n\n";
    }
}

int main() {
    runTest(1, "abc*d", "abd");
    runTest(2, "a*b*c*", "");
    runTest(3, "leetcode", "leetcode");
    runTest(4, "xy**z", "z");
    runTest(5, "ab**cd*e", "ce");
    return 0;
}
