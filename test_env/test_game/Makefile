UNAME := $(shell uname)
LINUXLIBS := -lsfml-window -lsfml-graphics
MACLIBS := -framework sfml-window -framework sfml-graphics

CXX := g++
CXXFLAGS := -g


LIBS := $(MACLIBS)
ifeq ($(UNAME), Linux)
LIBS := $(LINUXLIBS)
endif

all: test_game

test_game: test_game.o Game.o
	$(CXX) $(CXXFLAGS) test_game.o Game.o -o $@ $(LIBS)

test_game.o: test_game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Game.o: Game.cpp Game.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

VisibleGameObject.o: VisibleGameObject.cpp VisibleGameObject.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Removing garbage files (.o and executable)"
	$(RM) using_opengl *.o
