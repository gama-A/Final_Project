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
    int fileIndex = 1;
    fstream profiles;
    profiles.open("Profile_Data.txt", fstream::out | fstream::app);
    profiles.close();
    profiles.open("Profile_Data.txt", fstream::in | fstream::out | fstream::app);
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
                cout << "VALUE OF I IS: [" << i << "] , VALUE OF F_INDEX IS: " << f_index << endl;
                // f_index seems to be thorwing -1 in most cases so im gonnna try to fix that
                string info;
                int lineNo = 0;
                if (lineNo == f_index) {
                    cout << "bruh how" << endl;
                }
                else {
                    cout << "lineNo: " << lineNo << ",f_index: " << f_index << endl;
                }
                while(lineNo != f_index && getline(profiles,info)) {
                    //cout << "INFO IS: " << info << endl;
                cout << "LineNO++" << endl;
                    lineNo++;
                }
                cout << "lINENO IS: " << lineNo << endl;
                cout << info << ",";
                adjL.printFriends(i);
                profiles.clear();
                profiles.seekg(0);
            }
        }else if(input == 2) {
            string name, occupation, friends, age, friendName;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter occupation: ";
            cin >> occupation;
            cout << "Enter friends (all at once,comma separated): ";
            cin >> friends;
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
            cin >> friend1;
            cout << "Enter the 2nd name: ";
            cin >> friend2;
            adjL.addFriendship(friend1, friend2);
        }else if(input == 4) {
            string name, info;
            cout << "Enter the name: ";
            cin >> name;
            int f_index = rbt.find_user(name);
            int lineNo = 1;
            while(lineNo != f_index && getline(profiles, info)) {
                lineNo++;
            }
            cout << info << endl;
            profiles.seekg(0);
        }else if(input == 5) {
            string name;
            vector<int> fileIndices;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Friends of " << name << ":\n";
            fileIndices = adjL.infoAllFriends(name);
            for(auto i : fileIndices) {
                string info;
                int lineNo = 1;
                while(lineNo != i && getline(profiles, info)) {
                    lineNo++;
                }
                cout << info << endl;
            }
            profiles.seekg(0);
        }else if(input == 6) {
            string lower, upper, name;
            vector<int> nameIndices;
            cout << "Enter lower bound name: ";
            cin >> lower;
            cout << "Enter upper bound name: ";
            cin >> upper;
            rbt.range_search(nameIndices, lower, upper);
            for(auto i : nameIndices) {
                string info;
                int lineNo = 1;
                while(lineNo != i && getline(profiles, info)) {
                    lineNo++;
                }
                cout << info << endl;
            }
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
