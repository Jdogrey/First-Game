#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>

#include "Objects/room.h"

using namespace std;

void lobbyLoop();

void gameLoop(shared_ptr<Room> startingRoom);

#endif // GAMELOOP_H