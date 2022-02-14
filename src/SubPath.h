#pragma once
#include "canvas_Namespace.h"
#include "CircularStack.h"

BEGIN_CANVAS_NAMESPACE

typedef struct Coord {
  unsigned int x;
  unsigned int y;
  Coord() {
    x = 0;
    y = 0;
  }
  Coord(unsigned int x, unsigned int y) : x(x), y(y) {}
  bool operator==(Coord& other) {
    return this->x == other.x && this->y == other.y;
  }
} Coord;

// A SubPath is an stack of coordinates
class SubPath{
  public:
    SubPath();
    SubPath(unsigned int maxPathLength);
    SubPath(unsigned int x, unsigned int y, unsigned int maxPathLength);
    ~SubPath();

    void push(unsigned int x, unsigned int y); // adds a coordinate to the _coords CircularStack
    Coord pop(); // gets a coordinate from the _coords CircularStack
    Coord peek(); // looks at the last coordinate added to the _coords CircularStack
    void clear(); // clears the _coords CircularStack
    unsigned int getCurrentSize(); // returns the current number of coordinates in the _coords CiruclarStack
    void setIsClosed(bool isClosed); // sets the _isClosed flag
    bool getIsClosed(); // returns the value of the _isClosed flag

  private:
    bool _isClosed;
    CircularStack<Coord> _coords;
};

END_CANVAS_NAMESPACE
