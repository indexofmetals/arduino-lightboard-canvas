#include "CanvasState.h"
#include "CircularStack.h"

CanvasState::CanvasState() {}

CanvasState::CanvasState(unsigned int stackSize) : _stack(CircularStack<CanvasSetting>(stackSize)) {}

CanvasState::~CanvasState() {}

void CanvasState::save(CanvasSetting canvasSetting) {
  _stack.push(canvasSetting);
}

CanvasSetting CanvasState::restore() {
  return _stack.pop(); 
}

CanvasSetting CanvasState::peek() {
  return _stack.peek();
}

void CanvasState::reset() {
  _stack.clear();
}

unsigned int CanvasState::getCurrentSize() {
  return _stack.getCurrentSize();
}
