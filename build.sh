#!/bin/bash

clang -o fluids $1 -fsanitize=address -pedantic -Wall -I/opt/hombrew/Cellar/sdl2/2.30.11/include -L/opt/homebrew/Cellar/sdl2/2.30.11/lib -lSDL2


