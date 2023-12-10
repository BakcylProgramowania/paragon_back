cmake_minimum_required(VERSION 3.20)

add_executable(core.cpp core)
target_include_directories(core PRIVATE ${INCLUDE_DIR})
target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)
