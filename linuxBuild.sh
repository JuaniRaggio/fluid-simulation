#!/bin/bash
src_files=src/*.c
main_file=$1

if [ -z "$main_file" ]; then
    echo "Use: $0 <main.c>"
    exit 1
fi

gcc $main_file $src_files -Wall -fsanitize=address -pedantic -lm $(sdl2-config --cflags --libs)

