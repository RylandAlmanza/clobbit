#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "entity.h"
#include "part.h"
#include "frame.h"
#include "colorpairs.h"

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

void Player_update(Entity *self, ...) {
  // The player's update function should be passed a list of key states
  va_list keys;
  va_start(keys, self);
  bool up_pressed = va_arg(keys, int);    // The first should be the up key
  bool right_pressed = va_arg(keys, int); // The second should be right
  bool down_pressed = va_arg(keys, int);  // Third is down
  bool left_pressed = va_arg(keys, int);  // Fourth is left
  bool x_pressed = va_arg(keys, int);     // And fifth is x
  va_end(keys);

  if (x_pressed) {
    if (self->animationProgress == 0) {
      strcpy(self->currentAnimation, "swing");
    }
  }

  if (self->animationProgress < 3 &&
      strcmp(self->currentAnimation, "swing") == 0) {
    char temp[255];
    strcpy(temp, orientation_to_string(self->orientation));
    strcat(temp, "_swing_%i");
    sprintf(self->currentFrame, temp, self->animationProgress);
    self->animationProgress += 1;
    return;
  } else {
    strcpy(self->currentAnimation, "idle");
    strcpy(self->currentFrame, orientation_to_string(self->orientation));
    strcat(self->currentFrame, "_idle");
    self->animationProgress = 0;
  }

  if (up_pressed) {
    self->moveForward(self);
  }

  if (right_pressed) {
    self->turn(self, RIGHT);
    strcpy(self->currentFrame, orientation_to_string(self->orientation));
    strcat(self->currentFrame, "_idle");
  }

  if (down_pressed) {
    self->moveBackward(self);
  }

  if (left_pressed) {
    self->turn(self, LEFT);
    strcpy(self->currentFrame, orientation_to_string(self->orientation));
    strcat(self->currentFrame, "_idle");
  }
  
  //printw("orientation: %s", self->currentFrame);
}

Entity construct_Entity(int x, int y, int orientation) {
  Entity entity;
  entity.x = x;
  entity.y = y;
  entity.orientation = orientation;
  entity.animationProgress = 0;
  entity.addPart = &Entity_addPart;
  entity.moveForward = &Entity_moveForward;
  entity.moveBackward = &Entity_moveBackward;
  entity.turn = &Entity_turn;
  entity.numberOfParts = 0;
  return entity;
}

Entity construct_Player(int x, int y, int orientation) {
  Entity player = construct_Entity(x, y, orientation);
  player.update = &Player_update;
  
  Part torso = construct_Part();
  torso.addFrame(&torso, "north_idle", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "east_idle", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "south_idle", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "west_idle", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "north_swing_0", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "north_swing_1", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "north_swing_2", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "east_swing_0", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "east_swing_1", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "east_swing_2", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "south_swing_0", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "south_swing_1", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "south_swing_2", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "west_swing_0", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "west_swing_1", 2, 2, '@', WHITE_ON_BLACK);
  torso.addFrame(&torso, "west_swing_2", 2, 2, '@', WHITE_ON_BLACK);

  Part front = construct_Part();
  front.isSolid = false;
  front.addFrame(&front, "north_idle", 2, 1, '^', WHITE_ON_BLACK);
  front.addFrame(&front, "east_idle", 3, 2, '>', WHITE_ON_BLACK);
  front.addFrame(&front, "south_idle", 2, 3, 'v', WHITE_ON_BLACK);
  front.addFrame(&front, "west_idle", 1, 2, '<', WHITE_ON_BLACK);

  Part sword_part_1 = construct_Part();
  sword_part_1.isWeapon = true;
  sword_part_1.isSolid = false;
  sword_part_1.addFrame(&sword_part_1, "north_swing_0", 1, 1, '\\',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "north_swing_1", 2, 1, '|',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "north_swing_2", 3, 1, '/',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "east_swing_0", 3, 1, '/',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "east_swing_1", 3, 2, '-',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "east_swing_2", 3, 3, '\\',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "south_swing_0", 3, 3, '\\',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "south_swing_1", 2, 3, '|',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "south_swing_2", 1, 3, '/',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "west_swing_0", 1, 3, '/',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "west_swing_1", 1, 2, '-',
                        WHITE_ON_BLACK);
  sword_part_1.addFrame(&sword_part_1, "west_swing_2", 1, 1, '\\',
                        WHITE_ON_BLACK);

  Part sword_part_2 = construct_Part();
  sword_part_2.isWeapon = true;
  sword_part_2.isSolid = false;
  sword_part_2.addFrame(&sword_part_2, "north_swing_1", 2, 0, '.',
                        WHITE_ON_BLACK);
  sword_part_2.addFrame(&sword_part_2, "east_swing_1", 4, 2, '-',
                        WHITE_ON_BLACK);
  sword_part_2.addFrame(&sword_part_2, "south_swing_1", 2, 4, '\'',
                        WHITE_ON_BLACK);
  sword_part_2.addFrame(&sword_part_2, "west_swing_1", 0, 2, '-',
                        WHITE_ON_BLACK);

  player.addPart(&player, torso);
  player.addPart(&player, front);
  player.addPart(&player, sword_part_1);
  player.addPart(&player, sword_part_2);

  strcpy(player.currentFrame, "north_idle");

  return player;
}
