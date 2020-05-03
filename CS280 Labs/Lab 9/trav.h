#include <map>
#include <iostream>

class Tree {
    Tree	*left;
    Tree	*right;
    int		node;
    
    static std::map<int, Tree*> allNodes;
    
public:
    Tree(int n, Tree *l=0, Tree *r=0) : left(l), right(r), node(n) {
        allNodes[n] = this;
    }
    
    int GetNode() { return node; }
    
    void Insert(Tree *newnode) {
       if( newnode->node == this->node )
            return;
        if (newnode->node < this->node){
            if(left != NULL){
           left->Insert(newnode);
            }
            else{
             left = newnode;
            }
        }
        if (newnode->node > this->node){
           if(right != NULL){
           right->Insert(newnode); 
           }
           else{
               right = newnode;
           }
           
        }
    }
    
    int Find(int node) {
      if(this->node == node){
           cout<< "Finding "<<node<<": "<<node<<endl; 
      return node;}
      else if(this->node < node){
          if(right!=NULL){
              return right->Find(node);}
          cout<< "Finding "<<node<<": "<<-1<<endl;
          return -1;
      }
      else{
         if(left!=NULL){
              return left->Find(node);}
          cout<< "Finding "<<node<<": "<<-1<<endl;
          return -1;
      }
        cout<< "Finding "<<node<<": "<<-1<<endl;
        return -1;
    }
    
    
    
    void Print(Tree *root) {
        if(root!=NULL){
        Print(root->left); 
        cout<< root->node << endl;
        Print(root->right); 
        }
        return;
        }
};