find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(core-lib core.cpp)

target_sources(core-lib PRIVATE core.cpp)
target_sources(core-lib PRIVATE authenticator.cpp)
target_include_directories(core-lib PRIVATE ${INCLUDE_DIR})
target_link_libraries(core-lib PRIVATE nlohmann_json::nlohmann_json)

