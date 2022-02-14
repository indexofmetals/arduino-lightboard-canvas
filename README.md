# arduino-lightboard-canvas
HTML Canvas drawing methods for LED matrices with Arduino or similar

The structure and tooling for this project was more or less directly copied from the excellent Arduino MIDI Library from FortySevenEffects. Check it out here
https://github.com/FortySevenEffects/arduino_midi_library

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
