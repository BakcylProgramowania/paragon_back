add_executable(api-test ApiTest.cpp)

target_include_directories(api-test PRIVATE 
    ${INCLUDE_DIR}
    )

target_link_libraries(api-test PRIVATE
    GTest::gtest_main
    GTest::gmock
    api-lib
    )

gtest_discover_tests(api-test)