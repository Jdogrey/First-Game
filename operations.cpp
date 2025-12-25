#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cctype>

#include "operations.h"
#include "Objects/room.h"

using namespace std;

bool takeInput(shared_ptr<Room>& room) {
    if (!room) {
        cerr << "Error: current room is null.\n";
        return true;
    }
    
    string choice;
    cout << "\n";
    room->GameOutput();
    room->OptionsOutput();
    cout << "Enter q to quit.";
    if(room->getName() == "Start Run Room") {
        cout << " Enter d to drop into the dungeon.";
    }
    cout << "\n";
    cout << "Choose an option: ";
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    if ((choice == "n" || choice == "north") && room->GetNorth() != nullptr) {
        room = room->GetNorth();
    } 
    else if ((choice == "e" || choice == "east") && room->GetEast() != nullptr) {
        room = room->GetEast();
    }
    else if ((choice == "s" || choice == "south") && room->GetSouth() != nullptr) {
        room = room->GetSouth();
    }
    else if ((choice == "w" || choice == "west") && room->GetWest() != nullptr) {
        room = room->GetWest();
    }
    else if (choice == "q" || choice == "quit") {
        cout << "Quitting the game." << endl;
        return true;
    }
    else if ((choice == "d" || choice == "drop") && room->getName() == "Start Run Room") {
        cout << "Dropping into the dungeon..." << endl;
        room = make_shared<StartingRoom>(0, "Starting Room");
        return false;
    }
    else {
        cout << "\n>>>  Invalid input or no room in that direction.  <<<" << endl;
    }
    return false;
}

bool takeInput(shared_ptr<Room>& room, int& x, int& y) {
    if (!room) {
        cerr << "Error: current room is null.\n";
        return true;
    }

    string choice;
    cout << "\n";
    room->GameOutput();
    room->OptionsOutput();
    cout << "Press q to quit." << endl;
    cout << "\n";
    cout << "Choose an option: ";
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

    if ((choice == "n" || choice == "north") && room->GetNorth() != nullptr) {
        room = room->GetNorth();
        y++;
    } 
    else if ((choice == "e" || choice == "east") && room->GetEast() != nullptr) {
        room = room->GetEast();
        x++;
    }
    else if ((choice == "s" || choice == "south") && room->GetSouth() != nullptr) {
        room = room->GetSouth();
        y--;
    }
    else if ((choice == "w" || choice == "west") && room->GetWest() != nullptr) {
        room = room->GetWest();
        x--;
    }
    else if (choice == "q" || choice == "quit") {
        cout << "Quitting the game." << endl;
        return true;
    }
    else {
        cout << "\n>>>  Invalid input or no room in that direction.  <<<" << endl;
    }
    return false;
}