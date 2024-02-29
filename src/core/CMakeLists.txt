find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

add_library(core-lib authenticator.cpp token.cpp accountManager.cpp)

target_include_directories(core-lib PRIVATE ${INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(core-lib PRIVATE ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})
