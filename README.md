# arduino-lightboard-canvas

(not in a working state)

HTML Canvas drawing methods for LED matrices with Arduino or similar

Here's an idea of what it'll look like:
![IMG_2927](https://user-images.githubusercontent.com/17439898/175981681-68da6351-f5af-4de8-a832-d39c4dc30bbe.JPG)

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
