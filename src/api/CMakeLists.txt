find_package(oatpp 1.3.0 REQUIRED)

add_library(api-lib Api.cpp)

target_include_directories(api-lib PRIVATE ${oatpp_INCLUDE_DIRS})

target_link_libraries(api-lib PRIVATE oatpp::oatpp)
