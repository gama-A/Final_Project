// Gama Aristondo, 8404071
//
// Users.h
//
// Header file for the RBT representation of the users in the system
// each user will have a pointer (index) to the graph and file

#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <string>

struct Node {
    std::string name;
    int graphIndex;
    int fileIndex;
    Node *left, *right, *parent;
    bool color;
    // for color: true/1 = black, false/0 = red
};

class Users
{
    public:

    Users();

    ~Users();

    void add_user(std::string name, int g_index);

    std::string find_user(std::string name);

    vector<std::string> range_search(std::string name1, std::string name2);
    // i don't know if a vector of the names is the best might have to rethink this one

    private:

    Node* root;

    void rotateRight(Node* p);
    void rotateLeft(Node* p);
    
    void fixStructure(Node* root, Node* p);
    
};

#define
