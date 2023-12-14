add_executable(core core.cpp)
target_include_directories(core PRIVATE ${INCLUDE_DIR})
target_link_libraries(core PRIVATE nlohmann_json::nlohmann_json)
