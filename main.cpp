// Gama Aristondo, 8404071
//
// main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "Users.h"
#include "Friendships.h"

using namespace std;

void welcomePrompt() {
    string output = "Welcome to the social network! What action would you like to make?\n"
                    "1) Print all\n"
                    "2) Insert new user\n"
                    "3) Add friendship relationship\n"
                    "4) Information of a user\n"
                    "5) List information of all friends of one user\n"
                    "6) List information of range of users\n"
                    "7) Exit\n"
                    "Input number: \n";
    cout << output;
}

int main(int argc, char** argv) {
    Users rbt;
    Friendships adjL;
    string file(argv[1]);
    ifstream infile;
    infile.open(file);
    string line, sub;
    string name, age, occupation;
    int counter = 0;
    int fileLine = 1;
    fstream profiles;
    profiles.open("Profile_Data.csv");
    while(getline(infile,line)) {
        vector<string> inputs;
        line.erase(remove(line.begin(),line.end(),'"'),line.end());
        stringstream ss(line);
        while(ss.good()) {
            getline(ss, sub, ',');
            inputs.push_back(sub); //isnt all of them pushed into same vector? since vector<inputs> defined outside teh while loop
        }
        name = inputs[0]; // so these might not work ? double checking
        age = inputs[1];
        occupation = inputs[2];
        inputs.erase(inputs.begin(), inputs.begin()+2);
        rbt.add_user(name, counter);
        // assuming inputs 3-> inputs.size() is the rest of friends
        vector<string> friends;
        //for (int i = 0; i < inputs.size(); i++) {
        //    friends.push_back(inputs[i]);
        //}
        adJL.insert(name, inputs, fileLine);
        // stub add user and friends Sahil this is where your stuff goes
        stringstream n;
        n << setw(20) << name;
        stringstream a;
        a << setw(3) << age;
        stringstream o;
        o << setw(30) << occupation;
        profiles << n.str() << a.str() << o.str();
        counter += 53;
        fileLine++;
    }
    infile.close();
    bool status = true;
    int input;
    while(status) {
        welcomePrompt();
        cin >> input;
        if(input == 1) {
            vector<string> v;
            rbt.user_names(v);

            // stub Sahil (go through the names of the vector, print whats in the file, then the friends)
            // stub (given name, print friends)
            adjL.printAllFriends(stub name);
        }else if(input == 2) {
            string name, occupation, friends, age;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter occupation: ";
            cin >> occupation;
            cout << "Enter friends (all at once,comma separated): ";
            cin >> friends;
            stringstream N;
            N << setw(20) << name;
            stringstream A;
            A << setw(3) << age;
            stringstream O;
            O << setw(30) << occupation;
            profiles << N.str() << A.str() << O.str();
            rbt.add_user(name, counter);
            fileLine++;
            counter += 53;
            vector<string> f;
            //f.push_back(names) stub
            adjL.insert(name, f, fileLine);
            // stub Sahil (use the string friends and name to create the friendships)
        }else if(input == 3) {
            string friend1, friend2;
            cout << "Enter the 1st name: ";
            cin >> friend1;
            cout << "Enter the 2nd name: ";
            cin >> friend2;
            adjL.addFriendship(friend1, friend2);
        }else if(input == 4) {
            string name;
            cout << "Enter the name: ";
            cin >> name;
            int f_index = rbt.find_user(name);
            // stub
        }else if(input == 5) {
            string name;
            vector<int> fileIndices;
            cout << "Enter the name: ";
            cin >> name;
            fileIndices = adjL.printFriends(name); // a vector of indices of friends
            // stub Sahil (obtain the names of the friends and their file index) 
        }else if(input == 6) {
            string lower, upper;
            vector<string> names; // vector of names in the range
            cout << "Enter lower bound name: ";
            cin >> lower;
            cout << "Enter upper bound name: ";
            cin >> upper;
            rbt.range_search(names, lower, upper); // change to range search to return indices of file (so we can find them infile)
            // stub
        }else if(input == 7) {
            status == false;
        }else {
            cout << "INVALID INPUT";
        }
    }
    return 0;
}
