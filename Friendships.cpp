#include "Friendships.h"
#include "Users.h"
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

Friendships::Friendships(){
}
void Friendships::insert(string name, vector<string> friendsList, int fileLine) {
    Node_Graph *n = new Node_Graph();
    n->name = name;
    n->fileIndex = fileLine;
    string L;
    for (int i =0 ; i < friendsList.size(); i++) {
        //this->addFriendship(name, friendsList[i]);
        L = friendsList[i];
        n->friends.push_back(L);
        //people[L]->friends.push_back(name);
    }
    people[name] = n;

}

void Friendships::insertSingle(string name, int fileLine) {
    Node_Graph *n = new Node_Graph();
    n->name = name;
    n->fileIndex = fileLine;
    people[name] = n;
}
void Friendships::addFriendship(string friend1, string friend2){
    vector<string>::iterator it;
    it = find (people[friend1]->friends.begin(), people[friend1]->friends.end(), friend2);
    if (it != people[friend1]->friends.end()){
        cout << "Friendship already exists" << endl;
        return;
    }
    people[friend1]->friends.push_back(friend2);
    people[friend2]->friends.push_back(friend1);
}

void Friendships::printFriends(string name){
    for (int i = 0; i < people[name]->friends.size(); i++) {
        cout << people[name]->friends[i] << ",";
    }
    cout << endl;
}

/*
void Friendships::updatePostRBT(string name, Users &u)){

    for (it = people.begin(); it != people.end(); it++) {
        it->second->fileIndex = u.find_user(it->first); //sets fileIndex . next need to set R/L children
 
}
    //finding the name occupation
    //for (int i =0; i < people[name]->friends.size(); i++) {

    //}
}
*/
vector<int> Friendships::infoAllFriends(string name) { // indice in the profile data
    vector<string> temp = people[name]->friends;
    vector<int> friendsPDLine;
    for (int i =0 ; i < temp.size(); i++) {
        friendsPDLine.push_back(people[temp[i]]->fileIndex);
        //cout << "Name: " temp[i] << endl; //temp[i] is a name of a friend
        // Mike's friends:
        // Jacob, age, occupation
        // Sarah, age, occupation


        //cout << ProfileData[temp[i]].occupation << endl;  
        //cout << ProfileData[temp[i]].age << endl;

    }
    return friendsPDLine;
}

/*
int Friendships::getUserIndex(string name) {
    return people[name]->fileIndex;
}
*/