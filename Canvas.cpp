#include <Arduino.h>
#include <OctoWS2811.h>
#include "canvas.h"
#include <stdbool.h>
#include <stdint.h>

//helper
void SWAP(int x, int y) {
  (x) = (x) ^ (y);
  (y) = (x) ^ (y);
  (x) = (x) ^ (y);
}

Canvas::Canvas(unsigned int width, unsigned int height, unsigned int maxNumPaths, unsigned int maxPathLength, unsigned int maxNumStates) :
  width(width), height(height), maxNumPaths(maxNumPaths), maxPathLength(maxPathLength), maxNumStates(maxNumStates) {
  paths = new CanvasPath [maxNumPaths]{ CanvasPath(maxPathLength) };
  states = new CanvasState [maxNumStates];
  canvas = new unsigned int*[width];
  for (unsigned int x = 0; x < width; x++) {
    canvas[x] = new unsigned int[height];
  }
}

Canvas::~Canvas() {
  for (unsigned int x = 0; x < width; x++) {
    delete[] canvas[x];
  }
  delete[] canvas;
}

void Canvas::setBackgroundColor(unsigned int color) {
  for (unsigned int x = 0; x < width; x++) {
    for (unsigned int y = 0; y < height; y++) {
      canvas[x][y] = color;
    }
  }
}

void Canvas::setStrokeColor(unsigned int color) {
  if (color < 0) {
    fillColor = 0;
    return;
  }
  if (color > 0xFFFFFF) {
    fillColor = 0xFFFFFF;
    return;
  }
  strokeColor = color;
}

void Canvas::setFillColor(unsigned int color) {
  if (color < 0) {
    fillColor = 0;
    return;
  }
  if (color > 0xFFFFFF) {
    fillColor = 0xFFFFFF;
    return;
  }
  fillColor = color;
}

unsigned int Canvas::getPix(unsigned int x, unsigned int y) {
  return canvas[x][y];
}

// if out of bounds, do nothing. otherwise, draw on the canvas
void Canvas::drawPix(int x, int y, unsigned int color) {
  if (x < 0 || x >= int(width)) return;
  if (y < 0 || y >= int(height)) return;
  canvas[x][y] = color;
}

//// Bresenham line drawing algorithm
//void Canvas::line(int x1, int y1, int x2, int y2) {
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
//
//// Horizontal line
//void Canvas::horiz(int x1, int x2, int y, int c) {
//  if (x1 >= x2) SWAP(x1, x2);
//  for (; x1 <= x2; x1++) setPix(x1, y, c);
//}
//
//void Canvas::strokeRect(int x, int y, int w, int h) {
//  // x is the corner vertex
//  // horizontal lines
//  horiz(x, x + w - 1, y, strokeColor);
//  horiz(x, x + w - 1, y + h - 1, strokeColor);
//  //vertical lines
//  line(x, y, x, y + h - 1, strokeColor);
//  line(x + w - 1, y, x + w - 1, y + h - 1, strokeColor);
//}
//
//void Canvas::fillRect(int x, int y, int w, int h) {
//  strokeRect(x, y, w, h);
//  for (int i = y + 1; i < y + h - 1; i++) {
//    horiz(x + 1, x + w - 2, i, fillColor);
//  }
//}
//
//void Canvas::strokeTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
//  line(x1, y1, x2, y2, strokeColor);
//  line(x2, y2, x3, y3, strokeColor);
//  line(x3, y3, x1, y1, strokeColor);
//}
//
//int Canvas::getStrokeColor () {
//  return strokeColor;
//}
//
//int Canvas::getFillColor() {
//  return fillColor;
//}
