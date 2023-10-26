#include <iostream>
#include <vector>
/*
    This class will be adapted for the problem of Advent of Code
    The member variables could be altered

    In this case, the nodes will be directories. I need to store its
    name and its size

    How to use:
        - Create a root node like: NonBinaryNode* root = new NonBinaryNode(NULL, "root");
        - Create children like: NonBinaryNode* child1 = new NonBinaryNode(root, "child1");
*/

class NonBinaryNode{

private:
    std::string name;
    double size;

    NonBinaryNode* parent;
    std::vector <NonBinaryNode*> children;

public:
    // Constructor
    NonBinaryNode(NonBinaryNode* parent, std::string name){

        this->parent = parent;
        if(parent)
            parent->add_child(this);
        this->name = name;
        size = 0;
    }

    // Destructor
    virtual ~NonBinaryNode(){};

    // Member methods

    void add_child(NonBinaryNode* child){
        children.push_back(child);
    }

    void increaseSize(double size){
        this->size += size;
    }

    NonBinaryNode* getParent(){
        return this->parent;
    }

    std::vector <NonBinaryNode*> getChildren(){
        return this->children;
    }

    std::string getName(){
        return this->name;
    }

    double getSize(){
        return this->size;
    }

};