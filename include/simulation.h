#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "error_management.h"
#include "formats.h"
#include "environment.h"

#define EPSILOM 0.0001
#define DROP_SIZE 0.1

typedef struct Cell_flow {
    double up;
    double down;
    double left;
    double right;
} TCell_flow;

typedef TCell_flow environment_flow[ROWS][COLUMNS];

void apply_flows(environment env, environment_flow env_flows);

void get_flows(environment env, environment_flow env_flows);

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface, environment env);

#endif

