#include "CanvasPath.h"
#include "SubPath.h"
#include "CircularStack.h"

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

//// Bresenham line drawing algorithm
//void CanvasPath::lineTo(int x, int y) {
//  const int x1 = subPaths
//  if (y1 == y2) {
//    horiz(x1, x2, y1, strokeColor);
//    return;
//  }
//  int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
//  dx = x2 - x1;
//  dy = y2 - y1;
//  dx1 = fabs(dx);
//  dy1 = fabs(dy);
//  px = 2 * dy1 - dx1;
//  py = 2 * dx1 - dy1;
//  if (dy1 <= dx1) {
//    if (dx >= 0)
//    {
//      x = x1;
//      y = y1;
//      xe = x2;
//    }
//    else
//    {
//      x = x2;
//      y = y2;
//      xe = x1;
//    }
//    setPix(x, y, strokeColor);
//    for (i = 0; x < xe; i++)
//    {
//      x = x + 1;
//      if (px < 0)
//      {
//        px = px + 2 * dy1;
//      }
//      else
//      {
//        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
//        {
//          y = y + 1;
//        }
//        else
//        {
//          y = y - 1;
//        }
//        px = px + 2 * (dy1 - dx1);
//      }
//      setPix(x, y, strokeColor);
//    }
//  }
//  else
//  {
//    if (dy >= 0)
//    {
//      x = x1;
//      y = y1;
//      ye = y2;
//    }
//    else
//    {
//      x = x2;
//      y = y2;
//      ye = y1;
//    }
//    setPix(x, y, strokeColor);
//    for (i = 0; y < ye; i++)
//    {
//      y = y + 1;
//      if (py <= 0)
//      {
//        py = py + 2 * dx1;
//      }
//      else
//      {
//        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
//        {
//          x = x + 1;
//        }
//        else
//        {
//          x = x - 1;
//        }
//        py = py + 2 * (dx1 - dy1);
//      }
//      setPix(x, y, strokeColor);
//    }
//  }
//}
