UNAME := $(shell uname)
LINUXLIBS := -lsfml-window -lsfml-system -lGLU -lGL
MACLIBS := -framework sfml-window -framework sfml-system

CXX := g++ #gcc c++
CXXFLAGS := -g


LIBS := $(MACLIBS)
ifeq ($(UNAME), Linux)
LIBS := $(LINUXLIBS)
endif

all: using_opengl

%.o: %.cpp	
	$(CXX) $(CXXFLAGS) -c $< -o $@

using_opengl: using_opengl.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

clean:
	@echo "Removing garbage files (.o and executable)"
	$(RM) using_opengl *.o
