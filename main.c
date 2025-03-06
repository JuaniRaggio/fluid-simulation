#include "include/error_management.h"
#include "include/formats.h"
#include "include/simulation.h"
#include <SDL2/SDL.h>

int main(void) {
  // Falta hacer el randNormalize
  CHECK_ERROR(SDL_Init(SDL_INIT_VIDEO) != 0, SDL_GetError());
  SDL_Window *window = SDL_CreateWindow(
      "Fluid simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
  CHECK_ERROR(window == NULL, SDL_GetError());

  SDL_Surface *window_surface = SDL_GetWindowSurface(window);
  CHECK_ERROR(window_surface == NULL, SDL_GetError());

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
