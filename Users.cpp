// Gama Aristondo, 8404071
//
// Users.cpp

#include <iostream>
#include <string>

#include "Users.h"

using namespace std;

Users::Users() {
    this->root = NULL;
}

Users::~Users() {
    clearTree(this->root);
}

void clearTree(Node *p) {
    if(!p) {
        return;
    }
    clearTree(p->left);
    clearTree(p->right);
    delete p;
}

void Users::add_user(string name) {
    Node *p = new Node;
    p->name = name;
    p->color = 0;
    root = insert(this->root, p);
    return;
}

Node* insert(Node *root, Node *p) {
    if(this->root == NULL) {
        this->root = p;
    }
    else if(insert->name < root->name) {
        root->left = insert(root->left, p);
        root->left->parent = root;
    }
    else if(insert->name > root->name) {
        root->right = insert(root->right, p);
        root->right->parent = root;
    }
    return root;
}

int User::find_user(string name) {
    int index;
    // stub
    return index;
}

vector<string> User::range_search(string name1, string name2) {
    return "";
}

void Users::rotateLeft() {
    return;
}

void Users::rotateRight() {
    return;
}
