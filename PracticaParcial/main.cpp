#include <iostream>
#include <string>
#include <vector>

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

class Solution{
public:

    TreeNode* solve(TreeNode* root){
        return;
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

};

int main(){


    return 0;
}