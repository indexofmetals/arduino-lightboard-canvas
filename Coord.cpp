#include "Coord.h"

Coord::Coord() {
  this->x = 0;
  this->y = 0;
}

Coord::Coord(int x, int y) : x(x), y(y) {}

Coord::~Coord() {}

Coord& Coord::operator= (const Coord& c) {
  Coord coord;
  coord.x = c.x;
  coord.y = c.y;
  return coord;
}

bool Coord::operator== (const Coord& c) {
  return c.x == this->x && c.y == this->y;
}
