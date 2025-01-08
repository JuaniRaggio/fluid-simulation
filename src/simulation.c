#include "../include/simulation.h"
#include "../include/window.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface, environment env) {
    bool simulation_running = true;
    material material_type = solid_type;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            simulation_running = event_reaction(&event, env, &material_type);
            draw_environment(window_surface, env);
            CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
            draw_grid(window_surface);
            CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
        }
    }
    return 0;
}

