cmake_minimum_required(VERSION 3.10)
project(arduino-lightboard-canvas CXX)

add_subdirectory(builder)

setup_builder()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(external)
