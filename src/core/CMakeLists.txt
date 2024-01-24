find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(core-lib core.cpp authenticator.cpp token.cpp)

target_include_directories(core-lib PRIVATE ${INCLUDE_DIR})
target_link_libraries(core-lib PRIVATE nlohmann_json::nlohmann_json ${OPENSSL_LIBRARIES})

