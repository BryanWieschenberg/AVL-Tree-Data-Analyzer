#include <iostream>
#include <string>
#include "AVLTree.h"
#include <iomanip>
#include <queue>
using namespace std;

AVLTree::AVLTree(){
    root = nullptr;
}

AVLTree::~AVLTree(){
    

}

AVLNode* AVLTree::getRoot(){
    return root;
}


// search value ss in the AVL tree
bool AVLTree::find(string ss){
    if (root == nullptr) {
        return false;
    }
    
    AVLNode* node = root;
    
    while (node != nullptr) {
        if (ss.compare(node->ssn) == 0) {
            return true;
        }
        if (ss.compare(node->ssn) < 0) {
            node = node->left;
        }
        else{
            node = node->right;
        }
    }
    return false;
}

// return the height of the subtree rooted at node
// if subtree is empty, height is -1
// if subtree has one node, height is 0
int AVLTree::height(AVLNode* node){
    
    if(node != nullptr){
        return node->height;
    }
    else{
        return -1;
    }
}

// return the balance factor of the node
int AVLTree::balanceFactor(AVLNode* node){
    return height(node->left) - height(node->right);
}

// update the height of the node
// this should be done whenever the tree is modified
void AVLTree::updateHeight(AVLNode* node){
    int hl = height(node->left);
    int hr = height(node->right);
    node->height = (hl>hr ? hl : hr) + 1;
}


// rotate right the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateRight(AVLNode* node){
    AVLNode* lp = node->left;      // left child of node
    if (node->parent!=nullptr) {  // node is not root
        if (node->parent->left == node) { // node is a left child
            node->parent->left = lp;
        }else{
            node->parent->right = lp;     // node is a right child
        }
    }

    if (lp->right != nullptr) {           // pointer update
        lp->right->parent = node;
    }
    
    lp->parent = node->parent;
    node->left = lp->right;
    lp->right = node;
    node->parent = lp;
    updateHeight(node);                   // after rotation, update height
    updateHeight(lp);                     // after rotation, update height
    if (node == root) {
        root = lp;
    }
    return lp; // lp is the new root of the subtree
}


// rotate left the subtree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::rotateLeft(AVLNode* node){
    AVLNode* rp = node->right;
    if (node->parent!=nullptr) {
        if (node->parent->left == node) {
            node->parent->left = rp;
        }else{
            node->parent->right = rp;
        }
    }

    if (rp->left != nullptr) {
       rp->left->parent = node;
    }
    
    rp->parent = node->parent;
    
    node->right = rp->left;
    rp->left = node;
    node->parent = rp;
    node->parent = rp;
    updateHeight(node);
    updateHeight(rp);
    if (node == root) {
        root = rp;
    }
    return rp;
}


// rebalance a tree rooted at node
// return the new root of the subtree
AVLNode* AVLTree::balance(AVLNode* node){
    updateHeight(node);
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left); // for left right case
        }
        
        AVLNode* temp = rotateRight(node);
        updateHeight(temp);
        return temp;
    }
    
    if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);  // for right left case
        }
        AVLNode* temp2 = rotateLeft(node);
        updateHeight(temp2);
        return temp2;
    }
    return node;
}

// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
// insert a new node with (ss, na) to the AVL tree
// if there exists ss value, return false
// otherwise, insert it, balance the tree, return true
bool AVLTree::insert(string ss, string na){
    if(find(ss)){  //If there is already the same SSN it does not add it
        return false;
    }
    
    AVLNode* new_node = new AVLNode(ss, na);
    if(root == nullptr){ //If this is a new SSN it create a new_Node and returns true
        root = new_node;
        return true;
    }
    
    AVLNode* cur = root; //This makes a temp root
    
    while(true){
        if(ss < cur->ssn){
            if(cur->left == nullptr){
                cur->left = new_node;
                new_node->parent = cur;
                break;
            }
            cur = cur->left;
        }
        else{
            if(cur->right == nullptr){
                cur->right = new_node;
                new_node->parent = cur;
                break;
            }
            cur = cur->right;
        }
    }
    
    //rebalance the tree
    while(cur != nullptr){
        cur = balance(cur);
        cur = cur->parent;
    }
    
    return true;
}


