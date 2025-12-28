#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <memory>

#include "Objects/room.h"
#include "Objects/GameMap.h"

using namespace std;

bool takeInput(shared_ptr<Room>& room);
bool takeInput(shared_ptr<Room>& room, int& x, int& y);
shared_ptr<Room> generateRoom(shared_ptr<GameMap> gameMap, int x, int y);

#endif // OPERATIONS_H