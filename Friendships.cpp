#include "Friendships.h"
#include "Users.h"
#include <iostream>
using namespace std;

Friendships::Friendships(){
}
void Friendships::insert(string name, vector<string> friendsList) {
    Node_Graph *n = new Node_Graph();
    n->name = name;
    LLNode L;
    for (int i =0 ; i < friendsList.size(); i++) {
        L.name = friendsList[i];
        n->friends.push_back(L);
    }
    people[name] = n;

}

void Friendships::addFriendship(string friend1, string friend2){
    people[friend1]->friends.push_back(friend2);
    people[friend2]->friends.push_back(friend1);
}

void Friendships::updatePostRBT(string name, Users &u)){

    for (it = people.begin(); it != people.end(); it++) {
        it->second->fileIndex = u.find_user(it->first); //sets fileIndex . next need to set R/L children
 
}
    //finding the name occupation
    //for (int i =0; i < people[name]->friends.size(); i++) {

    //}
}