cmake_minimum_required(VERSION 3.26)
project(ShoppingListApp)

set(CMAKE_CXX_STANDARD 14)

add_executable(ShoppingListApp main.cpp
        Subject.h
        Subject.cpp
        Observer.cpp)
