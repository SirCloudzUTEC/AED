#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

class Solution {
private:
    unordered_set<int> markedSet;
    int totalFound;
    TreeNode* answer;

public:
    TreeNode* lowestCommonAncestorOfMarked(TreeNode* root, vector<int>& marked) {
        if (!root || marked.empty()) return nullptr;
        
        if (markedSet.empty()) {
            for (int x : marked) {
                markedSet.insert(x);
            }
            totalFound = 0;
            answer = nullptr;
        }

        TreeNode* left = root->left ? lowestCommonAncestorOfMarked(root->left, marked) : nullptr;
        TreeNode* right = root->right ? lowestCommonAncestorOfMarked(root->right, marked) : nullptr;

        if (markedSet.count(root->val)) {
            return root;
        }

        if (left && right) {
            return root;
        }

        return left ? left : right;
    }

};

TreeNode* node(int val, TreeNode* left = nullptr, TreeNode* right = nullptr) {
    return new TreeNode(val, left, right);
}

void runTest(int testNumber, TreeNode* root, vector<int> marked, int expectedValue) {
    Solution sol;
    TreeNode* ans = sol.lowestCommonAncestorOfMarked(root, marked);

    cout << "Test " << testNumber << ": ";

    if (expectedValue == INT_MIN) {
        if (ans == nullptr) {
            cout << "PASO";
        } else {
            cout << "FALLO";
        }
        cout << " | Esperado: null"
             << " | Obtenido: " << (ans ? to_string(ans->val) : "null") << endl;
        return;
    }

    if (ans != nullptr && ans->val == expectedValue) {
        cout << "PASO";
    } else {
        cout << "FALLO";
    }

    cout << " | Esperado: " << expectedValue
         << " | Obtenido: " << (ans ? to_string(ans->val) : "null") << endl;
}

int main() {
    TreeNode* t1 = node(3,
        node(5, node(6), node(2, node(7), node(4))),
        node(1, node(0), node(8)));

    runTest(1, t1, vector<int>{7, 4}, 2);
    runTest(2, t1, vector<int>{6, 4}, 5);
    runTest(3, t1, vector<int>{6, 0}, 3);
    runTest(4, t1, vector<int>{5}, 5);
    runTest(5, t1, vector<int>{10, 20}, INT_MIN);
    runTest(6, t1, vector<int>{7, 4, 6}, 5);
    runTest(7, t1, vector<int>{7, 4, 8}, 3);

    TreeNode* t2 = node(1, node(2, node(3, node(4), nullptr), nullptr), nullptr);
    runTest(8, t2, vector<int>{3, 4}, 3);
    runTest(9, t2, vector<int>{2, 4}, 2);

    runTest(10, nullptr, vector<int>{1, 2}, INT_MIN);

    return 0;
}
