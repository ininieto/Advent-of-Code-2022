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
    //bool explored;   

    std::vector<Node*> parents; // A node can support multiple parents
    std::vector <Node*> children;

public:
    // Constructor
    Node(Node* parent, std::pair<int, int> position, int value, int minDistance);

    // Destructor
    virtual ~Node(){};

    // Member methods
    void add_child(Node* child);
    void addParent(Node* parent);
    std::vector <Node*> getParents();
    std::vector <Node*> getChildren();

    // Getters and Setters

    /*
    void setExplored();
    bool getExplored();
    */
    int getValue();
    std::pair<int, int> getPosition();
    void setMinDistance(int minDistance);
    int getMinDistance();
};

#endif