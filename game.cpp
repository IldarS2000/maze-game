#include "pch.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include "game.h"


game::game() : level(1) {}

game::~game() {}

void game::print_rules() {
  std::cout << "\n Control buttons:\n\n";
  std::cout << "     w\n";
  std::cout << "   a s d\n\n";
  system("pause");
}

bool game::main_menu() {
  int switcher = 1;
  while (1) {
    switch (switcher) {
    case 1:
      std::cout << "\n\n\n                   <<  PLAY  >>\n\n                      OPTIONS\n\n                       EXIT\n";
      break;
    case 2:
      std::cout << "\n\n\n                       PLAY\n\n                  <<  OPTIONS  >>\n\n                       EXIT\n";
      break;
    case 3:
      std::cout << "\n\n\n                       PLAY\n\n                      OPTIONS\n\n                  <<   EXIT   >>\n";
      break;
    }
    int choice = _getch();
    if (choice == 72 || choice == 'W' || choice == 'w') {  // up
      if (switcher != 1) {
        switcher -= 1;
      }
      else switcher = 3;
    }
    else if (choice == 80 || choice == 'S' || choice == 's') { // down
      if (switcher != 3) {
        switcher += 1;
      }
      else switcher = 1;
    }
    else if (choice == 13 || choice == 32) { // enter or space
      if (switcher == 1) { // play
        system("cls");
        return true;
      }
      if (switcher == 2) { // options
        system("cls");
        print_rules();
      }
      if (switcher == 3) { // exit
        return false;
      }
    }
    system("cls");
  }
}

void game::print_like_telegraph(const std::string &letter) {
  for (const auto &temp : letter) {
    Sleep(80);
    std::cout << temp;
  }
}

bool game::restart_menu() {
  int switcher = 1;
  while (1) {
    switch (switcher) {
    case 1:
      std::cout << "\n\n\n                   <<  NEXT LEVEL  >>\n\n                          EXIT\n";
      break;
    case 2:
      std::cout << "\n\n\n                       NEXT LEVEL\n\n                     <<   EXIT   >>\n";
      break;
    }
    int choice = _getch();
    if (choice == 72 || choice == 'W' || choice == 'w') {  // up
      if (switcher != 1) {
        switcher -= 1;
      }
      else switcher = 2;
    }
    else if (choice == 80 || choice == 'S' || choice == 's') { // down
      if (switcher != 2) {
        switcher += 1;
      }
      else switcher = 1;
    }
    else if (choice == 13 || choice == 32) { // enter or space
      if (switcher == 1) { // play
        ++level;
        system("cls");
        return true;
      }
      if (switcher == 2) { // exit
        system("cls");
        std::cout << "\n";
        std::string letter = " Good bye! Have good time! :)";
        print_like_telegraph(letter);
        std::cout << "\n";
        Sleep(5000);
        return false;
      }
    }
    system("cls");
  }
}

void game::start_game() {
  if (main_menu()) {
    do {
      map.generate_map();              // create new map
      //human.set_pos(WIN_Y, WIN_X - 1);     // for DEBUG map
      human.set_pos(START_Y, START_X);     // set start point for the player
      map(START_Y, START_X) = PLAYER;  // set start point on the map
      map(WIN_Y, WIN_X) = EXIT;        // set win point on the map
      map.show_map();
      bool win = false;                // condition of win

      int start_time = (unsigned)time(0);
      while (!win) {
        human.action(map);   // move and print map here
        if (map(WIN_Y, WIN_X) == PLAYER) {     // check win
          int difference_time = (unsigned)time(0) - start_time;
          win = true;
          std::cout << "\n You have finished level: " << level << "\n";
          std::cout << " Time: ";
          if (difference_time / 60) {
            std::cout << difference_time / 60 << " min ";
          }
          std::cout << difference_time % 60 << " sec\n";
        }
      }
      system("pause");
      system("cls"); // erase last map from console
    } while (restart_menu());
  }
}