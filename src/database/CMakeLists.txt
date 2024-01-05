project(database-lib)

add_library(database-lib database.cpp)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

target_include_directories(database-lib PRIVATE
    ${LIBMONGOCXX_INCLUDE_DIRS}
    ${LIBBSONCXX_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}  # Add the source directory if needed
)

target_link_libraries(database-lib PRIVATE
    ${LIBBSONCXX_LIBRARIES}
    ${LIBMONGOCXX_LIBRARIES}
)

# Optional: Print out include directories and libraries for debugging
message("LIBMONGOCXX_INCLUDE_DIRS: ${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_INCLUDE_DIRS: ${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES: ${LIBBSONCXX_LIBRARIES}")
message("LIBMONGOCXX_LIBRARIES: ${LIBMONGOCXX_LIBRARIES}")
