#include "../include/simulation.h"
#include "../include/window.h"

void apply_flows(environment env, environment_flow env_flows) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (i + 1 < ROWS && env_flows[i][j].down > EPSILOM) {
                env[i + 1][j].fill_level += env_flows[i][j].down;
                env[i][j].fill_level -= env_flows[i][j].down;
            }
            if (j - 1 >= 0 && env_flows[i][j].left > EPSILOM) {
                env[i][j - 1].fill_level += env_flows[i][j].left;
                env[i][j].fill_level -= env_flows[i][j].left;
            }
            if (j + 1 < COLUMNS && env_flows[i][j].right > EPSILOM) {
                env[i][j + 1].fill_level += env_flows[i][j].right;
                env[i][j].fill_level -= env_flows[i][j].right;
            }
        }
    }
}

double calculate_fluid_flow(double source_fill, double target_fill) {
    source_fill = fmax(0.0, fmin(source_fill, FULLFILLED));
    target_fill = fmax(0.0, fmin(target_fill, FULLFILLED));
    return fmin((source_fill - target_fill) / 2.0, FULLFILLED);
}

void get_flows(environment env, environment_flow env_flows) {
    memset(env_flows, 0, sizeof(environment_flow));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            if (env[i][j].fill_level == EMPTY || !env[i][j].properties->gravity)  {
                continue;
            }
            if (i + 1 < ROWS && env[i + 1][j].properties->gravity && env[i + 1][j].fill_level != FULLFILLED) {
                env_flows[i][j].down = fmin(1 - env[i + 1][j].fill_level, env[i][j].fill_level);
            }
            if (j + 1 < COLUMNS && env[i][j + 1].properties->gravity && env[i][j + 1].fill_level - env[i][j].fill_level < EPSILOM) {
                env_flows[i][j].right = calculate_fluid_flow(env[i][j].fill_level, env[i][j + 1].fill_level);
            }
            if (j - 1 >= 0 && env[i][j - 1].properties->gravity && env[i][j - 1].fill_level - env[i][j].fill_level < EPSILOM) {
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
        }
            simulation_step(env);
            draw_environment(window_surface, env);
            draw_grid(window_surface);
            SDL_UpdateWindowSurface(window);
    }
    return 0;
}

