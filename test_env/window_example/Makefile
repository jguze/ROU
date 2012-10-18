UNAME := $(shell uname)
LINUXLIBS := -lsfml-window -lsfml-graphics -lsfml-system
MACLIBS := -framework sfml-window -framework -framework sfml-graphics -framework sfml-system

CXX := g++ #gcc c++
CXXFLAGS := -g


LIBS := $(MACLIBS)
ifeq ($(UNAME), Linux)
LIBS := $(LINUXLIBS)
endif

all: window

%.o: %.cpp	
	$(CXX) $(CXXFLAGS) -c $< -o $@

window: window.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

clean:
	@echo "Removing garbage files (.o and executable)"
	$(RM) window *.o
