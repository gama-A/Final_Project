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

void Users::fixStructure(Node *root, Node *p) {
    Node *parent_p = p->parent;
    Node *grandparent_p = p->parent->parent;
    return;
}

void Users::add_user(string name, int g_index) {
    Node *p = new Node;
    p->name = name;
    p->graphIndex = g_index;
    p->color = 0;
    this->root = insert(this->root, p);
    fixStructure(this->root, p);
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
    Node *r = this->root;
    index = find_userHelper(name, r);
    return index;
}

int find_userHelper(string name, Node* root) {
    if(!root) {
        return -1;
    }
    else if(root->name == name) {
        return root->graphIndex;
    }
    else if(name < root->name) {
        return find_userHelper(name, root->left);
    }
    else if(name > root->name) {
        return find_userHelper(name, root->right);
    }
}

vector<string> User::range_search(string name1, string name2) {
    return "";
}

void Users::rotateLeft(Node *root, Node *p) {
    return;
}

void Users::rotateRight(Node *root, Node *p) {
    return;
}
