CXX = g++
CXXFLAGS = -w -Iincludes -lSDL2 -lSDL2_mixer -lSDL2_image -lsdl2_ttf -std=c++20
SRCDIR = src
BINDIR = bin
TARGET = $(BINDIR)/game
SRCS = $(shell find $(SRCDIR) -name "*.cpp") 
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