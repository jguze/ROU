UNAME := $(shell uname)
LINUXLIBS := -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network
MACLIBS := -framework sfml-window -framework sfml-graphics -framework sfml-network

CXX := g++
CXXFLAGS := -g


LIBS := $(MACLIBS)
ifeq ($(UNAME), Linux)
LIBS := $(LINUXLIBS)
endif

all: test_game_s

Map.o: Map.cpp Map.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 		

GameObjectManager.o: GameObjectManager.cpp GameObjectManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

VisibleGameObject.o: VisibleGameObject.cpp VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Player.o: Player.cpp Player.h VisibleGameObject.h Map.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Game.o: Game.cpp Game.h Player.h GameObjectManager.h Map.h stdafx.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

test_game.o: test_game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

test_game_s: test_game.o Game.o Player.o VisibleGameObject.o GameObjectManager.o Map.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	@echo "Removing garbage files (.o and executable)"
	$(RM) test_game_s *.o
