#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "colorpairs.h"
#include "orientation.h"
#include "entity.h"
#include "frame.h"

void draw_entity(Entity entity) {
  int i;
  for (i = 0; i < entity.numberOfParts; i++) {
    Frame frame = entity.parts[i].getFrame(&(entity.parts[i]),
                                           entity.currentFrame);
    if (strcmp(frame.name, "null") == 0) {
      continue;
    }
    attron(COLOR_PAIR(frame.colorpair));
    mvaddch(frame.y + entity.y, frame.x + entity.x, frame.character);
    attroff(COLOR_PAIR(frame.colorpair));
  }
}

int main() {
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);

  // Start color and initialize all the combinations we may use.
  start_color();
  init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
  init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
  init_pair(GREEN_ON_RED, COLOR_GREEN, COLOR_RED);
  init_pair(YELLOW_ON_RED, COLOR_YELLOW, COLOR_RED);
  init_pair(RED_ON_GREEN, COLOR_RED, COLOR_GREEN);
  init_pair(YELLOW_ON_GREEN, COLOR_YELLOW, COLOR_GREEN);
  init_pair(WHITE_ON_GREEN, COLOR_WHITE, COLOR_GREEN);
  init_pair(BLACK_ON_YELLOW, COLOR_BLACK, COLOR_YELLOW);
  init_pair(RED_ON_YELLOW, COLOR_RED, COLOR_YELLOW);
  init_pair(GREEN_ON_YELLOW, COLOR_GREEN, COLOR_YELLOW);
  init_pair(WHITE_ON_BLUE, COLOR_WHITE, COLOR_BLUE);
  init_pair(WHITE_ON_WHITE, COLOR_WHITE, COLOR_WHITE);

  Entity player = construct_Player(0, 0, NORTH);
  //refresh();

  int ch;
  bool up, right, down, left, x;
  while (ch != 113) {
    up = right = down = left = x = false;
    while (player.animationProgress != 0) {
      clear();
      draw_entity(player);
      refresh();
      usleep(100000);
      player.update(&player, up, right, down, left, x);
    }
    clear();
    draw_entity(player);
    refresh();
    ch = getch();
    if (ch == KEY_UP) {
      up = true;
    }
    if (ch == KEY_RIGHT) {
      right = true;
    }
    if (ch == KEY_DOWN) {
      down = true;
    }
    if (ch == KEY_LEFT) {
      left = true;
    }
    if (ch == 'x') {
      x = true;
    }
    player.update(&player, up, right, down, left, x);
  }

  curs_set(1);
  endwin();

  return 0;
}
