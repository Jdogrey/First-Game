#include <iostream>
#include <memory>
#include <string>

#include "operations.h"
#include "Objects/room.h"

using namespace std;

bool takeInput(shared_ptr<Room>& room) {
    string choice;
    room->GameOutput();
    room->OptionsOutput();
    cout << "Press q to quit." << endl;
    cout << "Choose an option: ";
    cin >> choice;
    if (choice == "n" && room->GetNorth() != nullptr) {
        room = room->GetNorth();
    } 
    else if (choice == "e" && room->GetEast() != nullptr) {
        room = room->GetEast();
    }
    else if (choice == "s" && room->GetSouth() != nullptr) {
        room = room->GetSouth();
    }
    else if (choice == "w" && room->GetWest() != nullptr) {
        room = room->GetWest();
    }
    else if (choice == "q") {
        cout << "Quitting the game." << endl;
        return true;
    }
    else {
        cout << "Invalid input or no room in that direction." << endl;
    }
    return false;
}