#include <stdint.h>
#include "CircularStack.h"
#ifndef CanvasState_H
#define CanvasState_H

// TODO: this cpp file

typedef struct CanvasSetting {
  uint16_t strokeColor = 0;
  uint16_t fillColor = 0;
  CanvasSetting() {}
  CanvasSetting(uint16_t strokeColor, uint16_t fillColor) : strokeColor(strokeColor), fillColor(fillColor) {}
} CanvasSetting;

// This is actually a stack of states, but the HTML spec poorly named this class
class CanvasState {
  public:
    CanvasState();
    CanvasState(unsigned int stackSize);
    ~CanvasState();

    void save(CanvasSetting canvasSetting);      // push
    CanvasSetting restore();   // pop
    CanvasSetting peek();
    void reset();   // Resets to default and clears _stack
    unsigned int getCurrentSize();

  private:
    CircularStack<CanvasSetting> _stack;
};
#endif
