cmake_minimum_required(VERSION 3.27)
project(device_checker)

include(cmake/App.cmake)

set(SOURCES main.cpp)

add_app("${SOURCES}")
