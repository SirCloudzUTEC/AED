#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

// Problema 1
string solve1(const string& s) {
    Stack<char> res;
    for (int i=0; i<s.length();i++){
        if (s[i]=='*'){
            res.pop();
        }
        else{
            res.push(s[i]);
        }
    }

    string sal;
    while (!res.isEmpty()){
        sal = res.top()+sal;
        res.pop();
    }

    return sal;

}   

// Problema 2
string solve2(const string& path) {
    vector<string> st;
    string palabra;

    for (int i = 0; i <= path.size(); i++) {
        if (i < path.size() && path[i] != '/') {
            palabra += path[i];
        } else {
            if (!palabra.empty()) {
                if (palabra == "..") {
                    if (!st.empty()) st.pop_back();
                } else if (palabra != ".") {
                    st.push_back(palabra);
                }
                palabra.clear();
            }
        }
    }

    string res;
    for (const auto& dir : st) {
        res += "/" + dir;
    }

    return res.empty() ? "/" : res;
}

// Problema 3
bool solve(const vector<int>& pushed, const vector<int>& popped) {
    Stack<int> temp;
    int idx=0;
    for (int pusheado:pushed){
        temp.push(pusheado);
        while(!temp.isEmpty() && temp.top() == popped[idx]){
            temp.pop();
            idx++;
        }
    }
    return temp.isEmpty();
}

// Problema 4
string solve(const string& s) {
    Stack<int> nums;
    Stack<string> strs;
    string current = "";
    int num = 0;

    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        } 
        else if (c == '[') {
            nums.push(num);
            strs.push(current);
            num = 0;
            current = "";
        } 
        else if (c == ']') {
            int times = nums.top(); nums.pop();
            string prev = strs.top(); strs.pop();
            string temp = "";
            for (int i = 0; i < times; i++) {
                temp += current;
            }
            current = prev + temp;
        } 
        else {
            current += c;
        }
    }

    return current;
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
