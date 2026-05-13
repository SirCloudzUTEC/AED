#include <iostream>
#include <vector>
#include <string>

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

    // 1 
    TreeNode* build(vector<int>&nums, int left, int right){
        if (left > right) return nullptr;

        int maxIDX = left;
        for (int i = 0; i<right; i++){
            if (nums[i] > maxIDX){
                maxIDX = i;
            }
        }

        TreeNode* root = new TreeNode(nums[maxIDX]); 
        root->left = build(nums, left, maxIDX-1);
        root->right = build(nums, maxIDX+1, right);

        return root;
    }

    TreeNode* magic (vector<int>& nums){
        return build(nums, 0, nums.size()-1);
    }

    // 2 
    DFS dfs(TreeNode* root){
        if (!root) return {nullptr, 0};

        DFS left = dfs(root->left);
        DFS right = dfs(root->right);
        
        if (left.depth > right.depth){
            return {left.node, left.depth+1};
        }
        
        if (left.depth < right.depth){
            return {right.node, right.depth+1};
        }

        return {root, left.depth+1};
    }

    TreeNode* LowestCommonAncestor(TreeNode* root){
        return dfs(root).node;
    }

    // 3

    int contDfs(TreeNode* root, int maximum){
        if (!root) return 0;

        int cont=0;
        if (root->val >= maximum){
            cont=1;
        }
        maximum = max(maximum, root->val);

        cont += contDfs(root->left, maximum);
        cont += contDfs(root->right, maximum);

        return cont;
    }

    int goodNodes(TreeNode* root){
        return contDfs(root, root->val);
    }


    //4
    void ordenamiento(TreeNode* root, vector<int>& a){
        if (!root) return;

        ordenamiento(root->left, a);
        a.push_back(root->val);
        ordenamiento(root->right, a);
    }

    vector<int> magic(TreeNode* root1, TreeNode* root2){
        if (!root1 || !root2) return {};
        vector<int> salida, cont1, cont2;
        
        ordenamiento(root1, cont1);
        ordenamiento(root2,cont2);
        
        int size1 = cont1.size()-1, size2 = cont2.size()-1;
        while (size1 >=0 && size2 >= 0){
            if (cont1[size1] > cont2[size2]){
                salida.push_back(cont1[size1]);
                size1--;
            }
            else{
                salida.push_back(cont2[size2]);
                size2--;
            }
        }

        while (size1>=0){
            salida.push_back(cont1[size1]);
            size1--;
        }

        while (size2>=0){
            salida.push_back(cont2[size2]);
            size2--;
        }

        return salida;
    }   



};

int main(){
    
    return 0;
}