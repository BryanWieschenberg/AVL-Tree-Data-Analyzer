#include <iostream>
#include <string>
#include "AVLNode.h"
using namespace std;

AVLNode::AVLNode(string ss, string na){
    ssn = ss;
    name = na;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    height = 0;
}
