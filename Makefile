CXX = g++
CXXFLAGS = -w -Iincludes -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -std=c++23
SRCDIR = src
BINDIR = bin
TARGET = $(BINDIR)/game
SRCS = main.cpp $(shell find $(SRCDIR) -name "*.cpp") 
CMD = $(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET)

all:
	mkdir -p $(BINDIR)
	$(CMD)

.PHONY: clean run

clean:
	rm -rf $(BINDIR)

run:
	mkdir -p $(BINDIR)
	$(CMD)
	cd $(BINDIR) && ./game