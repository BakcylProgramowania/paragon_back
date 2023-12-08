file(GLOB_RECURSE api_sources *.cpp)

add_library(api-lib ${api_sources})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(oatpp 1.3.0 REQUIRED)

target_link_libraries(api-lib PRIVATE oatpp::oatpp)

target_include_directories(api-lib PRIVATE ${oatpp_INCLUDE_DIRS})

install(TARGETS api-lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
