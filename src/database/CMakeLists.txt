project(database-lib) 
add_library(database-lib database.cpp)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})

target_link_libraries(database-lib PUBLIC mongo::bsoncxx_shared) 
target_link_libraries(database-lib PUBLIC mongo::mongocxx_shared)
