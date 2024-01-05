project(database-lib) 
add_library(database-lib SHARED database.cpp)

# Find the MongoDB C++ driver packages.
find_library(LIBBSONCXX_LIBRARIES bsoncxx)
find_library(LIBMONGOCXX_LIBRARIES mongocxx)

set_target_properties(mongo::bsoncxx_shared PROPERTIES
                      IMPORTED_LOCATION ${LIBBSONCXX_LIBRARIES}
                     )

set_target_properties(mongo::mongocxx_shared PROPERTIES
                      IMPORTED_LOCATION ${LIBMONGOCXX_LIBRARIES}
                     )


# Link against the MongoDB C++ driver shared libraries.
target_link_libraries(database-lib PRIVATE mongo::bsoncxx_shared mongo::mongocxx_shared)

# It's often unnecessary to include directories manually as find_package should handle it.
# However, if you need to include directories for any reason, use target_include_directories.
# Remove these if they are not needed.
target_include_directories(database-lib PRIVATE ${BSONCXX_INCLUDE_DIRS})
target_include_directories(database-lib PRIVATE ${MONGOCXX_INCLUDE_DIRS})
