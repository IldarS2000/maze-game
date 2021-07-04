#ifndef PLAYER_H
#define PLAYER_H

#include "labirint.h"

class player {
private:
  int y;
  int x;
private:
  bool check_move(const labirint&, int, int) const;
  char take_move() const;
public:
  player();
  player(int, int);
  void set_pos(int y, int x);
  ~player();

  void action(labirint&);
};

#endif //  PLAYER_H

