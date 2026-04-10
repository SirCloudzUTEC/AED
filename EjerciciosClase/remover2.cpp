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
    Node* deleteAllOccurrences(Node* head, int target) {
        if (head == nullptr) return nullptr;

        Node* curr = head;

        while (curr!= nullptr){
            Node* nextNode = curr->next;

            if (curr->val == target){
                if (curr == head){
                    head = curr->next;
                    if (head!=nullptr){
                        head->prev = nullptr;
                    }
                }

                else{
                    Node* dspNode = curr->next;
                    Node* antesNode = curr->prev;

                    if(dspNode) dspNode->prev = antesNode;
                    if(antesNode) antesNode->next = dspNode;
                }

                delete curr;
            }

            curr = nextNode;

        }
        return head;
}
};

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

vector<int> toVector(Node* head) {
    vector<int> result;
    while (head != nullptr) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

void printVector(const vector<int>& v) {
    cout << "[";
    for (int i = 0; i < (int)v.size(); i++) {
        cout << v[i];
        if (i + 1 < (int)v.size()) cout << ", ";
    }
    cout << "]";
}

void deleteList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void runTest(const vector<int>& input, int target, const vector<int>& expected, int testNumber) {
    Solution sol;
    Node* head = buildList(input);
    Node* result = sol.deleteAllOccurrences(head, target);
    vector<int> output = toVector(result);

    cout << "Caso " << testNumber << ": ";
    printVector(input);
    cout << ", target = " << target << " -> ";
    printVector(output);
    cout << " | esperado: ";
    printVector(expected);

    if (output == expected) cout << "  OK";
    else cout << "  NO";
    cout << "\n";

    deleteList(result);
}

int main() {
    runTest({}, 3, {}, 1);
    runTest({7}, 7, {}, 2);
    runTest({7}, 5, {7}, 3);
    runTest({1, 2, 3, 2, 4, 2}, 2, {1, 3, 4}, 4);
    runTest({5, 5, 5, 5}, 5, {}, 5);

    return 0;
}
