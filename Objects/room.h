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

    // constructors and getters/setters

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

    // PrintInfo for debugging

    void PrintInfo() const {
        std::cout << "Room ID: " << id << ", Name: " << name << ", Type: " << getType() << std::endl;
    }

    // Outputs for gameplay

    virtual void GameOutput() const;
    virtual void OptionsOutput() const;
};

class PlaceholderRoom : public Room {
    public:
    PlaceholderRoom() : Room() {}
    std::string getType() const override { return "Placeholder"; }

    void GameOutput() const override;
};

class StartingRoom : public Room {
    public:
    StartingRoom() : Room() {}
    StartingRoom(int id, const std::string& name) : Room(id, name) {
        SetNorth(std::make_shared<PlaceholderRoom>());
        SetEast(std::make_shared<PlaceholderRoom>());
        SetSouth(std::make_shared<PlaceholderRoom>());
        SetWest(std::make_shared<PlaceholderRoom>());
    }
    std::string getType() const override { return "Starting"; }

    void GameOutput() const override;
};

class THall : public Room {
    public:
    THall() : Room() {}
    THall(int id, const std::string& name, Orientation ori) : Room(id, name) {
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
    THall(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : Room(id, name, north, east, south, west) {}
    std::string getType() const override { return "T-Hall"; }

    void GameOutput() const override;
};

class TRoom : public THall {
    public:
    TRoom() : THall() {}
    TRoom(int id, const std::string& name, Orientation ori) : THall(id, name, ori) {}
    TRoom(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : THall(id, name, north, east, south, west) {}
    std::string getType() const override { return "T-Room"; }

    void GameOutput() const override;
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

    void GameOutput() const override;
};

class TwoEntranceRoom : public HallRoom {
    public:
    TwoEntranceRoom() : HallRoom() {}
    TwoEntranceRoom(int id, const std::string& name, Orientation ori) : HallRoom(id, name, ori) {}
    TwoEntranceRoom(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : HallRoom(id, name, north, east, south, west) {}
    std::string getType() const override { return "Two-Entrance"; }

    void GameOutput() const override;
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

    void GameOutput() const override;
};

class FourEntranceRoom : public CrossRoom {
    public:
    FourEntranceRoom() : CrossRoom() {}
    FourEntranceRoom(int id, const std::string& name) : CrossRoom(id, name) {}
    FourEntranceRoom(int id, const std::string& name, Room * north, Room * east, Room * south, Room * west)
        : CrossRoom(id, name, north, east, south, west) {}
    std::string getType() const override { return "Four-Entrance"; }

    void GameOutput() const override;
};

class DeadEnd : public Room {
    public:
    DeadEnd() : Room() {}
    DeadEnd(int id, const std::string& name, Orientation ori) : Room(id, name) {
        switch(ori) {
            case NORTH:
                SetNorth(std::make_shared<PlaceholderRoom>());
                break;
            case EAST:
                SetEast(std::make_shared<PlaceholderRoom>());
                break;
            case SOUTH:
                SetSouth(std::make_shared<PlaceholderRoom>());
                break;
            case WEST:
                SetWest(std::make_shared<PlaceholderRoom>());
                break;
        }
    }
    std::string getType() const override { return "Dead-End"; }

    void GameOutput() const override;
};

class DeadEndRoom : public DeadEnd {
    public:
    DeadEndRoom() : DeadEnd() {}
    DeadEndRoom(int id, const std::string& name, Orientation ori) : DeadEnd(id, name, ori) {}
    std::string getType() const override { return "Dead-End Room"; }

    void GameOutput() const override;
};

// Shop will have 5 items randomly generated when the room is created
// TO BE IMPLEMENTED

class ShopRoom : public DeadEndRoom {
    public:
    ShopRoom() : DeadEndRoom() {}
    ShopRoom(int id, const std::string& name, Orientation ori) : DeadEndRoom(id, name, ori) {}

    std::string getType() const override { return "Shop"; }

    void GameOutput() const override;
    void OptionsOutput() const override;
};

class BossRoom : public DeadEndRoom {
    public:
    BossRoom() : DeadEndRoom() {}
    BossRoom(int id, const std::string& name, Orientation ori) : DeadEndRoom(id, name, ori) {}
    std::string getType() const override { return "Boss"; }

    void GameOutput() const override;
    void OptionsOutput() const override;
};

#endif // ROOM_H