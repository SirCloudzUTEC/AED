#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

/*
Problema: Puntuación de paréntesis

Dada una cadena balanceada s compuesta únicamente por los caracteres '(' y ')',
calcula su puntuación de acuerdo con las siguientes reglas:

1. "()" tiene puntuación 1
2. AB tiene puntuación A + B, donde A y B son cadenas balanceadas
3. "(A)" tiene puntuación 2 * A, donde A es una cadena balanceada

Debes implementar una solución en tiempo O(n).

Restricciones:
- 2 <= s.length <= 10^5
- s contiene únicamente '(' y ')'
- s es una cadena balanceada
*/

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


class Solution {
public:
    int scoreOfParentheses(string s) {
        Stack<char> parentesis;
        Stack<int> resultados;

        for (int i=0; i<s.length();i++){
            if (s[i]=='('){
                parentesis.push('(');
            }
            if (s[i]==')'){
                int temp=1;
                parentesis.pop();
                if (parentesis.isEmpty()){
                    resultados.push(temp);
                }
                else if (s[i]=='('){
                    temp++;
                    resultados.push(2*temp+1);
                    parentesis.pop();

                }
                else{
                    
                    resultados.push(temp);
                }
            }
        }

        int suma=0;
        while (!resultados.isEmpty()){
            suma+=resultados.top();
            resultados.pop();
        }
        
        return suma;
    }
};

void runTest(const string& s, int expected) {
    Solution sol;
    int result = sol.scoreOfParentheses(s);

    cout << "Input: \"" << s << "\"\n";
    cout << "Esperado: " << expected << "\n";
    cout << "Obtenido: " << result << "\n";
    cout << (result == expected ? "[OK]" : "[ERROR]") << "\n";
    cout << "-----------------------------\n";

}

int main() {
    // Test 1: caso mínimo
    runTest("()", 1);

    // Test 2: un par anidado
    runTest("(())", 2);

    // Test 3: concatenación simple
    runTest("()()", 2);

    // Test 4: mezcla de anidación y concatenación
    runTest("(()(()))", 6);

    // Test 5: anidación más profunda
    runTest("((()))", 4);

    // Test 6: varias concatenaciones independientes
    runTest("()()()", 3);

    // Test 7: combinación no trivial
    runTest("(()())", 4);

    // Test 8: combinación más extensa
    runTest("((())())", 6);

    cout << "Todos los tests pasaron correctamente.\n";
    return 0;
}
