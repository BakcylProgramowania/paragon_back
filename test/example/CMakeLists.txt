add_executable(example-test ExampleTest.cpp)

target_include_directories(example-test PRIVATE 
    ${INCLUDE_DIR}
)

target_link_libraries(example-test
    PRIVATE
    example-lib
    gtest_main
    gmock_main
    gtest
    gmock
)

gtest_discover_tests(example-test)
