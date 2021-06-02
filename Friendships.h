// Gama Aristondo, 8404071
// Sahil Naik, 8272395
// Friendships.h
//
// Header file for the graph representation of friendships (adjacency list),
// each item (user) in the list will also have pointer to the file as to where their information is

#ifndef FRIENDSHIPS_H
#define FRIENDSHIPS_H

#include <iostream>
#include "Users.h"
#include <string>
#include <vector>
#include <unordered_set>

struct LLNode {
    std::string name;
    //std::string occupation;
    //int age;
}
struct Node_Graph {
    std::string name;
    int fileIndex;
    std::vector<LLNode> friends; // linked list of friends
    Node_Graph *left; // left pointer in rbt ?
    Node_Graph *right; // right pointer in rbt ?
    Node_Graph() : name(""), fileIndex(0), left(NULL), right(NULL)  {}
};

// while taking in the inputs from the csv file, we create teh NodeGraph with name, friends.
// create the LL Node for all the friends and their occupations/age/name
// At the very end, we traverse and grab the file index from the rbt and also the left and right children in the rbt


// ALSO NEED A WAY TO RECHANGE THE L/R CHILDREN
class Friendships
{
    public:
        Friendships();
        void insert(std::string name, std::vector<std::string> friendsList); // figure out a way to grab all the friends 
        // friendsList needs to be created in main once we grab all the friends of the person from the csv file.
        void addFriendship(std::string friend1, std::string friend2);
        void updatePostRBT(std::string name); // use
    private:
        
        unordered_set<Node_Graph*> people;

};

#endif
