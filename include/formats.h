#ifndef __FORMATS_H__
#define __FORMATS_H__

#include <SDL2/SDL.h>
#include <stdbool.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define CELL_SIZE 15
#define COLUMNS SCREEN_WIDTH/CELL_SIZE
#define ROWS SCREEN_HEIGHT/CELL_SIZE
#define GRID_LINE_THICKNESS 1
#define COLOR_BLACK 0x00000000
#define COLOR_WHITE 0xffffffff
#define COLOR_GRAY 0x1f1f1f1f
#define COLOR_BLUE 0x34c3eb

typedef struct Fluid {
    Uint32 color;
    double density;
    bool gravity;
    // Extensible
} TFluid;

typedef struct Cell {
    Uint32 x;
    Uint32 y;
    Uint32 size;
    /* number between 0 and 1 */
    double fill_level;
    // Its const cause fluid properties shouldn't change and pointer to use less memory 
    const TFluid * properties;
} TCell;

#endif

