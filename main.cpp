#include <iostream>
#include <memory>

#include "Objects/room.h"
#include "Objects/GameMap.h"

using namespace std;

bool test(); 

int main() {
    test();
    return 0;
}

bool test() {
    Room * test = new TRoom(1, "Test Room", NORTH);
    test->GameOutput();
    shared_ptr<Room> startingRoom = make_shared<StartingRoom>(0, "Starting Room");
    GameMap gameMap(startingRoom);
    return true;
}