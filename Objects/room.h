#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <memory>

enum Orientation {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class Room {
    
    int id;
    std::string name;
    std::shared_ptr<Room> north;
    std::shared_ptr<Room> east;
    std::shared_ptr<Room> south;
    std::shared_ptr<Room> west;
    int gold;

    public:

    Room() : id(-1), name("Placeholder"), north(nullptr), east(nullptr), south(nullptr), west(nullptr) {}
    Room(int id, const std::string& name) : id(id), name(name), north(nullptr), east(nullptr), south(nullptr), west(nullptr) {}
    Room(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : id(id), name(name),  north(north), east(east), south(south), west(west) {}
    int getId() const { return id; }
    std::string getName() const { return name; }
    virtual std::string getType() const = 0;
    void SetWest(std::shared_ptr<Room> room) { west = room; }
    void SetEast(std::shared_ptr<Room> room) { east = room; }
    void SetNorth(std::shared_ptr<Room> room) { north = room; }
    void SetSouth(std::shared_ptr<Room> room) { south = room; }
    std::shared_ptr<Room> GetWest() const { return west; }
    std::shared_ptr<Room> GetEast() const { return east; }
    std::shared_ptr<Room> GetNorth() const { return north; }
    std::shared_ptr<Room> GetSouth() const { return south; }

    void PrintInfo() const {
        std::cout << "Room ID: " << id << ", Name: " << name << ", Type: " << getType() << std::endl;
    }
    void GameOutput() const;
};

class PlaceholderRoom : public Room {
    public:
    PlaceholderRoom() : Room() {}
    std::string getType() const override { return "Placeholder"; }
};

class StartingRoom : public Room {
    public:
    StartingRoom() : Room() {}
    StartingRoom(int id, const std::string& name) : Room(id, name) {}
    std::string getType() const override { return "Starting"; }
};

class TRoom : public Room {
    public:
    TRoom() : Room() {}
    TRoom(int id, const std::string& name, Orientation ori) : Room(id, name) {
        switch(ori) {
            case NORTH:
                SetWest(std::make_shared<PlaceholderRoom>());
                SetEast(std::make_shared<PlaceholderRoom>());
                SetSouth(std::make_shared<PlaceholderRoom>());
                break;
            case EAST:
                SetNorth(std::make_shared<PlaceholderRoom>());
                SetSouth(std::make_shared<PlaceholderRoom>());
                SetWest(std::make_shared<PlaceholderRoom>());
                break;
            case SOUTH:
                SetNorth(std::make_shared<PlaceholderRoom>());
                SetEast(std::make_shared<PlaceholderRoom>());
                SetWest(std::make_shared<PlaceholderRoom>());
                break;
            case WEST:
                SetNorth(std::make_shared<PlaceholderRoom>());
                SetEast(std::make_shared<PlaceholderRoom>());
                SetSouth(std::make_shared<PlaceholderRoom>());
                break;
        }
    }
    TRoom(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : Room(id, name, north, east, south, west) {}
    std::string getType() const override { return "T"; }
};

class HallRoom : public Room {
    public:
    HallRoom() : Room() {}
    HallRoom(int id, const std::string& name, Orientation ori) : Room(id, name) {
        switch(ori) {
            case NORTH:
                SetEast(std::make_shared<PlaceholderRoom>());
                SetWest(std::make_shared<PlaceholderRoom>());
                break;
            case SOUTH:
                SetEast(std::make_shared<PlaceholderRoom>());
                SetWest(std::make_shared<PlaceholderRoom>());
                break;
            case EAST:
                SetNorth(std::make_shared<PlaceholderRoom>());
                SetSouth(std::make_shared<PlaceholderRoom>());
                break;
            case WEST:
                SetNorth(std::make_shared<PlaceholderRoom>());
                SetSouth(std::make_shared<PlaceholderRoom>());
                break;
        }
    }
    HallRoom(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : Room(id, name, north, east, south, west) {}
    std::string getType() const override { return "Hall"; }
};

class CrossRoom : public Room {
    public:
    CrossRoom() : Room() {}
    CrossRoom(int id, const std::string& name) : Room(id, name) {
        SetNorth(std::make_shared<PlaceholderRoom>());
        SetEast(std::make_shared<PlaceholderRoom>());
        SetSouth(std::make_shared<PlaceholderRoom>());
        SetWest(std::make_shared<PlaceholderRoom>());
    }
    CrossRoom(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : Room(id, name, north, east, south, west) {}
    std::string getType() const override { return "Cross"; }
};

#endif // ROOM_H