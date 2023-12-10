cmake_minimum_required(VERSION 3.12)

add_library(database-lib database.cpp)
add_executable(database-exec database.cpp)

find_package(libmongocxx REQUIRED)
find_package(mongocxx REQUIRED)

message("LIBBSONCXX_INCLUDE_DIRS=${LIBBSONCXX_INCLUDE_DIRS}")
message("LIBBSONCXX_LIBRARIES=${LIBBSONCXX_LIBRARIES}")

message("LIBMONGOCXX_INCLUDE_DIRS=${LIBMONGOCXX_INCLUDE_DIRS}")
message("LIBMONGOCXX_LIBRARIES=${LIBMONGOCXX_LIBRARIES}")


target_include_directories(database-exec PUBLIC 
    ${INCLUDE_DIR} ${LIBBSONCXX_INCLUDE_DIRS} ${LIBBSONCXX_LIBRARIES} ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBMONGOCXX_LIBRARIES}
    )

target_include_directories(database-lib PUBLIC 
    ${INCLUDE_DIR} ${LIBBSONCXX_INCLUDE_DIRS} ${LIBBSONCXX_LIBRARIES} ${LIBMONGOCXX_INCLUDE_DIRS} ${LIBMONGOCXX_LIBRARIES}
	)


target_link_libraries(database-exec 
	 ${LIBBSONCXX_LIBRARIES} ${LIBMONGOCXX_LIBRARIES}
    )


