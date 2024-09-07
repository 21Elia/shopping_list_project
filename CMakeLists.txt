cmake_minimum_required(VERSION 3.26)
project(ShoppingListApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME}_lib
        Subject.cpp
        Observer.cpp
        Item.cpp
        ShoppingList.cpp
        App.cpp
        User.cpp
        ShoppingListNotifier.cpp
        MainController.h
        MainController.h
        MainController.cpp
        DataManager.h
        DataManager.cpp
)

target_link_libraries(${PROJECT_NAME}_lib ${wxWidgets_LIBRARIES})

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
        App.cpp
        User.cpp
        ShoppingListNotifier.h
        ShoppingListNotifier.cpp
)

target_link_libraries(ShoppingListApp ${PROJECT_NAME}_lib ${wxWidgets_LIBRARIES})

add_subdirectory(tests)
