find_package(libmongocxx REQUIRED)
find_package(mongocxx REQUIRED)

add_library(database-lib database.cpp)

target_include_directories(database-lib PUBLIC 
    ${INCLUDE_DIR} ${LIBBSONCXX_INCLUDE_DIRS} ${LIBBSONCXX_LIBRARIES} ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBMONGOCXX_LIBRARIES}
    )
    
target_link_libraries(database-lib
     ${LIBBSONCXX_LIBRARIES} ${LIBMONGOCXX_LIBRARIES}
     )
