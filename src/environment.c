#include "../include/environment.h"

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

bool event_reaction(SDL_Event * event, environment env, material * material_type) {
    switch (event->type) {
        case SDL_QUIT:
            return false;
        case SDL_MOUSEMOTION:
            if (event->motion.state == true) {
                Uint32 x = event->motion.x - event->motion.x % CELL_SIZE;
                Uint32 y = event->motion.y - event->motion.y % CELL_SIZE;
                env[y / CELL_SIZE][x / CELL_SIZE] = (TCell) {
                    // The x inside our cells has to be first pixel inside the cell being the first pixel the upper
                    // left one and the last pixel the lower right one so its from left to right, up to down
                    .x = x,
                    .y = y,
                    .fill_level = FULLFILLED,
                    .size = CELL_SIZE,
                    .properties = &material_properties[*material_type],
                };
            }
            break;
        case SDL_KEYDOWN:
            if (event->key.keysym.sym == SDLK_SPACE) {
                *material_type = (*material_type + 1) % material_count;
            }
            break;
    }
    return true;
}

