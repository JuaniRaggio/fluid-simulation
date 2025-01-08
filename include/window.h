#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include "formats.h"
#include "simulation.h"

void draw_environment(SDL_Surface * wiondows_surface, environment env);
void draw_grid(SDL_Surface * windows_surface);
void draw_particle(SDL_Surface * window_surface, TCell cell);

#endif

