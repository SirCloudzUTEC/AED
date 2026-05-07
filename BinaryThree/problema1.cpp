
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
// Problema 1: Maximum Depth of Binary Tree
// Función: int maxDepth(TreeNode* root)
// ============================================================

class SolutionMaxDepth {
public:
    int maxDepth(TreeNode* root) {
        int conthi=-1,conthd=-1;
        
        if (root->left != nullptr) {
            conthi = maxDepth(root->left);
        }
        else{
            return 1;
        }
        if (root->right != nullptr) {
            conthd = maxDepth(root->right);

        }else{
            return 1;
        }

        return 1+max(conthi,conthd);
    }
};

void testMaxDepth() {
    SolutionMaxDepth sol;
    string p = "maxDepth";

    TreeNode* t1 = nullptr;
    printResult(p, 1, sol.maxDepth(t1) == 0);

    TreeNode* t2 = node(1);
    printResult(p, 2, sol.maxDepth(t2) == 1);
    deleteTree(t2);

    TreeNode* t3 = node(1, node(2), node(3));
    printResult(p, 3, sol.maxDepth(t3) == 2);
    deleteTree(t3);

    TreeNode* t4 = node(3, node(9), node(20, node(15), node(7)));
    printResult(p, 4, sol.maxDepth(t4) == 3);
    deleteTree(t4);

    TreeNode* t5 = node(1, node(2, node(3, node(4))));
    printResult(p, 5, sol.maxDepth(t5) == 4);
    deleteTree(t5);

    TreeNode* t6 = node(1, nullptr, node(2, nullptr, node(3, nullptr, node(4))));
    printResult(p, 6, sol.maxDepth(t6) == 4);
    deleteTree(t6);

    TreeNode* t7 = node(1, node(2, node(4), node(5)), node(3));
    printResult(p, 7, sol.maxDepth(t7) == 3);
    deleteTree(t7);

    TreeNode* t8 = node(-1, node(-2), node(-3, node(-4), nullptr));
    printResult(p, 8, sol.maxDepth(t8) == 3);
    deleteTree(t8);

    TreeNode* t9 = node(1, node(2, node(4, node(8)), node(5)), node(3, nullptr, node(7)));
    printResult(p, 9, sol.maxDepth(t9) == 4);
    deleteTree(t9);

    TreeNode* t10 = node(10, node(5, node(3), node(7)), node(15, node(12), node(20, node(18), node(25))));
    printResult(p, 10, sol.maxDepth(t10) == 4);
    deleteTree(t10);
}


int main() {
    cout << "===== TESTS DE ÁRBOLES BINARIOS Y BST =====\n\n";

    testMaxDepth();
    cout << '\n';

   
    return 0;
}
