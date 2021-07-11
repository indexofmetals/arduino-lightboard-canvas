#include "SubPath.h"
#include "CircularStack.h"

SubPath::SubPath() : _isClosed(false), _coords(CircularStack<Coord>()){}
SubPath::SubPath(unsigned int maxPathLength) : _isClosed(false), _coords(CircularStack<Coord>(maxPathLength)) {}

SubPath::SubPath(unsigned int x, unsigned int y, unsigned int maxPathLength) :
  _isClosed(false),
  _coords(CircularStack<Coord>(maxPathLength)) {}

  SubPath::~SubPath() {}

  void SubPath::push(unsigned int x, unsigned int y) {
    Coord coord = {x, y};
    _coords.push(coord);
  }

  Coord SubPath::pop() {
    return _coords.pop();
  }

  void SubPath::clear() {
    _isClosed = false;
    _coords.clear();
  }

  bool SubPath::getIsClosed() {
    return _isClosed;
  }

  void SubPath::setIsClosed(bool isClosed) {
    _isClosed = isClosed;
  }

  Coord SubPath::peek() {
    return _coords.peek();
  }
