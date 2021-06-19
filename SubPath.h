#ifndef SubPath_H
#define SubPath_H

typedef struct Coord {
  unsigned int x;
  unsigned int y;
} Coord;

// A SubPath is an stack of coordinates
class SubPath{
  public:
    SubPath();
    SubPath(unsigned int maxPathLength);
    SubPath(unsigned int x, unsigned int y, unsigned int maxPathLength);
    ~SubPath();

    void push(unsigned int x, unsigned int y);
    void pop();   
    Coord peak();
    void clear();
    void getStackSize();
    void setIsClosed(bool isClosed);
    bool getIsClosed();

  private:
    bool _isClosed;
    Coord* _stack;
    unsigned int _stackSize;
    unsigned int _maxPathLength;
};
#endif
