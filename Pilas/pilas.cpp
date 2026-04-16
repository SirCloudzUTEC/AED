#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T, int MAX_SIZE = 100>
class Stack {
private:
    T list[MAX_SIZE];
    int topIndex;

public:
    Stack() : topIndex(-1) {}

    bool isFull() const {
        return topIndex == MAX_SIZE - 1;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    void push(const T &value) {
        if (isFull()) {
            throw overflow_error("La pila esta llena");
        }
        list[++topIndex] = value;
    }

    void pop() {
        if (isEmpty()) {
            throw underflow_error("La pila esta vacia");
        }
        --topIndex;
    }

    T top() const {
        if (isEmpty()) {
            throw underflow_error("La pila esta vacia");
        }
        return list[topIndex];
    }

    void print() const {
        if (isEmpty()) {
            cout << "La pila esta vacia\n";
            return;
        }

        cout << "Pila (base -> cima): ";
        for (int i = 0; i <= topIndex; i++) {
            cout << list[i] << " ";
        }
        cout << "\n";
    }
};

string solve(const string& s) {
    int len = s.length();
    Stack<string>* res;
    for (int i=0; i<len;i++){
        if (s[i] == '*'){
            i++;
        }
        else{
            res->push(&s[i]);
        }

    }

    return &res;
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
