#include <iostream>
#include <vector>

#include "Node.h"

/*
    This class will be adapted for the problem of Advent of Code 12/12/2022
    The member variables could be altered

    In this case, the nodes will be letters. The adjacent nodes will be treated as children,
    being the root node the S node. 

    How to use:
        - Create a root node like: Node* root = new Node(NULL, "root");
        - Create children like: Node* child1 = new Node(root, "child1");
*/


// Constructor
Node::Node(Node* parent, std::pair<int, int> position, int value, int minDistance){

    this->parent = parent;
    if(parent)
        parent->add_child(this);
    this->position = position;
    this->value = value;
    this->minDistance = minDistance;
    checked = false;
}

// Member methods

void Node::add_child(Node* child){
    children.push_back(child);
}

void Node::setChecked(){
    this->checked = true;
}

Node* Node::getParent(){
    return this->parent;
}

std::vector <Node*> Node::getChildren(){
    return this->children;
}

int Node::getValue(){
    return this->value;
}

void Node::setMinDistance(int minDistance){
    this->minDistance = minDistance;
}

std::pair<int, int> Node::getPosition(){
    return this->position;
}

int Node::getMinDistance(){
    return this->minDistance;
}

bool Node::getChecked(){
    return this->checked;
}

