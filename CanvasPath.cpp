#include "CanvasPath.h"

CanvasPath::CanvasPath() {}

CanvasPath::CanvasPath(unsigned int maxPathLength) :
  maxPathLength(maxPathLength), pathLength(0), numSubPaths(0), needsNewSubpath(false) {
  subPaths = new Coord[maxPathLength];
}

CanvasPath::~CanvasPath() {
  delete[] subPaths;
}

unsigned int CanvasPath::getPathLength() {
  return pathLength;
}

unsigned int CanvasPath::getMaxPathLength() {
  return maxPathLength;
}

unsigned int CanvasPath::getNumSubPaths() {
  return numSubPaths;
}
