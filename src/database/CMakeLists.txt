add_library(example-lib Example.cpp)

target_include_directories(example-lib PRIVATE
    ${INCLUDE_DIR}
    )
