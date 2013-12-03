#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "part.h"
#include "frame.h"

void Part_addFrame(Part *self, char name[255], int x, int y,
                       char character, TCOD_color_t color) {
  self->numberOfFrames += 1;

  Frame frame;
  strcpy(frame.name, name);
  frame.x = x;
  frame.y = y;
  frame.character = character;
  frame.color = color;

  self->frames[self->numberOfFrames - 1] = frame;
}

Frame Part_getFrame(Part *self, char name[255]) {
  int i;
  for (i = 0; i < self->numberOfFrames; i++) {
    if (strcmp(self->frames[i].name, name) == 0) {
      return self->frames[i];
    }
  }
  Frame frame;
  strcpy(frame.name, "null");
}

Part construct_Part() {
  Part part;
  part.isWeapon = false;
  part.isSolid = true;
  part.numberOfFrames = 0;
  part.addFrame = &Part_addFrame;
  part.getFrame = &Part_getFrame;
  return part;
}
