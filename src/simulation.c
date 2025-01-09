#include "../include/simulation.h"
#include "../include/window.h"

#define DIRECTIONS 4

void apply_flows(environment env, environment_flow env_flows) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (env_flows[i][j].down) {
                env[i + 1][j].fill_level += env_flows[i][j].down;
                env[i][j].fill_level -= env_flows[i][j].down;
            } 
            if (env_flows[i][j].left) {
                env[i][j - 1].fill_level += env_flows[i][j].left;
                env[i][j].fill_level -= env_flows[i][j].left;
            } 
            if (env_flows[i][j].right) {
                env[i][j + 1].fill_level += env_flows[i][j].right;
                env[i][j].fill_level -= env_flows[i][j].right;
            }
        }
    }
}

double calculate_fluid_flow(double source_fill, double target_fill) { return (source_fill - target_fill) / 2; }

void get_flows(environment env, environment_flow env_flows) {
    double transfer_vector;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            env_flows[i][j] = (TCell_flow) {0};
            if (env[i][j].fill_level == EMPTY || !env[i][j].properties->gravity)  {
                continue;
            }
            if (i + 1 < ROWS && env[i + 1][j].properties->gravity && env[i + 1][j].fill_level != FULLFILLED) {
                transfer_vector = 1 - env[i + 1][j].fill_level > env[i][j].fill_level ?
                                    env[i][j].fill_level:1 - env[i + 1][j].fill_level;
                env_flows[i][j].down = transfer_vector;
            } else if (j + 1 < COLUMNS && env[i][j + 1].properties->gravity && env[i][j + 1].fill_level - env[i][j].fill_level < EPSILOM) {
                env_flows[i][j].right = calculate_fluid_flow(env[i][j].fill_level, env[i][j + 1].fill_level);
            } else if (j - 1 >= 0 && env[i][j - 1].properties->gravity && env[i][j - 1].fill_level - env[i][j].fill_level < EPSILOM) {
                env_flows[i][j].left = calculate_fluid_flow(env[i][j].fill_level, env[i][j - 1].fill_level);
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

