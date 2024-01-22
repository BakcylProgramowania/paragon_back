add_subdirectory(example)
add_subdirectory(api)
add_subdirectory(core)
add_subdirectory(database)

add_executable(example-main main.cpp)
target_include_directories(example-main PRIVATE ${INCLUDE_DIR} ${oatpp_INCLUDE_DIRS} ${oatpp-swagger_INCLUDE_DIRS})
target_link_libraries(example-main PRIVATE database-lib example-lib api-lib core-lib)

add_custom_target(example-main-run
    COMMAND example-main
    DEPENDS example-main
)
