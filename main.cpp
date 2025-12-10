#include <iostream>

#include "Objects/room.h"

int main() {
    test();
    return 0;
}

bool test() {
    Room * test = TRoom(1, "Test Room", NORTH);
    return true;
}