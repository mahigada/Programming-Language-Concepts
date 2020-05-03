//Mahi Gada
//CS280
/*
In this lab we will create and traverse trees.
You will be given code that reads integers from the standard input. 
You may assume these are positive ints only and need no error checking on input.
You will write code that inserts these integers into nodes in a binary tree.
When inserting a node in a tree, the node is inserted into the left subtree if the integer in the new node is less 
than the current node. It is inserted into the right subtree if greater than the current node. It is ignored 
(that is, not inserted) if equal to the current node.
The sequence 4 5 3 5 generates this tree:
Then, based on command line arguments, you will either:
do an inorder traversal of the tree and print out the traversal
find a value in the tree and print it out if found
The first action is triggered when argv[1] == "print". If it is, do an inorder traversal and print each tree node, one node per line of output. 
An inorder traversal means to traverse the left subtree (if one exists), then print the current node, then traverse the right subtree (if one exists).
The second action is triggered when argv[1] == "find". 
If it does, search the tree for argv[2] (a string which you will need to convert to an int). 
If found, print the int. If not found, print -1. The output format should be one line:
Finding number-you-are-searching-for: result
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "trav.h"
std::map<int, Tree*> Tree::allNodes;
// trav print
// trav find X
int
main(int argc, char *argv[])
{
    if( argc < 2 )
        return 0;
    string cmd(argv[1]);
    // READ IN THE INTEGERS
    vector<int> ids;
    int input;
    while( cin >> input ) {
        ids.push_back( input );
    }
    // MAKE NODES FROM THE INTEGERS
    vector<Tree*> nodes;
    for( int id: ids ) {
        nodes.push_back( new Tree(id) );
    }
    if( ids.size() == 0 )
        return -1;
    
    // PUT NODES INTO A TREE USING Insert
    Tree *theTree = nodes[0];
    
    if( theTree == nullptr )
        return -1;
    
    for( auto n : nodes ) {
        theTree->Insert(n);
    }
    
    // PRINT TREE
    if( cmd == "print" ) {
    	theTree->Print(theTree);
    }
    if (cmd =="find"){
        int num = stoi(argv[2]);
        theTree->Find(num);
         
    }
    // SEARCH TREE FOR ARGV[2]
    // INSERT CODE HERE
    return 0;
}
