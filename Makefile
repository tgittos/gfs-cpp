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
	LDFLAGS = -framework sfml-system -framework sfml-graphics -framework sfml-window
endif
# Pass compiler preprocessor variables in
#-DFREEGLUT FREEGLUT # gcc
#/DFREEGLUT FREEGLUT # windows
EXECUTABLES = pang

.PHONY: all
.DEFAULT: all

all: includes $(EXECUTABLES)

clean:
	rm -Rf out
	rm -Rf bin

pang: includes cgame.o main.o
	$(CC) out/cgame.o out/main.o $(IFLAGS) $(LDFLAGS) $(CFLAGS) -o bin/$@

cgame.o: game.o player.o mainmenu.o splashscreen.o gameobjectmanager.o
	ld -r out/game.o out/player.o out/mainmenu.o out/splashscreen.o out/gameobjectmanager.o -o out/cgame.o

player.o: playerpaddle.o visiblegameobject.o
	ld -r out/playerpaddle.o out/visiblegameobject.o -o out/player.o

%: %.o
	$(CC) out/$< $(IFLAGS) $(LDFLAGS) $(CFLAGS) -o bin/$@

%.o: %.cpp
	$(CC) $(IFLAGS) $(CFLAGS) -c -o out/$@ src/$<

%.cpp:
	mkdir -p out bin
	literati tangle -o src/. lit/src/$@.lit

includes:
	literati tangle -o include/. lit/include