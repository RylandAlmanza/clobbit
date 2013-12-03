#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdarg.h>
#include <time.h>
#include "orientation.h"
#include "part.h"

typedef struct EntityS Entity;

struct EntityS {
  int x;
  int y;
  int orientation;
  int ticksSinceLastUpdate;
  char currentFrame[255];
  char currentAnimation[255];
  int animationProgress;
  Part parts[25];
  int numberOfParts;
  void (*addPart)(Entity *self, Part part);
  void (*moveForward)(Entity *self);
  void (*moveBackward)(Entity *self);
  void (*turn)(Entity *self, int turn_direction);
  void (*update)(Entity *self, ...);
};

Entity construct_Entity(int x, int y, int orientation);

#endif
