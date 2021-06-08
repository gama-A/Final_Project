// Gama Aristondo, 8404071
// Sahil Naik, 8272395
// Users.h
//
// Header file for the RBT representation of the users in the system
// each user will have a pointer (index) to the graph and file

#ifndef USERS_H
#define USERS_H

#include <iostream>
#include <string>
#include <vector>

struct Node {
    std::string name;
    int fileIndex;    // integer indicating the offset of the information
    Node *left, *right, *parent;
    bool color;
    // for color: true/1 = black, false/0 = red
};

class Users
{
    public:

    Users();

    ~Users();

    void add_user(std::string name, int f_index);

    void range_search(std::vector<int> &v, std::string name1, std::string name2);
    // i don't know if 

    int find_user(std::string name);
    // returns file index

    std::vector<std::string> users_names();

    private:

    Node* root;
    Node* TNULL;

    void destroy(Node *p);

    // Node* insert(Node *root, Node *p);

    void rotateRight(Node* p);
    void rotateLeft(Node* p);
    
    void fixStructure(Node* p);

    std::vector<std::string> users_names_Helper(std::vector<std::string> &v, Node *p);

    void range_search_Helper(Node *p, std::vector<int> &v, std::string name1, std::string name2);
    
};

#endif
