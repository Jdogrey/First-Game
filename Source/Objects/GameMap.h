#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <unordered_map>
#include <memory>

#include "room.h"

enum Difficulty {
    EASY = -1,
    NORMAL,
    HARD,
    VERY_HARD,
    EXPERT,
    INSANE
};

/*  Notes for personal memory:
    West is lower x, East is higher x
    South is lower y, North is higher y
*/

struct Coord {
    int x;
    int y;
    bool operator==(const Coord& other) const noexcept {
        return x == other.x && y == other.y;
    }
};

struct CoordHash {
    std::size_t operator()(const Coord& c) const noexcept {
        return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
    }
};

class GameMap {
    std::unordered_map<Coord, std::shared_ptr<Room>, CoordHash> rooms;
    Difficulty diff;
    int roomCount = 1;

    public:
    
    void AddRoom(int x, int y, const std::shared_ptr<Room>& room);

    GameMap(const std::shared_ptr<Room>& startingRoom, Difficulty diff) : diff(diff) {
        AddRoom(0, 0, startingRoom);
    }

    std::shared_ptr<Room> GetRoom(int x, int y) const;
    void SetupRoom(int x, int y, const std::shared_ptr<Room>& room);
    Difficulty GetDifficulty() const { return diff; }
    int GetRoomCount() const { return roomCount; }

};

#endif // GAMEMAP_H