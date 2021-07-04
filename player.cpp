#include "pch.h"
#include "constants.h"
#include "player.h"
#include <conio.h>
#include <windows.h>


player::player() {}

player::~player() {}

player::player(int y, int x) {
  this->y = y;
  this->x = x;
}

void player::set_pos(int y, int x) {
  this->y = y;
  this->x = x;
}

// проверяем корректность хода на карте
bool player::check_move(const labirint &maze, int t_y, int t_x) const {
  if (t_y <= HEIGHT && t_x <= WIDTH && maze(t_y, t_x) != WALL) {
    return true;
  }
  return false;
}
// вырываем символ хода из консоли и проверяем на корректные символы
char player::take_move() const {
  int move;
  do {
    move = _getch();
  } while (move != 'W' && move != 'w' && move != 'S' && move != 's' && 
           move != 'A' && move != 'a' && move != 'D' && move != 'd' && 
           move != 72 && move != 80 && move != 75 && move != 77);
  return move;
}

void player::action(labirint &maze) {
  switch (take_move()) {
  case 'W': case 'w': case 72:
    while (check_move(maze, y - 1, x)) {
      maze(y, x) = PATH;
      --y;
      maze(y, x) = PLAYER;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });    // fast repaint map
      maze.show_map();
      // feature for fast moving in maze
      if ((maze(y - 1, x) == PATH || maze(y + 1, x) == PATH) && (maze(y, x - 1) == PATH || maze(y, x + 1) == PATH))
        break;
    }
    break;
  case 'S': case 's': case 80:
    while (check_move(maze, y + 1, x)) {
      maze(y, x) = PATH;
      ++y;
      maze(y, x) = PLAYER;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });    // fast repaint map
      maze.show_map();
      // feature for fast moving in maze
      if ((maze(y - 1, x) == PATH || maze(y + 1, x) == PATH) && (maze(y, x - 1) == PATH || maze(y, x + 1) == PATH))
        break;
    }
    break;
  case 'A': case 'a': case 75:
    while (check_move(maze, y, x - 1)) {
      maze(y, x) = PATH;
      --x;
      maze(y, x) = PLAYER;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });    // fast repaint map
      maze.show_map();
      // feature for fast moving in maze
      if ((maze(y - 1, x) == PATH || maze(y + 1, x) == PATH) && (maze(y, x - 1) == PATH || maze(y, x + 1) == PATH))
        break;
    }
    break;
  case 'D': case 'd': case 77:
    while (check_move(maze, y, x + 1)) {
      maze(y, x) = PATH;
      ++x;
      maze(y, x) = PLAYER;
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ 0, 0 });    // fast repaint map
      maze.show_map();
      // feature for fast moving in maze
      if ((maze(y - 1, x) == PATH || maze(y + 1, x) == PATH) && (maze(y, x - 1) == PATH || maze(y, x + 1) == PATH))
        break;
    }
    break;
  }
}
