#include <iostream>

#include "room.h"

using namespace std;

void Room::GameOutput() const {
    cout << "There are rooms in the following directions: ";
    bool first = true;
    if(north != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "North" << endl;
    }
    if(east != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "East" << endl;
    }
    if(south != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "South" << endl;
    }
    if(west != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "West" << endl;
    }
    cout << "." << endl;
}

void Room::OptionsOutput() const {
    cout << "You can make the following choices: ";
    bool first = true;
    if(north != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "[n]orth";
    }
    if(east != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "[e]ast";
    }
    if(south != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "[s]outh";
    }
    if(west != nullptr) {
        if(!first) { 
            cout << ", ";
        }
        first = false;
        cout << "[w]est";
    }
    cout << "." << endl;
}

void PlaceholderRoom::GameOutput() const {
    cout << "This is a placeholder room. If you are seeing this in normal gameplay, this is a bug." << endl;
    Room::GameOutput();
}

void StartingRoom::GameOutput() const {
    cout << "You are in the starting room. This room will always be the same empty 4 way room." << endl;
    Room::GameOutput();
}

void THall::GameOutput() const {
    cout << "You are at a T-shaped junction in the hall." << endl;
    Room::GameOutput();
}

void CrossRoom::GameOutput() const {
    cout << "You are in a 4-way junction in the hall." << endl;
    Room::GameOutput();
}

void HallRoom::GameOutput() const {
    cout << "You are in a hall. It's just a straight path through." << endl;
    Room::GameOutput();
}

void TRoom::GameOutput() const {
    cout << "You are in a room with 3 exits." << endl;
    Room::GameOutput();
}

void DeadEnd::GameOutput() const {
    cout << "You have reached a dead-end in the hall." << endl;
    Room::GameOutput();
}

void FourEntranceRoom::GameOutput() const {
    cout << "You are in a room with 4 exits." << endl;
    Room::GameOutput();
}

void TwoEntranceRoom::GameOutput() const {
    cout << "You are in a room with 2 exits." << endl;
    Room::GameOutput();
}

void DeadEndRoom::GameOutput() const {
    cout << "You are in a room with 1 exit." << endl;
    Room::GameOutput();
}