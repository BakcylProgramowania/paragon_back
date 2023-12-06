add_subdirectory(api)

add_executable(api-main main.cpp)
target_include_directories(api-main PRIVATE ${INCLUDE_DIR})
target_link_libraries(api-main PRIVATE api-lib)

add_custom_target(api-main-run
    COMMAND api-main
    DEPENDS api-main
    )

add_subdirectory(example)

add_executable(example-main main.cpp)
target_include_directories(example-main PRIVATE ${INCLUDE_DIR})
target_link_libraries(example-main PRIVATE example-lib)

add_custom_target(example-main-run
    COMMAND example-main
    DEPENDS example-main
    )