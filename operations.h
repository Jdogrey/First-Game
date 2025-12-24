#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <memory>

#include "Objects/room.h"

using namespace std;

bool takeInput(shared_ptr<Room>& room);
bool takeInput(shared_ptr<Room>& room, int& x, int& y);

#endif // OPERATIONS_H