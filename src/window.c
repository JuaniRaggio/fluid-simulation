#include <SDL2/SDL.h>
#include "../include/window.h"
#include "../include/formats.h"

#define LINE_THICKNESS 1

static void draw_lines(SDL_Surface * windows_surface, Uint32 color,
                       size_t x_init_point, size_t y_init_point, size_t limit,
                       size_t line_length, size_t line_thickness) {
    for (size_t position = 0; position < limit; ++position) {
        SDL_Rect line = (SDL_Rect){position*x_init_point, position*y_init_point, line_thickness, line_length};
        SDL_FillRect(windows_surface, &line, color);
    }
}

void draw_grid(SDL_Surface * windows_surface) {
    // Draw columns
    draw_lines(windows_surface, COLOR_GRAY, CELL_SIZE, 0, COLUMNS, SCREEN_HEIGHT, LINE_THICKNESS);
    // Draw rows
    draw_lines(windows_surface, COLOR_GRAY, 0, CELL_SIZE, ROWS, SCREEN_WIDTH, LINE_THICKNESS);
}

