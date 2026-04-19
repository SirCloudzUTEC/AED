#include <iostream>
#include <vector>
using namespace std;

bool solve(const vector<int>& pushed, const vector<int>& popped) {
    // TODO: Implementar simulación con pila
    return false;
}

void runTest(int testNumber, const vector<int>& pushed, const vector<int>& popped, bool expected) {
    bool result = solve(pushed, popped);
    if (result == expected) {
        cout << "Test " << testNumber << " OK\n";
    } else {
        cout << "Test " << testNumber << " FAILED\n";
        cout << "Esperado: " << (expected ? "true" : "false") << "\n";
        cout << "Obtenido: " << (result ? "true" : "false") << "\n\n";
    }
}

int main() {
    runTest(1, {1,2,3,4,5}, {4,5,3,2,1}, true);
    runTest(2, {1,2,3,4,5}, {4,3,5,1,2}, false);
    runTest(3, {1}, {1}, true);
    runTest(4, {1,2,3}, {3,2,1}, true);
    runTest(5, {1,2,3}, {2,1,3}, true);
    return 0;
}
