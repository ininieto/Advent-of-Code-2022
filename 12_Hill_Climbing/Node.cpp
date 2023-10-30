#pragma once
#include <iostream>
#include <vector>
/*
    This class will be adapted for the problem of Advent of Code 12/12/2022
    The member variables could be altered

    In this case, the nodes will be letters. The adjacent nodes will be treated as children,
    being the root node the S node. 

    How to use:
        - Create a root node like: Node* root = new Node(NULL, "root");
        - Create children like: Node* child1 = new Node(root, "child1");
*/

class Node{

private:
    int value;  // Ascii value of the letter assigned to the node
    std::pair<int, int> position;
    int minDistance;
    bool checked;   

    Node* parent;
    std::vector <Node*> children;

public:
    // Constructor
    Node(Node* parent, std::pair<int, int> position, int value){

        this->parent = parent;
        if(parent)
            parent->add_child(this);
        this->position = position;
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

    std::pair<int, int> getPosition(){
        return this->position;
    }

};