#ifndef Coord_H
#define Coord_H
struct Coord {
  Coord();
  Coord(int x, int y);
  ~Coord();
  int x;
  int y;
  Coord& operator=(const Coord& c);
  bool operator==(const Coord& c);
};
#endif
