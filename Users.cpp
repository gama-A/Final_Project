// Gama Aristondo, 8404071
//
// Users.cpp

#include <iostream>
#include <string>

#include "Users.h"

using namespace std;

Users::Users() {
    this->TNULL = new Node;
    this->TNULL->color = 1;
    this->TNULL->left = NULL;
    this->TNULL->right = NULL;
    this->root = this->TNULL;
}

Users::~Users() {
    clearTree(this->root);
}

void Users::clearTree(Node *p) {
    if(!p) {
        return;
    }
    clearTree(p->left);
    clearTree(p->right);
    delete p;
}

void Users::fixStructure(Node *p) {
    Node *u;
    while( p->parent->color == 0 ){
        if( p->parent == p->parent->parent->right ) {
            u = p->parent->parent->left;
            if( (u != NULL) && (u->color == 0) ){
                u->color = 1;
                p->parent->color = 1;
                p->parent->parent->color = 0;
            }
            else {
                if (p == p->parent->left) {
                    p = p->parent;
                    rotateRight(p);
                }
                p->parent->color = 1;
                p->parent->parent->color = 0;
                rotateLeft(p->parent->parent);
            }
        }
        else {
            u = p->parent->parent->right;
            if( (u != NULL) && (u->color == 0) ){
                u->color = 1;
                p->parent->color = 1;
                p->parent->parent->color = 0;
                p = p->parent->parent;
            }
            else {
                if(p == p->parent->right) {
                    p = p->parent;
                    rotateLeft(p);
                }
                p->parent->color = 1;
                p->parent->parent->color = 0;
                rotateRight(p->parent->parent);
            }
        }
        if(p == this->root) {
            break;
        }
    }
    root->color = 1;
}

void Users::add_user(string name, int f_index) {
    Node *p = new Node;
    p->name = name;
    p->parent = NULL;
    p->color = 0;
    p->fileIndex = f_index;
    p->left = TNULL;
    p->right = TNULL;

    Node *y = NULL;
    Node *x = this->root;
    while(x != TNULL) {
        y = x;
        if(p->name < x->name) {
            x = x->left;
        }else {
            x = x->right;
        }
    }
    p->parent = y;
    if(y == NULL) {
        this->root = p;
    }else if(p->name < y->name) {
        y->left = p;
    }else {
        y->right = p;
    }

    if(p->parent == NULL) {
        p->color = 1;
        return;
    }
    if(p->parent->parent == NULL) {
        return;
    }
    fixStructure(p);
}
/*
Node* Users::insert(Node *root, Node *p) {
    if(this->root == NULL) {
        this->root = p;
    }
    else if(p->name < root->name) {
        root->left = insert(root->left, p);
        root->left->parent = root;
    }
    else if(p->name > root->name) {
        root->right = insert(root->right, p);
        root->right->parent = root;
    }
    return root;
}*/

void Users::range_search(vector<int> v, string name1, string name2) {
    Node *p = this->root;
    range_search_Helper(p, v, name1, name2);
}

void Users::range_search_Helper(Node *p, vector<int> v, string name1, string name2) {
    if(!p) {
        return;
    }
    if( p->name < name1 ) {
        range_search_Helper(p->right,v,name1,name2);
    }
    if( (name1 <= p->name) && (p->name <= name2) ) {
        v.push_back(p->fileIndex);
        range_search_Helper(p->left,v,name1,name2);
        range_search_Helper(p->right,v,name1,name2);
    }
    if( p->name > name2 ) {
        range_search_Helper(p->left,v,name1,name2);
    }
}

int Users::find_user(string name) {
    int index;
    Node *p = this->root;
    while(p) {
        if(p->name == name) {
            index = p->fileIndex;
            break;
        }
        else if(p->name < name) {
            p = p->left;
        }
        else if(p->name > name) {
            p = p->right;
        }
    }
    if(!p) {
        index = -1;
    }
    return index;
}

void Users::users_names(vector<string> v) {
    Node *p = this->root;
    users_names_Helper(v, p);
}

void Users::users_names_Helper(vector<string> v, Node *p) {
    if(p) {
        v.push_back(p->name);
        users_names_Helper(v, p->left);
        users_names_Helper(v, p->right);
    }
}

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
