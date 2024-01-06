find_package(oatpp 1.3.0 REQUIRED)
find_package(oatpp-swagger 1.3.0 REQUIRED) 

add_library(api-lib Api.cpp)

target_compile_definitions(api-lib PUBLIC -DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")

target_include_directories(api-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${oatpp_INCLUDE_DIRS} ${oatpp-swagger_INCLUDE_DIRS})

target_include_directories(api-lib PRIVATE
    src/api
    src/core)
    
target_link_libraries(api-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)
