#ifndef LABIRINT_H
#define LABIRINT_H


class labirint {
private:
  short maze[HEIGHT][WIDTH];
private:
  bool check_dead_end(int x, int y);
  bool check_paths_of_map();
public:
  labirint();
  ~labirint();
  short& operator()(int, int);
  const short& operator()(int, int) const;
  void show_map() const;
  void generate_map();

};

#endif // LABIRINT_H




