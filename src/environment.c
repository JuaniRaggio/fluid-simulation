#include "../include/environment.h"
#include <SDL2/SDL_events.h>

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

// Expects lower limit to be 0
// Returns true if valid
static bool validate_dimension(Sint32 coord, int upper_limit);

void new_environment(environment garbage_environment) {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLUMNS; ++j) {
      garbage_environment[i][j] = (TCell){
          .x = j * CELL_SIZE,
          .y = i * CELL_SIZE,
          .size = CELL_SIZE,
          .fill_level = EMPTY,
          .properties = &material_properties[water_type],
      };
    }
  }
}

bool validate_dimension(Sint32 coord, int upper_limit) {
  static const bool invalid = false, valid = true; 
  if (coord >= upper_limit || coord < 0)
    return invalid;
  return valid;
}

bool event_reaction(SDL_Event *event, environment env, material *material_type,
                    bool *rain_mode) {
  static bool delete_mode = false;

  // I have to improove the rain_mode cause for some reason each drop ends up
  // being like a "piramid", I think whats happening is that they spread out
  // before falling
  /* if (*rain_mode) { */
  /*   TCell *first_row = env[0]; */
  /*   for (int i = 0; i < COLUMNS; i++) { */
  /*     first_row[i] = (TCell){ */
  /*         .x = i, */
  /*         .y = 0, */
  /*         .fill_level = FULLFILLED, */
  /*         .size = CELL_SIZE, */
  /*         .properties = &material_properties[water_type], */
  /*     }; */
  /*   } */
  /* } */
  switch (event->type) {
  case SDL_QUIT:
    return false;
  case SDL_KEYDOWN:
    SDL_Keycode kc = event->key.keysym.sym;
    if (kc == SDLK_SPACE) {
      *material_type = (*material_type + 1) % material_count;
    } else if (kc == SDLK_BACKSPACE) {
      delete_mode = !delete_mode;
    } else if (kc == SDLK_r) {
      // Rainmode - toggle
      *rain_mode = !*rain_mode;
    }
    break;
  case SDL_MOUSEMOTION:
    if (event->motion.state) {
      if (!validate_dimension(event->motion.x, SCREEN_WIDTH) ||
          !validate_dimension(event->motion.y, SCREEN_HEIGHT))
        break;
      Uint32 x = event->motion.x - event->motion.x % CELL_SIZE;
      Uint32 y = event->motion.y - event->motion.y % CELL_SIZE;
      double current_level = FULLFILLED;
      if (delete_mode) {
        current_level = EMPTY;
        *material_type = water_type;
      }
      env[y / CELL_SIZE][x / CELL_SIZE] = (TCell){
          // The x inside our cells has to be first pixel inside the cell being
          // the first pixel the upper
          // left one and the last pixel the lower right one so its from left to
          // right, up to down
          .x = x,
          .y = y,
          .fill_level = current_level,
          .size = CELL_SIZE,
          .properties = &material_properties[*material_type],
      };
    }
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (event->button.state) {
      Uint32 x = event->button.x - event->button.x % CELL_SIZE;
      Uint32 y = event->button.y - event->button.y % CELL_SIZE;
      double current_level = FULLFILLED;
      if (delete_mode) {
        current_level = EMPTY;
        *material_type = water_type;
      }
      env[y / CELL_SIZE][x / CELL_SIZE] = (TCell){
          // The x inside our cells has to be first pixel inside the cell being
          // the first pixel the upper
          // left one and the last pixel the lower right one so its from left to
          // right, up to down
          .x = x,
          .y = y,
          .fill_level = current_level,
          .size = CELL_SIZE,
          .properties = &material_properties[*material_type],
      };
    }
    break;
  }
  return true;
}
