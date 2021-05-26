// Gama Aristondo, 8404071
//
// main.cpp

#include <iostream>
#include <string>

using namespace std;

void welcomePrompt() {
    string output = "Welcome to the social network! What action would you like to make?\n"
                    "1) Print all\n"
                    "2) Insert new user\n"
                    "3) Add friendship relationship\n"
                    "4) List information of all friends of one user\n"
                    "5) List information of range of users\n"
                    "6) Exit\n"
                    "Input number: \n";
    cout << output;
}

int main(int argc, char** argv) {
    string file(argv[0]);
    bool status = true;
    int input;
    while(status) {
        welcomePrompt();
        cin >> input;
        if(input == 1) {
            // stub
        }else if(input == 2) {
            // stub
        }else if(input == 3) {
            // stub
        }else if(input == 4) {
            // stub
        }else if(input == 5) {
            // stub
        }else if(input == 6) {
            status == false;
        }else {
            cout << "INVALID INPUT";
        }
    }
    return 0;
}
