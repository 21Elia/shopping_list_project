enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(test_shopping_list
        test_shopping_list.cpp
        test_item.cpp
        test_user.cpp
)

target_link_libraries(test_shopping_list
        GTest::gtest
        GTest::gtest_main
        pthread
        ${PROJECT_NAME}_lib
)


