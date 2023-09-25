#include <iostream>
#include <string>
using namespace std;

struct AVLNode{
  string ssn;
  string name;
  AVLNode *left;
  AVLNode *right;
  AVLNode *parent;
  int height;
    
  AVLNode(string ss, string na);
};
