#include "Canvas.h"
#include <stdbool.h>
#include <stdint.h>

BEGIN_CANVAS_NAMESPACE

//helper
void SWAP(int x, int y) {
  (x) = (x) ^ (y);
  (y) = (x) ^ (y);
  (x) = (x) ^ (y);
}

Canvas::Canvas(unsigned int width, unsigned int height, unsigned int maxNumSubPaths, unsigned int maxPathLength, unsigned int maxNumStates) :
  _width(width), _height(height), _maxNumSubPaths(maxNumSubPaths), _maxPathLength(maxPathLength), _maxNumStates(maxNumStates) {
  path = CanvasPath(maxNumSubPaths, maxPathLength);
  canvasState = CanvasState(maxNumStates);
  canvas = new unsigned int*[width];
  for (unsigned int x = 0; x < width; x++) {
    canvas[x] = new unsigned int[height];
  }
}

Canvas::~Canvas() {
  for (unsigned int x = 0; x < _width; x++) {
    delete[] canvas[x];
  }
  delete[] canvas;
}

//void Canvas::setStrokeColor(unsigned int color) {
//  if (color < 0) {
//    fillColor = 0;
//    return;
//  }
//  if (color > 0xFFFFFF) {
//    fillColor = 0xFFFFFF;
//    return;
//  }
//  strokeColor = color;
//}
//
//void Canvas::setFillColor(unsigned int color) {
//  if (color < 0) {
//    fillColor = 0;
//    return;
//  }
//  if (color > 0xFFFFFF) {
//    fillColor = 0xFFFFFF;
//    return;
//  }
//  fillColor = color;
//}
//
//unsigned int Canvas::getPix(unsigned int x, unsigned int y) {
//  return canvas[x][y];
//}
//
//// if out of bounds, do nothing. otherwise, draw on the canvas
//void Canvas::drawPix(int x, int y, unsigned int color) {
//  if (x < 0 || x >= int(width)) return;
//  if (y < 0 || y >= int(height)) return;
//  canvas[x][y] = color;
//}

//void Canvas::beginPath () {
//  currentDefaultPath.clearSubPaths();
//}
//
//void Canvas::moveTo(unsigned int x, unsigned int y) {
//  currentDefaultPath.addSubPath(x, y);  
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

END_CANVAS_NAMESPACE
