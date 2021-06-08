// Gama Aristondo, 8404071
//
// main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>
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
    int fileIndex = 0;
    fstream profiles;
    profiles.open("Profile_Data.txt", fstream::out | fstream::app);
    profiles.close();
    profiles.open("Profile_Data.txt", fstream::in | fstream::out | fstream::app);
    getline(infile,line);
    while(getline(infile,line)) {
        vector<string> inputs;
        line.erase(remove(line.begin(),line.end(),'"'),line.end());
        stringstream ss(line);
        while(ss.good()) {
            getline(ss, sub, ',');
            inputs.push_back(sub);
        }
        name = inputs[0];
        age = inputs[1];
        occupation = inputs[2];
        inputs.erase(inputs.begin(), inputs.begin()+3);
        inputs.pop_back();
        rbt.add_user(name, fileIndex);
        adjL.insert(name, inputs, fileIndex);
        profiles << name << "," << age << "," << occupation << endl;
        fileIndex++;
    }
    infile.close();
    bool status = true;
    int input;
    while(status) {
        welcomePrompt();
        cin >> input;
        if(input == 1) {
            vector<string> names;
            names = rbt.users_names();
            for(auto i : names) {
                int f_index = rbt.find_user(i);
                string info;
                int lineNo = 0;
                profiles.clear();
                profiles.seekg(0);
                while(lineNo < f_index) {
                    lineNo++;
                    getline(profiles,info);
                }
                getline(profiles,info);
                cout << info << ",";
                adjL.printFriends(i);
                profiles.clear();
                profiles.seekg(0);
            }
        }else if(input == 2) {
            string first, last, name, occupation, friends, age, friendName;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            name = first + " " + last;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter occupation: ";
            getline(cin, occupation);
            cout << "Enter friends (all at once,comma separated): ";
            getline(cin,friends);
            profiles << name << "," << age << "," << occupation << endl;
            rbt.add_user(name, fileIndex);
            vector<string> f;
            stringstream F(friends);
            while(F.good()) {
                getline(F,friendName,'"');
                f.push_back(friendName);
            }
            adjL.insert(name, f, fileIndex);
            fileIndex++;
        }else if(input == 3) {
            string friend1, friend2;
            cout << "Enter the 1st name: ";
            getline(cin,friend1);
            cout << "Enter the 2nd name: ";
            getline(cin,friend2);
            adjL.addFriendship(friend1, friend2);
        }else if(input == 4) {
            string first;
            string last;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            string full = first + " " + last;
            string info;
            try {
                int f_index = rbt.find_user(full);
                int lineNo = 0;
                if(f_index == -1) {
                    throw f_index;
                }
                while(lineNo < f_index) {
                    lineNo++;
                    getline(profiles,info);
                }
                getline(profiles,info);
                cout << info << endl;
            }
            catch(int e) {
                cout << "User does not exist" << endl;
            }
            
            profiles.clear();
            profiles.seekg(0);
        }else if(input == 5) {
            string first, last, name;
            vector<int> fileIndices;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            name = first + " " + last;
            try {
                int f_index = rbt.find_user(name);
                if(f_index == -1) {
                    throw f_index;
                }
                cout << "Friends of " << name << ":\n";
                fileIndices = adjL.infoAllFriends(name);
                for(auto i : fileIndices) {
                    string info;
                    int lineNo = 0;
                    profiles.clear();
                    profiles.seekg(0);
                    while(lineNo < i) {
                        lineNo++;
                        getline(profiles,info);
                    }
                    getline(profiles,info);
                    cout << info << endl;
                }
            }
            catch(int e) {
                cout << "User does not exist";
            }
            profiles.clear();
            profiles.seekg(0);
        }else if(input == 6) {
            string lower, upper;
            vector<int> nameIndices;
            cout << "Enter lower bound name: ";
            cin >> lower;
            cout << "Enter upper bound name: ";
            cin >> upper;
            rbt.range_search(nameIndices, lower, upper);
            for(auto i : nameIndices) {
                string info;
                int lineNo = 0;
                profiles.clear();
                profiles.seekg(0);
                while(lineNo < i) {
                    lineNo++;
                    getline(profiles,info);
                }
                getline(profiles,info);
                cout << info << endl;
            }
            profiles.clear();
            profiles.seekg(0);
        }else if(input == 7) {
            status = false;
        }else {
            cout << "INVALID INPUT";
        }
    }
    profiles.close();
    return 0;
}
