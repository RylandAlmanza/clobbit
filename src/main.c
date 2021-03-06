#include <stdlib.h>
#include <time.h>
#include "libtcod.h"
#include "colors.h"
#include "point.h"
#include "orientation.h"
#include "player.h"
#include "waddleblockus.h"
#include "frame.h"

Point *weapon_points;
int number_of_weapon_points;

int random_between(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void reset_weapon_points() {
  number_of_weapon_points = 0;
  Point *temp = realloc(weapon_points, sizeof(Point));
  if (temp != NULL) {
    weapon_points = temp;
  } else {
    free(weapon_points);
  }
}

void draw_entity(Entity entity) {
  int i;
  for (i = 0; i < entity.numberOfParts; i++) {
    Frame frame = entity.parts[i].getFrame(&(entity.parts[i]),
                                           entity.currentFrame);
    if (strcmp(frame.name, "null") == 0) {
      continue;
    }
    int x = frame.x + entity.x;
    int y = frame.y + entity.y;
    bool drawn = false;
    if (entity.parts[i].isWeapon) {
      Point weapon_point = {.x = x, .y = y};
      weapon_points[number_of_weapon_points] = weapon_point;
      number_of_weapon_points += 1;
      Point *temp = realloc(weapon_points,
                            (number_of_weapon_points + 1) * sizeof(Point));
      if (temp != NULL) {
        weapon_points = temp;
      } else {
        free(weapon_points);
      }
    } else {
      int j;
      for (j = 0; j < number_of_weapon_points; j++) {
        if (weapon_points[j].x == x && weapon_points[j].y == y) {
          TCOD_console_put_char_ex(NULL, x, y, frame.character, RED, BLACK);
          drawn = true;
          break;
        }
      }
    }
    if (!drawn) {
      TCOD_console_put_char_ex(NULL, x, y, frame.character, frame.color,
                               BLACK);
    }
  }
}  

int main(int argc, char *argv[]) {
  bool real_time;

  TCOD_console_init_root(50, 40, "Lobbit - Little Hunter of Big Things",
                         false, TCOD_RENDERER_OPENGL);
  TCOD_console_set_default_background(NULL, BLACK);
  TCOD_console_set_default_foreground(NULL, WHITE);
  TCOD_console_set_color_control(TCOD_COLCTRL_1, RED, WHITE);

  bool mode_chosen = false;
  int mode_selected = 0;
  while (!mode_chosen) {
    char real_time_string[255] = "Real-time";
    char turn_based_string[255] = "Turn-based";
    char temp[255] = "";
    TCOD_console_clear(NULL);
    TCOD_console_print(NULL, 1, 1, "Choose your play style:");
    if (mode_selected == 0) {
      TCOD_console_put_char_ex(NULL, 1, 2, '>', WHITE, BLACK);
      strcpy(temp, "%c");
      strcat(temp, real_time_string);
      strcat(temp, "%c");
      strcpy(real_time_string, temp);
      TCOD_console_print(NULL, 3, 2, real_time_string, TCOD_COLCTRL_1,
                         TCOD_COLCTRL_STOP);
      TCOD_console_print(NULL, 3, 3, turn_based_string);
    } else {
      TCOD_console_put_char_ex(NULL, 1, 3, '>', WHITE, BLACK);
      strcat(temp, "%c");
      strcat(temp, turn_based_string);
      strcat(temp, "%c");
      strcpy(turn_based_string, temp);
      TCOD_console_print(NULL, 3, 2, real_time_string);
      TCOD_console_print(NULL, 3, 3, turn_based_string, TCOD_COLCTRL_1,
                         TCOD_COLCTRL_STOP);
    }

    TCOD_console_flush(NULL);
    TCOD_key_t key = TCOD_console_wait_for_keypress(true);
    if (key.pressed) {
      if (key.vk == TCODK_UP) {
        mode_selected -= 1;
      }
      if (key.vk == TCODK_DOWN) {
        mode_selected += 1;
      }
      if (key.vk == TCODK_ENTER) {
        mode_chosen = true;
      }
      if (mode_selected < 0) mode_selected = 1;
      if (mode_selected > 1) mode_selected = 0;
    }
  }

  real_time = mode_selected ? false : true;

  weapon_points = malloc(sizeof(Point));

  srand(time(NULL));

  Entity player = construct_Player(0, 12, NORTH);
  Entity monster = construct_WaddleBlockus(random_between(0, 44),
                                           random_between(0, 34),
                                           random_between(0, 3));
  draw_entity(player);
  draw_entity(monster);
  TCOD_console_flush(NULL);

  TCOD_keycode_t key;
  bool up, right, down, left, x;
  while (!TCOD_console_is_window_closed()) {
    up = right = down = left = x = false;
    if (real_time) {
      up = TCOD_console_is_key_pressed(TCODK_UP);
      right = TCOD_console_is_key_pressed(TCODK_RIGHT);
      down = TCOD_console_is_key_pressed(TCODK_DOWN);
      left = TCOD_console_is_key_pressed(TCODK_LEFT);
      TCOD_key_t key = TCOD_console_check_for_keypress(TCOD_KEY_PRESSED);
      
      if (key.vk != TCODK_NONE) {
        if (key.c == 'x') {
          x = true;
        }
      }
    }

    while (player.animationProgress != 0) {
      TCOD_console_clear(NULL);
      draw_entity(player);
      draw_entity(monster);
      TCOD_console_flush(NULL);
      usleep(100000);
      reset_weapon_points();
      player.update(&player, up, right, down, left, x);
      monster.update(&monster);
    }
    TCOD_console_clear(NULL);
    reset_weapon_points();
    draw_entity(player);
    draw_entity(monster);
    TCOD_console_flush(NULL);

    if (real_time) {
      usleep(100000);
      reset_weapon_points();
      player.update(&player, up, right, down, left, x);
      monster.update(&monster);
    } else {
      TCOD_key_t key = TCOD_console_wait_for_keypress(true);
      if (key.pressed) {
        if (key.vk == TCODK_UP) {
          up = true;
        }
        if (key.vk == TCODK_RIGHT) {
          right = true;
        }
        if (key.vk == TCODK_DOWN) {
          down = true;
        }
        if (key.vk == TCODK_LEFT) {
          left = true;
        }
        if (key.c == 'x') {
          x = true;
        }
        reset_weapon_points();
        player.update(&player, up, right, down, left, x);
        monster.update(&monster);
      }
    }
  }

  free(weapon_points);

  return 0;
}
