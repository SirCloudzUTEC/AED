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
    Node* reverseDoublyLinkedList(Node* head) {
        if (head == nullptr) return nullptr;

        Node* temp=nullptr;
        Node* curr=head;

        while (curr!=nullptr){
            temp=curr->prev;

            curr->prev = curr->next;
            curr->next = temp;

            curr = curr->prev;
        }

        if (temp!=nullptr) head=temp->prev;

        return head;
    }
};

// Construye una lista doblemente enlazada a partir de un vector
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

// Convierte la lista a vector
vector<int> toVector(Node* head) {
    vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// Imprime un vector
void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]";
}

// Libera memoria
void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Ejecuta un caso de prueba
void runTest(const vector<int>& input, const vector<int>& expected, int testNumber) {
    Solution sol;
    Node* head = buildList(input);
    Node* result = sol.reverseDoublyLinkedList(head);
    vector<int> output = toVector(result);

    cout << "Caso " << testNumber << ": ";
    printVector(input);
    cout << " -> ";
    printVector(output);
    cout << " | esperado: ";
    printVector(expected);

    if (output == expected) cout << "  OK";
    else cout << "  NO";
    cout << "\n";

    deleteList(result);
}

int main() {
    runTest({}, {}, 1);
    runTest({5}, {5}, 2);
    runTest({1, 2}, {2, 1}, 3);
    runTest({1, 2, 3, 4}, {4, 3, 2, 1}, 4);
    runTest({10, 20, 30, 40, 50}, {50, 40, 30, 20, 10}, 5);

    return 0;
}
