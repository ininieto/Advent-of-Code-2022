#pragma once

#ifndef NODE
#define NODE

#include <iostream>
#include <vector>

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
    Node(Node* parent, std::pair<int, int> position, int value, int minDistance);

    // Destructor
    virtual ~Node(){};

    // Member methods
    void add_child(Node* child);
    void setChecked();
    int getValue();
    int getMinDistance();
    bool getChecked();
    Node* getParent();
    std::vector <Node*> getChildren();
    std::pair<int, int> getPosition();
};

#endif