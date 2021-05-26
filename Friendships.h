// Gama Aristondo, 8404071
//
// Friendships.h
//
// Header file for the graph representation of friendships (adjacency list),
// each item (user) in the list will also have pointer to the file as to where their information is

#ifndef FRIENDSHIPS_H
#define FRIENDSHIPS_H

#include <iostream>
#include <string>
#include <vector>

struct Node_Graph {
    string name;
    int fileIndex;
    Node_Graph *next;
};

class Friendships
{
    public:

    private:

    vector<Node_Graph*> friends;

};

#endif
