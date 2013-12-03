#include "orientation.h"

int get_orientation_after_turn(int current_orientation, int turn_direction) {
  if (turn_direction == RIGHT) {
    switch (current_orientation) {
      case NORTH:
        return EAST;
        break;
      case EAST:
        return SOUTH;
        break;
      case SOUTH:
        return WEST;
        break;
      case WEST:
        return NORTH;
        break;
    }
  } else if (turn_direction == LEFT) {
    switch (current_orientation) {
      case NORTH:
        return WEST;
        break;
      case EAST:
        return NORTH;
        break;
      case SOUTH:
        return EAST;
        break;
      case WEST:
        return SOUTH;
        break;
    }
  }
}

char *orientation_to_string(int orientation) {
  switch (orientation) {
    case NORTH:
      return "north";
      break;
    case EAST:
      return "east";
      break;
    case SOUTH:
      return "south";
      break;
    case WEST:
      return "west";
      break;
  }
}
