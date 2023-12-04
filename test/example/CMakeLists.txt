add_executable(example-test ExampleTest.cpp)

target_include_directories(example-test PRIVATE 
    ${INCLUDE_DIR}
    )

target_link_libraries(example-test PRIVATE
    GTest::gtest_main
    GTest::gmock
    example-lib
    )

gtest_discover_tests(example-test)