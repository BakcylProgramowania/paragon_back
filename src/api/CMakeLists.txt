find_package(oatpp 1.3.0 REQUIRED)

add_library(api-lib Api.cpp)

target_include_directories(api-lib PUBLIC ${oatpp_INCLUDE_DIRS} oatpp:oatpp)

target_link_libraries(api-lib oatpp:oatpp)
