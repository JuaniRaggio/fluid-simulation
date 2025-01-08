#!/bin/bash
gcc $1 -Wall -fsanitize=address -Wall -pedantic $(sdl2-config --cflags --libs)


