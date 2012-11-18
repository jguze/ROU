UNAME := $(shell uname)
LINUXLIBS := -lsfml-window -lsfml-graphics -lsfml-system -lsfml-network
MACLIBS := -framework sfml-window -framework sfml-graphics -framework sfml-network

CXX := g++
CXXFLAGS := -g


LIBS := $(MACLIBS)
ifeq ($(UNAME), Linux)
LIBS := $(LINUXLIBS)
endif

all: game

Server.o: Server.cpp Server.h
	$(CXX) $(CXXFLAGS) -c $< -o $@ 	

Game.o: Game.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ 	

game: Game.o Server.o Client.o UserInputWindow.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

UserInputWindow.o: UserInputWindow.cpp UserInputWindow.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

Client.o: Client.cpp Client.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	@echo "Removing garbage files (.o and executable)"
	$(RM) game *.o

