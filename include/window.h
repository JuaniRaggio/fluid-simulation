#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
#include "formats.h"

void draw_grid(SDL_Surface * windows_surface);
void draw_particle(SDL_Surface * window_surface, TCell cell);

#endif

