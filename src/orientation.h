#ifndef ORIENTATION_H_
#define ORIENTATION_H_

#include "point.h"

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define RIGHT 0
#define LEFT 1

static const Point NORTH_DELTA = {.x = 0, .y = -1};
static const Point EAST_DELTA = {.x = 1, .y = 0};
static const Point SOUTH_DELTA = {.x = 0, .y = 1};
static const Point WEST_DELTA = {.x = -1, .y = 0};

int get_orientation_after_turn(int current_orientation, int turn_direction);
char *orientation_to_string(int orientation);  

#endif
