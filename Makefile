CXX = g++
CXXFLAGS = -w -lSDL2 -lSDL2_mixer -lSDL2_image -lsdl2_ttf
SRCDIR = src
SRCDIR2 = includes
BINDIR = bin
TARGET = $(BINDIR)/game
SRCS = $(shell find $(SRCDIR) -name "*.cpp") $(shell find $(SRCDIR2) -name "*.cpp")
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