#include "CircularStack.h"

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
  // keep track of the 'current size' for the purposes of dumping the contents if necessary
  _currentSize = _currentSize == _capacity ? _capacity : _currentSize + 1;
  arr[_top] = t;
  _top = (_top + 1) % _capacity;
}

template <class T>
T CircularStack<T>::pop() {
  _currentSize = _currentSize == 0 ? 0 : _currentSize - 1;
  _top = (_top + _capacity - 1 ) % _capacity;
  return arr[_top];
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
