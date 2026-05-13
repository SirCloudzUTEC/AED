#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cassert>

using namespace std;

struct TreeNode {
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode() : val(0), left(nullptr), right(nullptr) {}
 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 TreeNode(int x, TreeNode *left, TreeNode *right) : val(x),
 left(left),
 right(right) {}
};

struct DFS{
    TreeNode* node;
    int depth;
};

class Solution{
public:

    TreeNode* solve(TreeNode* root){
        return nullptr;
    }

    TreeNode* constructor(vector<int>& nums, int left, int right){
        if (left>right) return nullptr;

        int mid = left + (right-left) / 2;

        TreeNode* root = new TreeNode(nums[mid]);
        root->left = constructor(nums,left,mid-1);
        root->right = constructor(nums,mid+1, right);
        return root;
    }

    // Input: nums = [-10,-3,0,5,9]
    // Output: [0,-3,9,-10,null,5]
    TreeNode* sortedArrayToBST(vector<int>& nums){
       return constructor(nums, 0, nums.size()-1);
    }

    // ===================================================================
    // Algoritmos de Orden

    void inorder(TreeNode* root, vector<int>&v){
        if (!root) return ;
        inorder(root->left,v);

        v.push_back(root->val);
        inorder(root->right,v);
    }

    void preoder(TreeNode* root, vector<int>&v){
        if(!root) return;

        v.push_back(root->val);

        preoder(root->left,v);
        preoder(root->right,v);
    }

    void postorder(TreeNode* root, vector<int>& v){
        if(!root) return ;

        postorder(root->left,v);
        postorder(root->right,v);

        v.push_back(root->val);
    }

    int amountOfTime(TreeNode* root, int start) {
        if (root->val == start) return 0;
        if (!root) nullptr;
        int cont=0;

        TreeNode* izq;
    }

    TreeNode* build(vector<int>& nums, int left, int right){
        if (left >right) return nullptr;

        int maxIdx = left;
        for (int i = 0; i<=right;i++){
            if (nums[i] > nums[maxIdx]){
                maxIdx = i;
            }
        }

        TreeNode* root = new TreeNode(nums[maxIdx]);

        root->left = build(nums, left, maxIdx -1);
        root->right = build(nums, maxIdx+1, right);
        return root;
    }

    TreeNode* magic (vector<int> & nums){
            return build(nums, 0, nums.size()-1);
    }

    DFS dfs(TreeNode* root){
        if (!root) return {nullptr, 0};

        DFS left = dfs(root->left);
        DFS right = dfs(root->right);

        if (left.depth>right.depth){
            return {left.node, left.depth+1};
        }
        if (right.depth>left.depth){
            return {right.node, right.depth+1};
        }

        return {root, left.depth+1};
    }

    TreeNode* LowestCommonAncestor(TreeNode* root){
        return dfs(root).node;
    }

    int dfsGN(TreeNode* root, int maximum){
        if (!root) return 0;

        int count = 0;

        if(root->val >= maximum) count = 1;

        maximum = max(root->val, maximum);

        count += dfsGN(root->left, maximum);
        count += dfsGN(root->right, maximum);
    
        return count;
    }

    int goodNodes(TreeNode* root){
        if (!root) return 0;
        return dfsGN(root, root->val);
    }



};



int main(){
    Solution sol;
    // Test 1: Single node
    TreeNode* test1 = new TreeNode(5);
    assert(sol.goodNodes(test1) == 1);
    // Test 2: Tree with some good nodes
    TreeNode* test2 = new TreeNode(3);
    test2->left = new TreeNode(1);
    test2->left->left = new TreeNode(3);
    test2->right = new TreeNode(4);
    test2->right->right = new TreeNode(5);
    assert(sol.goodNodes(test2) == 4);
    // Test 3: Árbol con todos los nodos iguales
    TreeNode* test3 = new TreeNode(2);
    test3->left = new TreeNode(2);
    test3->right = new TreeNode(2);
    test3->left->left = new TreeNode(2);
    test3->left->right = new TreeNode(2);
    assert(sol.goodNodes(test3) == 5); // todos son "good nodes"
    // Test 4: Árbol creciente en línea recta (derecha)
    TreeNode* test4 = new TreeNode(1);
    test4->right = new TreeNode(2);
    test4->right->right = new TreeNode(3);
    test4->right->right->right = new TreeNode(4);
    assert(sol.goodNodes(test4) == 4); // cada nodo es mayor que el anterior
    // Test 5: Árbol decreciente
    TreeNode* test5 = new TreeNode(5);
    test5->left = new TreeNode(3);
    test5->left->left = new TreeNode(1);
    test5->right = new TreeNode(4);
    assert(sol.goodNodes(test5) == 1); // solo la raíz
    // Test 6: Árbol donde cada hijo izquierdo es mayor que el padre
    TreeNode* test6 = new TreeNode(1);
    test6->left = new TreeNode(2);
    test6->left->left = new TreeNode(3);
    assert(sol.goodNodes(test6) == 3); // todos son good nodes
    // Test 7: Árbol zig-zag con algunos valores menores
    TreeNode* test7 = new TreeNode(3);
    test7->right = new TreeNode(1);
    test7->right->left = new TreeNode(4);
    assert(sol.goodNodes(test7) == 2); // 3 y 4 son good nodes
    // Test 8: Árbol con valores negativos
    TreeNode* test8 = new TreeNode(-1);
    test8->left = new TreeNode(-2);
    test8->right = new TreeNode(-3);
    assert(sol.goodNodes(test8) == 1); // solo -1 es good node
    // Test 9: Árbol más complejo con mezcla de buenos y no buenos nodos
    TreeNode* test9 = new TreeNode(5);
    test9->left = new TreeNode(1);
    test9->right = new TreeNode(7);
    test9->right->left = new TreeNode(6);
    test9->right->right = new TreeNode(9);
    assert(sol.goodNodes(test9) == 3); // 5, 7, 9
    // Test 10: Árbol vacío
    TreeNode* test10 = nullptr;
    assert(sol.goodNodes(test10) == 0);
    std::cout << "All tests passed!\n";
    return 0;
}