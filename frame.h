#ifndef FRAME_H_
#define FRAME_H_

typedef struct FrameS Frame;

struct FrameS {
  char name[255];
  int x;
  int y;
  char character;
  int colorpair;
};

#endif
