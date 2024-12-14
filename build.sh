#!/usr/bin/bash
echo "Building ..."
cc game.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game.o
echo "Done! Run the game?? (Y/N)"
read x
if [ $x == "Y" ]; then
   ./game.o
fi
