#include "SubPath.h"

SubPath::SubPath(unsigned int maxPathLength) : _stackSize(0), _maxPathLength(maxPathLength), _isClosed(false) {
  _stack = new Coord [maxPathLength];
}

SubPath::SubPath(unsigned int x, unsigned int y, unsigned int maxPathLength) : _stackSize(1), _maxPathLength(maxPathLength), _isClosed(false) {
    _stack = new Coord [maxPathLength] {Coord {x, y}};
}

SubPath::~SubPath() {
  delete[] _stack;
}

void SubPath::push(unsigned int x, unsigned int y) {
  if (_stackSize < _maxPathLength) {
    Coord coord = {x, y};
    _stack[_stackSize] = coord;
    _stackSize++;
  }
}

void SubPath::pop() {
  if (_stackSize > 0) {
    _stackSize--;
  }
}

void SubPath::clear() {
  _stackSize = 0;  
}

bool SubPath::getIsClosed() {
  return _isClosed;  
}

void SubPath::setIsClosed(bool isClosed) {
  _isClosed = isClosed;
}

Coord SubPath::peak() {
  if (_stackSize > 0) {
    return _stack[_stackSize - 1];  
  }
}
