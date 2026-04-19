#include <iostream>
#include <string>
using namespace std;

string solve(const string& s) {
    // TODO: Implementar solución usando pila(s)
    return "";
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
    runTest(1, "3[a]", "aaa");
    runTest(2, "2[ab]3[c]", "ababccc");
    runTest(3, "3[a2[c]]", "accaccacc");
    runTest(4, "1[x]", "x");
    runTest(5, "2[abc]3[cd]ef", "abcabccdcdcdef");
    return 0;
}
