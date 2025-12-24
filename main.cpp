#include <iostream>
#include <memory>

#include "Objects/room.h"
#include "Objects/GameMap.h"
#include "gameLoop.h"

using namespace std;

bool test(); 

int main() {
    test();
    lobbyLoop();
    return 0;
}

bool test() {
    Room * test = new TRoom(1, "Test Room", EAST);
    test->GameOutput();
    shared_ptr<Room> startingRoom = make_shared<StartingRoom>(0, "Starting Room");
    shared_ptr<Room> tRoom = make_shared<TRoom>(1, "T-Room 1", EAST);
    shared_ptr<Room> tRoomTwo = make_shared<TRoom>(5, "T-Room 2", NORTH);
    shared_ptr<Room> hallRoom = make_shared<HallRoom>(2, "Hall Room 1", NORTH);
    shared_ptr<Room> bendHall = make_shared<BendHall>(3, "Bend Hall 1", WEST);
    shared_ptr<Room> crossRoom = make_shared<CrossRoom>(4, "Cross Room 1");
    GameMap gameMap = GameMap(startingRoom);
    gameMap.SetupRoom(0, 1, tRoom);        // North of starting room
    gameMap.SetupRoom(-1, 1, hallRoom);     // West of T-Room
    gameMap.SetupRoom(0, -1, bendHall);     // South of starting Room
    gameMap.SetupRoom(-1, 0, tRoomTwo);    // West of Starting Room
    gameMap.SetupRoom(-1, -1, crossRoom);   // South of T-Room Two

    shared_ptr<Room> testRoom = gameMap.GetRoom(-1, 0);
    testRoom->GameOutput();
    return true;
}