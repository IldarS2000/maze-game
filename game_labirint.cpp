#include "pch.h"
#include "game.h"
#include <windows.h>


int main() {
  system("mode con cols=80 lines=40");
  game instance;
  instance.start_game();
 
  return 0;
}


