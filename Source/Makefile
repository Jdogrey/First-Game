# Makefile for building the game using MSVC. I'll have to learn and experiment with MSVC.

# Compiler and flags
CXX = cl
CXXFLAGS = /nologo /W3 /EHsc /MD /Zi

# Source files
SRC = loader.cpp main.cpp \
      Objects/GameMap.cpp Objects/room.cpp \
      json11/json11.cpp \
      gameLoop.cpp operations.cpp

# Object files (replace .cpp with .obj)
OBJS = $(SRC:.cpp=.obj)

# Executable
EXE = ..\game.exe

# Default target
all: $(EXE)

# Link the executable
$(EXE): $(OBJS)
	$(CXX) /nologo $(OBJS) /Fe:$(EXE)

# Compile .cpp to .obj
%.obj: %.cpp
	$(CXX) $(CXXFLAGS) /c $< /Fo$@

# Clean up
clean:
	del /Q $(OBJS) $(EXE)

.PHONY: all clean