#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "gameLoop.h"
#include "Objects/room.h"
#include "Objects/GameMap.h"
#include "operations.h"

using namespace std;

map<int, string> descMap = {
    {0, "You spawn in a small room. There is nothing in here."},
    {1, "You are in the lobby. More will be added here later. For now, you can go east to start a new run."},
    {2, "You move into a room with a pylon in the middle. If you touch this pylon, you will be dropped into the dungeon."}
};

void lobbyLoop() {
    shared_ptr<Room> respawnRoom = make_shared<DeadEndRoom>(0, "Respawn Room", EAST);
    shared_ptr<Room> lobby = make_shared<TwoEntranceRoom>(1, "Lobby", NORTH);
    shared_ptr<Room> startRunRoom = make_shared<DeadEndRoom>(2, "Start Run Room", WEST);

    respawnRoom->SetEast(lobby);
    lobby->SetWest(respawnRoom);
    lobby->SetEast(startRunRoom);
    startRunRoom->SetWest(lobby);

    shared_ptr<Room> currentRoom = respawnRoom;

    bool exit = false;

    while(!exit) {
        cout << "\n" << descMap[currentRoom->getId()] << endl;
        exit = takeInput(currentRoom);
        if (currentRoom->getType() == "Starting Room") {
            gameLoop();
            currentRoom = respawnRoom;
        }
    }
}

void gameLoop(shared_ptr<Room> startingRoom) {
    
}

