#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>

#include "Objects/room.h"
#include "Objects/GameMap.h"

using namespace std;

void lobbyLoop();

void gameLoop(shared_ptr<Room> startingRoom, Difficulty diff);

#endif // GAMELOOP_H