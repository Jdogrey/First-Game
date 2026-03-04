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
    cout << "Press q to leave this run and return to the lobby." << endl;
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
    bool northUnavailable = false;
    bool eastUnavailable = false;
    bool southUnavailable = false;
    bool westUnavailable = false;

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

    if(north && !north->GetSouth()) northUnavailable = true;
    if(east && !east->GetWest()) eastUnavailable = true;
    if(south && !south->GetNorth()) southUnavailable = true;
    if(west && !west->GetEast()) westUnavailable = true;

    // Check if 2 rooms share corners to determine which type of 2 entry room to create

    bool adjacent = false;

    if(minEntries == 2 && ((northConnected && eastConnected) ||
       (eastConnected && southConnected) ||
       (southConnected && westConnected) ||
       (westConnected && northConnected))) {
        adjacent = true;
    }

    int maxRNG;
    int minRNG;

    switch(minEntries) {
        case 1:
            minRNG = 0;
            break;
        case 2:
            minRNG = 30;
            break;
        case 3:
            minRNG = 60;
            break;
        case 4:
            minRNG = 80; 
            break;
        default:
            minRNG = 0;
            break;
    }

    switch(maxEntries) {
        case 1:
            maxRNG = 29;
            break;
        case 2:
            maxRNG = 59;
            break;
        case 3:
            maxRNG = 79;
            break;
        case 4:
            maxRNG = 100;
            break;
        default:
            maxRNG = 100;
            break;
    }

    // Setup rng

    uniform_int_distribution<> dis(minRNG, maxRNG); 

    int roomType = dis(rng);
    shared_ptr<Room> newRoom;
    Orientation ori;
    int roomCategory = -1;


    // Cases for room category
    // FIXME: Fix implementation for T-Rooms

    if(roomType < 30) {

        roomCategory = 0; // Dead-End

        if(northConnected) {
            ori = Orientation::NORTH;
        }
        else if(eastConnected) {
            ori = Orientation::EAST;
        }
        else if(southConnected) {
            ori = Orientation::SOUTH;
        }
        else {
            ori = Orientation::WEST;
        }
    }

    else if(roomType >= 30 && roomType < 60) {
        if(adjacent) {

            roomCategory = 1; // Bend

            if(northConnected && eastConnected) {
                ori = Orientation::NORTH;
            }
            else if(eastConnected && southConnected) {
                ori = Orientation::EAST;
            }
            else if(southConnected && westConnected) {
                ori = Orientation::SOUTH;
            }
            else {
                ori = Orientation::WEST;
            }
        }
        else if(!adjacent && maxEntries == 2) {

            roomCategory = 2; // Straight

            if(northConnected && southConnected) {
                ori = Orientation::EAST; // Vertical
            }
            else {
                ori = Orientation::NORTH; // Horizontal
            }
        }
        else {
            uniform_int_distribution<> dis(0, 1);
            int oriRNG = dis(rng);
            if(oriRNG == 0) {

                roomCategory = 1; // Bend

                if(northConnected) {
                    if(eastUnavailable) {
                        ori = Orientation::WEST;
                    }
                    else if(westUnavailable) {
                        ori = Orientation::NORTH;
                    }
                    else {
                        int direction = dis(rng);

                        if(direction == 0) {
                            ori = Orientation::NORTH;
                        }
                        else {
                            ori = Orientation::WEST;
                        }
                    }
                }
                else if(eastConnected) {
                    if(southUnavailable) {
                        ori = Orientation::NORTH;
                    }
                    else if(northUnavailable) {
                        ori = Orientation::EAST;
                    }
                    else {
                        int direction = dis(rng);

                        if(direction == 0) {
                            ori = Orientation::EAST;
                        }
                        else {
                            ori = Orientation::NORTH;
                        }
                    }
                }
                else if(southConnected) {
                    if(westUnavailable) {
                        ori = Orientation::EAST;
                    }
                    else if(eastUnavailable) {
                        ori = Orientation::SOUTH;
                    }
                    else {
                        int direction = dis(rng);

                        if(direction == 0) {
                            ori = Orientation::SOUTH;
                        }
                        else {
                            ori = Orientation::EAST;
                        }
                    }
                }
                else {
                    if(northUnavailable) {
                        ori = Orientation::SOUTH;
                    }
                    else if(southUnavailable) {
                        ori = Orientation::WEST;
                    }
                    else {
                        int direction = dis(rng);

                        if(direction == 0) {
                            ori = Orientation::WEST;
                        }
                        else {
                            ori = Orientation::SOUTH;
                        }
                    }
                }
            }
            else {

                roomCategory = 2; // Straight

                if(northConnected || southConnected) {
                    ori = Orientation::EAST; // Vertical
                }
                else {
                    ori = Orientation::NORTH; // Horizontal
                }
            }
        }
    }

    // FIXME: Fix implementation for T-Rooms

    else if(roomType >= 60 && roomType < 80) {
        roomCategory = 3; // T-Junction
        if(maxEntries == 3) {
            if(northUnavailable) {
                ori = Orientation::NORTH;
            }
            else if(eastUnavailable) {
                ori = Orientation::EAST;
            }
            else if(southUnavailable) {
                ori = Orientation::SOUTH;
            }
            else {
                ori = Orientation::WEST;
            }
        }
        else if(minEntries == 3) {
            if(!northConnected) {
                ori = Orientation::NORTH;
            }
            else if(!eastConnected) {
                ori = Orientation::EAST;
            }
            else if(!southConnected) {
                ori = Orientation::SOUTH;
            }
            else {
                ori = Orientation::WEST;
            }
        }
        else if(minEntries == 2) {
            uniform_int_distribution<> dis(0,1);
            if(northConnected && eastConnected) {
                
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::SOUTH;
                }
                else {
                    ori = Orientation::WEST;
                }
            }
            else if(eastConnected && southConnected) {
                
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::NORTH;
                }
                else {
                    ori = Orientation::WEST;
                }
            }
            else if(southConnected && westConnected) {
                
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::NORTH;
                }
                else {
                    ori = Orientation::EAST;
                }
            }
            else if(westConnected && northConnected) {
                
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::SOUTH;
                }
                else {
                    ori = Orientation::EAST;
                }
            }
            else if(northConnected && southConnected) {
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::WEST;
                }
                else {
                    ori = Orientation::EAST;
                }
            }
            else {
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::NORTH;
                }
                else {
                    ori = Orientation::SOUTH;
                }
            }
        }
        else {
            uniform_int_distribution<> dis(0, 2);
            
            if(northConnected) {
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::EAST;
                }
                else if(direction == 1) {
                    ori = Orientation::SOUTH;
                }
                else {
                    ori = Orientation::WEST;
                }
            }
            else if(eastConnected) {
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::NORTH;
                }
                else if(direction == 1) {
                    ori = Orientation::SOUTH;
                }
                else {
                    ori = Orientation::WEST;
                }
            }
            else if(southConnected) {
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::NORTH;
                }
                else if(direction == 1) {
                    ori = Orientation::EAST;
                }
                else {
                    ori = Orientation::WEST;
                }
            }
            else {
                int direction = dis(rng);

                if(direction == 0) {
                    ori = Orientation::NORTH;
                }
                else if(direction == 1) {
                    ori = Orientation::EAST;
                }
                else {
                    ori = Orientation::SOUTH;
                }
            }
        }
    }

    else {
        roomCategory = 4; // Cross. Doesn't need orientation because all orientations are the same.
    }

    /* 

    Notes about room type:

    0 - Dead-End
    1 - Bend
    2 - Straight
    3 - T-Junction
    4 - Cross
    
    */

    // Create room based on determined category and randomly generated subcategory

    switch(roomCategory) {
        case 0: // Dead-End
            {
                int generatedRooms = gameMap->GetRoomCount();
                int minRoom = 0;
                int maxRoom = 0;
                if(generatedRooms < 10) {
                    minRoom = 2;
                    maxRoom = 3;
                }
                else if(generatedRooms >= 10 && generatedRooms < 50) {
                    minRoom = 1;
                    maxRoom = 3;
                }
                else if (generatedRooms >= 50 && generatedRooms < 100) {
                    minRoom = 0;
                    maxRoom = 3;
                }
                else {
                    minRoom = 0;
                    maxRoom = 0;
                }

                uniform_int_distribution<> dis(minRoom, maxRoom); 
                int subType = dis(rng);

                switch(subType) {
                    case 0:
                        newRoom = make_shared<BossRoom>(0, "Boss Room", ori);
                        break;
                    case 1:
                        newRoom = make_shared<ShopRoom>(0, "Shop", ori);
                        break;
                    case 2:
                        newRoom = make_shared<DeadEndRoom>(0, "Dead-End Room", ori);
                        break;
                    default:
                        newRoom = make_shared<DeadEnd>(0, "Dead-End", ori);
                        break;
                }
                break;
            }
        case 1: // Bend
            {
                uniform_int_distribution<> dis(0, 1);
                int subType = dis(rng);

                if(subType == 0) {
                    newRoom = make_shared<BendRoom>(0, "Bend Room", ori);
                }
                else {
                    newRoom = make_shared<BendHall>(0, "Bend Hall", ori);
                }
                break;
            }
        case 2: // Straight
            {
                uniform_int_distribution<> dis(0, 1);
                int subType = dis(rng);

                if(subType == 0) {
                    newRoom = make_shared<TwoEntranceRoom>(0, "Two-Entrance Room", ori);
                }
                else {
                    newRoom = make_shared<HallRoom>(0, "Straight Hall", ori);
                }
                break;
            }
        case 3: // T-Junction
            {
                uniform_int_distribution<> dis(0, 1);
                int subType = dis(rng);

                if(subType == 0) {
                    newRoom = make_shared<TRoom>(0, "Three-Entrance Room", ori);
                }
                else {
                    newRoom = make_shared<THall>(0, "T-Junction Hall", ori);
                }
                break;
            }
        case 4: // Cross
            {
                uniform_int_distribution<> dis(0, 1);
                int subType = dis(rng);

                if(subType == 0) {
                    newRoom = make_shared<FourEntranceRoom>(0, "Four-Entrance Room");
                }
                else {
                    newRoom = make_shared<CrossRoom>(0, "Cross Hall");
                }
                break;
            }
        default:
            newRoom = make_shared<PlaceholderRoom>(); 
            break;
    }

    return newRoom;
}

