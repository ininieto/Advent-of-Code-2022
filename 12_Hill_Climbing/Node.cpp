#pragma once
#include <iostream>
#include <vector>
/*
    This class will be adapted for the problem of Advent of Code 12/12/2022
    The member variables could be altered

    In this case, the nodes will be letters. The adjacent nodes will be treated as children,
    being the root node the S node. 

    How to use:
        - Create a root node like: NonBinaryNode* root = new NonBinaryNode(NULL, "root");
        - Create children like: NonBinaryNode* child1 = new NonBinaryNode(root, "child1");
*/

class Node{

private:
    int value;  // Ascii value of the letter assigned to the node
    bool checked;   

    Node* parent;
    std::vector <Node*> children;

public:
    // Constructor
    Node(Node* parent, int value){

        this->parent = parent;
        if(parent)
            parent->add_child(this);
        this->value = value;
        checked = false;
    }

    // Destructor
    virtual ~Node(){};

    // Member methods

    void add_child(Node* child){
        children.push_back(child);
    }

    void setChecked(){
        this->checked = true;
    }

    Node* getParent(){
        return this->parent;
    }

    std::vector <Node*> getChildren(){
        return this->children;
    }

    int getValue(){
        return this->value;
    }

};