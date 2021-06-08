// Gama Aristondo, 8404071
// Sahil Naik, 8272395
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
            cout << endl;
        }else if(input == 2) {
            string first, ps, last, answer, full;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            cin >> answer;
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                full = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                full = first + " " + last + " " + ps;
            }else if(answer == "n") {
                full = first + " " + last;
            }
            string occupation, friends, age, friendName;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter occupation (Fill spaces with '_'): ";
            cin >> occupation;
            replace(occupation.begin(), occupation.end(), '_', ' ');
            cout << "Enter friends (all at once,comma separated) (Replace space in names with '_'): ";
            cin >> friends;
            replace(friends.begin(), friends.end(), '_', ' ');
            profiles << full << "," << age << "," << occupation << endl;
            rbt.add_user(full, fileIndex);
            vector<string> f;
            stringstream F(friends);
            while(F.good()) {
                getline(F,friendName,',');
                f.push_back(friendName);
            }
            adjL.insertSingle(full, fileIndex);
            for (auto i : f) {
                adjL.addFriendship(full, i);
            }
            fileIndex++;
        }else if(input == 3) {
            string friend1, friend2;
            string first, ps, last, answer;
            cout << "First user's info: " << endl;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            cin >> answer;
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                friend1 = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                friend1 = first + " " + last + " " + ps;
            }else if(answer == "n") {
                friend1 = first + " " + last;
            }
            cout << "Second user's info: " << endl;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            cin >> answer;
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                friend2 = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                friend2 = first + " " + last + " " + ps;
            }else if(answer == "n") {
                friend2 = first + " " + last;
            }
            try {
                int f_index1 = rbt.find_user(friend1);
                int f_index2 = rbt.find_user(friend2);
                int lineNo = 0;
                if(f_index1 == -1 || f_index2 == -1) {
                    throw -1;
                }
                adjL.addFriendship(friend1, friend2);
            }
            catch(int e) {
                cout << setfill(' ') << setw (10) << "One or more of the user does not exist" << endl;
            }
        }else if(input == 4) {
            string first, ps, last, answer, full;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            cin >> answer;
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                full = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                full = first + " " + last + " " + ps;
            }else if(answer == "n") {
                full = first + " " + last;
            }
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
                cout << endl;
                getline(profiles,info);
                cout << info << endl;
            }
            catch(int e) {
                cout << "User does not exist" << endl;
            }
            cout << endl;
            profiles.clear();
            profiles.seekg(0);
        }else if(input == 5) {
            string first, ps, last, answer, full;
            vector<int> fileIndices;
            cout << "Enter first name: ";
            cin >> first;
            cout << "Enter last name: ";
            cin >> last;
            cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            cin >> answer;
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                full = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                full = first + " " + last + " " + ps;
            }else if(answer == "n") {
                full = first + " " + last;
            }
            try {
                int f_index = rbt.find_user(full);
                if(f_index == -1) {
                    throw f_index;
                }
                cout << endl;
                cout << left << setfill(' ') << setw(10) << "Friends of " << full << ":\n";
                fileIndices = adjL.infoAllFriends(full);
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
            cout << endl;
            profiles.clear();
            profiles.seekg(0);
        }else if(input == 6) {
        
            string lower, upper;
            //string first, ps, last, answer;
            cout << "First user's info (if the name has spaces, replace with '_'): " << endl;
            cout << "Enter name: ";
            cin >> lower;
            replace(lower.begin(), lower.end(), '_', ' ');
            //cout << "Enter last name: ";
            //cin >> last;
            //cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            //cin >> answer;
            /*
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                lower = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                lower = first + " " + last + " " + ps;
            }else if(answer == "n") {
                lower = first + " " + last;
            }
            */
            cout << "Second user's info (if name has spaces, replace with '_'): " << endl;
            cout << "Enter name: ";
            cin >> upper;
            replace(upper.begin(), upper.end(), '_', ' ');
            //cout << "Enter last name: ";
            //cin >> last;
            //cout << "Does this person have a prefix, suffix, or none: (p, s, or n)";
            //cin >> answer;
            /*
            if(answer == "p") {
                cout << "Enter: ";
                cin >> ps;
                upper = ps + " " + first + " " + last;
            }else if(answer == "s") {
                cout << "Enter: ";
                cin >> ps;
                upper = first + " " + last + " " + ps;
            }else if(answer == "n") {
                upper = first + " " + last;
            }
            */
            
            vector<int> nameIndices;
            rbt.range_search(nameIndices, lower, upper);
            cout << endl;
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
            cout << endl;
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
