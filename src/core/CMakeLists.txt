find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

add_library(core-lib core.cpp authenticator.cpp token.cpp accountManager.cpp)

target_include_directories(core-lib PRIVATE ${INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(core-lib PRIVATE nlohmann_json::nlohmann_json ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})
