// Gama Aristondo, 8404071
//
// main.cpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

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
    string file(argv[1]);
    ifstream infile;
    infile.open(file);
    string line, sub;
    vector<string> inputs;
    string name, occupation;
    int age, counter;
    fstream profiles;
    profiles.open("Profile_Data.csv");
    while(getline(infile,line)) {
        line = line.erase(remove(line.begin(),line.end(),'"'),line.end());
        string_stream ss(line);
        while(ss.good()) {
            getline(ss, sub, ',');
            inputs.push_back(sub);
        }
        name = inputs[0];
        age = inputs[1];
        occupation = inputs[2];
        rbt.add_user(name, counter);
        // stub add user and friends
        stringstream n;
        n << setw(20) << name;
        stringstream a;
        a << setw(3) << age;
        stringstream o;
        o << setw(30) << occupation;
        profiles << n.str() << a.str() << o.str();
        counter += 53;
    }
    infile.close();
    bool status = true;
    int input;
    while(status) {
        welcomePrompt();
        cin >> input;
        if(input == 1) {
            // stub
        }else if(input == 2) {
            string name, occupation, friends;
            int age;
            cout << "Enter the name: ";
            cin >> name;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter occupation: ";
            cin >> occupation;
            cout << "Enter friends (all at once,comma separated): ";
            cin >> friends;
            // stub
        }else if(input == 3) {
            string friend1, friend2;
            cout << "Enter the 1st name: ";
            cin >> friend1;
            cout << "Enter the 2nd name: ";
            cin >> friend2;
            //stub
        }else if(input == 4) {
            string name;
            cout << "Enter the name: ";
            cin >> name;
            int f_index = rbt.find_user(name);
            // stub
        }else if(input == 5) {
            string name;
            cout << "Enter the name: ";
            cin >> name
            // stub 
        }else if(input == 6) {
            string lower, upper;
            vector<string> names;
            cout << "Enter lower bound name: ";
            cin >> lower;
            cout << "Enter upper bound name: ";
            cin >> upper;
            Users.range_search(names, lower, upper);
            // stub
        }else if(input == 7) {
            status == false;
        }else {
            cout << "INVALID INPUT";
        }
    }
    return 0;
}
