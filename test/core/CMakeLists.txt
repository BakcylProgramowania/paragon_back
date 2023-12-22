add_executable(core-test core_test.cpp)

target_include_directories(core-test PRIVATE 
    ${INCLUDE_DIR}
    )

target_link_libraries(core-test PRIVATE
    GTest::gtest_main
    GTest::gmock
    core-lib
    )

gtest_discover_tests(core-test)
