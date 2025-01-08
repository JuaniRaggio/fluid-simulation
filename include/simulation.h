#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "error_management.h"
#include "formats.h"

typedef TCell environment[ROWS][COLUMNS];

void new_environment(environment garbage_environment);

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface, environment env);

#endif

