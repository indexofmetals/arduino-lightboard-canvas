#include "CanvasPath.h"
#include "SubPath.h"

CanvasPath::CanvasPath(unsigned int maxNumSubPaths, unsigned int maxPathLength) :
  _maxNumSubPaths(maxNumSubPaths), _maxPathLength(maxPathLength), _numSubPaths(0), _needsNewSubpath(false) {
  _stack = new SubPath[maxNumSubPaths] { SubPath(maxPathLength) };
}

CanvasPath::~CanvasPath() {
  delete[] _stack;
}

unsigned int CanvasPath::getNumSubPaths() {
  return _numSubPaths;
}

unsigned int CanvasPath::getMaxPathLength() {
  return _maxPathLength;
}

void CanvasPath::moveTo(unsigned int x, unsigned int y) {
  if (_numSubPaths < _maxNumSubPaths) {
     SubPath subPath(x, y, _maxPathLength);
     _stack[_numSubPaths] = subPath;
     _numSubPaths++;
  }  
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
