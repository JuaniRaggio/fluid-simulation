#include <stdio.h>
#include <SDL2/SDL.h>
#include "include/window.h"
#include "include/formats.h"

#define CHECK_ERROR(test, message) \
    do { \
        if((test)) { \
            fprintf(stdout, "%s\n", (message)); \
            exit(1); \
        } \
    } while(0)

static const int screen_height = 600;
static const int screen_width = 900;

int main(void) {
    CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
    SDL_Window * window = SDL_CreateWindow("Fluid simulation",
                                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                           screen_width, screen_height, SDL_WINDOW_OPENGL);
    CHECK_ERROR(window == NULL, SDL_GetError());

    SDL_Surface * window_surface = SDL_GetWindowSurface(window);
    CHECK_ERROR(window_surface == NULL, SDL_GetError());

    draw_grid(window_surface);
    CHECK_ERROR(SDL_UpdateWindowSurface(window) != 0, SDL_GetError());

    SDL_DestroyWindowSurface(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

