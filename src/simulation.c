#include "../include/simulation.h"
#include "../include/window.h"

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface) {
    bool simulation_running = true;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) simulation_running = false;
            if (event.type == SDL_MOUSEMOTION) {
                if (event.motion.state == true) {
                    TCell solid_particle = {
                        // The x inside our cells has to be first pixel inside the cell being the first pixel the upper
                        // left one and the last pixel the lower right one so its from left to right, up to down
                        .x = event.motion.x - event.motion.x % CELL_SIZE,
                        .y = event.motion.y - event.motion.y % CELL_SIZE,
                        .size = CELL_SIZE,
                        .properties = {
                            .color = COLOR_WHITE,
                        },
                    };
                    draw_particle(window_surface, solid_particle);
                    CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
                }
            }
        }
    }
    return 0;
}

