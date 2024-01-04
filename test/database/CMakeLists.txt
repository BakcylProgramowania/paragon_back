add_executable(databaseTest databaseTest.cpp)

target_include_directories(databaseTest PRIVATE 
    ${INCLUDE_DIR}
    )

target_link_libraries(databaseTest PRIVATE
    GTest::gtest_main
    GTest::gmock
    database-lib
    )

gtest_discover_tests(databaseTest)