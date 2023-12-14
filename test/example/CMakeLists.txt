add_executable(example-test ExampleTest.cpp)

target_include_directories(example-test PRIVATE 
    ${INCLUDE_DIR}
    )

find_package(GTest REQUIRED)

add_executable(example-test
    your_source_files.cpp
)

target_link_libraries(example-test
    PRIVATE
    GTest::gmock
    GTest::gtest
    GTest::gmock_main
    GTest::gtest_main
)

gtest_discover_tests(example-test)
