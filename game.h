#ifndef GAME_H
#define GAME_H

#include <string>
#include "constants.h"
#include "labirint.h"
#include "player.h"

class game {
private:
  player human;
  labirint map;
  int level;
private:
  bool main_menu();
  void print_rules();
  bool restart_menu();
  void print_like_telegraph(const std::string&);
public:
  game();
  ~game();

  void start_game();  // start game function
};

#endif //  GAME_H