AVLNode* AVLTree::maxOfSubtree(AVLNode* node){
    if (node == nullptr) {
        return nullptr;
    }
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

// delete the node containing value ss
// if there is not such node, return false
// otherwise, delete the node, balance the tree, return true
// delete node with ss from the AVL tree
// if there is no such node, return false
// otherwise, delete it, balance the tree, return true
bool AVLTree::deleteNode(string ss){
    AVLNode* node = root;

    //find the node to delete
    while (node != nullptr){
        if (ss.compare(node->ssn) == 0){
            break;
        }
        if (ss.compare(node->ssn) < 0){
            node = node->left;
        }
        else{
            node = node->right;
        }
    }

    // node not found
    if (node == nullptr){
        return false;
    }

    // case 1: node is a leaf
    if (node->left == nullptr && node->right == nullptr){
        if (node == root){
            root = nullptr;
        }
        else if (node->parent->left == node){
            node->parent->left = nullptr;
        }
        else{
            node->parent->right = nullptr;
        }
        delete node;
    }
    // case 2: node has only one child
    else if (node->left == nullptr || node->right == nullptr){
        AVLNode* child = node->left == nullptr ? node->right : node->left;
        if (node == root){
            root = child;
        }
        else if (node->parent->left == node){
            node->parent->left = child;
        }
        else{
            node->parent->right = child;
        }
        child->parent = node->parent;
        delete node;
    }
    // case 3: node has two children
    else{
        // find the in-order successor (the leftmost node in the right subtree)
        AVLNode* successor = node->right;
        while (successor->left != nullptr){
            successor = successor->left;
        }

        // replace the node with its successor
        node->ssn = successor->ssn;
        node->name = successor->name;

        // delete the successor node (which has at most one child)
        AVLNode* child = successor->left == nullptr ? successor->right : successor->left;
        if (successor->parent->left == successor){
            successor->parent->left = child;
        }
        else{
            successor->parent->right = child;
        }
        if (child != nullptr){
            child->parent = successor->parent;
        }
        delete successor;
    }

    // balance the tree starting from the node's parent
    AVLNode* cur = node->parent;
    while (cur != nullptr){
        cur = balance(cur);
        cur = cur->parent;
    }

    return true;
}


// internal function
// do not call it directly
void AVLTree::print(AVLNode* x, int indent){
    if(x == nullptr) return;
    if (x->right != nullptr){
        print(x->right, indent+4);
    }
    
    if (indent != 0){
        cout << std::setw(indent) << ' ';
    }
    
    if(x->right != nullptr){
        cout << " /\n" << std::setw(indent) << ' ';
    }
    
    cout << x->ssn << endl;
    
    if (x->left != nullptr){
        cout << std::setw(indent) << ' ' <<" \\\n";
        print(x->left, indent+4);
    }
    
}

// print out the structure of the binary tree
// use it for debugging, I love this function
void AVLTree::print(){
    int count = 0;
    print(root, count);
}


// it does not level order traversal
// it prints out the number of node
// use it mainly for debugging
// Perform a level-order traversal of the tree and print out the SSN and name of each node
void AVLTree::levelOrder(){
    int nodeCount = 0;
    if (root == nullptr){
        return;
    }                //Returns how many nodes there are
    queue<AVLNode*> q;
    q.push(root);

    while (!q.empty()){
        AVLNode* node = q.front();
        q.pop();
        nodeCount++;
        if (node->left != nullptr){
            q.push(node->left);
        }
        if (node->right != nullptr){
            q.push(node->right);
        }
    }
    cout << "tree size... " << nodeCount << endl;
}
