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
        return dfsGN(root, root->val);
    }

    void INORDER(TreeNode* root, vector<int>& vec){
        if (!root) return;

        inorder(root->left, vec);
        vec.push_back(root->val);
        inorder(root->right,vec);
    }

   vector<int> magic(TreeNode* root1, TreeNode* root2){
        if (!root1 || !root2) return {};
        vector<int> salida;

        vector<int>r1;
        vector<int>r2;

        INORDER(root1, r1);
        INORDER(root2,r2);
        int cont1 = r1.size()-1, cont2 = r2.size()-1;
    
        while (cont1 >= 0 && cont2 >= 0){
            if (r1[cont1] > r2[cont2]){
                salida.push_back(r1[cont1]);
                cont1--;
            }
            else{
                salida.push_back(r2[cont2]);
                cont2--;
            }
        }

        while(cont1>=0){
            salida.push_back(r1[cont1]);
            cont1--;
        }

        while(cont2>=0){
            salida.push_back(r2[cont2]);
            cont2--;
        }

        return salida;
   }
};



int main(){ 
    
    
    return 0;
}