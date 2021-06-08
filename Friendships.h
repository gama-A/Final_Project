// Gama Aristondo, 8404071
// Sahil Naik, 8272395
// Friendships.h
//
// Header file for the graph representation of friendships (adjacency list),
// each item (user) in the list will also have pointer to the file as to where their information is

#ifndef FRIENDSHIPS_H
#define FRIENDSHIPS_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

/*
struct LLNode {
    std::string name;
    //std::string occupation;
    //int age;
};
*/
// gives us the option of having all the frineddsd info in the LLNode, might be better than having to search later but idk 
// if not might be better to just change LLnode to just a string so a vetor of strings
struct Node_Graph {
    std::string name;
    int fileIndex;
    std::vector<std::string> friends; // vector of friends
    //Node_Graph *left; // left pointer in rbt ?
    //Node_Graph *right; // right pointer in rbt ?
    Node_Graph() : name(""), fileIndex(0)  {}
};

// while taking in the inputs from the csv file, we create teh NodeGraph with name, friends.
// create the LL Node for all the friends and their occupations/age/name
// At the very end, we traverse and grab the file index from the rbt and also the left and right children in the rbt


// ALSO NEED A WAY TO RECHANGE THE L/R CHILDREN
class Friendships
{
    public:
        Friendships();
        void insert(std::string name, std::vector<std::string> friendsList, int fileLine); // figure out a way to grab all the friends 
        // friendsList needs to be created in main once we grab all the friends of the person from the csv file.
        void addFriendship(std::string friend1, std::string friend2);
        //void updatePostRBT(std::string name); // use
        std::vector<int> infoAllFriends(std::string name);
        void printFriends(std::string name);
        //int getUserIndex(std::string name);
    private:
        
        std::unordered_map<std::string, Node_Graph*> people;

};

#endif
