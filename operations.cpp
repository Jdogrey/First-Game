#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <cctype>
#include <random>

#include "operations.h"
#include "Objects/room.h"
#include "Objects/GameMap.h"

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
        cout << " Enter d to touch the pylon drop into the dungeon.";
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
    else if ((choice == "d" || choice == "drop" || choice == "t") && room->getName() == "Start Run Room") {
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

shared_ptr<Room> generateRoom(shared_ptr<GameMap> gameMap, int x, int y) {
    static random_device rd;
    static mt19937 rng(rd());

    // variables to determine room type

    int maxEntries = 0;
    int minEntries = 0;
    auto north = gameMap->GetRoom(x, y + 1);
    auto east = gameMap->GetRoom(x + 1, y);
    auto south = gameMap->GetRoom(x, y - 1);
    auto west = gameMap->GetRoom(x - 1, y);
    bool northConnected = false;
    bool eastConnected = false;
    bool southConnected = false;
    bool westConnected = false;

    // Check existing adjacent rooms for connections for maximum and minimum entries in new room

    if (north && north->GetSouth()) {
        minEntries++;
        northConnected = true;
    }
    if (east && east->GetWest()) {
        minEntries++;
        eastConnected = true;
    }
    if (south && south->GetNorth()) {
        minEntries++;
        southConnected = true;
    }
    if (west && west->GetEast()) {
        minEntries++;
        westConnected = true;
    }

    maxEntries = minEntries;

    if (!north) maxEntries++;
    if (!east) maxEntries++;
    if (!south) maxEntries++;
    if (!west) maxEntries++;

    // Check if 2 rooms share corners to determine which type of 2 entry room to create

    bool adjacent = false;

    if(maxEntries == 2 && (northConnected && eastConnected) ||
       (eastConnected && southConnected) ||
       (southConnected && westConnected) ||
       (westConnected && northConnected)) {
        adjacent = true;
    }

    // Setup rng

    static uniform_int_distribution<> dis(0, 2); 

    int roomType = dis(rng);
    shared_ptr<Room> newRoom;

    // Cases for room types CURRENTLY PLACEHOLDER NEEDS IMPLEMENTATION
    // FIXME: Implement actual room generation logic based on min/max entries and roomType

    if(roomType == 0) {
        newRoom = make_shared<BossRoom>(0, "Generated Boss Room", NORTH);
    }
    else if(roomType == 1) {
        newRoom = make_shared<ShopRoom>(0, "Generated Shop", EAST);
    }
    else if(roomType == 2) {
        newRoom = make_shared<DeadEnd>(0, "Generated Dead End");
    }
    else if(roomType == 3) {
        newRoom = make_shared<DeadEndRoom>(0, "Generated Dead End Room", SOUTH);
    }
    else {
        newRoom = make_shared<TRoom>(0, "Generated Dead End Room", EAST);
    }

    gameMap->SetupRoom(x, y, newRoom);
    return newRoom;
}