#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    // Siempre, siempre Inicializar en NUll
    //new->lower_than = lower_than;
    TreeMap* new = (TreeMap* ) malloc(sizeof(TreeMap));
    new->lower_than = lower_than;
    new->current = NULL;
    new->root = NULL;
    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) { 

    TreeNode* new = createTreeNode(key, value);
    if (tree->root == NULL)
    {
        tree->current = new; 
        tree->root = new ; return;    
    }

    if (searchTreeMap(tree, key) == NULL) // tree current es el padre gracias a esto //
    {
    if (tree->lower_than(tree->current->pair->key, key )  == 1){
        tree->current->right = new;
       
    }
    else if(tree->lower_than(key, tree->current->pair->key ) == 1){
        tree->current->left = new;
        new->parent = tree->current;
        tree->current = new;
    }
    }
}

TreeNode * minimum(TreeNode * x){
    TreeNode* current = x;

    while(current->left != NULL)
    {
        current = current->left;
    }
    return current;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if(tree->root == NULL || tree == NULL) return;
    
    if (node->left == NULL && node->right == NULL) // caso 1
    {
        if(tree->lower_than(node->pair->key, node->parent->pair->key) == 1){
        node->parent->left = NULL; 
        }else if (tree->lower_than(node->parent->pair->key, node->pair->key )  == 1)
        {
        node->parent->right = NULL;
        }
    }
    else if(node->right == NULL) // caso 2
    {
        TreeNode* son = node->left;
        node->pair = son->pair;
        node->right = son->right;
        node->left = son->left;

    }
    else if ( node->left == NULL) 
    {

        TreeNode* son = node->right;
        node->pair = son->pair;
        node->right = son->right;
        node->left = son->left;
  
    }
    else if(node->left != NULL && node->right != NULL)// caso 3 
    {
        TreeNode* current = node->right;
        TreeNode* min = minimum(current);
        node->pair = min->pair;
        removeNode(tree, min);
    }

    }


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* aux = tree->root;
    while(aux != NULL){
        tree->current = aux;
    if(tree->lower_than(key, aux->pair->key ) == 1){
        aux = aux->left;
    }else if (tree->lower_than(aux->pair->key, key )  == 1){
        aux = aux->right;
    }else {tree->current = aux; return aux->pair;}
    }
     return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {

    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* MinNode = minimum(tree->root);
    Pair* MinKey = MinNode->pair->key;
    return MinKey; //mickey xd

}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
