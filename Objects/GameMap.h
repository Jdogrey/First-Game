#include <unordered_map>
#include <memory>

#include "room.h"

struct Coord {
    int x;
    int y;
    bool operator==(const Coord& other) const noexcept {
        return x == other.x && y == other.y;
    }
};

struct CoordHash {
    std::size_t operator()(const Coord& c) const {
        return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
    }
};

class GameMap {
    std::unordered_map<Coord, std::shared_ptr<Room>, CoordHash> rooms;

    public:
    
    GameMap(std::shared_ptr<Room> startingRoom) {
        rooms[{0, 0}] = startingRoom;
    }
};