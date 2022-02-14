#include "CircularStack.h"
#include "SubPath.h"
#include "CanvasState.h"

BEGIN_CANVAS_NAMESPACE

template <class T>
CircularStack<T>::CircularStack() : _top(0), _currentSize(0), _capacity(DEFAULT_STACK_SIZE), arr(new T[DEFAULT_STACK_SIZE]) {} 

template <class T>
CircularStack<T>::CircularStack(unsigned int capacity) : _top(0), _currentSize(0), _capacity(capacity), arr(new T[capacity]) {}

template <class T>
CircularStack<T>::CircularStack(unsigned int capacity, T t) : _top(0), _currentSize(0), _capacity(capacity), arr(new T[capacity] { t }) {}

template <class T>
CircularStack<T>::~CircularStack() {
  delete[] arr;
}

template <class T>
void CircularStack<T>::push(T t) {
  // if it's full, overwrite the oldest item
  _currentSize = _currentSize == _capacity ? _capacity : _currentSize + 1;
  arr[_top] = t;
  _top = (_top + 1) % _capacity;
}

template <class T>
T CircularStack<T>::pop() {
  // if it's empty, no it isn't
  T el = arr[_top];
  _currentSize = _currentSize == 0 ? 0 : _currentSize - 1;
  _top = _currentSize == 0 ? 0 : (_top + _capacity - 1 ) % _capacity;

  return el;
}

template <class T>
T CircularStack<T>::peek() {
  return arr[_top];
}

template <class T>
unsigned int CircularStack<T>::getCurrentSize() {
  return _currentSize;
}

template <class T>
void CircularStack<T>::clear() {
  _currentSize = 0;
  _top = 0;
}

template class CircularStack<Coord>;
template class CircularStack<SubPath>;
template class CircularStack<CanvasSetting>;

END_CANVAS_NAMESPACE
