#include "../include/simulation.h"
#include "../include/window.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

typedef enum {solid_type = 0, water_type, material_count} material;
#define SOLID_COLOR COLOR_WHITE
#define WATER_COLOR COLOR_BLUE
const TFluid material_properties[material_count] = {
    // Vector with material properties, they are ordered by the material enum
    // Solid
    {
        .color = SOLID_COLOR,
        .gravity = false,
    },
    // Water
    {
        .color = WATER_COLOR,
        .gravity = true,
    },
};

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface) {
    bool simulation_running = true;
    material material_type = solid_type;
    SDL_Event event;
    while (simulation_running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    simulation_running = false;
                    break;
                case SDL_MOUSEMOTION:
                    if (event.motion.state == true) {
                        TCell solid_particle = {
                            // The x inside our cells has to be first pixel inside the cell being the first pixel the upper
                            // left one and the last pixel the lower right one so its from left to right, up to down
                            .x = event.motion.x - event.motion.x % CELL_SIZE,
                            .y = event.motion.y - event.motion.y % CELL_SIZE,
                            .size = CELL_SIZE,
                            .properties = &material_properties[material_type],
                        };
                        draw_particle(window_surface, solid_particle);
                        CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        material_type = (material_type + 1) % material_count;
                    }
                    break;
            }
        }
    }
    return 0;
}

