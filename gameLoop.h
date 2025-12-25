#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <iostream>

using namespace std;

void lobbyLoop();

void gameLoop(shared_ptr<Room> startingRoom);

#endif // GAMELOOP_H