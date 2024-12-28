#!/usr/bin/bash
echo "Building ..."
x86_64-w64-mingw32-gcc game.c -o game.exe -Iinclude -Llib -lraylib -lm -lpthread -lwinmm -lgdi32
echo "Done! Run the game?? (Y/N)"
read x
if [ $x == "Y" ]; then
   ./CursedDino.exe
fi
