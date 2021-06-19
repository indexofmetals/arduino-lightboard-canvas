#ifndef CanvasState_H
#define CanvasState_H

typedef struct CanvasSetting {
  uint16_t strokeColor;
  uint16_t fillColor;
} CanvasSetting;

// This is actually a stack of states, but the HTML spec poorly named this class
class CanvasState {
  public:
    CanvasState();
    CanvasState(unsigned int stackSize);
    ~CanvasState();

    void save();      // push
    void restore();   // pop
    void peak();
    void reset();   // Resets to default and clears _stack
    unsigned int getStackSize();

  private:
    CanvasSetting* _stack;
    unsigned int _stackSize;
};
#endif
