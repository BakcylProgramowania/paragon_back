find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(core core.cpp)

target_sources(core PRIVATE core.cpp)
target_include_directories(core PRIVATE ${INCLUDE_DIR})
target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)

