#include <iostream>
#include <memory>
#include <windows.h>

#include "Objects/room.h"
#include "Objects/GameMap.h"
#include "gameLoop.h"
#include "operations.h"

using namespace std;

bool test(); 

int main() {
    SetDllDirectoryA("dlls");
    // test();
    lobbyLoop();
    return 0;
}

bool test() {
    Room * test = new TRoom(1, "Test Room", Orientation::EAST);
    test->GameOutput();
    shared_ptr<Room> startingRoom = make_shared<StartingRoom>(0, "Starting Room");
    shared_ptr<Room> tRoom = make_shared<TRoom>(1, "T-Room 1", Orientation::EAST);
    shared_ptr<Room> tRoomTwo = make_shared<TRoom>(5, "T-Room 2", Orientation::NORTH);
    shared_ptr<Room> hallRoom = make_shared<HallRoom>(2, "Hall Room 1", Orientation::NORTH);
    shared_ptr<Room> bendHall = make_shared<BendHall>(3, "Bend Hall 1", Orientation::WEST);
    shared_ptr<Room> crossRoom = make_shared<CrossRoom>(4, "Cross Room 1");
    shared_ptr<GameMap> gameMapPtr = make_shared<GameMap>(startingRoom, NORMAL);
    GameMap& gameMap = *gameMapPtr;
    gameMap.SetupRoom(0, 1, tRoom);        // North of starting room
    gameMap.SetupRoom(-1, 1, hallRoom);     // West of T-Room
    gameMap.SetupRoom(0, -1, bendHall);     // South of starting Room
    gameMap.SetupRoom(-1, -1, crossRoom);   // South of T-Room Two

    cout << "\n--- Testing Room Generation ---\n";

    shared_ptr<Room> randomRoom = generateRoom(gameMapPtr, -1, 0); 
    gameMap.SetupRoom(-1, 0, randomRoom);

    randomRoom->GameOutput();

    shared_ptr<GameMap> gameMapPtr2 = make_shared<GameMap>(startingRoom, NORMAL);
    shared_ptr<Room> randomRoom2 = generateRoom(gameMapPtr2, 0, 1);
    randomRoom2->GameOutput();
    shared_ptr<Room> randomRoom3 = generateRoom(gameMapPtr2, 0, 1);
    randomRoom3->GameOutput();
    shared_ptr<Room> randomRoom4 = generateRoom(gameMapPtr2, 0, 1);
    randomRoom4->GameOutput();  
    shared_ptr<Room> randomRoom5 = generateRoom(gameMapPtr2, 0, 1);
    randomRoom5->GameOutput();
    shared_ptr<Room> randomRoom6 = generateRoom(gameMapPtr2, 0, 1);
    randomRoom6->GameOutput();

    for(int i = 0; i < 200; i++) {

        cout << "\n--- Rooms to the North --- \n";

        randomRoom2 = generateRoom(gameMapPtr2, 0, 1);
        randomRoom2->GameOutput();
        randomRoom3 = generateRoom(gameMapPtr2, 0, 1);
        randomRoom3->GameOutput();
        randomRoom4 = generateRoom(gameMapPtr2, 0, 1);
        randomRoom4->GameOutput();  
        randomRoom5 = generateRoom(gameMapPtr2, 0, 1);
        randomRoom5->GameOutput();
        randomRoom6 = generateRoom(gameMapPtr2, 0, 1);
        randomRoom6->GameOutput();
        
        cout << "\n--- Rooms to the East --- \n";

        randomRoom2 = generateRoom(gameMapPtr2, 1, 0);
        randomRoom2->GameOutput();
        randomRoom3 = generateRoom(gameMapPtr2, 1, 0);
        randomRoom3->GameOutput();
        randomRoom4 = generateRoom(gameMapPtr2, 1, 0);
        randomRoom4->GameOutput();  
        randomRoom5 = generateRoom(gameMapPtr2, 1, 0);
        randomRoom5->GameOutput();
        randomRoom6 = generateRoom(gameMapPtr2, 1, 0);
        randomRoom6->GameOutput();

        cout << "\n--- Rooms to the South --- \n";

        randomRoom2 = generateRoom(gameMapPtr2, 0, -1);
        randomRoom2->GameOutput();
        randomRoom3 = generateRoom(gameMapPtr2, 0, -1);
        randomRoom3->GameOutput();
        randomRoom4 = generateRoom(gameMapPtr2, 0, -1);
        randomRoom4->GameOutput();  
        randomRoom5 = generateRoom(gameMapPtr2, 0, -1);
        randomRoom5->GameOutput();
        randomRoom6 = generateRoom(gameMapPtr2, 0, -1);
        randomRoom6->GameOutput();

        cout << "\n--- Rooms to the West --- \n";

        randomRoom2 = generateRoom(gameMapPtr2, -1, 0);
        randomRoom2->GameOutput();
        randomRoom3 = generateRoom(gameMapPtr2, -1, 0);
        randomRoom3->GameOutput();
        randomRoom4 = generateRoom(gameMapPtr2, -1, 0);
        randomRoom4->GameOutput();  
        randomRoom5 = generateRoom(gameMapPtr2, -1, 0);
        randomRoom5->GameOutput();
        randomRoom6 = generateRoom(gameMapPtr2, -1, 0);
        randomRoom6->GameOutput();
    }

    shared_ptr<Room> testRoom = gameMap.GetRoom(-1, 0);
    testRoom->GameOutput();
    return true;
}