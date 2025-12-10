#include <unordered_map>
#include <memory>

#include "room.h"

struct Coord {
    int x;
    int y;
};

struct CoordHash {
    std::size_t operator()(const Coord& c) const {
        return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
    }
};

class GameMap {
    std::unordered_map<Coord, std::shared_ptr<Room>, CoordHash> rooms;
};