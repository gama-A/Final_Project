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

class Users
{
    public:

    Users();

    ~Users();

    add_User(std::string name);

    private:

    rotateRight();
    rotateLeft();
    // Not done in function definition

    struct Node {
        std::string name;
        int graphIndex;
        int fileIndex;
        Node *left, *right, *parent;
    }
    // Possibly will need to be updated

};

#define
