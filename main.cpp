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
    int fileIndex = 0;
    fstream profiles;
    profiles.open("Profile_Data.csv");
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
        inputs.erase(inputs.begin(), inputs.begin()+2);
        rbt.add_user(name, fileIndex);
        adjL.insert(name, inputs, fileIndex);
        stringstream n;
        n << setw(20) << name;
        stringstream a;
        a << setw(2) << age;
        stringstream o;
        o << setw(30) << occupation;
        profiles << n.str() << a.str() << o.str();
        fileIndex++;
    }
    infile.close();
    profiles.close();
    bool status = true;
    int input;
    while(status) {
        welcomePrompt();
        cin >> input;
        if(input == 1) {
            vector<string> n;         // work on this Gama
            vector<int> f;
            rbt.users_Index(n,f);
            for(auto j : f) {
                string info = "";
                string name, age, occupation;
                profiles.open("Profile_Data.csv", fstream::in);
                profiles.seekg(52*j, ios::beg);
                char buffer[52];
                profiles.read(buffer,52);
                for(int i = 0; i < 52; i++) {
                    info = info + buffer[i];
                }
                name = info.substr(0,20);
                age = info.substr(20,2);
                occupation = info.substr(22,30);
                cout << name << "," << age << "," << occupation << ",";
            }
            for(auto i : n) {              // this won't work
                adjL.printAllFriends(i);
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
            profiles.open("Profile_Data.csv",ios_base::app);
            stringstream N;
            N << setw(20) << name;
            stringstream A;
            A << setw(2) << age;
            stringstream O;
            O << setw(30) << occupation;
            profiles << N.str() << A.str() << O.str();
            profiles.close();
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
            info = "";
            cout << "Enter the name: ";
            cin >> name;
            int f_index = rbt.find_user(name);
            profiles.open("Profile_Data.csv", fstream::in);
            profiles.seekg(52*f_index, ios::beg);
            char buffer[52];
            profiles.read(buffer,52);
            profiles.close();
            for(int i = 0; i < 52; i++) {
                info = info + buffer[i];
            }
            name = info.substr(0,20);
            age = info.substr(20,2);
            occupation = info.substr(22,30);
            cout << name << "," << age << "," << occupation << endl;
        }else if(input == 5) {
            string name, age, occupation;
            vector<int> fileIndices;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Friends of " << name << ":\n";
            profiles.open("Profile_Data.csv", fstream::in);
            fileIndices = adjL.printFriends(name);
            for(auto i : fileIndices) {
                string info = "";
                profiles.seekg(52*i, ios::beg);
                char buffer[52];
                profiles.read(buffer,52);
                for(i = 0; i < 52; i++) {
                    info = info + buffer[i];
                }
                name = info.substr(0,20);
                age = info.substr(20,2);
                occupation = info.substr(22,30);
                cout << name << "," << "," << occupation << endl;
            }
            profiles.close();
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
