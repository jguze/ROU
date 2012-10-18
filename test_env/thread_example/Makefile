UNAME := $(shell uname)
LINUXLIBS := -lsfml-system
MACLIBS := -framework sfml-system
CXX := g++ #gcc
CXXFLAGS := -g

#Determine if we are on linux or mac
LIBS := $(MACLIBS)
ifeq ($(UNAME), Linux)
LIBS := $(LINUXLIBS)
endif

all: threading threadBase

%.o: %.cpp	
	$(CXX) $(CXXFLAGS) -c $< -o $@

threading: threading.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

threadBase: threadBase.o
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

clean:
	@echo "Removing garbage files (.o and executable)"
	$(RM) threading threadBase *.o
