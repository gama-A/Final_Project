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

    void add_User(std::string name);

    std::string find_User(std::string name);

    vector<string> range_search(std::string name1, std::string name2);

    private:

    Node* root;

    void rotateRight();
    void rotateLeft();
    // Not done in function definition

};

#define
