#include "CanvasPath.h"
#include "SubPath.h"
#include "CircularStack.h"

BEGIN_CANVAS_NAMESPACE

CanvasPath::CanvasPath() {
  _maxNumSubPaths = DEFAULT_STACK_SIZE;
  _maxPathLength = DEFAULT_STACK_SIZE; 
  _needsNewSubpath = false;
  _subPaths = CircularStack<SubPath>();
}

CanvasPath::CanvasPath(unsigned int maxNumSubPaths, unsigned int maxPathLength) :
  _maxNumSubPaths(maxNumSubPaths), 
  _maxPathLength(maxPathLength),
  _needsNewSubpath(false), 
  _subPaths(CircularStack<SubPath>(maxNumSubPaths)) {}

CanvasPath::~CanvasPath() {}

unsigned int CanvasPath::getNumSubPaths() {
  return _subPaths.getCurrentSize();
}

void CanvasPath::moveTo(unsigned int x, unsigned int y) {
  _needsNewSubpath = true;
  _subPaths.push(SubPath (x, y, _maxPathLength));
}

END_CANVAS_NAMESPACE

