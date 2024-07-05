cmake_minimum_required(VERSION 3.26)
project(ShoppingListApp)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ShoppingListApp main.cpp
        Subject.h
        Subject.cpp
        Observer.cpp
        Item.h
        Item.cpp
        ShoppingList.h
        ShoppingList.cpp
        MainFrame.h
        MainFrame.cpp
        App.h
        App.cpp)

target_link_libraries(ShoppingListApp ${wxWidgets_LIBRARIES})
