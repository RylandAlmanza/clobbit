#include <string.h>
#include "waddleblockus.h"
#include "part.h"
#include "colors.h"

void WaddleBlockus_update(Entity *self, ...) {
  self->ticksSinceLastUpdate += 1;
  if (self->ticksSinceLastUpdate < 4) return;
  if (strcmp(self->currentAnimation, "walk") == 0) {
    self->animationProgress += 1;
    if (self->animationProgress == 2) {
      self->animationProgress = 0;
    }
    char temp[255];
    strcpy(temp, orientation_to_string(self->orientation));
    strcat(temp, "_walk_%i");
    sprintf(self->currentFrame, temp, self->animationProgress);
  }
  self->moveForward(self);
  self->ticksSinceLastUpdate = 0;
}

Entity construct_WaddleBlockus(int x, int y, int orientation) {
  Entity waddle_blockus = construct_Entity(x, y, orientation);
  waddle_blockus.update = &WaddleBlockus_update;
  
  int i, j;
  int torso_width = 3;
  int torso_length = 4;
  for (j = 0; j < torso_length; j++) {
    for (i = 0; i < torso_width; i++) {
      Part torso_part = construct_Part();
      torso_part.addFrame(&torso_part, "north_walk_0", i + 1, j + 1, '#',
                          WHITE);
      torso_part.addFrame(&torso_part, "north_walk_1", i + 1, j + 1, '#',
                          WHITE);
      torso_part.addFrame(&torso_part, "east_walk_0", torso_length - j - 1,
                          i + 1, '#', WHITE);
      torso_part.addFrame(&torso_part, "east_walk_1", torso_length - j - 1,
                          i + 1, '#', WHITE);
      torso_part.addFrame(&torso_part, "south_walk_0", torso_width - i,
                          torso_length - j - 1, '#', WHITE);
      torso_part.addFrame(&torso_part, "south_walk_1", torso_width - i,
                          torso_length - j - 1, '#', WHITE);
      torso_part.addFrame(&torso_part, "west_walk_0", j + 1, torso_width - i,
                          '#', WHITE);
      torso_part.addFrame(&torso_part, "west_walk_1", j + 1, torso_width - i,
                          '#', WHITE);
      waddle_blockus.addPart(&waddle_blockus, torso_part);
    }
  }

  Part front_left_leg = construct_Part();
  front_left_leg.addFrame(&front_left_leg, "north_walk_0", 0, 2, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "north_walk_1", 0, 1, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "east_walk_0", 2, 0, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "east_walk_1", 3, 0, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "south_walk_0", 4, 2, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "south_walk_1", 4, 3, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "west_walk_0", 2, 4, 'O', WHITE);
  front_left_leg.addFrame(&front_left_leg, "west_walk_1", 1, 4, 'O', WHITE);

  Part front_right_leg = construct_Part();
  front_right_leg.addFrame(&front_right_leg, "north_walk_0", 4, 1, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "north_walk_1", 4, 2, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "east_walk_0", 3, 4, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "east_walk_1", 2, 4, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "south_walk_0", 0, 3, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "south_walk_1", 0, 2, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "west_walk_0", 1, 0, 'O',
                           WHITE);
  front_right_leg.addFrame(&front_right_leg, "west_walk_1", 2, 0, 'O',
                           WHITE);

  Part back_right_leg = construct_Part();
  back_right_leg.addFrame(&back_right_leg, "north_walk_0", 4, 3, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "north_walk_1", 4, 4, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "east_walk_0", 1, 4, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "east_walk_1", 0, 4, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "south_walk_0", 0, 1, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "south_walk_1", 0, 0, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "west_walk_0", 3, 0, 'O', WHITE);
  back_right_leg.addFrame(&back_right_leg, "west_walk_1", 4, 0, 'O', WHITE);

  Part back_left_leg = construct_Part();
  back_left_leg.addFrame(&back_left_leg, "north_walk_0", 0, 4, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "north_walk_1", 0, 3, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "east_walk_0", 0, 0, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "east_walk_1", 1, 0, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "south_walk_0", 4, 0, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "south_walk_1", 4, 1, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "west_walk_0", 4, 4, 'O', WHITE);
  back_left_leg.addFrame(&back_left_leg, "west_walk_1", 3, 4, 'O', WHITE);

  Part head = construct_Part();
  head.addFrame(&head, "north_walk_0", 2, 0, '#', WHITE);
  head.addFrame(&head, "north_walk_1", 2, 0, '#', WHITE);
  head.addFrame(&head, "east_walk_0", 4, 2, '#', WHITE);
  head.addFrame(&head, "east_walk_1", 4, 2, '#', WHITE);
  head.addFrame(&head, "south_walk_0", 2, 4, '#', WHITE);
  head.addFrame(&head, "south_walk_1", 2, 4, '#', WHITE);
  head.addFrame(&head, "west_walk_0", 0, 2, '#', WHITE);
  head.addFrame(&head, "west_walk_1", 0, 2, '#', WHITE);

  waddle_blockus.addPart(&waddle_blockus, front_left_leg);
  waddle_blockus.addPart(&waddle_blockus, front_right_leg);
  waddle_blockus.addPart(&waddle_blockus, back_right_leg);
  waddle_blockus.addPart(&waddle_blockus, back_left_leg);
  waddle_blockus.addPart(&waddle_blockus, head);

  char temp[255];
  strcpy(waddle_blockus.currentAnimation, "walk");
  strcpy(temp, orientation_to_string(waddle_blockus.orientation));
  strcat(temp, "_walk_%i");
  sprintf(waddle_blockus.currentFrame, temp, waddle_blockus.animationProgress);

  return waddle_blockus;
}
