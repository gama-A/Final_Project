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
    Node *parent_p = NULL;
    Node *grandparent_p = NULL;
    Node *uncle_p = NULL;
    while( p->parent->color == 0 ){
        parent_p = p->parent;
        grandparent_p = parent_p->parent;
        if( parent_p == grandparent_p->left ) {
            uncle_p = grandparent_p->right;
            if( (uncle_p != NULL) && (uncle_p->color == 0) {
                grandparent_p->color = 0;
                parent_p->color = 1;
                uncle_p = 1;
                p = grandparent_p;
            }
            else {
                if (p == parent_p->right) {
                    p = p->parent;
                    rotateLeft(p);
                }
                parent_p->color = 1;
                grandparent_p->color = 0;
                rotateRight(grandparent_p);
            }
        }
        else {
            uncle_p = grandparent_p->left;
            if( (uncle_p != NULL) && (uncle_p->color == 0) {
                grandparent_p->color = 0;
                parent_p->color = 1;
                uncle_p->color = 1;
                p = grandparent_p;
            }
            else {
                if(p == parent_p->left) {
                    p = p->parent;
                    rotateRight(p);
                }
                parent_p->color = 1;
                grandparent_p->color = 0;
                rotateLeft(grandparent_p);
            }
        }
    }
    root->color = 1;
}

void Users::add_user(string name) {
    Node *p = new Node;
    p->name = name;
    p->parent = NULL;
    p->color = 0;
    this->root = insert(this->root, p);
    if(p->parent == NULL) {
        p->color = 1;
        return;
    }
    if(p->parent->parent == NULL) {
        return;
    }
    fixStructure(this->root, p);
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

void Users::range_search(vector<Node*> v, string name1, string name2) {
    Node *p = this->root;
    range_search_Helper(p, v, name1, name2);
}

void range_search_Helper(Node *p, vector<Node*> v, string name1, string name2) {
    if(!p) {
        return;
    }
    if( p->name < name1 ) {
        range_search_Helper(p->right,v,name1,name2);
    }
    if( (name1 <= p->name) && (p->name <= name2) ) {
        v.push_back(p);
        range_search_Helper(p->left,v,name1,name2);
        range_search_Helper(p->right,v,name1,name2);
    }
    if( p->name > name2 ) {
        range_search_Helper(p->left,v,name1,name2);
    }
}
// Might have to double check this ^

void Users::rotateLeft(Node *p) {
    Node *q = p->right;
    p->right = q->left;
    if(q->left != NULL) {
        q->left->parent = p;
    }
    q->parent = p->parent;
    if(p->parent == NULL) {
        this->root = q;
    }else if(p == p->parent->left) {
        p->parent->left = q;
    }else {
        p->parent->right = q;
    }
    q->left = p;
    p->parent = q;
}

void Users::rotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    if(q->right != NULL) {
        q->right->parent = p;
    }
    q->parent = p->parent;
    if(p->parent == NULL) {
        this->root = q;
    }else if(p == p->parent->right) {
        p->parent->right = q;
    }else {
        p->parent->left = q;
    }
    q->right = p;
    p->parent = q;
}
