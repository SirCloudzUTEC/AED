#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    Node* prev;
    Node* next;

    Node(int _val) : val(_val), prev(nullptr), next(nullptr) {}
};

class Solution {
public:
    Node* deleteAtIndex(Node* head, int index) {
        if (head == nullptr) return nullptr;

        if (index == 0 ){
            if(head->next != nullptr){
                head = head->next;
                return head;
            }
            head = head->next;
        }

        Node* curr=head;

        for (int i=0; i<index; i++){
            if (curr->next == nullptr) return head;
            curr = curr->next;
        }

        if(curr==nullptr) return head;

        Node* nextHead = curr->next;
        Node* prevHead = curr->prev;

        if(nextHead) nextHead->prev = prevHead;
        if(prevHead) prevHead->next = nextHead;

        delete curr;
        return head;
    }
        
};

// Construir lista
Node* buildList(const vector<int>& values) {
    if (values.empty()) return nullptr;

    Node* head = new Node(values[0]);
    Node* curr = head;

    for (int i = 1; i < (int)values.size(); i++) {
        Node* node = new Node(values[i]);
        curr->next = node;
        node->prev = curr;
        curr = node;
    }

    return head;
}

// Convertir a vector
vector<int> toVector(Node* head) {
    vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Imprimir vector
void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]";
}

// Liberar memoria
void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Test
void runTest(const vector<int>& input, int index, const vector<int>& expected, int testNumber) {
    Solution sol;
    Node* head = buildList(input);
    Node* result = sol.deleteAtIndex(head, index);
    vector<int> output = toVector(result);

    cout << "Caso " << testNumber << ": ";
    printVector(input);
    cout << ", index = " << index << " -> ";
    printVector(output);
    cout << " | esperado: ";
    printVector(expected);

    if (output == expected) cout << "  OK";
    else cout << "  NO";
    cout << "\n";

    deleteList(result);
}


int main() {
    runTest({}, 0, {}, 1);                       // lista vacía
    runTest({10}, 0, {}, 2);                     // eliminar único nodo
    runTest({1,2,3}, 0, {2,3}, 3);               // eliminar cabeza
    runTest({1,2,3,4}, 2, {1,2,4}, 4);           // eliminar en medio
    runTest({5,6,7}, 5, {5,6,7}, 5);             // índice inválido

    return 0;
}
