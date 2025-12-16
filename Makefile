# Setting all the variables I need
CXX = g++
CXXFLAGS = -Wall -Werror -g 

# Objects

OBJS = loader.o main.o Objects/GameMap.o Objects/room.o json11/json11.o

all: game.exe

# Target executable

game.exe: $(OBJS)
	$(CXX) $(CXXFLAGS) -o game.exe $(OBJS)

# Generic rule for compiling .cpp files to .o files

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Dependencies

loader.o: loader.cpp
main.o: main.cpp Objects/room.h Objects/GameMap.h Objects/room.h
Objects/GameMap.o: Objects/GameMap.cpp
Objects/room.o: Objects/room.cpp Objects/room.h
json11/json11.o: json11/json11.cpp json11/json11.hpp

#clean target to remove compiled files

clean:
	rm -f $(OBJS) game.exe

.PHONY: all clean