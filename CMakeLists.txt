cmake_minimum_required(VERSION 3.22)
project(FrostDB)

set(CMAKE_CXX_STANDARD 20)

add_executable(FrostDB main.cpp
        FrostBase.cpp
        FrostBase.h
        JSON.cpp
        JSON.h)
