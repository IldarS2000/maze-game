#include "pch.h"
#include "constants.h"
#include "labirint.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


labirint::labirint() {}

labirint::~labirint() {}

short& labirint::operator()(int i, int j) {
  return maze[i][j];
}

const short& labirint::operator()(int i, int j) const {
  return maze[i][j];
}

void labirint::show_map() const {
  for (int i = 0; i < HEIGHT; ++i) {
    for (int j = 0; j < WIDTH; ++j) {
      if (maze[i][j] == WALL) {
        std::cout << BRICK;
        std::cout << BRICK;
      }
      else if (maze[i][j] == PATH) {
        std::cout << "  ";
      }
      else if (maze[i][j] == PLAYER) {
        std::cout << ";)";
      }
      else if (maze[i][j] == EXIT) {
        std::cout << "$$";
      }
    }
    std::cout << "\n";
  }
}

bool labirint::check_paths_of_map() {
  bool b = true;
  for (int i = 1; i < (HEIGHT - 1); i += 2)
    for (int j = 1; j < (WIDTH - 1); j += 2)
      if (maze[i][j] == WALL)
        b = false;
  return b;
}

bool labirint::check_dead_end(int x, int y) {
  // первые проверки - проверки — на присутствие рядом внешней непроницаемой стены.
  int a = 0;

  if (x != 1) {
    if (maze[y][x - 2] == PATH) // влево
      a += 1;
  }
  else a +=  1;

  if (y != 1) {
    if (maze[y - 2][x] == PATH) // вниз
      a += 1;
  }
  else a += 1;

  if (x != WIDTH - 2) {
    if (maze[y][x + 2] == PATH) // вправо
      a += 1;
  }
  else a += 1;

  if (y != HEIGHT - 2) {
    if (maze[y + 2][x] == PATH) // вверх
      a += 1;
  }
  else a += 1;

  if (a == 4)
    return 1; // копатель в тупике
  else
    return 0; // есть куда копать
}

void labirint::generate_map() {
  srand((unsigned)time(0));

  // заполняем матрицу стенами
  for (int i = 0; i < HEIGHT; ++i) 
    for (int j = 0; j < WIDTH; ++j)
      maze[i][j] = WALL;

  // точка начала прорывания
  int x = 2 * (rand() % ((WIDTH - 1) >> 1)) + 1;
  int y = 2 * (rand() % ((HEIGHT - 1) >> 1)) + 1;
  maze[y][x] = PATH;

  bool stop_dig = false; // признак того что в карте еще не все пути прорыты
  for (unsigned i = 0;!stop_dig;++i) {
    int r_direct = rand() % 4; // рандомируем одно из четырех направлений
    // прорываем по две клетки в одном направлении за прыжок                        
    switch (r_direct) {
    // прорываем вверх
    case 0:
      if (y != 1 && maze[y - 2][x] == WALL) {
        maze[y - 1][x] = PATH;
        maze[y - 2][x] = PATH;
        y -= 2;
      }
      break;
    // прорываем вниз
    case 1:
      if (y != HEIGHT - 2 && maze[y + 2][x] == WALL) {
        maze[y + 1][x] = PATH;
        maze[y + 2][x] = PATH;
        y += 2;
      }
      break;
    // прорываем налево
    case 2:
      if (x != 1 && maze[y][x - 2] == WALL) {
        maze[y][x - 1] = PATH;
        maze[y][x - 2] = PATH;
        x -= 2;
      }
      break;
    // прорываем направо
    case 3:
      if (x != WIDTH - 2 && maze[y][x + 2] == WALL) {
        maze[y][x + 1] = PATH;
        maze[y][x + 2] = PATH;
        x += 2;
      }
      break;
    }
    if (check_dead_end(x, y)) {
      // закидываем копателя из тупика в рандомную тропинку
      do {
        x = 2 * (rand() % ((WIDTH - 1) >> 1)) + 1;
        y = 2 * (rand() % ((HEIGHT - 1) >> 1)) + 1;
      } while (maze[y][x] != PATH);
    }
    if (i % SQUARE_OF_MAZE == 0) {
      stop_dig = check_paths_of_map(); // if true - карта сгенерирована прекращаем цикл
    }
  }
}
