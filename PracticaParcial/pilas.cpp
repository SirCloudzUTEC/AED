#include <iostream>
#include <vector>
#include <string>

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

class Solution {
public:
    bool isValid(string s) {
        Stack<char> izq;
        for (int i=0; i<s.length();i++){
            if (s[i]=='[' || s[i]=='{' || s[i]=='('){
                izq.push(s[i]);
            }
            else{
                if (izq.isEmpty()) return 0;

                char top = izq.top();
                izq.pop();

                if ((s[i]==')' && top != '(') || (s[i]=='}' && top != '{') || (s[i]==']' && top != '[')) return 0;
            }
        }
        return 1;
        
    }

    int evalRPN(vector<string>& tokens) {
        Stack<int> nums;
        int res;
        for (int i=0; i<tokens.size();i++){
            if (tokens[i] == "+" ){
                int num1=nums.top(); nums.pop();
                int num2=nums.top(); nums.pop();
                nums.push(num2+num1);
            }
            else if(tokens[i] != "-"){
                int num1=nums.top(); nums.pop();
                int num2=nums.top(); nums.pop();
                nums.push(num2-num1);
            }
            else if(tokens[i] != "*"){
                int num1=nums.top(); nums.pop();
                int num2=nums.top(); nums.pop();
                nums.push(num2*num1);
            }
            else if (tokens[i] != "/"){
                int num1=nums.top(); nums.pop();
                int num2=nums.top(); nums.pop();
                nums.push(num2/num1);
            }
            else{
                nums.push(stoi(tokens[i]));
            }
        }
        return res;
    }

    
    string decodeString(string s) {
        Stack<string> conjunto;
        string salida="",num="";
        for (int i=0;i<s.length();i++){
            if (isdigit(s[i])){
                num+=s[i];
            }
            else if(s[i] == '['){
                conjunto.push(salida);
                conjunto.push(num);
                salida="";
                num="";
            }
            else if (s[i] == ']'){
                int multiplo = stoi(conjunto.top());
                conjunto.pop();
                string concatenar = conjunto.top(), temp="";
                conjunto.pop();
                
                while (multiplo--){
                    temp += salida;
                }

                salida = concatenar + temp;
            }
            else{
                salida+=s[i];
            }
        }
        return salida;
    }

    string minRemoveToMakeValid(string s) {
        Stack<string> conjunto;
        string salida="", prueba;

        // Input: s = "lee(t(c)o)de)"
        // Output: "lee(t(c)o)de

        for (int i=0;i<s.length();i++){
            if (s[i] == '('){
                conjunto.push(prueba);
                salida="";
            }
            else if(s[i] == ')'){

            }
            else{
                prueba += s[i];
            }
        }

        return salida;
    }

    int postFixOperation(string input){
        int sum=0;
        Stack<int> ingresos;

        for (int i=0; i<input.length(); i++){
            char c = input[i];
            if (c == '+' || c == '-' || 
            c == '*' || c == '/'){
                int op2 = ingresos.top();
                ingresos.pop();
                int op1 = ingresos.top();
                ingresos.pop();

                switch(c){
                    case '+':
                        sum += op1+op2;
                        break;

                    case '-':
                        sum += op1-op2;
                        break;
                    
                    case '*':
                        sum += op1*op2;
                        break;
                    
                    case '/':
                        sum+= op1/op2;
                        break;    
                }
            }
            else{
                ingresos.push(input[i]-'0');
            }
        }

        return sum;
    }

    int operation(string input){

        Stack<int> ingresos;
        Stack<char> operadores;

        for (int i = 0; i < input.length(); i++){

            char c = input[i];

            if (isdigit(c)){

                ingresos.push(c - '0');
            }

            else if (c == '+' || c == '-' ||
                    c == '*' || c == '/'){

                while (!operadores.isEmpty() &&
                    ((operadores.top() == '*' || operadores.top() == '/') ||
                    ((c == '+' || c == '-') &&
                    (operadores.top() == '+' || operadores.top() == '-')))){

                    int op2 = ingresos.top();
                    ingresos.pop();

                    int op1 = ingresos.top();
                    ingresos.pop();

                    char oper = operadores.top();
                    operadores.pop();

                    int sum = 0;

                    switch(oper){

                        case '+':
                            sum = op1 + op2;
                            break;

                        case '-':
                            sum = op1 - op2;
                            break;

                        case '*':
                            sum = op1 * op2;
                            break;

                        case '/':
                            sum = op1 / op2;
                            break;
                    }

                    ingresos.push(sum);
                }

                operadores.push(c);
            }
        }

        while (!operadores.isEmpty()){

            int op2 = ingresos.top();
            ingresos.pop();

            int op1 = ingresos.top();
            ingresos.pop();

            char oper = operadores.top();
            operadores.pop();

            int sum = 0;

            switch(oper){

                case '+':
                    sum = op1 + op2;
                    break;

                case '-':
                    sum = op1 - op2;
                    break;

                case '*':
                    sum = op1 * op2;
                    break;

                case '/':
                    sum = op1 / op2;
                    break;
            }

            ingresos.push(sum);
        }

        return ingresos.top();
}

};

int main (){
    string input ="3+2+2*3";
    Solution res;
    cout<< res.operation(input)<<endl;

    return 0;
}