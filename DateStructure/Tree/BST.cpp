#include <bits/stdc++.h>
using namespace std;



struct TreeNode{
    int data;
    TreeNode *left,*right;
    int size,count;
    TreeNode(int value):data(value),size(1),count(1),left(nullptr),right(nullptr){}
};
template <typename T=int>
class BST{
private:
public:
    TreeNode* insert(TreeNode* root,T value){
        if(root==nullptr){
            return new TreeNode(value);
        }
        if(value<root->data){
            root->left=insert(root->left,value);
        }
        else if(value>root->data){
            root->right=insert(root->right,value);
        }
        else{
            root->count++;
        }
        root->size=root->count+(root->left?root->left->size:0)+(root->right?root->right->size:0);
        return root;
    }
    
    bool search(TreeNode* root,T value){
        if(root==nullptr) return false;
        if(root->data==value) return true;
        else if(value>root->data) return search(root->right,value);
        else return search(root->left, value);
    }

    TreeNode* findMin(TreeNode* root){
        if(root==nullptr) return root;
        while(root->left!=nullptr){
            root=root->left;
        }
        return root;
    }
    TreeNode* findMax(TreeNode* root){
        if(root==nullptr) return root;
        while(root->right!=nullptr){
            root=root->right;
        }
        return root;
    }

    TreeNode* remove(TreeNode* root,T value){
        if(root==nullptr) return root;
        if(value<root->data){
            root->left=remove(root->left,value);
        }
        else if(value>root->data){
            root->right=remove(root->right,value);
        }
        else{
            if(root->count>1){
                root->count--;
            }
            else{
                if(root->left==nullptr){
                    TreeNode* tmp=root->right;
                    delete root;
                    return tmp;
                }
                else if(root->right==nullptr){
                    TreeNode* tmp=root->left;
                    delete root;
                    return tmp;
                }
                else{
                    TreeNode* tmp=findMin(root->right);
                    root->data=tmp->data;
                    root->count=tmp->count;
                    tmp->count=1;
                    root->right=remove(root->right,tmp->data);
                }
            }
        }
        root->size=root->count+(root->left?root->left->size:0)+(root->right?root->right->size:0);
        return root;
    }

    int qryRank(TreeNode* root,T value){
        if(root==nullptr) return 0;
        if(value==root->data) return (root->left?root->left->size:0)+1;
        if(value>root->data) return qryRank(root->right,value)+(root->count)+(root->left?root->left->size:0);
        else return qryRank(root->left,value);
    }
    T qryth(TreeNode* root,int k){
        if(root==nullptr) return -1;
        if(root->left){
            if(root->left->size>=k) return qryth(root->left,k);
            if(root->left->size+root->count>=k) return root->data;
        }
        else {
            if(k<=root->count) return root->data;
        }
        return qryth(root->right,k-(root->left?root->left->size:0)-root->count);
    }
};




