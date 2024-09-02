enable_testing()

add_subdirectory(./lib/googletest-1.15.2)
set(gtest_SOURCE_DIR ./lib/googletest-1.15.2/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILE
        test_item.cpp
        test_shopping_list.cpp
        test_user.cpp
)

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


