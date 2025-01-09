#include "../include/simulation.h"
#include "../include/window.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#define DROP_SIZE 0.1
#define EPSILOM 0.0001

/* static void copy_env(environment target, environment source) { */
/*     for (int i = 0; i < ROWS; ++i) */
/*         for (int j = 0; j < COLUMNS; ++j) */
/*             target[i][j] = source[i][j]; */
/* } */

typedef struct Cell_flow {
    double up;
    double down;
    double left;
    double right;
} TCell_flow;

typedef TCell_flow environment_flow[ROWS][COLUMNS];

void apply_flows(environment env, environment_flow env_flows) {
    for (int i = ROWS - 2; i >= 0; --i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (env_flows[i][j].down == FULLFILLED && env[i][j].fill_level == FULLFILLED) {
                env[i + 1][j].fill_level = FULLFILLED;
                env[i][j].fill_level = EMPTY;
            }
        }
    }
}

void get_flows(environment env, environment_flow env_flows) {
    for (int i = ROWS - 2; i >= 0; --i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (env[i + 1][j].fill_level != FULLFILLED && env[i][j].properties != &material_properties[solid_type]) {
                env_flows[i][j].down = FULLFILLED;
            } else {
                env_flows[i][j].down = 0;
            }
        }
    }
}

void simulation_step(environment env) {
    environment_flow env_flows;
    get_flows(env, env_flows);
    apply_flows(env, env_flows);
}

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface, environment env) {
    bool simulation_running = true;
    material material_type = solid_type;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            simulation_running = event_reaction(&event, env, &material_type);
            simulation_step(env);
            draw_environment(window_surface, env);
            draw_grid(window_surface);
            CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
        }
        CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
    }
    return 0;
}

