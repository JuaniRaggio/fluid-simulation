#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "formats.h"

#define EMPTY 0.0
#define FULLFILLED 1.0
typedef enum {solid_type = 0, water_type, material_count} material;
#define SOLID_COLOR COLOR_WHITE
#define WATER_COLOR COLOR_BLUE

typedef TCell environment[ROWS][COLUMNS];
extern const TFluid material_properties[material_count];

void new_environment(environment garbage_environment);

bool event_reaction(SDL_Event * event, environment env, material * material_type);

#endif

