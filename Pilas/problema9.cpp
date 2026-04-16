#include <iostream>
#include <vector>
#include <string>
using namespace std;

int solve(const vector<string>& tokens) {
    // TODO: Implementar solucion usando una pila
    return 0;
}

void runTest(int testNumber, const vector<string>& input, int expected) {
    int result = solve(input);

    if (result == expected) {
        cout << "Test " << testNumber << " OK\n";
    } else {
        cout << "Test " << testNumber << " FAILED\n";
        cout << "Esperado: " << expected << "\n";
        cout << "Obtenido: " << result << "\n\n";
    }
}

int main() {
    runTest(1, {"2","1","+","3","*"}, 9);
    runTest(2, {"4","13","5","/","+"}, 6);
    runTest(3, {"10","6","9","3","+","-11","*","/","*","17","+","5","+"}, 22);
    runTest(4, {"3","4","+"}, 7);
    runTest(5, {"5","1","2","+","4","*","+","3","-"}, 14);

    return 0;
}
