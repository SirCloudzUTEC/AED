
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
// Problema 2: Same Tree
// Función: bool isSameTree(TreeNode* p, TreeNode* q)
// ============================================================

class SolutionSameTree {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (!p && !q) return true;
        if(!p || !q) return true;
        //if ( p == q ) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }
};

void testSameTree() {
    SolutionSameTree sol;
    string p = "isSameTree";

    printResult(p, 1, sol.isSameTree(nullptr, nullptr) == true);

    TreeNode* a2 = node(1);
    printResult(p, 2, sol.isSameTree(a2, nullptr) == false);
    deleteTree(a2);

    TreeNode* a3 = node(1);
    TreeNode* b3 = node(1);
    printResult(p, 3, sol.isSameTree(a3, b3) == true);
    deleteTree(a3); deleteTree(b3);

    TreeNode* a4 = node(1);
    TreeNode* b4 = node(2);
    printResult(p, 4, sol.isSameTree(a4, b4) == false);
    deleteTree(a4); deleteTree(b4);

    TreeNode* a5 = node(1, node(2), node(3));
    TreeNode* b5 = node(1, node(2), node(3));
    printResult(p, 5, sol.isSameTree(a5, b5) == true);
    deleteTree(a5); deleteTree(b5);

    TreeNode* a6 = node(1, node(2), nullptr);
    TreeNode* b6 = node(1, nullptr, node(2));
    printResult(p, 6, sol.isSameTree(a6, b6) == false);
    deleteTree(a6); deleteTree(b6);

    TreeNode* a7 = node(1, node(2, node(4), nullptr), node(3));
    TreeNode* b7 = node(1, node(2, node(5), nullptr), node(3));
    printResult(p, 7, sol.isSameTree(a7, b7) == false);
    deleteTree(a7); deleteTree(b7);

    TreeNode* a8 = node(-1, node(-2), node(-3));
    TreeNode* b8 = node(-1, node(-2), node(-3));
    printResult(p, 8, sol.isSameTree(a8, b8) == true);
    deleteTree(a8); deleteTree(b8);

    TreeNode* a9 = node(1, node(2, node(4), node(5)), node(3));
    TreeNode* b9 = node(1, node(2, node(4), nullptr), node(3));
    printResult(p, 9, sol.isSameTree(a9, b9) == false);
    deleteTree(a9); deleteTree(b9);

    TreeNode* a10 = node(10, node(5, node(3), node(7)), node(15));
    TreeNode* b10 = node(10, node(5, node(3), node(7)), node(15));
    printResult(p, 10, sol.isSameTree(a10, b10) == true);
    deleteTree(a10); deleteTree(b10);
}

int main() {
    cout << "===== TESTS DE ÁRBOLES BINARIOS Y BST =====\n\n";


    testSameTree();
    cout << '\n';

   
    return 0;
}
