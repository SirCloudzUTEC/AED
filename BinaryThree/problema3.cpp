
#include <bits/stdc++.h>
using namespace std;

/*
 Guía de laboratorio - Árboles Binarios y BST
 Profesor: Brenner Ojeda

 Este archivo contiene 8 plantillas estilo LeetCode.
 Cada problema incluye:
 - Estructura TreeNode.
 - Función que el estudiante debe implementar.
 - Solución de referencia.
 - 10 tests unitarios detallados.

 Para usarlo como plantilla de evaluación:
 1. Puede borrar el cuerpo de las funciones dentro de class Solution.
 2. Dejar los tests intactos.
 3. Compilar con: g++ -std=c++17 archivo.cpp -o main
*/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

TreeNode* node(int val, TreeNode* left = nullptr, TreeNode* right = nullptr) {
    return new TreeNode(val, left, right);
}

void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

vector<vector<int>> serializeByLevels(TreeNode* root) {
    vector<vector<int>> levels;
    if (!root) return levels;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; ++i) {
            TreeNode* cur = q.front();
            q.pop();
            level.push_back(cur->val);
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        levels.push_back(level);
    }
    return levels;
}

void printResult(const string& problem, int testNumber, bool passed) {
    cout << "[" << problem << "] Test " << testNumber << ": "
         << (passed ? "PASO" : "FALLO") << '\n';

}


// ============================================================
// Problema 3: Binary Tree Level Order Traversal
// Función: vector<vector<int>> levelOrder(TreeNode* root)
// ============================================================

class SolutionLevelOrder {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr){
            return ;}
        queue<TreeNode*>  q;
        q.push(root);
        vector<vector<int>> final;
        while (!q.empty()){
            TreeNode* node = q.front();
            q.pop();
            vector<TreeNode*> nivel;
            if (node->left != nullptr){
                q.push(node->left);
            }
            if (node->right != nullptr){
                q.push(node->right);
            }

            for (int i =0 ;i <q.size(); i++){
                nivel.push_back(q.back());
            }
            final.push_back(nivel);
        }
        return final;
    }

void testLevelOrder() {
    SolutionLevelOrder sol;
    string p = "levelOrder";

    printResult(p, 1, sol.levelOrder(nullptr) == vector<vector<int>>{});

    TreeNode* t2 = node(1);
    printResult(p, 2, sol.levelOrder(t2) == vector<vector<int>>{{1}});
    deleteTree(t2);

    TreeNode* t3 = node(1, node(2), node(3));
    printResult(p, 3, sol.levelOrder(t3) == vector<vector<int>>{{1}, {2, 3}});
    deleteTree(t3);

    TreeNode* t4 = node(3, node(9), node(20, node(15), node(7)));
    printResult(p, 4, sol.levelOrder(t4) == vector<vector<int>>{{3}, {9, 20}, {15, 7}});
    deleteTree(t4);

    TreeNode* t5 = node(1, node(2, node(3, node(4))));
    printResult(p, 5, sol.levelOrder(t5) == vector<vector<int>>{{1}, {2}, {3}, {4}});
    deleteTree(t5);

    TreeNode* t6 = node(1, nullptr, node(2, nullptr, node(3)));
    printResult(p, 6, sol.levelOrder(t6) == vector<vector<int>>{{1}, {2}, {3}});
    deleteTree(t6);

    TreeNode* t7 = node(1, node(2, node(4), node(5)), node(3, node(6), node(7)));
    printResult(p, 7, sol.levelOrder(t7) == vector<vector<int>>{{1}, {2, 3}, {4, 5, 6, 7}});
    deleteTree(t7);

    TreeNode* t8 = node(-1, node(-2), node(-3, node(-4), nullptr));
    printResult(p, 8, sol.levelOrder(t8) == vector<vector<int>>{{-1}, {-2, -3}, {-4}});
    deleteTree(t8);

    TreeNode* t9 = node(10, node(5, nullptr, node(7)), node(15, node(12), nullptr));
    printResult(p, 9, sol.levelOrder(t9) == vector<vector<int>>{{10}, {5, 15}, {7, 12}});
    deleteTree(t9);

    TreeNode* t10 = node(0, node(1, node(3), nullptr), node(2, nullptr, node(4, node(5), nullptr)));
    printResult(p, 10, sol.levelOrder(t10) == vector<vector<int>>{{0}, {1, 2}, {3, 4}, {5}});
    deleteTree(t10);
}

int main() {
    cout << "===== TESTS DE ARBOLES BINARIOS Y BST =====\n\n";

    testLevelOrder();
    cout << '\n';

    return 0;
}
}