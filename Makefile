# OSTYPE is not set by default on OS X
ifndef OSTYPE
	OSTYPE = $(shell uname -s)
endif

CC = g++
CFLAGS = -Wall -g -m32
# Linux flags
LDFLAGS = -lGL -lGLU -lglut -lGLEW
IFLAGS = -Ilib -Iinclude
# Override if we're in OS X
ifeq "$(OSTYPE)" "Darwin"
	LDFLAGS = -framework sfml-system -framework sfml-graphics -framework sfml-window -framework sfml-audio
endif
# Pass compiler preprocessor variables in
#-DFREEGLUT FREEGLUT # gcc
#/DFREEGLUT FREEGLUT # windows
EXECUTABLES = pang

.PHONY: all clean includes assets
.DEFAULT: all

all: includes $(EXECUTABLES) assets

pang: includes gamelib.o main.o
	mkdir -p bin
	$(CC) out/gamelib.o out/main.o $(IFLAGS) $(LDFLAGS) $(CFLAGS) -o bin/$@

gamelib.o: playerlib.o game.o mainmenu.o splashscreen.o gameobjectmanager.o servicelocator.o soundlib.o
	ld -r out/playerlib.o out/soundlib.o out/game.o out/servicelocator.o  out/mainmenu.o out/splashscreen.o out/gameobjectmanager.o -o out/gamelib.o

playerlib.o: playerpaddle.o gameball.o visiblegameobject.o
	ld -r out/playerpaddle.o out/gameball.o out/visiblegameobject.o -o out/playerlib.o

soundlib.o: soundfilecache.o sfmlsoundprovider.o
	ld -r out/soundfilecache.o out/sfmlsoundprovider.o -o out/soundlib.o

%: %.o
	$(CC) out/$< $(IFLAGS) $(LDFLAGS) $(CFLAGS) -o bin/$@

%.o: %.cpp
	$(CC) $(IFLAGS) $(CFLAGS) -c -o out/$@ src/$<

%.cpp:
	mkdir -p out
	literati tangle -o src/. lit/src/$@.lit

%.hpp:
	mkdir -p out
	literati tangle -o include/. lit/include/$@.lit

clean:
	rm -Rf out
	rm -Rf bin

includes:
	literati tangle -o include/. lit/include

assets:
	mkdir -p bin/assets
	cp -r assets/* bin/assets/.