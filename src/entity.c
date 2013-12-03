#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "entity.h"
#include "part.h"
#include "frame.h"
#include "colors.h"

void Entity_addPart(Entity *self, Part part) {
  self->numberOfParts++;
  self->parts[self->numberOfParts-1] = part;
}

void Entity_moveForward(Entity *self) {
  Point delta;

  switch (self->orientation) {
    case NORTH:
      delta = NORTH_DELTA;
      break;
    case EAST:
      delta = EAST_DELTA;
      break;
    case SOUTH:
      delta = SOUTH_DELTA;
      break;
    case WEST:
      delta = WEST_DELTA;
      break;
  }

  self->x += delta.x;
  self->y += delta.y;
}

void Entity_moveBackward(Entity *self) {
  Point delta;

  switch (self->orientation) {
    case NORTH:
      delta = SOUTH_DELTA;
      break;
    case EAST:
      delta = WEST_DELTA;
      break;
    case SOUTH:
      delta = NORTH_DELTA;
      break;
    case WEST:
      delta = EAST_DELTA;
      break;
  }

  self->x += delta.x;
  self->y += delta.y;
}

void Entity_turn(Entity *self, int turn_direction) {
  //printw("turning");
  self->orientation = get_orientation_after_turn(self->orientation,
                                                 turn_direction);
}

Entity construct_Entity(int x, int y, int orientation) {
  Entity entity;
  entity.x = x;
  entity.y = y;
  entity.orientation = orientation;
  entity.ticksSinceLastUpdate = 0;
  entity.animationProgress = 0;
  entity.addPart = &Entity_addPart;
  entity.moveForward = &Entity_moveForward;
  entity.moveBackward = &Entity_moveBackward;
  entity.turn = &Entity_turn;
  entity.numberOfParts = 0;
  return entity;
}
