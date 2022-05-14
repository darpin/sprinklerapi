cmake_minimum_required(VERSION 3.22)
project(sprinklerapi)

set(CMAKE_CXX_STANDARD 20)

## include the libhttpserver files and directories
include_directories($ENV{HOME}/github.com/etr/libhttpserver/src)
link_directories($ENV{HOME}/github.com/etr/libhttpserver/build/src/.libs)

## include the rapidjson files
include_directories($ENV{HOME}/github.com/Tencent/rapidjson/include)


add_executable(sprinklerapi main.cpp)
target_link_libraries(sprinklerapi httpserver)