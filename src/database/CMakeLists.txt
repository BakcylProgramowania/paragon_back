project(database-lib) 
add_library(database-lib database.cpp)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

target_link_libraries(database-lib PRIVATE mongo::bsoncxx_shared)
target_link_libraries(database-lib PRIVATE mongo::mongocxx_shared)

# Set the IMPORTED_LOCATION for the imported targets
set_target_properties(mongo::bsoncxx_shared PROPERTIES IMPORTED_LOCATION "${LIBBSONCXX_LIBRARY}")
set_target_properties(mongo::mongocxx_shared PROPERTIES IMPORTED_LOCATION "${LIBMONGOCXX_LIBRARY}")
