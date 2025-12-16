#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

#include "GameMap.h"

void GameMap::AddRoom(int x, int y, const std::shared_ptr<Room>& room) {
    rooms[{x, y}] = room;
}

std::shared_ptr<Room> GameMap::GetRoom(int x, int y) const {
    auto it = rooms.find({x, y});
    if (it != rooms.end()) {
        return it->second;
    }
    return nullptr;
}

void GameMap::SetupRoom(int x, int y, const std::shared_ptr<Room>& room) {
    // Set adjacent rooms
    auto northRoom = GetRoom(x, y + 1);
    auto eastRoom = GetRoom(x + 1, y);
    auto southRoom = GetRoom(x, y - 1);
    auto westRoom = GetRoom(x - 1, y);

    if (northRoom) {
        room->SetNorth(northRoom);
        northRoom->SetSouth(room);
    }
    if (eastRoom) {
        room->SetEast(eastRoom);
        eastRoom->SetWest(room);
    }
    if (southRoom) {
        room->SetSouth(southRoom);
        southRoom->SetNorth(room);
    }
    if (westRoom) {
        room->SetWest(westRoom);
        westRoom->SetEast(room);
    }
    AddRoom(x, y, room);
}