#include <iostream>
#include <fstream>
#include "AVLTree.h"
#include <string>
#include <chrono>
using namespace std;

int main(int argc, char* argv[]){
    clock_t start, end;
    double duration;
    
    //Start Clock
    start = clock();

    AVLTree tree;
    string operation, SSN, firstName, lastName;
    int insert = 0, deleteCount = 0, retrieve = 0;

    fstream input(argv[1]); //Takes in input of the files
    while (input >> operation >> SSN >> firstName >> lastName){
        string name = firstName + " " + lastName;
        bool result;                             //Checks if the operation is "i", "r", "d"
        if(operation == "i"){
            result = tree.insert(SSN, name);
            if(result){
                insert++;
            }
        }
        else if(operation == "d"){
            result = tree.deleteNode(SSN);
            if(result){
                deleteCount++;
            }
        }
        else if(operation == "r"){
            bool found = tree.find(SSN);
            if (found){
                retrieve++;
            }
        }
    }
    
    input.close();
    int treeHeight = tree.height(tree.getRoot());  //Gets height of the tree
    
    //Stops clock
    end = clock();
    duration = (end - start) / (double) CLOCKS_PER_SEC;

    cout << "The Number of Valid Insertion: " << insert << endl;
    cout << "The Number of Valid Deletion: " << deleteCount << endl;
    cout << "The Number of Valid Retrieval: " << retrieve << endl;
    cout << "The height of the AVL tree: " << treeHeight << endl;
    cout << "Time elapsed: " << duration << endl;
    tree.levelOrder();

    return 0;
}
