#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdarg.h>
#include <time.h>
#include "orientation.h"
#include "part.h"
#include "cell.h"

typedef struct EntityS Entity;

struct EntityS {
  int x;
  int y;
  int orientation;
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
Entity construct_Player(int x, int y, int orientation);

#endif
