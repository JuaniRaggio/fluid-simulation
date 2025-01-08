#include "../include/simulation.h"
#include "../include/window.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

#define EMPTY 0.0
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
    /* { */
    /*     .color = COLOR_BLACK, */
    /*     .gravity = false, */
    /* }, */
};

void new_environment(environment garbage_environment) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLUMNS; ++j) {
            garbage_environment[i][j] = (TCell) {
                .x = j * CELL_SIZE,
                .y = i * CELL_SIZE,
                .size = CELL_SIZE,
                .fill_level = EMPTY,
                .properties = &material_properties[water_type],
            };
        }
    }
}

bool run_simulation(SDL_Window * window, SDL_Surface * window_surface, environment env) {
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
                        Uint32 x = event.motion.x - event.motion.x % CELL_SIZE;
                        Uint32 y = event.motion.y - event.motion.y % CELL_SIZE;
                        env[y / CELL_SIZE][x / CELL_SIZE] = (TCell) {
                            // The x inside our cells has to be first pixel inside the cell being the first pixel the upper
                            // left one and the last pixel the lower right one so its from left to right, up to down
                            .x = x,
                            .y = y,
                            .fill_level = 1,
                            .size = CELL_SIZE,
                            .properties = &material_properties[material_type],
                        };
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE) {
                        material_type = (material_type + 1) % material_count;
                    }
                    break;
            }
            draw_environment(window_surface, env);
            CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());
        }
    }
    return 0;
}

