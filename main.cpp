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
        stringstream n;
        n << std::left << setw(20) << name;
        stringstream a;
        a << std::left << setw(2) << age;
        stringstream o;
        o << std::left << setw(30) << occupation;
        profiles << n.str() << a.str() << o.str();
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
            rbt.users_names(names);
            for(auto i : names) {
                int f_index = rbt.find_user(i);
                string info = "";
                string name, age, occupation;
                profiles.seekg(52*f_index, ios::beg);
                char buffer[52];
                profiles.read(buffer,52);
                for(int i = 0; i < 52; i++) {
                    info = info + buffer[i];
                }
                name = info.substr(0,20);
                age = info.substr(20,2);
                occupation = info.substr(22,30);
                cout << name << "," << age << "," << occupation << ",";
                adjL.printFriends(i);
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
            stringstream N;
            N << setw(20) << name;
            stringstream A;
            A << setw(2) << age;
            stringstream O;
            O << setw(30) << occupation;
            profiles << N.str() << A.str() << O.str();
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
            profiles.seekg(52*f_index, ios::beg);
            char buffer[52];
            profiles.read(buffer,52);
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
            fileIndices = adjL.infoAllFriends(name);
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
                cout << name << "," << age << "," << occupation << endl;
            }
        }else if(input == 6) {
            string lower, upper, name, age, occupation;
            vector<int> nameIndices;
            cout << "Enter lower bound name: ";
            cin >> lower;
            cout << "Enter upper bound name: ";
            cin >> upper;
            rbt.range_search(nameIndices, lower, upper);
            for(auto i : nameIndices) {
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
                cout << name << "," << age << "," << occupation << endl;
            }
        }else if(input == 7) {
            status = false;
        }else {
            cout << "INVALID INPUT";
        }
    }
    profiles.close();
    return 0;
}
