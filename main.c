#include <SDL2/SDL.h>
#include <stdbool.h>
#include "include/formats.h"
#include "include/simulation.h"
#include "include/window.h"
#include "include/error_management.h"

int main(void) {
    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
    SDL_Window * window = SDL_CreateWindow("Fluid simulation",
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    CHECK_ERROR(window == NULL, SDL_GetError());

    SDL_Surface * window_surface = SDL_GetWindowSurface(window);
    CHECK_ERROR(window_surface == NULL, SDL_GetError());

    /* draw_grid(window_surface); */
    /* CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError()); */

    environment current_environment;
    new_environment(current_environment);

    run_simulation(window, window_surface, current_environment);
    // TODO Manage posible simulation errors

    SDL_FreeSurface(window_surface);
    SDL_DestroyWindowSurface(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

