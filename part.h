#ifndef PART_H_
#define PART_H_

#include <stdbool.h>
#include "frame.h"

typedef struct PartS Part;

struct PartS {
  bool isWeapon;
  bool isSolid;
  Frame frames[25];
  int numberOfFrames;
  void (*addFrame)(Part *self, char name[255], int x, int y,
                   char character, int colorpair);
  Frame (*getFrame)(Part *self, char *name);
};

Part construct_Part();

#endif
