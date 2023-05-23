cmake_minimum_required(VERSION 3.25)
project(CPP_PROJECT)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)
add_library(json INTERFACE)

add_executable(CPP_PROJECT main.cpp Menu.cpp Manager.cpp)


target_include_directories(json INTERFACE include)
