#ifndef CircularStack_H
#define CircularStack_H
#define DEFAULT_STACK_SIZE 100
template <class T>

// IMPORTANT NOTE: while this CircularStack cannot be over-or-underflowed, it is 
// incumbent upon the user to keep track of the current size when dumping the contents,
// for example when drawing all of the coordinates of a subpath.

class CircularStack {
  public:
    CircularStack();
    CircularStack(unsigned int capacity);
    CircularStack(unsigned int capacity, T t);
    ~CircularStack();

    void push(T);
    T pop();
    T peek();
    unsigned int getCurrentSize();
    void clear();
  
  private:
    unsigned int _top;
    unsigned int _currentSize;
    unsigned int _capacity;
    T *arr;
};
#endif
