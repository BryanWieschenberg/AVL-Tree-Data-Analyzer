#include <iostream>
#include <string>
#include "AVLNode.h"
using namespace std;

class AVLTree{
    AVLNode* root;
        
    public:
    AVLTree();
    ~AVLTree();
    AVLNode* getRoot();                   // return root
    bool find(string ss);                 // search ss value in the AVL tree. if find, return true
    int height(AVLNode* node);            // return the height of the subtree rooted at node
    int balanceFactor(AVLNode* node);     // return the balance factor of node
    void updateHeight(AVLNode* node);     // update the height value of a given node
    AVLNode * rotateRight(AVLNode* node);  // rotate right the subtree rooted at node
    AVLNode * rotateLeft(AVLNode* node);   // rotate left the subtree rooted at node
    bool insert(string ss, string na);     // insert one pair of SSN and name to the BST
                                           // insert() function will rebalance if it is necessary
    void print(AVLNode* x, int indent);
    void print();                          // print out the structure of the tree, used for debugging
    AVLNode* balance(AVLNode* node);
    AVLNode* maxOfSubtree(AVLNode* node);    // find the node with largest value in the subtree
    bool  deleteNode(string ss);             // delete the node with value ss
    void levelOrder();                       // level order traversal. It prints out the number of nodes in the tree
};
