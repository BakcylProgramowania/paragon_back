add_executable(core core.cpp)

find_package(nlohmann_json 3.2.0 REQUIRED)

target_include_directories(core PRIVATE ${INCLUDE_DIR})
target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)
