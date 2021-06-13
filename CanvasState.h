#ifndef CanvasState_H
#define CanvasState_H

typedef struct CanvasSetting {
  uint16 strokeColor;
  uint16 fillColor;
} CanvasSetting;

// This is actually a stack of states, but the HTML spec poorly named this class
class CanvasState {
  public:
    CanvasState(unsigned int stackSize);
    ~CanvaseState();

    void save();      // push
    void restore();   // pop
    void peak();
    void reset();   // Resets to default and clears _stack
    void getStackSize;

  private:
    CanvasSetting* _stack;
    unsigned int _stackSize;
}
#endif
