.PHONY: build
# Define the compiler
CC = gcc

# Define the target executable name
TARGETLIN = bin/CursedDinoLinux
TARGETWIN = bin/CursedDinoWindows.exe

# Define the source file
SRC = src/main.c src/game.c src/menus.c

# Compiler flags
CFLAGS = -lraygui -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -O2 -Llib -Iinclude
DFLAGS = -fsanitize=address -g -O0

# Build target
$(TARGETLIN): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGETLIN) $(SRC)

debug:
	$(CC) $(DFLAGS) $(CFLAGS) -o $(TARGETLIN) $(SRC)

win:
	x86_64-w64-mingw32-gcc $(SRC) -Iinclude -Llib -lraylib -lm -lpthread -lwinmm -lgdi32 -mwindows -o $(TARGETWIN) 

winDebug:
	x86_64-w64-mingw32-gcc $(SRC) -Iinclude -Llib -lraylib -lm -lpthread -lwinmm -lgdi32 -o $(TARGETWIN) 
