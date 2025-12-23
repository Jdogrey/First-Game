#include <iostream>
#include <string>
#include <memory>

#include "gameLoop.h"
#include "Objects/room.h"
#include "Objects/GameMap.h"
#include "operations.h"

using namespace std;

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
        exit = takeInput(currentRoom);
    }
}

void gameLoop() {
    
}

