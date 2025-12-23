#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "GameMap.h"

using namespace std;

void GameMap::AddRoom(int x, int y, const std::shared_ptr<Room>& room) {
    rooms[{x, y}] = room;
}

shared_ptr<Room> GameMap::GetRoom(int x, int y) const {
    auto it = rooms.find({x, y});
    if (it != rooms.end()) {
        return it->second;
    }
    return nullptr;
}

void GameMap::SetupRoom(int x, int y, const std::shared_ptr<Room>& room) {
    // Set adjacent rooms

    AddRoom(x, y, room);

    shared_ptr<Room> northRoom = GetRoom(x, y + 1);
    shared_ptr<Room> eastRoom = GetRoom(x + 1, y);
    shared_ptr<Room> southRoom = GetRoom(x, y - 1);
    shared_ptr<Room> westRoom = GetRoom(x - 1, y);

    if (northRoom) {
        if(northRoom->GetSouth() != nullptr) {
            room->SetNorth(northRoom);
            northRoom->SetSouth(room);
        }
    }
    if (eastRoom) {
        if(eastRoom->GetWest() != nullptr) {
            room->SetEast(eastRoom);
            eastRoom->SetWest(room);
        }
    }
    if (southRoom) {
        if(southRoom->GetNorth() != nullptr) {
            room->SetSouth(southRoom);
            southRoom->SetNorth(room);
        }
    }
    if (westRoom) {
        if(westRoom->GetEast() != nullptr) {
            room->SetWest(westRoom);
            westRoom->SetEast(room);
        }
    }
}