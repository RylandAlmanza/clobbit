#ifndef FRAME_H_
#define FRAME_H_

#include "libtcod.h"

typedef struct FrameS Frame;

struct FrameS {
  char name[255];
  int x;
  int y;
  char character;
  TCOD_color_t color;
};

#endif
