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

string solve(const string& path) {
    int len=path.length();
    Stack<string>* pila;
    string res;
    int cont=0;
    for (int i=0;i<len;i++){
        if (path[i]!='/'){
            int j=i, idx=0;
            string palabra;
            while (path[j]!='/' && path[j]!= '.'){
                
                
                palabra[idx] = path[j];
                idx++;
                j++;
            }
            pila->push(palabra);
            cont++;
        }
    }

    for (int i=0;i<cont;i++){
        

        }   

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
    runTest(1, "/home/", "/home");
    runTest(2, "/../", "/");
    runTest(3, "/home//foo/", "/home/foo");
    runTest(4, "/a/./b/../../c/", "/c");
    runTest(5, "/home//foo/../bar/./baz/", "/home/bar/baz");
    return 0;
}
