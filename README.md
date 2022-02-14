# arduino-lightboard-canvas
HTML Canvas drawing methods for LED matrices with Arduino or similar

Contributing:

## Setup

Pull Google Test / Google Mock subrepository:

```
$ git submodule init
$ git submodule update
```

Create build directory, run CMake, build and run unit tests:

```
$ mkdir build && cd build
$ cmake ..
$ make
$ ctest --verbose
```
