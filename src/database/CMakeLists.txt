add_library(database-lib database.cpp databaseImpl.cpp)

find_package(mongocxx REQUIRED)
find_package(bsoncxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIR} ${LIBBSONCXX_INCLUDE_DIR} PRIVATE ${INCLUDE_DIR})

target_link_libraries(database-lib PUBLIC mongo::bsoncxx_shared) 
target_link_libraries(database-lib PUBLIC mongo::mongocxx_shared)

