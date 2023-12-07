add_library(api-lib Api.cpp)

add_subdirectory(libs/oatpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(api-lib PRIVATE
    ${INCLUDE_DIR}
    )

file(GLOB_RECURSE api_sources *.cpp)

target_link_libraries(api-lib PUBLIC oatpp)

install(TARGETS api-lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})